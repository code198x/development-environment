# psx.inc - Sony PlayStation Hardware Definitions
# For use with MIPS assemblers (GNU as, etc.)
# Comprehensive hardware register and memory map definitions

# ============================================================================
# Memory Map
# ============================================================================

# Main RAM
.equ RAM_BASE,          0x80000000  # Main RAM base (cached)
.equ RAM_BASE_UNCACHED, 0xA0000000  # Main RAM base (uncached)
.equ RAM_SIZE,          0x200000    # 2MB main RAM

# BIOS ROM
.equ BIOS_BASE,         0xBFC00000  # BIOS ROM base
.equ BIOS_SIZE,         0x80000     # 512KB BIOS ROM

# I/O Registers
.equ IO_BASE,           0x1F800000  # I/O register base

# Expansion regions
.equ EXP1_BASE,         0x1F000000  # Expansion region 1
.equ EXP2_BASE,         0x1F802000  # Expansion region 2
.equ EXP3_BASE,         0x1FA00000  # Expansion region 3

# Parallel port
.equ PARALLEL_BASE,     0x1F040000  # Parallel port base

# Hardware registers
.equ HW_REGS_BASE,      0x1F801000  # Hardware registers base

# ============================================================================
# Memory Control Registers
# ============================================================================

.equ MEM_CONTROL_1,     0x1F801000  # Memory control 1
.equ MEM_CONTROL_2,     0x1F801004  # Memory control 2
.equ EXP1_BASE_ADDR,    0x1F801008  # Expansion 1 base address
.equ EXP2_BASE_ADDR,    0x1F80100C  # Expansion 2 base address
.equ EXP1_DELAY_SIZE,   0x1F801010  # Expansion 1 delay/size
.equ EXP3_DELAY_SIZE,   0x1F801014  # Expansion 3 delay/size
.equ BIOS_DELAY_SIZE,   0x1F801018  # BIOS delay/size
.equ SPU_DELAY,         0x1F80101C  # SPU delay
.equ CDROM_DELAY,       0x1F801020  # CD-ROM delay
.equ EXP2_DELAY_SIZE,   0x1F801024  # Expansion 2 delay/size
.equ COMMON_DELAY,      0x1F801028  # Common delay

# ============================================================================
# Interrupt Control
# ============================================================================

.equ I_STAT,            0x1F801070  # Interrupt status register
.equ I_MASK,            0x1F801074  # Interrupt mask register

# Interrupt bits
.equ IRQ_VBLANK,        0x0001      # Vertical blank
.equ IRQ_GPU,           0x0002      # GPU
.equ IRQ_CDROM,         0x0004      # CD-ROM
.equ IRQ_DMA,           0x0008      # DMA
.equ IRQ_TIMER0,        0x0010      # Timer 0
.equ IRQ_TIMER1,        0x0020      # Timer 1
.equ IRQ_TIMER2,        0x0040      # Timer 2
.equ IRQ_CONTROLLER,    0x0080      # Controller/memory card
.equ IRQ_SIO,           0x0100      # SIO
.equ IRQ_SPU,           0x0200      # SPU
.equ IRQ_LIGHTPEN,      0x0400      # Lightpen

# ============================================================================
# DMA Registers
# ============================================================================

# DMA Channel 0 (MDECin)
.equ DMA0_MADR,         0x1F801080  # DMA0 memory address
.equ DMA0_BCR,          0x1F801084  # DMA0 block control
.equ DMA0_CHCR,         0x1F801088  # DMA0 channel control

# DMA Channel 1 (MDECout)
.equ DMA1_MADR,         0x1F801090  # DMA1 memory address
.equ DMA1_BCR,          0x1F801094  # DMA1 block control
.equ DMA1_CHCR,         0x1F801098  # DMA1 channel control

# DMA Channel 2 (GPU)
.equ DMA2_MADR,         0x1F8010A0  # DMA2 memory address
.equ DMA2_BCR,          0x1F8010A4  # DMA2 block control
.equ DMA2_CHCR,         0x1F8010A8  # DMA2 channel control

