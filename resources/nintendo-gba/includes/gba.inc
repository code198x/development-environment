@ gba.inc - Game Boy Advance Hardware Definitions
@ For use with ARM assemblers (gas, armips, etc.)
@ Comprehensive memory map, I/O registers, and constants

@ ============================================================================
@ Memory Map
@ ============================================================================

@ System areas
.equ BIOS_ROM,          0x00000000  @ BIOS ROM (16KB)
.equ EWRAM,             0x02000000  @ External Work RAM (256KB)
.equ IWRAM,             0x03000000  @ Internal Work RAM (32KB)
.equ IO_REGISTERS,      0x04000000  @ I/O Registers
.equ PALETTE_RAM,       0x05000000  @ BG/OBJ Palette RAM (1KB)
.equ VRAM,              0x06000000  @ Video RAM (96KB)
.equ OAM,               0x07000000  @ OBJ Attribute Memory (1KB)

@ Cartridge areas
.equ ROM_WS0,           0x08000000  @ ROM Wait State 0 (32MB)
.equ ROM_WS1,           0x0A000000  @ ROM Wait State 1 (32MB)
.equ ROM_WS2,           0x0C000000  @ ROM Wait State 2 (32MB)
.equ SRAM,              0x0E000000  @ SRAM (64KB max)

@ Memory sizes
.equ EWRAM_SIZE,        0x40000     @ 256KB
.equ IWRAM_SIZE,        0x8000      @ 32KB
.equ VRAM_SIZE,         0x18000     @ 96KB
.equ OAM_SIZE,          0x400       @ 1KB
.equ PALETTE_SIZE,      0x400       @ 1KB

@ ============================================================================
@ LCD I/O Registers
@ ============================================================================

@ Display control
.equ REG_DISPCNT,       0x04000000  @ Display control
.equ REG_GREENSWAP,     0x04000002  @ Green swap (undocumented)
.equ REG_DISPSTAT,      0x04000004  @ Display status
.equ REG_VCOUNT,        0x04000006  @ Vertical counter
.equ REG_BG0CNT,        0x04000008  @ BG0 control
.equ REG_BG1CNT,        0x0400000A  @ BG1 control
.equ REG_BG2CNT,        0x0400000C  @ BG2 control
.equ REG_BG3CNT,        0x0400000E  @ BG3 control

@ Background scrolling
.equ REG_BG0HOFS,       0x04000010  @ BG0 horizontal offset
.equ REG_BG0VOFS,       0x04000012  @ BG0 vertical offset
.equ REG_BG1HOFS,       0x04000014  @ BG1 horizontal offset
.equ REG_BG1VOFS,       0x04000016  @ BG1 vertical offset
.equ REG_BG2HOFS,       0x04000018  @ BG2 horizontal offset
.equ REG_BG2VOFS,       0x0400001A  @ BG2 vertical offset
.equ REG_BG3HOFS,       0x0400001C  @ BG3 horizontal offset
.equ REG_BG3VOFS,       0x0400001E  @ BG3 vertical offset

@ Background rotation/scaling (BG2, BG3)
.equ REG_BG2PA,         0x04000020  @ BG2 rotation/scaling parameter A
.equ REG_BG2PB,         0x04000022  @ BG2 rotation/scaling parameter B
.equ REG_BG2PC,         0x04000024  @ BG2 rotation/scaling parameter C
.equ REG_BG2PD,         0x04000026  @ BG2 rotation/scaling parameter D
.equ REG_BG2X,          0x04000028  @ BG2 reference point X
.equ REG_BG2Y,          0x0400002C  @ BG2 reference point Y
.equ REG_BG3PA,         0x04000030  @ BG3 rotation/scaling parameter A
.equ REG_BG3PB,         0x04000032  @ BG3 rotation/scaling parameter B
.equ REG_BG3PC,         0x04000034  @ BG3 rotation/scaling parameter C
.equ REG_BG3PD,         0x04000036  @ BG3 rotation/scaling parameter D
.equ REG_BG3X,          0x04000038  @ BG3 reference point X
.equ REG_BG3Y,          0x0400003C  @ BG3 reference point Y

