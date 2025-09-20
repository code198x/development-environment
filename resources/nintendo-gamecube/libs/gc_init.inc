# gc_init.inc - GameCube System Initialization and Utilities
# PowerPC assembly macros and functions for GameCube development

# ============================================================================
# Basic System Initialization
# ============================================================================

# Initialize GameCube system
.macro gc_init
    # Disable interrupts
    mfmsr   r3
    rlwinm  r3, r3, 0, 17, 15   # Clear EE bit (bit 15)
    mtmsr   r3
    isync

    # Set up basic BAT mappings for hardware access
    # Data BAT 0: Map hardware registers (0xCC000000)
    lis     r3, 0xCC00          # Effective address 0xCC000000
    ori     r3, r3, 0x1FFF      # 256MB block, VS|VP
    mtspr   SPR_DBAT0U, r3

    lis     r3, 0xCC00          # Real address 0xCC000000
    ori     r3, r3, 0x002A      # Cache-inhibited, guarded, R/W
    mtspr   SPR_DBAT0L, r3

    # Data BAT 1: Map main memory (0x80000000-0x81FFFFFF)
    lis     r3, 0x8000          # Effective address 0x80000000
    ori     r3, r3, 0x01FF      # 32MB block, VS|VP
    mtspr   SPR_DBAT1U, r3

    lis     r3, 0x0000          # Real address 0x00000000
    ori     r3, r3, 0x0002      # Cacheable, R/W
    mtspr   SPR_DBAT1L, r3

    # Instruction BAT 1: Same as data BAT 1 for code
    mtspr   SPR_IBAT1U, r3
    mtspr   SPR_IBAT1L, r3

    isync

    # Initialize stack pointer
    lis     r1, 0x8017
    ori     r1, r1, 0xFF00      # Stack at 0x8017FF00

    # Clear small data areas
    li      r2, 0               # Clear r2 (SDATA base)
    li      r13, 0              # Clear r13 (SDATA2 base)

    # Initialize floating point
    mfmsr   r3
    ori     r3, r3, 0x2000      # Set FP bit
    mtmsr   r3
    isync

    # Initialize FPSCR
    mtfsfi  7, 0
    mtfsfi  6, 0
    mtfsfi  5, 0
    mtfsfi  4, 0
    mtfsfi  3, 0
    mtfsfi  2, 0
    mtfsfi  1, 0
    mtfsfi  0, 0
.endm

# ============================================================================
# Cache Management
# ============================================================================

# Invalidate instruction cache
.macro icache_invalidate
    lis     r3, 0x8000          # Start address
    li      r4, ICACHE_SIZE / CACHE_LINE_SIZE  # Number of cache lines

.icache_loop:
    icbi    0, r3               # Invalidate cache block
    addi    r3, r3, CACHE_LINE_SIZE
    subi    r4, r4, 1
    cmpwi   r4, 0
    bgt     .icache_loop

    sync
    isync
.endm

# Flush data cache
.macro dcache_flush
    lis     r3, 0x8000          # Start address
    li      r4, DCACHE_SIZE / CACHE_LINE_SIZE  # Number of cache lines

.dcache_loop:
    dcbf    0, r3               # Flush cache block
    addi    r3, r3, CACHE_LINE_SIZE
    subi    r4, r4, 1
    cmpwi   r4, 0
    bgt     .dcache_loop

    sync
.endm

# Invalidate data cache
.macro dcache_invalidate
    lis     r3, 0x8000          # Start address
    li      r4, DCACHE_SIZE / CACHE_LINE_SIZE  # Number of cache lines

.dcache_inv_loop:
    dcbi    0, r3               # Invalidate cache block
    addi    r3, r3, CACHE_LINE_SIZE
    subi    r4, r4, 1
    cmpwi   r4, 0
    bgt     .dcache_inv_loop

    sync
.endm

# ============================================================================
# Memory Management
# ============================================================================

# Clear memory block
# r3 = address, r4 = size in bytes
.macro clear_memory
    cmpwi   r4, 0
    beqlr                       # Return if size is 0

    # Align to 4 bytes
    andi.   r5, r4, 3
    beq     .clear_aligned
    add     r4, r4, r5          # Round up
    andc    r4, r4, r5          # Clear low bits

.clear_aligned:
    srwi    r4, r4, 2           # Convert to word count
    li      r5, 0               # Clear value
    mtctr   r4                  # Set up counter

.clear_loop:
    stw     r5, 0(r3)
    addi    r3, r3, 4
    bdnz    .clear_loop
.endm

