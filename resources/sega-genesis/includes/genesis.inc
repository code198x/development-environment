; genesis.inc - Sega Genesis/Mega Drive Hardware Definitions
; For use with vasm or other 68000 assemblers

; ============================================================================
; Memory Map
; ============================================================================

; ROM
ROM_START       EQU $000000 ; ROM start (up to 4MB)
ROM_END         EQU $3FFFFF ; ROM end (4MB maximum)

; RAM
RAM_START       EQU $FF0000 ; Work RAM start (64KB)
RAM_END         EQU $FFFFFF ; Work RAM end

; Z80 RAM (shared with 68000 via bus control)
Z80_RAM_START   EQU $A00000 ; Z80 RAM start (8KB)
Z80_RAM_END     EQU $A01FFF ; Z80 RAM end

; VDP (Video Display Processor)
VDP_DATA        EQU $C00000 ; VDP data port
VDP_CTRL        EQU $C00004 ; VDP control port
VDP_HV_COUNTER  EQU $C00008 ; HV counter
VDP_PSG         EQU $C00011 ; PSG port (through VDP)

; I/O Ports
IO_PCBVER       EQU $A10001 ; PCB version
IO_CT1_DATA     EQU $A10003 ; Controller 1 data
IO_CT2_DATA     EQU $A10005 ; Controller 2 data
IO_EXT_DATA     EQU $A10007 ; Extension port data
IO_CT1_CTRL     EQU $A10009 ; Controller 1 control
IO_CT2_CTRL     EQU $A1000B ; Controller 2 control
IO_EXT_CTRL     EQU $A1000D ; Extension port control
IO_CT1_SERIAL   EQU $A1000F ; Controller 1 serial data
IO_CT2_SERIAL   EQU $A10011 ; Controller 2 serial data
IO_EXT_SERIAL   EQU $A10013 ; Extension port serial data

; Z80 Control
Z80_BUS_REQ     EQU $A11100 ; Z80 bus request
Z80_RESET       EQU $A11200 ; Z80 reset

; ============================================================================
; VDP Registers (0-23)
; ============================================================================

VDP_R0          EQU $8000   ; Mode register 1
VDP_R1          EQU $8100   ; Mode register 2
VDP_R2          EQU $8200   ; Scroll A name table
VDP_R3          EQU $8300   ; Window name table
VDP_R4          EQU $8400   ; Scroll B name table
VDP_R5          EQU $8500   ; Sprite table
VDP_R6          EQU $8600   ; Background color/priority
VDP_R7          EQU $8700   ; Mode register 3
VDP_R8          EQU $8800   ; Mode register 4
VDP_R9          EQU $8900   ; Mode register 5
VDP_R10         EQU $8A00   ; H-interrupt counter
VDP_R11         EQU $8B00   ; Mode register 6
VDP_R12         EQU $8C00   ; Mode register 7
VDP_R13         EQU $8D00   ; H-scroll table
VDP_R14         EQU $8E00   ; Name table pattern base
VDP_R15         EQU $8F00   ; Auto-increment
VDP_R16         EQU $9000   ; Scroll size
VDP_R17         EQU $9100   ; Window H position
VDP_R18         EQU $9200   ; Window V position
VDP_R19         EQU $9300   ; DMA length low
VDP_R20         EQU $9400   ; DMA length high
VDP_R21         EQU $9500   ; DMA source low
VDP_R22         EQU $9600   ; DMA source mid
VDP_R23         EQU $9700   ; DMA source high/control

; Mode register 1 bits
M1_DISPLAY_OFF  EQU $00     ; Display off
M1_DISPLAY_ON   EQU $40     ; Display on
M1_VINT_OFF     EQU $00     ; V-interrupt off
M1_VINT_ON      EQU $20     ; V-interrupt on
M1_DMA_OFF      EQU $00     ; DMA off
M1_DMA_ON       EQU $10     ; DMA on
M1_V28_OFF      EQU $00     ; 28-cell height
M1_V28_ON       EQU $08     ; 30-cell height
M1_FREEZE_OFF   EQU $00     ; HV counter normal
M1_FREEZE_ON    EQU $02     ; HV counter freeze

