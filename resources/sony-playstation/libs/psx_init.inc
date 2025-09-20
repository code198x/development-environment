# psx_init.inc - PlayStation System Initialization and Utilities
# MIPS assembly macros and functions for PlayStation development

# ============================================================================
# Basic System Initialization
# ============================================================================

# Initialize PlayStation system
.macro psx_init
    # Disable interrupts
    mfc0    $t0, COP0_STATUS
    li      $t1, ~STATUS_IE
    and     $t0, $t0, $t1
    mtc0    $t0, COP0_STATUS
    nop

    # Set up stack pointer
    li      $sp, STACK_BASE

    # Initialize scratchpad area
    li      $t0, SCRATCHPAD
    li      $t1, 0x400          # 1KB scratchpad
    li      $t2, 0
.scratchpad_clear:
    sw      $t2, 0($t0)
    addiu   $t0, $t0, 4
    addiu   $t1, $t1, -4
    bnez    $t1, .scratchpad_clear
    nop

    # Reset GPU
    li      $t0, GPU_GP1
    li      $t1, GPU_RESET
    sw      $t1, 0($t0)
    nop

    # Reset DMA
    li      $t0, DMA_DPCR
    sw      $zero, 0($t0)
    li      $t0, DMA_DICR
    sw      $zero, 0($t0)

    # Clear interrupt status
    li      $t0, I_STAT
    li      $t1, 0xFFFFFFFF
    sw      $t1, 0($t0)

    # Disable all interrupts initially
    li      $t0, I_MASK
    sw      $zero, 0($t0)
.endm

# ============================================================================
# Exception Handler Setup
# ============================================================================

# Install exception handler
.macro install_exception_handler handler_addr
    # Copy handler to exception vector
    li      $t0, 0x80000080     # Exception vector address
    la      $t1, \handler_addr
    li      $t2, 32             # Copy 32 instructions max

.copy_handler:
    lw      $t3, 0($t1)
    sw      $t3, 0($t0)
    addiu   $t0, $t0, 4
    addiu   $t1, $t1, 4
    addiu   $t2, $t2, -1
    bnez    $t2, .copy_handler
    nop

    # Flush instruction cache
    li      $t0, 0x1000
    mtc0    $t0, COP0_STATUS
    nop
    mtc0    $zero, COP0_STATUS
    nop
.endm

# ============================================================================
# Memory Management
# ============================================================================

# Fast memory clear (32-bit aligned)
# $a0 = address, $a1 = size in bytes
.macro clear_memory
    beqz    $a1, .clear_done
    nop

    # Ensure 4-byte alignment
    andi    $t0, $a1, 3
    beqz    $t0, .clear_aligned
    nop

    # Round up to next 4-byte boundary
    addiu   $a1, $a1, 3
    andi    $a1, $a1, ~3

.clear_aligned:
    srl     $a1, $a1, 2        # Convert to word count

.clear_loop:
    sw      $zero, 0($a0)
    addiu   $a0, $a0, 4
    addiu   $a1, $a1, -1
    bnez    $a1, .clear_loop
    nop

.clear_done:
.endm

# Fast memory copy (32-bit aligned)
# $a0 = source, $a1 = destination, $a2 = size in bytes
.macro copy_memory
    beqz    $a2, .copy_done
    nop

    # Ensure 4-byte alignment
    andi    $t0, $a2, 3
    beqz    $t0, .copy_aligned
    nop

    addiu   $a2, $a2, 3
    andi    $a2, $a2, ~3

.copy_aligned:
    srl     $a2, $a2, 2        # Convert to word count

.copy_loop:
    lw      $t0, 0($a0)
    sw      $t0, 0($a1)
    addiu   $a0, $a0, 4
    addiu   $a1, $a1, 4
    addiu   $a2, $a2, -1
    bnez    $a2, .copy_loop
    nop

.copy_done:
.endm

# ============================================================================
# DMA Operations
# ============================================================================

# Start DMA transfer
# $a0 = channel (0-6), $a1 = source address, $a2 = dest address, $a3 = size
.macro dma_transfer
    # Calculate DMA register addresses
    sll     $t0, $a0, 4         # Channel * 16
    li      $t1, 0x1F801080     # DMA base address
    add     $t0, $t0, $t1       # Channel base address

    # Set memory address
    sw      $a1, 0($t0)         # MADR

    # Set block control (size)
    sw      $a3, 4($t0)         # BCR

    # Start transfer (enable + direction)
    li      $t1, 0x01000201     # Enable + from memory + start
    sw      $t1, 8($t0)         # CHCR

    # Wait for completion