# DMA Channel 3 (CD-ROM)
.equ DMA3_MADR,         0x1F8010B0  # DMA3 memory address
.equ DMA3_BCR,          0x1F8010B4  # DMA3 block control
.equ DMA3_CHCR,         0x1F8010B8  # DMA3 channel control

# DMA Channel 4 (SPU)
.equ DMA4_MADR,         0x1F8010C0  # DMA4 memory address
.equ DMA4_BCR,          0x1F8010C4  # DMA4 block control
.equ DMA4_CHCR,         0x1F8010C8  # DMA4 channel control

# DMA Channel 5 (PIO)
.equ DMA5_MADR,         0x1F8010D0  # DMA5 memory address
.equ DMA5_BCR,          0x1F8010D4  # DMA5 block control
.equ DMA5_CHCR,         0x1F8010D8  # DMA5 channel control

# DMA Channel 6 (GPU OTC)
.equ DMA6_MADR,         0x1F8010E0  # DMA6 memory address
.equ DMA6_BCR,          0x1F8010E4  # DMA6 block control
.equ DMA6_CHCR,         0x1F8010E8  # DMA6 channel control

# DMA Control
.equ DMA_DPCR,          0x1F8010F0  # DMA control register
.equ DMA_DICR,          0x1F8010F4  # DMA interrupt control

# DMA Control Register bits
.equ DMA_ENABLE_0,      0x0008      # Enable DMA channel 0
.equ DMA_ENABLE_1,      0x0080      # Enable DMA channel 1
.equ DMA_ENABLE_2,      0x0800      # Enable DMA channel 2
.equ DMA_ENABLE_3,      0x8000      # Enable DMA channel 3
.equ DMA_ENABLE_4,      0x80000     # Enable DMA channel 4
.equ DMA_ENABLE_5,      0x800000    # Enable DMA channel 5
.equ DMA_ENABLE_6,      0x8000000   # Enable DMA channel 6

# ============================================================================
# Timer Registers
# ============================================================================

# Timer 0 (dotclock)
.equ TIMER0_COUNT,      0x1F801100  # Timer 0 current value
.equ TIMER0_MODE,       0x1F801104  # Timer 0 control/mode
.equ TIMER0_TARGET,     0x1F801108  # Timer 0 target value

# Timer 1 (horizontal sync)
.equ TIMER1_COUNT,      0x1F801110  # Timer 1 current value
.equ TIMER1_MODE,       0x1F801114  # Timer 1 control/mode
.equ TIMER1_TARGET,     0x1F801118  # Timer 1 target value

# Timer 2 (1/8 system clock)
.equ TIMER2_COUNT,      0x1F801120  # Timer 2 current value
.equ TIMER2_MODE,       0x1F801124  # Timer 2 control/mode
.equ TIMER2_TARGET,     0x1F801128  # Timer 2 target value

# Timer mode bits
.equ TMR_ENABLE,        0x0001      # Timer enable
.equ TMR_TARGET_MODE,   0x0002      # Target mode
.equ TMR_IRQ_TARGET,    0x0010      # IRQ when target reached
.equ TMR_IRQ_OVERFLOW,  0x0020      # IRQ on overflow
.equ TMR_IRQ_REPEAT,    0x0040      # Repeat IRQ
.equ TMR_IRQ_TOGGLE,    0x0080      # Toggle IRQ bit
.equ TMR_CLOCK_SYS,     0x0000      # System clock
.equ TMR_CLOCK_EXT,     0x0100      # External clock

# ============================================================================
# Controller/Memory Card
# ============================================================================

.equ JOY_DATA,          0x1F801040  # Joypad/memory card data
.equ JOY_STAT,          0x1F801044  # Joypad/memory card status
.equ JOY_MODE,          0x1F801048  # Joypad/memory card mode
.equ JOY_CTRL,          0x1F80104A  # Joypad/memory card control
.equ JOY_BAUD,          0x1F80104E  # Joypad/memory card baud rate

