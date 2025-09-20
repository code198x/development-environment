# dolphin.inc - Nintendo GameCube (Dolphin) Hardware Definitions
# For use with PowerPC assemblers (GNU as, devkitPPC, etc.)
# Comprehensive hardware register and memory map definitions

# ============================================================================
# Memory Map
# ============================================================================

# Main Memory (MEM1 - 24MB on retail GameCube)
.equ MEM1_BASE,         0x80000000  # Main RAM base (cached)
.equ MEM1_BASE_UNCACHED, 0xC0000000 # Main RAM base (uncached)
.equ MEM1_SIZE,         0x01800000  # 24MB main RAM

# Audio RAM (ARAM - 16MB)
.equ ARAM_BASE,         0x7E000000  # Audio RAM base
.equ ARAM_SIZE,         0x01000000  # 16MB audio RAM

# Embedded Frame Buffer (EFB)
.equ EFB_BASE,          0xCC000000  # EFB base address
.equ EFB_COLOR_BASE,    0xCC000000  # Color buffer
.equ EFB_DEPTH_BASE,    0xCC001000  # Depth buffer

# Hardware Registers
.equ HW_REGS_BASE,      0xCC000000  # Hardware register base

# BootROM
.equ BOOTROM_BASE,      0xFFF00000  # BootROM base
.equ BOOTROM_SIZE,      0x00100000  # 1MB BootROM

# L2 Cache (Locked Cache - can be used as fast RAM)
.equ L2_CACHE_BASE,     0xE0000000  # L2 cache base
.equ L2_CACHE_SIZE,     0x00040000  # 256KB L2 cache

# ============================================================================
# Command Processor (CP) Registers
# ============================================================================

.equ CP_STATUS,         0xCC000000  # CP status register
.equ CP_ENABLE,         0xCC000002  # CP enable register
.equ CP_CLEAR,          0xCC000004  # CP clear register
.equ CP_TOKEN,          0xCC00000E  # CP token register
.equ CP_BBOX_LEFT,      0xCC000010  # Bounding box left
.equ CP_BBOX_RIGHT,     0xCC000012  # Bounding box right
.equ CP_BBOX_TOP,       0xCC000014  # Bounding box top
.equ CP_BBOX_BOTTOM,    0xCC000016  # Bounding box bottom

# CP FIFO
.equ CP_FIFO_BASE_LO,   0xCC000020  # FIFO base address low
.equ CP_FIFO_BASE_HI,   0xCC000022  # FIFO base address high
.equ CP_FIFO_END_LO,    0xCC000024  # FIFO end address low
.equ CP_FIFO_END_HI,    0xCC000026  # FIFO end address high
.equ CP_FIFO_COUNT_HI,  0xCC000028  # FIFO count high
.equ CP_FIFO_COUNT_LO,  0xCC00002A  # FIFO count low
.equ CP_FIFO_WRITE_PTR, 0xCC00002C  # FIFO write pointer
.equ CP_FIFO_READ_PTR,  0xCC000030  # FIFO read pointer
.equ CP_FIFO_BP_LO,     0xCC000034  # FIFO breakpoint low
.equ CP_FIFO_BP_HI,     0xCC000036  # FIFO breakpoint high
.equ CP_FIFO_RW_DIST_LO, 0xCC000038 # FIFO read/write distance low
.equ CP_FIFO_RW_DIST_HI, 0xCC00003A # FIFO read/write distance high

# ============================================================================
# Pixel Engine (PE) Registers
# ============================================================================

.equ PE_ZCONF,          0xCC001000  # Z configuration
.equ PE_ALPHACONF,      0xCC001002  # Alpha configuration
.equ PE_DSTALPHACONF,   0xCC001004  # Destination alpha configuration
.equ PE_ALPHAMODE,      0xCC001006  # Alpha mode
.equ PE_ALPHAREAD,      0xCC001008  # Alpha read
.equ PE_CTRL,           0xCC00100A  # PE control
.equ PE_TOKEN,          0xCC00100E  # PE token
.equ PE_BBOX_LEFT,      0xCC001010  # PE bounding box left
.equ PE_BBOX_RIGHT,     0xCC001012  # PE bounding box right
.equ PE_BBOX_TOP,       0xCC001014  # PE bounding box top
.equ PE_BBOX_BOTTOM,    0xCC001016  # PE bounding box bottom