.dma_wait:
    lw      $t1, 8($t0)
    andi    $t1, $t1, 0x01000000
    bnez    $t1, .dma_wait
    nop
.endm

# GPU DMA transfer (channel 2)
# $a0 = command list address, $a1 = size in words
.macro gpu_dma_send
    li      $t0, DMA2_MADR
    sw      $a0, 0($t0)         # Set source address

    li      $t0, DMA2_BCR
    sw      $a1, 0($t0)         # Set size

    li      $t0, DMA2_CHCR
    li      $t1, 0x01000201     # Start DMA from memory to GPU
    sw      $t1, 0($t0)

    # Wait for completion
.gpu_dma_wait:
    lw      $t1, 0($t0)
    andi    $t1, $t1, 0x01000000
    bnez    $t1, .gpu_dma_wait
    nop
.endm

# ============================================================================
# GPU Utilities
# ============================================================================

# Send GPU command
# $a0 = command
.macro gpu_command
    li      $t0, GPU_GP0
    sw      $a0, 0($t0)
.endm

# Wait for GPU ready
.macro gpu_wait_ready
    li      $t0, GPU_GP1
.gpu_wait:
    lw      $t1, 0($t0)
    andi    $t1, $t1, 0x04000000 # Check ready bit
    beqz    $t1, .gpu_wait
    nop
.endm

# Set display mode
# $a0 = width (320/640), $a1 = height (240/480), $a2 = color depth (0=15bit, 1=24bit)
.macro set_display_mode
    # Set display area
    li      $t0, GPU_GP1

    # Display enable
    li      $t1, 0x03000000
    sw      $t1, 0($t0)

    # Set horizontal range
    li      $t1, 0x06000000
    or      $t1, $t1, $a0
    sw      $t1, 0($t0)

    # Set vertical range
    li      $t1, 0x07000000
    or      $t1, $t1, $a1
    sw      $t1, 0($t0)

    # Set display mode
    li      $t1, 0x08000000
    or      $t1, $t1, $a2
    sw      $t1, 0($t0)
.endm

# ============================================================================
# Controller Input
# ============================================================================

# Read controller data
# Returns controller state in $v0
.macro read_controller
    li      $t0, JOY_CTRL
    li      $t1, 0x1003         # Start transfer
    sh      $t1, 0($t0)

    # Send controller select command
    li      $t0, JOY_DATA
    li      $t1, 0x01
    sb      $t1, 0($t0)

    # Wait for response
.joy_wait1:
    li      $t0, JOY_STAT
    lh      $t1, 0($t0)
    andi    $t1, $t1, 0x0002
    beqz    $t1, .joy_wait1
    nop

    # Read response
    li      $t0, JOY_DATA
    lb      $v0, 0($t0)

    # Send read buttons command
    li      $t1, 0x42
    sb      $t1, 0($t0)

    # Wait and read button data
.joy_wait2:
    li      $t0, JOY_STAT
    lh      $t1, 0($t0)
    andi    $t1, $t1, 0x0002
    beqz    $t1, .joy_wait2
    nop

    li      $t0, JOY_DATA
    lb      $t1, 0($t0)         # First button byte
    sll     $t1, $t1, 8
    or      $v0, $v0, $t1

    # Read second button byte
    li      $t1, 0x00
    sb      $t1, 0($t0)

.joy_wait3:
    li      $t0, JOY_STAT
    lh      $t1, 0($t0)
    andi    $t1, $t1, 0x0002
    beqz    $t1, .joy_wait3
    nop

    li      $t0, JOY_DATA
    lb      $t1, 0($t0)         # Second button byte
    or      $v0, $v0, $t1

    # Invert bits (0 = pressed on PlayStation)
    xori    $v0, $v0, 0xFFFF
.endm

# ============================================================================
# Timer Functions
# ============================================================================

# Initialize timer
# $a0 = timer number (0-2), $a1 = target value, $a2 = mode
.macro init_timer
    # Calculate timer base address
    sll     $t0, $a0, 4         # Timer * 16
    li      $t1, TIMER0_COUNT
    add     $t0, $t0, $t1

    # Reset counter
    sw      $zero, 0($t0)       # COUNT register

    # Set target
    sw      $a1, 8($t0)         # TARGET register

    # Set mode and enable
    ori     $a2, $a2, TMR_ENABLE
    sw      $a2, 4($t0)         # MODE register