@ Window registers
.equ REG_WIN0H,         0x04000040  @ Window 0 horizontal dimensions
.equ REG_WIN1H,         0x04000042  @ Window 1 horizontal dimensions
.equ REG_WIN0V,         0x04000044  @ Window 0 vertical dimensions
.equ REG_WIN1V,         0x04000046  @ Window 1 vertical dimensions
.equ REG_WININ,         0x04000048  @ Inside window control
.equ REG_WINOUT,        0x0400004A  @ Outside window control

@ Special effects
.equ REG_MOSAIC,        0x0400004C  @ Mosaic effect
.equ REG_BLDCNT,        0x04000050  @ Color special effects control
.equ REG_BLDALPHA,      0x04000052  @ Alpha blending coefficients
.equ REG_BLDY,          0x04000054  @ Brightness coefficient

@ ============================================================================
@ Sound I/O Registers
@ ============================================================================

@ Sound channel 1 (square wave with sweep)
.equ REG_SOUND1CNT_L,   0x04000060  @ Channel 1 sweep control
.equ REG_SOUND1CNT_H,   0x04000062  @ Channel 1 duty/length/envelope
.equ REG_SOUND1CNT_X,   0x04000064  @ Channel 1 frequency/control

@ Sound channel 2 (square wave)
.equ REG_SOUND2CNT_L,   0x04000068  @ Channel 2 duty/length/envelope
.equ REG_SOUND2CNT_H,   0x0400006C  @ Channel 2 frequency/control

@ Sound channel 3 (wave output)
.equ REG_SOUND3CNT_L,   0x04000070  @ Channel 3 wave select
.equ REG_SOUND3CNT_H,   0x04000072  @ Channel 3 length/volume
.equ REG_SOUND3CNT_X,   0x04000074  @ Channel 3 frequency/control

@ Sound channel 4 (noise)
.equ REG_SOUND4CNT_L,   0x04000078  @ Channel 4 length/envelope
.equ REG_SOUND4CNT_H,   0x0400007C  @ Channel 4 noise parameters/control

@ Sound control
.equ REG_SOUNDCNT_L,    0x04000080  @ Sound volume/enable
.equ REG_SOUNDCNT_H,    0x04000082  @ DMA sound control/mixing
.equ REG_SOUNDCNT_X,    0x04000084  @ Sound on/off

@ Sound status
.equ REG_SOUNDBIAS,     0x04000088  @ Sound PWM control

@ Wave RAM
.equ REG_WAVE_RAM,      0x04000090  @ Channel 3 wave pattern RAM (16 bytes)

@ Direct sound
.equ REG_FIFO_A,        0x040000A0  @ Direct sound channel A FIFO
.equ REG_FIFO_B,        0x040000A4  @ Direct sound channel B FIFO

@ ============================================================================
@ DMA Registers
@ ============================================================================

@ DMA channel 0
.equ REG_DMA0SAD,       0x040000B0  @ DMA0 source address
.equ REG_DMA0DAD,       0x040000B4  @ DMA0 destination address
.equ REG_DMA0CNT_L,     0x040000B8  @ DMA0 word count
.equ REG_DMA0CNT_H,     0x040000BA  @ DMA0 control

@ DMA channel 1
.equ REG_DMA1SAD,       0x040000BC  @ DMA1 source address
.equ REG_DMA1DAD,       0x040000C0  @ DMA1 destination address
.equ REG_DMA1CNT_L,     0x040000C4  @ DMA1 word count
.equ REG_DMA1CNT_H,     0x040000C6  @ DMA1 control

@ DMA channel 2
.equ REG_DMA2SAD,       0x040000C8  @ DMA2 source address
.equ REG_DMA2DAD,       0x040000CC  @ DMA2 destination address
.equ REG_DMA2CNT_L,     0x040000D0  @ DMA2 word count
.equ REG_DMA2CNT_H,     0x040000D2  @ DMA2 control