# ============================================================================
# Video Interface (VI) Registers
# ============================================================================

.equ VI_VTR,            0xCC002000  # Vertical timing register
.equ VI_DCR,            0xCC002002  # Display configuration register
.equ VI_HTR0,           0xCC002004  # Horizontal timing 0
.equ VI_HTR1,           0xCC002006  # Horizontal timing 1
.equ VI_VTO,            0xCC002008  # Vertical timing odd
.equ VI_VTE,            0xCC00200A  # Vertical timing even
.equ VI_BBEI,           0xCC00200C  # Burst blanking interval (even)
.equ VI_BBOI,           0xCC00200E  # Burst blanking interval (odd)
.equ VI_TFBL,           0xCC002010  # Top field base address (left)
.equ VI_TFBR,           0xCC002014  # Top field base address (right)
.equ VI_BFBL,           0xCC002018  # Bottom field base address (left)
.equ VI_BFBR,           0xCC00201C  # Bottom field base address (right)
.equ VI_DPV,            0xCC002020  # Display position vertical
.equ VI_DPH,            0xCC002022  # Display position horizontal
.equ VI_DI0,            0xCC002024  # Display interrupt 0
.equ VI_DI1,            0xCC002026  # Display interrupt 1
.equ VI_DI2,            0xCC002028  # Display interrupt 2
.equ VI_DI3,            0xCC00202A  # Display interrupt 3
.equ VI_DL0,            0xCC00202C  # Display latch 0
.equ VI_DL1,            0xCC00202E  # Display latch 1
.equ VI_HSW,            0xCC002030  # Horizontal scaling width
.equ VI_HSR,            0xCC002032  # Horizontal scaling register
.equ VI_FCT0,           0xCC002034  # Filter coefficient table 0
.equ VI_FCT1,           0xCC002036  # Filter coefficient table 1
.equ VI_FCT2,           0xCC002038  # Filter coefficient table 2
.equ VI_FCT3,           0xCC00203A  # Filter coefficient table 3
.equ VI_FCT4,           0xCC00203C  # Filter coefficient table 4
.equ VI_FCT5,           0xCC00203E  # Filter coefficient table 5
.equ VI_FCT6,           0xCC002040  # Filter coefficient table 6
.equ VI_UNK,            0xCC002042  # Unknown
.equ VI_VICLK,          0xCC002048  # VI clock select
.equ VI_VISEL,          0xCC00204A  # VI select

# ============================================================================
# Processor Interface (PI) Registers
# ============================================================================

.equ PI_INTSR,          0xCC003000  # Interrupt status register
.equ PI_INTMSK,         0xCC003004  # Interrupt mask register
.equ PI_FIFO_BASE,      0xCC003008  # FIFO base address
.equ PI_FIFO_END,       0xCC00300C  # FIFO end address
.equ PI_FIFO_WPTR,      0xCC003010  # FIFO write pointer
.equ PI_RESET,          0xCC003024  # Reset register
.equ PI_RESETCODE,      0xCC003028  # Reset code
.equ PI_FLIPPER_REV,    0xCC00302C  # Flipper revision
.equ PI_FLIPPER_UNK,    0xCC003030  # Flipper unknown