# Controller button bits (when read)
.equ PAD_SELECT,        0x0001      # SELECT button
.equ PAD_L3,            0x0002      # L3 button (analog)
.equ PAD_R3,            0x0004      # R3 button (analog)
.equ PAD_START,         0x0008      # START button
.equ PAD_UP,            0x0010      # D-pad up
.equ PAD_RIGHT,         0x0020      # D-pad right
.equ PAD_DOWN,          0x0040      # D-pad down
.equ PAD_LEFT,          0x0080      # D-pad left
.equ PAD_L2,            0x0100      # L2 button
.equ PAD_R2,            0x0200      # R2 button
.equ PAD_L1,            0x0400      # L1 button
.equ PAD_R1,            0x0800      # R1 button
.equ PAD_TRIANGLE,      0x1000      # Triangle button
.equ PAD_CIRCLE,        0x2000      # Circle button
.equ PAD_CROSS,         0x4000      # Cross (X) button
.equ PAD_SQUARE,        0x8000      # Square button

# ============================================================================
# Serial I/O
# ============================================================================

.equ SIO_DATA,          0x1F801050  # Serial data register
.equ SIO_STAT,          0x1F801054  # Serial status register
.equ SIO_MODE,          0x1F801058  # Serial mode register
.equ SIO_CTRL,          0x1F80105A  # Serial control register
.equ SIO_MISC,          0x1F80105C  # Serial miscellaneous
.equ SIO_BAUD,          0x1F80105E  # Serial baud rate

# ============================================================================
# GPU Registers
# ============================================================================

.equ GPU_GP0,           0x1F801810  # GPU command/packet register
.equ GPU_GP1,           0x1F801814  # GPU status/control register

# GPU GP1 commands
.equ GPU_RESET,         0x00000000  # Reset GPU
.equ GPU_RESET_BUFFER,  0x01000000  # Reset command buffer
.equ GPU_RESET_IRQ,     0x02000000  # Reset IRQ
.equ GPU_DISPLAY_ENABLE, 0x03000000 # Display enable
.equ GPU_DMA_DIR,       0x04000000  # DMA direction
.equ GPU_DISPLAY_START, 0x05000000  # Display area start
.equ GPU_DISPLAY_RANGE, 0x06000000  # Display horizontal range
.equ GPU_DISPLAY_MODE,  0x08000000  # Display mode

# ============================================================================
# SPU (Sound Processing Unit)
# ============================================================================

.equ SPU_MAIN_VOL_L,    0x1F801D80  # Main volume left
.equ SPU_MAIN_VOL_R,    0x1F801D82  # Main volume right
.equ SPU_REVERB_VOL_L,  0x1F801D84  # Reverb volume left
.equ SPU_REVERB_VOL_R,  0x1F801D86  # Reverb volume right
.equ SPU_KEY_ON,        0x1F801D88  # Voice key on
.equ SPU_KEY_OFF,       0x1F801D8C  # Voice key off
.equ SPU_PITCH_MOD,     0x1F801D90  # Pitch modulation enable
.equ SPU_NOISE_EN,      0x1F801D94  # Noise enable
.equ SPU_REVERB_EN,     0x1F801D98  # Reverb enable
.equ SPU_VOICE_STATUS,  0x1F801D9C  # Voice status
.equ SPU_REVERB_ADDR,   0x1F801DA2  # Reverb work area start
.equ SPU_IRQ_ADDR,      0x1F801DA4  # IRQ address
.equ SPU_ADDR,          0x1F801DA6  # Current SPU address
.equ SPU_DATA,          0x1F801DA8  # SPU data
.equ SPU_CTRL,          0x1F801DAA  # SPU control
.equ SPU_STATUS,        0x1F801DAE  # SPU status
.equ SPU_CD_VOL_L,      0x1F801DB0  # CD volume left
.equ SPU_CD_VOL_R,      0x1F801DB2  # CD volume right
.equ SPU_EXT_VOL_L,     0x1F801DB4  # External volume left
.equ SPU_EXT_VOL_R,     0x1F801DB6  # External volume right