.endm

# Wait for timer
# $a0 = timer number (0-2)
.macro wait_timer
    sll     $t0, $a0, 4
    li      $t1, TIMER0_MODE
    add     $t0, $t0, $t1

.timer_wait:
    lw      $t1, 0($t0)
    andi    $t1, $t1, 0x1000    # Check target reached bit
    beqz    $t1, .timer_wait
    nop

    # Clear the flag
    lw      $t1, 0($t0)
    andi    $t1, $t1, ~0x1000
    sw      $t1, 0($t0)
.endm

# ============================================================================
# VSync and Timing
# ============================================================================

# Wait for vertical blank
.macro wait_vblank
    li      $t0, I_STAT

.vblank_wait:
    lw      $t1, 0($t0)
    andi    $t1, $t1, IRQ_VBLANK
    beqz    $t1, .vblank_wait
    nop

    # Clear VBlank interrupt flag
    sw      $t1, 0($t0)
.endm

# Enable VBlank interrupt
.macro enable_vblank_irq
    li      $t0, I_MASK
    lw      $t1, 0($t0)
    ori     $t1, $t1, IRQ_VBLANK
    sw      $t1, 0($t0)

    # Enable interrupts globally
    mfc0    $t0, COP0_STATUS
    ori     $t0, $t0, STATUS_IE
    mtc0    $t0, COP0_STATUS
    nop
.endm

# ============================================================================
# SPU (Sound) Utilities
# ============================================================================

# Initialize SPU
.macro spu_init
    # Reset SPU
    li      $t0, SPU_CTRL
    li      $t1, 0x0000
    sh      $t1, 0($t0)

    # Set main volume
    li      $t0, SPU_MAIN_VOL_L
    li      $t1, 0x3FFF         # Max volume
    sh      $t1, 0($t0)
    li      $t0, SPU_MAIN_VOL_R
    sh      $t1, 0($t0)

    # Enable SPU
    li      $t0, SPU_CTRL
    li      $t1, 0x8000         # SPU enable
    sh      $t1, 0($t0)
.endm

# Play sound on voice
# $a0 = voice number (0-23), $a1 = sample address, $a2 = pitch
.macro spu_play_voice
    # Calculate voice register base
    li      $t0, SPU_VOICE_BASE
    sll     $t1, $a0, 4         # Voice * 16
    add     $t0, $t0, $t1

    # Set sample address
    srl     $t1, $a1, 3         # Address / 8 (SPU addressing)
    sh      $t1, VOICE_START_ADDR($t0)

    # Set pitch
    sh      $a2, VOICE_PITCH($t0)

    # Set volume
    li      $t1, 0x3FFF
    sh      $t1, VOICE_VOL_L($t0)
    sh      $t1, VOICE_VOL_R($t0)

    # Set ADSR (simple envelope)
    li      $t1, 0x00FF         # Attack/Decay
    sh      $t1, VOICE_ADSR_LO($t0)
    li      $t1, 0x0000         # Sustain/Release
    sh      $t1, VOICE_ADSR_HI($t0)

    # Key on
    li      $t0, SPU_KEY_ON
    li      $t1, 1
    sll     $t1, $t1, $a0       # Shift to voice bit
    sw      $t1, 0($t0)
.endm

# ============================================================================
# Interrupt Management
# ============================================================================

# Enable specific interrupt
# $a0 = interrupt mask
.macro enable_interrupt
    li      $t0, I_MASK
    lw      $t1, 0($t0)
    or      $t1, $t1, $a0
    sw      $t1, 0($t0)
.endm

# Disable specific interrupt
# $a0 = interrupt mask
.macro disable_interrupt
    li      $t0, I_MASK
    lw      $t1, 0($t0)
    not     $a0, $a0
    and     $t1, $t1, $a0
    sw      $t1, 0($t0)
.endm

# Acknowledge interrupt
# $a0 = interrupt mask
.macro ack_interrupt
    li      $t0, I_STAT
    sw      $a0, 0($t0)
.endm

# ============================================================================
# Utility Macros
# ============================================================================

# No-operation delay
.macro nop_delay count
    .rept \count
    nop
    .endr
.endm

# Load immediate 32-bit value
.macro li32 reg, value
    lui     \reg, ((\value) >> 16) & 0xFFFF
    ori     \reg, \reg, (\value) & 0xFFFF
.endm

# Software breakpoint (for debugging)
.macro breakpoint
    break   0x0
.endm