# Copy memory block
# r3 = source, r4 = destination, r5 = size in bytes
.macro copy_memory
    cmpwi   r5, 0
    beqlr                       # Return if size is 0

    # Handle alignment
    andi.   r6, r5, 3
    beq     .copy_aligned
    add     r5, r5, r6
    andc    r5, r5, r6

.copy_aligned:
    srwi    r5, r5, 2           # Convert to word count
    mtctr   r5

.copy_loop:
    lwz     r6, 0(r3)
    stw     r6, 0(r4)
    addi    r3, r3, 4
    addi    r4, r4, 4
    bdnz    .copy_loop
.endm

# ============================================================================
# Video Interface Initialization
# ============================================================================

# Initialize video interface for NTSC
.macro vi_init_ntsc
    # Set up basic NTSC timing
    lis     r3, VI_VTR@ha

    # Vertical timing register
    li      r4, 0x0F06          # NTSC timing
    sth     r4, VI_VTR@l(r3)

    # Display configuration
    li      r4, 0x0001          # Enable display
    sth     r4, VI_DCR@l(r3)

    # Horizontal timing
    lis     r4, 0x0C0C
    ori     r4, r4, 0x0C0C
    stw     r4, VI_HTR0@l(r3)

    # Set framebuffer address (example)
    lis     r4, 0x8040          # Framebuffer at 0x80400000
    stw     r4, VI_TFBL@l(r3)   # Top field base left
    stw     r4, VI_BFBL@l(r3)   # Bottom field base left
.endm

# Initialize video interface for PAL
.macro vi_init_pal
    lis     r3, VI_VTR@ha

    # PAL timing (different from NTSC)
    li      r4, 0x1006
    sth     r4, VI_VTR@l(r3)

    # Display configuration
    li      r4, 0x0001
    sth     r4, VI_DCR@l(r3)

    # Horizontal timing
    lis     r4, 0x0D0C
    ori     r4, r4, 0x0D0C
    stw     r4, VI_HTR0@l(r3)

    # Set framebuffer address
    lis     r4, 0x8040
    stw     r4, VI_TFBL@l(r3)
    stw     r4, VI_BFBL@l(r3)
.endm

# ============================================================================
# Controller Input
# ============================================================================

# Read controller state
# r3 = controller number (0-3)
# Returns controller state in r3
.macro read_controller
    # Calculate SI channel address
    lis     r4, SI_CHANNEL_0@ha
    mulli   r5, r3, 4           # Each channel is 4 bytes apart
    add     r4, r4, r5

    # Read controller data
    lwz     r3, SI_CHANNEL_0@l(r4)

    # Mask off analog stick data (keep only buttons)
    rlwinm  r3, r3, 0, 16, 31   # Keep lower 16 bits
.endm

# Check if specific button is pressed
# r3 = controller state, r4 = button mask
# Returns 1 in r3 if pressed, 0 if not
.macro check_button
    and.    r3, r3, r4
    li      r3, 0
    beq     .button_not_pressed
    li      r3, 1
.button_not_pressed:
.endm

# ============================================================================
# Timer and Timing
# ============================================================================

# Get time base (64-bit timer)
# Returns time in r3 (upper) and r4 (lower)
.macro get_timebase
    mftbu   r3                  # Get upper 32 bits
    mftbl   r4                  # Get lower 32 bits
    mftbu   r5                  # Get upper again
    cmpw    r3, r5              # Check if it changed
    bne     get_timebase        # Retry if rollover occurred
.endm

# Delay for specified number of bus cycles
# r3 = number of cycles to delay
.macro delay_cycles
    mftbl   r4                  # Get current time
    add     r3, r3, r4          # Calculate end time

.delay_loop:
    mftbl   r4                  # Get current time
    cmpw    r4, r3              # Compare with end time
    blt     .delay_loop         # Loop if not reached
.endm

# ============================================================================
# Interrupt Management
# ============================================================================

# Enable specific processor interface interrupt
# r3 = interrupt mask
.macro enable_pi_interrupt
    lis     r4, PI_INTMSK@ha
    lwz     r5, PI_INTMSK@l(r4)
    or      r5, r5, r3
    stw     r5, PI_INTMSK@l(r4)
.endm

# Disable specific processor interface interrupt
# r3 = interrupt mask
.macro disable_pi_interrupt
    lis     r4, PI_INTMSK@ha
    lwz     r5, PI_INTMSK@l(r4)
    andc    r5, r5, r3
    stw     r5, PI_INTMSK@l(r4)
.endm

# Acknowledge processor interface interrupt
# r3 = interrupt mask
.macro ack_pi_interrupt
    lis     r4, PI_INTSR@ha
    stw     r3, PI_INTSR@l(r4)
.endm