@ DMA channel 3
.equ REG_DMA3SAD,       0x040000D4  @ DMA3 source address
.equ REG_DMA3DAD,       0x040000D8  @ DMA3 destination address
.equ REG_DMA3CNT_L,     0x040000DC  @ DMA3 word count
.equ REG_DMA3CNT_H,     0x040000DE  @ DMA3 control

@ ============================================================================
@ Timer Registers
@ ============================================================================

.equ REG_TM0CNT_L,      0x04000100  @ Timer 0 counter/reload
.equ REG_TM0CNT_H,      0x04000102  @ Timer 0 control
.equ REG_TM1CNT_L,      0x04000104  @ Timer 1 counter/reload
.equ REG_TM1CNT_H,      0x04000106  @ Timer 1 control
.equ REG_TM2CNT_L,      0x04000108  @ Timer 2 counter/reload
.equ REG_TM2CNT_H,      0x0400010A  @ Timer 2 control
.equ REG_TM3CNT_L,      0x0400010C  @ Timer 3 counter/reload
.equ REG_TM3CNT_H,      0x0400010E  @ Timer 3 control

@ ============================================================================
@ Serial Communication
@ ============================================================================

.equ REG_SIODATA32,     0x04000120  @ Serial data (32 bit mode)
.equ REG_SIOMULTI0,     0x04000120  @ Serial data 0 (multi-player mode)
.equ REG_SIOMULTI1,     0x04000122  @ Serial data 1 (multi-player mode)
.equ REG_SIOMULTI2,     0x04000124  @ Serial data 2 (multi-player mode)
.equ REG_SIOMULTI3,     0x04000126  @ Serial data 3 (multi-player mode)
.equ REG_SIOCNT,        0x04000128  @ Serial control
.equ REG_SIOMLT_SEND,   0x0400012A  @ Serial data (local of multi-player)
.equ REG_SIODATA8,      0x0400012A  @ Serial data (8 bit mode)

@ ============================================================================
@ Keypad Input
@ ============================================================================

.equ REG_KEYINPUT,      0x04000130  @ Key status
.equ REG_KEYCNT,        0x04000132  @ Key interrupt control

@ ============================================================================
@ Joybus Communication
@ ============================================================================

.equ REG_RCNT,          0x04000134  @ SIO mode select/general purpose data
.equ REG_JOYCNT,        0x04000140  @ JOY bus control
.equ REG_JOY_RECV,      0x04000150  @ JOY bus receive data
.equ REG_JOY_TRANS,     0x04000154  @ JOY bus transmit data
.equ REG_JOYSTAT,       0x04000158  @ JOY bus receive status

@ ============================================================================
@ Interrupt Control
@ ============================================================================

.equ REG_IE,            0x04000200  @ Interrupt enable
.equ REG_IF,            0x04000202  @ Interrupt request flags
.equ REG_WAITCNT,       0x04000204  @ Game Pak waitstate control
.equ REG_IME,           0x04000208  @ Interrupt master enable

@ ============================================================================
@ System Control
@ ============================================================================

.equ REG_POSTFLG,       0x04000300  @ Undocumented - post boot flag
.equ REG_HALTCNT,       0x04000301  @ Undocumented - power down control

@ ============================================================================
@ Display Control (DISPCNT) Bits
@ ============================================================================

.equ DCNT_MODE0,        0x0000      @ Video mode 0
.equ DCNT_MODE1,        0x0001      @ Video mode 1
.equ DCNT_MODE2,        0x0002      @ Video mode 2
.equ DCNT_MODE3,        0x0003      @ Video mode 3
.equ DCNT_MODE4,        0x0004      @ Video mode 4
.equ DCNT_MODE5,        0x0005      @ Video mode 5
.equ DCNT_GB,           0x0008      @ Game Boy mode
.equ DCNT_PAGE,         0x0010      @ Page select (modes 4,5)
.equ DCNT_OAM_HBL,      0x0020      @ Allow access to OAM in H-Blank
.equ DCNT_OBJ_1D,       0x0040      @ OBJ character VRAM mapping
.equ DCNT_BLANK,        0x0080      @ Force screen blank
.equ DCNT_BG0,          0x0100      @ Enable BG0
.equ DCNT_BG1,          0x0200      @ Enable BG1
.equ DCNT_BG2,          0x0400      @ Enable BG2
.equ DCNT_BG3,          0x0800      @ Enable BG3
.equ DCNT_OBJ,          0x1000      @ Enable objects
.equ DCNT_WIN0,         0x2000      @ Enable window 0
.equ DCNT_WIN1,         0x4000      @ Enable window 1
.equ DCNT_WINOBJ,       0x8000      @ Enable object window