# Interrupt bits
.equ PI_INT_ERROR,      0x00000001  # Error interrupt
.equ PI_INT_RSW,        0x00000002  # Reset switch interrupt
.equ PI_INT_DI,         0x00000004  # DVD interface interrupt
.equ PI_INT_SI,         0x00000008  # Serial interface interrupt
.equ PI_INT_EXI,        0x00000010  # External interface interrupt
.equ PI_INT_AI,         0x00000020  # Audio interface interrupt
.equ PI_INT_DSP,        0x00000040  # DSP interrupt
.equ PI_INT_MEM,        0x00000080  # Memory interface interrupt
.equ PI_INT_VI,         0x00000100  # Video interface interrupt
.equ PI_INT_PE_TOKEN,   0x00000200  # PE token interrupt
.equ PI_INT_PE_FINISH,  0x00000400  # PE finish interrupt
.equ PI_INT_CP,         0x00000800  # Command processor interrupt
.equ PI_INT_DEBUG,      0x00001000  # Debug interrupt
.equ PI_INT_HSP,        0x00002000  # High speed port interrupt

# ============================================================================
# Memory Interface (MI) Registers
# ============================================================================

.equ MI_MODE,           0xCC004000  # Memory interface mode
.equ MI_PROT,           0xCC004004  # Memory protection
.equ MI_INTRMASK,       0xCC004008  # Interrupt mask
.equ MI_INTRSTATUS,     0xCC00400C  # Interrupt status
.equ MI_UNK0,           0xCC004010  # Unknown
.equ MI_UNK1,           0xCC004014  # Unknown
.equ MI_UNK2,           0xCC004018  # Unknown
.equ MI_TIMER,          0xCC00401C  # Timer

# ============================================================================
# DVD Interface (DI) Registers
# ============================================================================

.equ DI_STATUS,         0xCC006000  # DI status register
.equ DI_COVER,          0xCC006004  # DI cover register
.equ DI_CMD_0,          0xCC006008  # DI command 0
.equ DI_CMD_1,          0xCC00600C  # DI command 1
.equ DI_CMD_2,          0xCC006010  # DI command 2
.equ DI_MAR,            0xCC006014  # DI memory address register
.equ DI_LENGTH,         0xCC006018  # DI length register
.equ DI_CR,             0xCC00601C  # DI control register
.equ DI_DATA,           0xCC006020  # DI immediate data
.equ DI_CONFIG,         0xCC006024  # DI configuration

# ============================================================================
# Serial Interface (SI) Registers
# ============================================================================

.equ SI_CHANNEL_0,      0xCC006400  # SI channel 0 (controller 1)
.equ SI_CHANNEL_1,      0xCC006404  # SI channel 1 (controller 2)
.equ SI_CHANNEL_2,      0xCC006408  # SI channel 2 (controller 3)
.equ SI_CHANNEL_3,      0xCC00640C  # SI channel 3 (controller 4)
.equ SI_POLL,           0xCC006410  # SI poll register
.equ SI_COM_CSR,        0xCC006414  # SI communication control
.equ SI_STATUS,         0xCC006418  # SI status register
.equ SI_EXI_CLOCK,      0xCC00641C  # SI EXI clock

# Controller button bits
.equ PAD_BUTTON_LEFT,   0x0001      # D-pad left
.equ PAD_BUTTON_RIGHT,  0x0002      # D-pad right
.equ PAD_BUTTON_DOWN,   0x0004      # D-pad down
.equ PAD_BUTTON_UP,     0x0008      # D-pad up
.equ PAD_TRIGGER_Z,     0x0010      # Z trigger
.equ PAD_TRIGGER_R,     0x0020      # R trigger
.equ PAD_TRIGGER_L,     0x0040      # L trigger
.equ PAD_BUTTON_A,      0x0100      # A button
.equ PAD_BUTTON_B,      0x0200      # B button
.equ PAD_BUTTON_X,      0x0400      # X button
.equ PAD_BUTTON_Y,      0x0800      # Y button
.equ PAD_BUTTON_START,  0x1000      # START button

# ============================================================================
# External Interface (EXI) Registers
# ============================================================================

# EXI Channel 0 (Memory cards slot A)
.equ EXI0_CSR,          0xCC006800  # EXI0 control/status
.equ EXI0_MAR,          0xCC006804  # EXI0 memory address
.equ EXI0_LENGTH,       0xCC006808  # EXI0 length
.equ EXI0_CR,           0xCC00680C  # EXI0 control
.equ EXI0_DATA,         0xCC006810  # EXI0 data