# Voice registers (24 voices, each using 16 bytes)
.equ SPU_VOICE_BASE,    0x1F801C00  # Voice register base
.equ SPU_VOICE_SIZE,    0x10        # Size per voice

# Voice register offsets (add to voice base + voice_num * SPU_VOICE_SIZE)
.equ VOICE_VOL_L,       0x00        # Volume left
.equ VOICE_VOL_R,       0x02        # Volume right
.equ VOICE_PITCH,       0x04        # Pitch
.equ VOICE_START_ADDR,  0x06        # Sample start address
.equ VOICE_ADSR_LO,     0x08        # ADSR settings low
.equ VOICE_ADSR_HI,     0x0A        # ADSR settings high
.equ VOICE_ADSR_VOL,    0x0C        # Current ADSR volume
.equ VOICE_REPEAT_ADDR, 0x0E        # Sample repeat address

# ============================================================================
# CD-ROM Registers
# ============================================================================

.equ CDROM_STATUS,      0x1F801800  # CD-ROM status register
.equ CDROM_COMMAND,     0x1F801801  # CD-ROM command register
.equ CDROM_DATA,        0x1F801802  # CD-ROM data register
.equ CDROM_IRQ,         0x1F801803  # CD-ROM interrupt register

# CD-ROM commands
.equ CD_SYNC,           0x00        # Sync command
.equ CD_NOP,            0x01        # No operation
.equ CD_SETLOC,         0x02        # Set location
.equ CD_PLAY,           0x03        # Play
.equ CD_FORWARD,        0x04        # Forward
.equ CD_BACKWARD,       0x05        # Backward
.equ CD_READN,          0x06        # Read with retry
.equ CD_STOP,           0x08        # Stop motor
.equ CD_PAUSE,          0x09        # Pause
.equ CD_RESET,          0x0A        # Reset
.equ CD_MUTE,           0x0B        # Mute
.equ CD_DEMUTE,         0x0C        # Demute
.equ CD_SETFILTER,      0x0D        # Set filter
.equ CD_SETMODE,        0x0E        # Set mode
.equ CD_GETPARAM,       0x0F        # Get parameters
.equ CD_GETLOCL,        0x10        # Get location (logical)
.equ CD_GETLOCP,        0x11        # Get location (physical)
.equ CD_SETSESSION,     0x12        # Set session
.equ CD_GETTN,          0x13        # Get track number
.equ CD_GETTD,          0x14        # Get track data
.equ CD_SEEKL,          0x15        # Seek (logical)
.equ CD_SEEKP,          0x16        # Seek (physical)
.equ CD_TEST,           0x19        # Test command
.equ CD_ID,             0x1A        # Get ID
.equ CD_READS,          0x1B        # Read (single speed)
.equ CD_READTOC,        0x1E        # Read table of contents

# ============================================================================
# System Control
# ============================================================================

.equ POST_STATUS,       0x1F801000  # POST status (read-only)
.equ SYS_CONTROL,       0x1F801060  # System control

# ============================================================================
# Constants and Useful Values
# ============================================================================

# Screen dimensions
.equ SCREEN_WIDTH,      320         # Standard screen width
.equ SCREEN_HEIGHT,     240         # Standard screen height (NTSC)
.equ SCREEN_HEIGHT_PAL, 256         # PAL screen height

# Video timing
.equ NTSC_FREQUENCY,    60          # NTSC refresh rate (Hz)
.equ PAL_FREQUENCY,     50          # PAL refresh rate (Hz)

# Memory sizes
.equ VRAM_SIZE,         0x100000    # 1MB VRAM
.equ SPU_RAM_SIZE,      0x80000     # 512KB SPU RAM

# DMA transfer modes
.equ DMA_BURST,         0x01000000  # Burst transfer
.equ DMA_SLICE,         0x02000000  # Slice transfer
.equ DMA_TO_RAM,        0x00000000  # Transfer to main RAM
.equ DMA_FROM_RAM,      0x01000000  # Transfer from main RAM