# Enable external interrupts in MSR
.macro enable_external_interrupts
    mfmsr   r3
    ori     r3, r3, MSR_EE      # Set external interrupt enable
    mtmsr   r3
    isync
.endm

# Disable external interrupts in MSR
.macro disable_external_interrupts
    mfmsr   r3
    rlwinm  r3, r3, 0, 17, 15   # Clear EE bit
    mtmsr   r3
    isync
.endm

# ============================================================================
# DVD Interface
# ============================================================================

# Check if DVD is present
# Returns 1 in r3 if disc present, 0 if not
.macro check_dvd_present
    lis     r4, DI_COVER@ha
    lwz     r3, DI_COVER@l(r4)
    rlwinm  r3, r3, 0, 30, 30   # Extract cover bit
    srwi    r3, r3, 1           # Shift to LSB
    xori    r3, r3, 1           # Invert (1 = present)
.endm

# ============================================================================
# DSP Communication
# ============================================================================

# Send mailbox message to DSP
# r3 = message (32-bit)
.macro dsp_send_mail
    lis     r4, DSP_MAILBOX_H@ha

    # Split 32-bit message into two 16-bit parts
    rlwinm  r5, r3, 16, 16, 31  # Upper 16 bits
    sth     r5, DSP_MAILBOX_H@l(r4)

    rlwinm  r5, r3, 0, 16, 31   # Lower 16 bits
    sth     r5, DSP_MAILBOX_L@l(r4)
.endm

# Receive mailbox message from DSP
# Returns message in r3
.macro dsp_receive_mail
    lis     r4, DSP_MAILBOX_H_R@ha

    # Wait for message
.dsp_wait_mail:
    lhz     r5, DSP_MAILBOX_H_R@l(r4)
    rlwinm. r6, r5, 0, 31, 31   # Check if message available
    beq     .dsp_wait_mail

    # Read message
    lhz     r3, DSP_MAILBOX_H_R@l(r4)
    lhz     r5, DSP_MAILBOX_L_R@l(r4)

    # Combine into 32-bit value
    rlwinm  r3, r3, 16, 0, 15   # Shift upper to high bits
    or      r3, r3, r5          # Combine with lower bits
.endm

# ============================================================================
# Utility Macros
# ============================================================================

# Load 32-bit immediate value
.macro li32 reg, value
    lis     \reg, (\value)@ha
    ori     \reg, \reg, (\value)@l
.endm

# Store 32-bit immediate to memory
.macro sti32 value, address
    lis     r0, (\value)@ha
    ori     r0, r0, (\value)@l
    lis     r11, (\address)@ha
    stw     r0, (\address)@l(r11)
.endm

# Load 32-bit value from memory
.macro lwi32 reg, address
    lis     r11, (\address)@ha
    lwz     \reg, (\address)@l(r11)
.endm

# No-operation with specific count
.macro nops count
    .rept \count
    nop
    .endr
.endm

# Function prologue
.macro function_enter
    mflr    r0                  # Save link register
    stw     r0, 4(r1)           # Store on stack
    stwu    r1, -64(r1)         # Create stack frame
.endm

# Function epilogue
.macro function_exit
    lwz     r0, 68(r1)          # Restore link register
    addi    r1, r1, 64          # Restore stack pointer
    mtlr    r0
    blr                         # Return
.endm

# ============================================================================
# Exception Handler Utilities
# ============================================================================

# Save volatile registers for interrupt handler
.macro save_volatile
    stw     r3, 8(r1)
    stw     r4, 12(r1)
    stw     r5, 16(r1)
    stw     r6, 20(r1)
    stw     r7, 24(r1)
    stw     r8, 28(r1)
    stw     r9, 32(r1)
    stw     r10, 36(r1)
    stw     r11, 40(r1)
    stw     r12, 44(r1)
    mfcr    r3
    stw     r3, 48(r1)          # Save condition register
    mfxer   r3
    stw     r3, 52(r1)          # Save XER
    mfctr   r3
    stw     r3, 56(r1)          # Save CTR
.endm

# Restore volatile registers
.macro restore_volatile
    lwz     r3, 56(r1)
    mtctr   r3                  # Restore CTR
    lwz     r3, 52(r1)
    mtxer   r3                  # Restore XER
    lwz     r3, 48(r1)
    mtcr    r3                  # Restore condition register
    lwz     r3, 8(r1)
    lwz     r4, 12(r1)
    lwz     r5, 16(r1)
    lwz     r6, 20(r1)
    lwz     r7, 24(r1)
    lwz     r8, 28(r1)
    lwz     r9, 32(r1)
    lwz     r10, 36(r1)
    lwz     r11, 40(r1)
    lwz     r12, 44(r1)
.endm