; Mode register 2 bits
M2_DISPLAY_OFF  EQU $00     ; Display off
M2_DISPLAY_ON   EQU $40     ; Display on
M2_VINT_OFF     EQU $00     ; V-interrupt off
M2_VINT_ON      EQU $20     ; V-interrupt on
M2_DMA_OFF      EQU $00     ; DMA off
M2_DMA_ON       EQU $10     ; DMA on
M2_V30_OFF      EQU $00     ; 28-cell height
M2_V30_ON       EQU $08     ; 30-cell height
M2_SMS_MODE     EQU $04     ; SMS mode
M2_128K_VRAM    EQU $01     ; 128KB VRAM mode

; ============================================================================
; VDP Status Register Bits
; ============================================================================

STAT_FIFO_EMPTY EQU $200    ; FIFO empty
STAT_FIFO_FULL  EQU $100    ; FIFO full
STAT_VINT       EQU $80     ; V-interrupt pending
STAT_SPRITE_OVF EQU $40     ; Sprite overflow
STAT_COLLISION  EQU $20     ; Sprite collision
STAT_ODD_FRAME  EQU $10     ; Odd frame (interlace)
STAT_VBLANK     EQU $08     ; V-blank active
STAT_HBLANK     EQU $04     ; H-blank active
STAT_DMA_BUSY   EQU $02     ; DMA in progress
STAT_PAL        EQU $01     ; PAL mode

; ============================================================================
; VDP Commands
; ============================================================================

; VDP access modes
VDP_CMD_READ    EQU $00000000 ; VRAM read
VDP_CMD_WRITE   EQU $40000000 ; VRAM write
VDP_CMD_CRAM_R  EQU $00000020 ; CRAM read
VDP_CMD_CRAM_W  EQU $C0000000 ; CRAM write
VDP_CMD_VSRAM_R EQU $00000010 ; VSRAM read
VDP_CMD_VSRAM_W EQU $40000010 ; VSRAM write

; DMA modes
DMA_VRAM_COPY   EQU $C0000080 ; VRAM to VRAM copy
DMA_FILL        EQU $80000080 ; VRAM fill
DMA_M68K_COPY   EQU $40000080 ; 68000 to VRAM copy

; ============================================================================
; VRAM Layout (typical arrangement)
; ============================================================================

; Pattern tables
TILES_START     EQU $0000   ; Start of tile patterns
TILES_SIZE      EQU $6000   ; Size for 768 tiles (48KB)

; Name tables
SCROLL_A        EQU $C000   ; Scroll A name table (32x32)
SCROLL_B        EQU $E000   ; Scroll B name table (32x32)
WINDOW          EQU $A000   ; Window name table
SPRITES         EQU $F000   ; Sprite attribute table

; H-scroll table
HSCROLL_TABLE   EQU $FC00   ; Horizontal scroll table

; ============================================================================
; Sprite Attributes
; ============================================================================

; Sprite attribute structure (8 bytes per sprite)
SPR_Y           EQU 0       ; Y position (word)
SPR_SIZE        EQU 2       ; Size and link (byte)
SPR_PATTERN     EQU 3       ; Pattern number and attributes (byte)
SPR_X           EQU 4       ; X position (word)

; Sprite sizes
SPR_SIZE_1x1    EQU $00     ; 8x8 pixels
SPR_SIZE_2x1    EQU $01     ; 16x8 pixels
SPR_SIZE_1x2    EQU $04     ; 8x16 pixels
SPR_SIZE_2x2    EQU $05     ; 16x16 pixels
SPR_SIZE_3x1    EQU $02     ; 24x8 pixels
SPR_SIZE_1x3    EQU $08     ; 8x24 pixels
SPR_SIZE_3x3    EQU $0A     ; 24x24 pixels
SPR_SIZE_4x1    EQU $03     ; 32x8 pixels
SPR_SIZE_1x4    EQU $0C     ; 8x32 pixels
SPR_SIZE_4x4    EQU $0F     ; 32x32 pixels