# MIPS Coprocessor 0 registers
.equ COP0_INDEX,        $0          # MMU Index register
.equ COP0_RANDOM,       $1          # MMU Random register
.equ COP0_ENTRYLO,      $2          # MMU EntryLo register
.equ COP0_CONTEXT,      $4          # MMU Context register
.equ COP0_BADVADDR,     $8          # Bad virtual address
.equ COP0_COUNT,        $9          # Timer count
.equ COP0_ENTRYHI,      $10         # MMU EntryHi register
.equ COP0_COMPARE,      $11         # Timer compare
.equ COP0_STATUS,       $12         # Status register
.equ COP0_CAUSE,        $13         # Exception cause
.equ COP0_EPC,          $14         # Exception program counter
.equ COP0_PRID,         $15         # Processor revision ID

# Status register bits
.equ STATUS_IE,         0x00000001  # Interrupt enable
.equ STATUS_EXL,        0x00000002  # Exception level
.equ STATUS_ERL,        0x00000004  # Error level
.equ STATUS_KU,         0x00000008  # User mode
.equ STATUS_IM,         0x0000FF00  # Interrupt mask
.equ STATUS_BEV,        0x00400000  # Boot exception vectors

# Cause register bits
.equ CAUSE_IP,          0x0000FF00  # Interrupt pending
.equ CAUSE_CE,          0x30000000  # Coprocessor error
.equ CAUSE_BD,          0x80000000  # Branch delay

# Exception codes
.equ EXC_INT,           0x00        # External interrupt
.equ EXC_MOD,           0x04        # TLB modification
.equ EXC_TLBL,          0x08        # TLB load/fetch
.equ EXC_TLBS,          0x0C        # TLB store
.equ EXC_ADEL,          0x10        # Address error (load/fetch)
.equ EXC_ADES,          0x14        # Address error (store)
.equ EXC_IBE,           0x18        # Bus error (instruction)
.equ EXC_DBE,           0x1C        # Bus error (data)
.equ EXC_SYS,           0x20        # System call
.equ EXC_BP,            0x24        # Breakpoint
.equ EXC_RI,            0x28        # Reserved instruction
.equ EXC_CPU,           0x2C        # Coprocessor unusable
.equ EXC_OV,            0x30        # Arithmetic overflow
.equ EXC_TR,            0x34        # Trap

# ============================================================================
# CD-ROM Sector Format
# ============================================================================

.equ SECTOR_SIZE,       0x800       # 2048 bytes per sector (Mode 1)
.equ SECTOR_SIZE_RAW,   0x930       # 2352 bytes raw sector
.equ SECTOR_HEADER_SIZE, 0x18       # 24 bytes header + subheader

# ============================================================================
# BIOS Functions (commonly used)
# ============================================================================

# Note: PlayStation BIOS functions are called via specific jump tables
# These are example addresses - actual addresses may vary by BIOS version

.equ BIOS_PRINTF,       0xBFC06A3C  # printf function
.equ BIOS_PUTS,         0xBFC06A4C  # puts function
.equ BIOS_MALLOC,       0xBFC07A3C  # malloc function
.equ BIOS_FREE,         0xBFC07A4C  # free function

# ============================================================================
# GPU Primitive Types
# ============================================================================

.equ GPU_TRI_FLAT,      0x20        # Flat triangle
.equ GPU_TRI_GOURAUD,   0x30        # Gouraud triangle
.equ GPU_TRI_TEXTURED,  0x24        # Textured triangle
.equ GPU_QUAD_FLAT,     0x28        # Flat quad
.equ GPU_QUAD_GOURAUD,  0x38        # Gouraud quad
.equ GPU_QUAD_TEXTURED, 0x2C        # Textured quad
.equ GPU_LINE,          0x40        # Line
.equ GPU_SPRITE,        0x64        # Sprite

# ============================================================================
# Stack and Memory Layout (typical)
# ============================================================================

.equ STACK_BASE,        0x801FFF00  # Typical stack location
.equ HEAP_BASE,         0x80100000  # Typical heap start
.equ SCRATCHPAD,        0x1F800000  # 1KB scratchpad RAM