@ ============================================================================
@ Display Status (DISPSTAT) Bits
@ ============================================================================

.equ DSTAT_IN_VBL,      0x0001      @ Currently in VBlank
.equ DSTAT_IN_HBL,      0x0002      @ Currently in HBlank
.equ DSTAT_IN_VCT,      0x0004      @ VCount trigger flag
.equ DSTAT_VBL_IRQ,     0x0008      @ VBlank interrupt request
.equ DSTAT_HBL_IRQ,     0x0010      @ HBlank interrupt request
.equ DSTAT_VCT_IRQ,     0x0020      @ VCount interrupt request
.equ DSTAT_VCT_MASK,    0xFF00      @ VCount trigger value

@ ============================================================================
@ Background Control Bits
@ ============================================================================

.equ BG_PRIORITY_0,     0x0000      @ Priority 0 (highest)
.equ BG_PRIORITY_1,     0x0001      @ Priority 1
.equ BG_PRIORITY_2,     0x0002      @ Priority 2
.equ BG_PRIORITY_3,     0x0003      @ Priority 3 (lowest)
.equ BG_CBB_0,          0x0000      @ Character base block 0
.equ BG_CBB_1,          0x0004      @ Character base block 1
.equ BG_CBB_2,          0x0008      @ Character base block 2
.equ BG_CBB_3,          0x000C      @ Character base block 3
.equ BG_MOSAIC,         0x0040      @ Mosaic enable
.equ BG_4BPP,           0x0000      @ 4 bits per pixel
.equ BG_8BPP,           0x0080      @ 8 bits per pixel
.equ BG_SBB_0,          0x0000      @ Screen base block 0
.equ BG_SBB_1,          0x0100      @ Screen base block 1
.equ BG_SBB_2,          0x0200      @ Screen base block 2
.equ BG_SBB_3,          0x0300      @ Screen base block 3
.equ BG_WRAP,           0x2000      @ Affine wrap enable
.equ BG_SIZE_0,         0x0000      @ Background size (depends on mode)
.equ BG_SIZE_1,         0x4000      @ Background size
.equ BG_SIZE_2,         0x8000      @ Background size
.equ BG_SIZE_3,         0xC000      @ Background size

@ ============================================================================
@ Object Attribute Memory (OAM) Structure
@ ============================================================================

@ OAM entry size
.equ OBJ_ATTR_SIZE,     8           @ 8 bytes per object

@ Attribute 0 bits
.equ ATTR0_Y_MASK,      0x00FF      @ Y coordinate
.equ ATTR0_REG,         0x0000      @ Regular object
.equ ATTR0_AFF,         0x0100      @ Affine object
.equ ATTR0_HIDE,        0x0200      @ Hidden object
.equ ATTR0_AFF_DBL,     0x0300      @ Affine object (double size)
.equ ATTR0_BLEND,       0x0400      @ Enable blending
.equ ATTR0_WIN,         0x0800      @ Object window
.equ ATTR0_MOSAIC,      0x1000      @ Mosaic enable
.equ ATTR0_4BPP,        0x0000      @ 4 bits per pixel
.equ ATTR0_8BPP,        0x2000      @ 8 bits per pixel
.equ ATTR0_SQUARE,      0x0000      @ Square shape
.equ ATTR0_WIDE,        0x4000      @ Wide shape
.equ ATTR0_TALL,        0x8000      @ Tall shape