# EXI Channel 1 (Memory cards slot B)
.equ EXI1_CSR,          0xCC006814  # EXI1 control/status
.equ EXI1_MAR,          0xCC006818  # EXI1 memory address
.equ EXI1_LENGTH,       0xCC00681C  # EXI1 length
.equ EXI1_CR,           0xCC006820  # EXI1 control
.equ EXI1_DATA,         0xCC006824  # EXI1 data

# EXI Channel 2 (Network adapter)
.equ EXI2_CSR,          0xCC006828  # EXI2 control/status
.equ EXI2_MAR,          0xCC00682C  # EXI2 memory address
.equ EXI2_LENGTH,       0xCC006830  # EXI2 length
.equ EXI2_CR,           0xCC006834  # EXI2 control
.equ EXI2_DATA,         0xCC006838  # EXI2 data

# ============================================================================
# Audio Interface (AI) Registers
# ============================================================================

.equ AI_CONTROL,        0xCC006C00  # AI control register
.equ AI_VOLUME,         0xCC006C04  # AI volume register
.equ AI_SAMPLE_COUNT,   0xCC006C08  # AI sample count
.equ AI_INTERRUPT_TIMING, 0xCC006C0C # AI interrupt timing

# ============================================================================
# DSP Interface Registers
# ============================================================================

.equ DSP_MAILBOX_H,     0xCC005000  # DSP mailbox high (CPU->DSP)
.equ DSP_MAILBOX_L,     0xCC005002  # DSP mailbox low (CPU->DSP)
.equ DSP_MAILBOX_H_R,   0xCC005004  # DSP mailbox high (DSP->CPU)
.equ DSP_MAILBOX_L_R,   0xCC005006  # DSP mailbox low (DSP->CPU)
.equ DSP_CONTROL,       0xCC005008  # DSP control register
.equ DSP_ARAM_MMIO,     0xCC005010  # DSP ARAM MMIO
.equ DSP_ARAM_SIZE,     0xCC005012  # DSP ARAM size
.equ DSP_ARAM_MODE,     0xCC005016  # DSP ARAM mode
.equ DSP_ARAM_REFRESH,  0xCC005018  # DSP ARAM refresh
.equ DSP_DMA_MMR_H,     0xCC00501A  # DSP DMA MRAM high
.equ DSP_DMA_MMR_L,     0xCC00501C  # DSP DMA MRAM low
.equ DSP_DMA_ARAM_H,    0xCC00501E  # DSP DMA ARAM high
.equ DSP_DMA_ARAM_L,    0xCC005020  # DSP DMA ARAM low
.equ DSP_DMA_SIZE_H,    0xCC005022  # DSP DMA size high
.equ DSP_DMA_SIZE_L,    0xCC005024  # DSP DMA size low
.equ DSP_DMA_CONTROL,   0xCC005026  # DSP DMA control
.equ DSP_DMA_LEFT,      0xCC005028  # DSP DMA bytes left
.equ DSP_ACCEL_CTRL,    0xCC00502A  # DSP accelerator control
.equ DSP_ACCEL_ADPCM_GAIN, 0xCC00502C # DSP ADPCM gain
.equ DSP_ACCEL_ADPCM_PRED, 0xCC00502E # DSP ADPCM predictor/scale

# DSP control bits
.equ DSP_CTRL_RESET,    0x0800      # DSP reset
.equ DSP_CTRL_PIINT,    0x0200      # DSP processor interface interrupt
.equ DSP_CTRL_HALT,     0x0004      # DSP halt
.equ DSP_CTRL_AIDINT,   0x0002      # DSP AID interrupt
.equ DSP_CTRL_ARAM,     0x0001      # DSP ARAM enable

# ============================================================================
# Thermal Management
# ============================================================================

.equ THERMAL_STATUS,    0xCC00400C  # Thermal status register