; Sprite attribute bits
SPR_PAL         EQU $6000   ; Palette (bits 13-14)
SPR_PRI         EQU $8000   ; Priority
SPR_HFLIP       EQU $0800   ; Horizontal flip
SPR_VFLIP       EQU $1000   ; Vertical flip

; ============================================================================
; Controller Input
; ============================================================================

; Standard 3-button controller bits
BTN_UP          EQU $01
BTN_DOWN        EQU $02
BTN_LEFT        EQU $04
BTN_RIGHT       EQU $08
BTN_B           EQU $10
BTN_C           EQU $20
BTN_A           EQU $40
BTN_START       EQU $80

; 6-button controller additional bits (requires special read sequence)
BTN_Z           EQU $01     ; (second read)
BTN_Y           EQU $02     ; (second read)
BTN_X           EQU $04     ; (second read)
BTN_MODE        EQU $08     ; (second read)

; ============================================================================
; Colors and Palettes
; ============================================================================

; Color format: $0BGR (4 bits per component)
COLOR_BLACK     EQU $0000
COLOR_WHITE     EQU $0EEE
COLOR_RED       EQU $000E
COLOR_GREEN     EQU $00E0
COLOR_BLUE      EQU $0E00
COLOR_YELLOW    EQU $00EE
COLOR_CYAN      EQU $0EE0
COLOR_MAGENTA   EQU $0E0E

; Palette indices
PAL0            EQU $0000   ; Palette 0
PAL1            EQU $2000   ; Palette 1
PAL2            EQU $4000   ; Palette 2
PAL3            EQU $6000   ; Palette 3

; ============================================================================
; Sound (PSG) Registers
; ============================================================================

; PSG register format: write to VDP_PSG
PSG_CH0_FREQ    EQU $80     ; Channel 0 frequency
PSG_CH0_VOL     EQU $90     ; Channel 0 volume
PSG_CH1_FREQ    EQU $A0     ; Channel 1 frequency
PSG_CH1_VOL     EQU $B0     ; Channel 1 volume
PSG_CH2_FREQ    EQU $C0     ; Channel 2 frequency
PSG_CH2_VOL     EQU $D0     ; Channel 2 volume
PSG_CH3_CTRL    EQU $E0     ; Channel 3 noise control
PSG_CH3_VOL     EQU $F0     ; Channel 3 noise volume

; Volume levels (0 = loudest, 15 = off)
PSG_VOL_MAX     EQU $00
PSG_VOL_OFF     EQU $0F

; ============================================================================
; Interrupt Vectors
; ============================================================================

VEC_STACK       EQU $000000 ; Initial stack pointer
VEC_RESET       EQU $000004 ; Reset vector
VEC_BUS_ERROR   EQU $000008 ; Bus error
VEC_ADDR_ERROR  EQU $00000C ; Address error
VEC_ILLEGAL     EQU $000010 ; Illegal instruction
VEC_DIVIDE_ZERO EQU $000014 ; Division by zero
VEC_CHK         EQU $000018 ; CHK instruction
VEC_TRAPV       EQU $00001C ; TRAPV instruction
VEC_PRIVILEGE   EQU $000020 ; Privilege violation
VEC_TRACE       EQU $000024 ; Trace
VEC_LINE_A      EQU $000028 ; Line A emulator
VEC_LINE_F      EQU $00002C ; Line F emulator
VEC_EXTERNAL    EQU $000068 ; External interrupt
VEC_LEVEL_1     EQU $000064 ; Level 1 interrupt
VEC_LEVEL_2     EQU $000068 ; Level 2 interrupt (external)
VEC_LEVEL_3     EQU $00006C ; Level 3 interrupt
VEC_LEVEL_4     EQU $000070 ; Level 4 interrupt (horizontal)
VEC_LEVEL_5     EQU $000074 ; Level 5 interrupt
VEC_LEVEL_6     EQU $000078 ; Level 6 interrupt (vertical)
VEC_LEVEL_7     EQU $00007C ; Level 7 interrupt

; Genesis-specific vectors
VEC_USER        EQU $000080 ; Start of user vectors