@ Attribute 1 bits
.equ ATTR1_X_MASK,      0x01FF      @ X coordinate
.equ ATTR1_AFF_ID_MASK, 0x3E00      @ Affine parameter ID
.equ ATTR1_HFLIP,       0x1000      @ Horizontal flip
.equ ATTR1_VFLIP,       0x2000      @ Vertical flip
.equ ATTR1_SIZE_0,      0x0000      @ Size 0
.equ ATTR1_SIZE_1,      0x4000      @ Size 1
.equ ATTR1_SIZE_2,      0x8000      @ Size 2
.equ ATTR1_SIZE_3,      0xC000      @ Size 3

@ Attribute 2 bits
.equ ATTR2_ID_MASK,     0x03FF      @ Character name
.equ ATTR2_PRIO_0,      0x0000      @ Priority 0 (highest)
.equ ATTR2_PRIO_1,      0x0400      @ Priority 1
.equ ATTR2_PRIO_2,      0x0800      @ Priority 2
.equ ATTR2_PRIO_3,      0x0C00      @ Priority 3 (lowest)
.equ ATTR2_PALBANK_MASK, 0xF000     @ Palette bank (4bpp mode)

@ ============================================================================
@ Key Input Bits
@ ============================================================================

.equ KEY_A,             0x0001      @ A button
.equ KEY_B,             0x0002      @ B button
.equ KEY_SELECT,        0x0004      @ SELECT button
.equ KEY_START,         0x0008      @ START button
.equ KEY_RIGHT,         0x0010      @ RIGHT on D-pad
.equ KEY_LEFT,          0x0020      @ LEFT on D-pad
.equ KEY_UP,            0x0040      @ UP on D-pad
.equ KEY_DOWN,          0x0080      @ DOWN on D-pad
.equ KEY_R,             0x0100      @ R shoulder button
.equ KEY_L,             0x0200      @ L shoulder button

@ Key combinations
.equ KEY_MASK,          0x03FF      @ All keys
.equ KEY_FIRE,          (KEY_A | KEY_B)
.equ KEY_DIR,           (KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT)
.equ KEY_SHOULDER,      (KEY_L | KEY_R)

@ ============================================================================
@ Interrupt Bits
@ ============================================================================

.equ IRQ_VBLANK,        0x0001      @ VBlank interrupt
.equ IRQ_HBLANK,        0x0002      @ HBlank interrupt
.equ IRQ_VCOUNT,        0x0004      @ VCount match interrupt
.equ IRQ_TIMER0,        0x0008      @ Timer 0 overflow
.equ IRQ_TIMER1,        0x0010      @ Timer 1 overflow
.equ IRQ_TIMER2,        0x0020      @ Timer 2 overflow
.equ IRQ_TIMER3,        0x0040      @ Timer 3 overflow
.equ IRQ_SERIAL,        0x0080      @ Serial communication
.equ IRQ_DMA0,          0x0100      @ DMA channel 0
.equ IRQ_DMA1,          0x0200      @ DMA channel 1
.equ IRQ_DMA2,          0x0400      @ DMA channel 2
.equ IRQ_DMA3,          0x0800      @ DMA channel 3
.equ IRQ_KEYPAD,        0x1000      @ Keypad
.equ IRQ_GAMEPAK,       0x2000      @ Game Pak (external IRQ)

@ ============================================================================
@ DMA Control Bits
@ ============================================================================

.equ DMA_DST_INC,       0x0000      @ Destination increment
.equ DMA_DST_DEC,       0x0020      @ Destination decrement
.equ DMA_DST_FIXED,     0x0040      @ Destination fixed
.equ DMA_DST_RELOAD,    0x0060      @ Destination increment/reload
.equ DMA_SRC_INC,       0x0000      @ Source increment
.equ DMA_SRC_DEC,       0x0080      @ Source decrement
.equ DMA_SRC_FIXED,     0x0100      @ Source fixed
.equ DMA_REPEAT,        0x0200      @ Repeat DMA
.equ DMA_16,            0x0000      @ 16-bit transfer
.equ DMA_32,            0x0400      @ 32-bit transfer
.equ DMA_AT_NOW,        0x0000      @ Start immediately
.equ DMA_AT_VBLANK,     0x1000      @ Start at VBlank
.equ DMA_AT_HBLANK,     0x2000      @ Start at HBlank
.equ DMA_AT_REFRESH,    0x3000      @ Start at display sync
.equ DMA_IRQ,           0x4000      @ Interrupt when complete
.equ DMA_ON,            0x8000      @ Enable DMA