# ============================================================================
# Constants and Useful Values
# ============================================================================

# Video timing (NTSC)
.equ VI_NTSC_CLOCK,     27000000    # 27MHz dot clock
.equ VI_LINES_NTSC,     525         # Lines per frame
.equ VI_LINES_VISIBLE,  480         # Visible lines

# Video timing (PAL)
.equ VI_PAL_CLOCK,      27000000    # 27MHz dot clock
.equ VI_LINES_PAL,      625         # Lines per frame
.equ VI_LINES_PAL_VIS,  576         # Visible lines

# CPU clock
.equ CPU_CLOCK,         486000000   # 486MHz (retail GameCube)
.equ CPU_CLOCK_DEV,     405000000   # 405MHz (development kit)

# Framebuffer formats
.equ GX_TF_RGB565,      0x00        # RGB565 format
.equ GX_TF_RGB8,        0x01        # RGB8 format
.equ GX_TF_RGBA6,       0x02        # RGBA6 format

# Texture formats
.equ GX_TF_I4,          0x00        # Intensity 4-bit
.equ GX_TF_I8,          0x01        # Intensity 8-bit
.equ GX_TF_IA4,         0x02        # Intensity+Alpha 4-bit each
.equ GX_TF_IA8,         0x03        # Intensity+Alpha 8-bit each
.equ GX_TF_RGB565,      0x04        # RGB 565
.equ GX_TF_RGB5A3,      0x05        # RGB5A3
.equ GX_TF_RGBA8,       0x06        # RGBA8
.equ GX_TF_C4,          0x08        # Color index 4-bit
.equ GX_TF_C8,          0x09        # Color index 8-bit
.equ GX_TF_C14X2,       0x0A        # Color index 14-bit
.equ GX_TF_CMPR,        0x0E        # Compressed (DXT1)

# ============================================================================
# PowerPC Special Purpose Registers
# ============================================================================

# Machine State Register (MSR) bits
.equ MSR_SF,            0x8000000000000000  # 64-bit mode (not used on GameCube)
.equ MSR_HV,            0x0000000000001000  # Hypervisor state
.equ MSR_VEC,           0x0000000002000000  # AltiVec available
.equ MSR_POW,           0x0000000000040000  # Power management enable
.equ MSR_ILE,           0x0000000000010000  # Interrupt little endian
.equ MSR_EE,            0x0000000000008000  # External interrupt enable
.equ MSR_PR,            0x0000000000004000  # Privilege level (0=supervisor)
.equ MSR_FP,            0x0000000000002000  # Floating point available
.equ MSR_ME,            0x0000000000001000  # Machine check enable
.equ MSR_FE0,           0x0000000000000800  # Floating point exception mode 0
.equ MSR_SE,            0x0000000000000400  # Single step trace enable
.equ MSR_BE,            0x0000000000000200  # Branch trace enable
.equ MSR_FE1,           0x0000000000000100  # Floating point exception mode 1
.equ MSR_IP,            0x0000000000000040  # Interrupt prefix
.equ MSR_IR,            0x0000000000000020  # Instruction relocate
.equ MSR_DR,            0x0000000000000010  # Data relocate
.equ MSR_RI,            0x0000000000000002  # Recoverable interrupt
.equ MSR_LE,            0x0000000000000001  # Little endian mode

# Special Purpose Register numbers
.equ SPR_XER,           1           # Fixed-point exception register
.equ SPR_LR,            8           # Link register
.equ SPR_CTR,           9           # Count register
.equ SPR_DSISR,         18          # DSI syndrome register
.equ SPR_DAR,           19          # Data address register
.equ SPR_DEC,           22          # Decrementer
.equ SPR_SRR0,          26          # Save/restore register 0
.equ SPR_SRR1,          27          # Save/restore register 1
.equ SPR_SPRG0,         272         # SPR general 0
.equ SPR_SPRG1,         273         # SPR general 1
.equ SPR_SPRG2,         274         # SPR general 2
.equ SPR_SPRG3,         275         # SPR general 3
.equ SPR_TBL,           284         # Time base lower
.equ SPR_TBU,           285         # Time base upper
.equ SPR_PVR,           287         # Processor version register