@ ============================================================================
@ Timer Control Bits
@ ============================================================================

.equ TM_FREQ_1,         0x0000      @ Frequency Fosc/1
.equ TM_FREQ_64,        0x0001      @ Frequency Fosc/64
.equ TM_FREQ_256,       0x0002      @ Frequency Fosc/256
.equ TM_FREQ_1024,      0x0003      @ Frequency Fosc/1024
.equ TM_CASCADE,        0x0004      @ Cascade mode
.equ TM_IRQ,            0x0040      @ Interrupt enable
.equ TM_ON,             0x0080      @ Timer enable

@ ============================================================================
@ Screen Dimensions
@ ============================================================================

.equ SCREEN_WIDTH,      240         @ Screen width in pixels
.equ SCREEN_HEIGHT,     160         @ Screen height in pixels
.equ SCREEN_SIZE,       (SCREEN_WIDTH * SCREEN_HEIGHT)

@ Mode 3/5 specific
.equ M3_WIDTH,          240         @ Mode 3 width
.equ M3_HEIGHT,         160         @ Mode 3 height
.equ M5_WIDTH,          160         @ Mode 5 width
.equ M5_HEIGHT,         128         @ Mode 5 height

@ ============================================================================
@ Memory Addresses for Different Areas
@ ============================================================================

@ VRAM layout
.equ BG_TILE_BASE_0,    (VRAM + 0x0000)     @ Background tile base 0
.equ BG_TILE_BASE_1,    (VRAM + 0x4000)     @ Background tile base 1
.equ BG_TILE_BASE_2,    (VRAM + 0x8000)     @ Background tile base 2
.equ BG_TILE_BASE_3,    (VRAM + 0xC000)     @ Background tile base 3

.equ BG_MAP_BASE_0,     (VRAM + 0x0000)     @ Background map base 0
.equ BG_MAP_BASE_1,     (VRAM + 0x0800)     @ Background map base 1
.equ BG_MAP_BASE_2,     (VRAM + 0x1000)     @ Background map base 2
.equ BG_MAP_BASE_3,     (VRAM + 0x1800)     @ Background map base 3

.equ OBJ_TILE_BASE,     (VRAM + 0x10000)    @ Object tile base
.equ MODE3_FRAME_0,     (VRAM + 0x0000)     @ Mode 3 frame buffer
.equ MODE4_FRAME_0,     (VRAM + 0x0000)     @ Mode 4 frame 0
.equ MODE4_FRAME_1,     (VRAM + 0xA000)     @ Mode 4 frame 1
.equ MODE5_FRAME_0,     (VRAM + 0x0000)     @ Mode 5 frame 0
.equ MODE5_FRAME_1,     (VRAM + 0xA000)     @ Mode 5 frame 1

@ Palette layout
.equ BG_PALETTE,        (PALETTE_RAM + 0x000)   @ Background palette (256 colors)
.equ OBJ_PALETTE,       (PALETTE_RAM + 0x200)   @ Object palette (256 colors)

@ ============================================================================
@ Common Colors (15-bit RGB)
@ ============================================================================

.equ RGB15,             (1 << 15)   @ 15-bit RGB marker
.equ RGB_BLACK,         0x0000      @ Black
.equ RGB_WHITE,         0x7FFF      @ White
.equ RGB_RED,           0x001F      @ Red
.equ RGB_GREEN,         0x03E0      @ Green
.equ RGB_BLUE,          0x7C00      @ Blue
.equ RGB_YELLOW,        (RGB_RED | RGB_GREEN)
.equ RGB_CYAN,          (RGB_GREEN | RGB_BLUE)
.equ RGB_MAGENTA,       (RGB_RED | RGB_BLUE)