# Hardware Implementation Registers (HID)
.equ SPR_HID0,          1008        # Hardware implementation 0
.equ SPR_HID1,          1009        # Hardware implementation 1
.equ SPR_HID2,          1011        # Hardware implementation 2

# Memory Management Unit (MMU) registers
.equ SPR_IBAT0U,        528         # Instruction BAT 0 upper
.equ SPR_IBAT0L,        529         # Instruction BAT 0 lower
.equ SPR_IBAT1U,        530         # Instruction BAT 1 upper
.equ SPR_IBAT1L,        531         # Instruction BAT 1 lower
.equ SPR_IBAT2U,        532         # Instruction BAT 2 upper
.equ SPR_IBAT2L,        533         # Instruction BAT 2 lower
.equ SPR_IBAT3U,        534         # Instruction BAT 3 upper
.equ SPR_IBAT3L,        535         # Instruction BAT 3 lower
.equ SPR_DBAT0U,        536         # Data BAT 0 upper
.equ SPR_DBAT0L,        537         # Data BAT 0 lower
.equ SPR_DBAT1U,        538         # Data BAT 1 upper
.equ SPR_DBAT1L,        539         # Data BAT 1 lower
.equ SPR_DBAT2U,        540         # Data BAT 2 upper
.equ SPR_DBAT2L,        541         # Data BAT 2 lower
.equ SPR_DBAT3U,        542         # Data BAT 3 upper
.equ SPR_DBAT3L,        543         # Data BAT 3 lower

# BAT register bit fields
.equ BAT_BEPI_MASK,     0xFFFE0000  # Block effective page index
.equ BAT_BL_MASK,       0x00001FFC  # Block length mask
.equ BAT_VS,            0x00000002  # Supervisor valid
.equ BAT_VP,            0x00000001  # Problem state valid
.equ BAT_BRPN_MASK,     0xFFFE0000  # Block real page number
.equ BAT_WIMG_MASK,     0x00000078  # Write-through, cache inhibit, etc.
.equ BAT_PP_MASK,       0x00000003  # Protection bits

# ============================================================================
# Exception Vectors
# ============================================================================

.equ EXC_RESET,         0x00000100  # System reset
.equ EXC_MACHINE_CHECK, 0x00000200  # Machine check
.equ EXC_DSI,           0x00000300  # Data storage interrupt
.equ EXC_ISI,           0x00000400  # Instruction storage interrupt
.equ EXC_EXTERNAL,      0x00000500  # External interrupt
.equ EXC_ALIGNMENT,     0x00000600  # Alignment
.equ EXC_PROGRAM,       0x00000700  # Program
.equ EXC_FPU,           0x00000800  # Floating point unavailable
.equ EXC_DECREMENTER,   0x00000900  # Decrementer
.equ EXC_SYSTEM_CALL,   0x00000C00  # System call
.equ EXC_TRACE,         0x00000D00  # Trace
.equ EXC_PERF_MONITOR,  0x00000F00  # Performance monitor
.equ EXC_IABR,          0x00001300  # Instruction address breakpoint
.equ EXC_THERMAL,       0x00001700  # Thermal management interrupt

# ============================================================================
# Cache Constants
# ============================================================================

.equ ICACHE_SIZE,       32768       # 32KB instruction cache
.equ DCACHE_SIZE,       32768       # 32KB data cache
.equ CACHE_LINE_SIZE,   32          # 32 bytes per cache line
.equ L2_CACHE_SIZE,     262144      # 256KB L2 cache

# ============================================================================
# GameCube Disc Format
# ============================================================================

.equ GC_DISC_HEADER_SIZE, 0x440     # GameCube disc header size
.equ GC_MAGIC,          0xC2339F3D  # GameCube disc magic number