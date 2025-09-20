; nes.inc - Nintendo Entertainment System Memory Map and Hardware Registers
; For use with ca65 (cc65 suite) or other 6502 assemblers

; ============================================================================
; CPU Memory Map
; ============================================================================

; Zero Page (fast RAM)
ZP_START        = $0000
ZP_END          = $00FF

; Stack
STACK_START     = $0100
STACK_END       = $01FF

; RAM (general purpose)
RAM_START       = $0200
RAM_END         = $07FF

; RAM Mirrors (avoid using)
MIRROR_START    = $0800
MIRROR_END      = $1FFF

; ============================================================================
; PPU (Picture Processing Unit) Registers - $2000-$2007
; ============================================================================

; PPU Control Registers (write)
PPU_CTRL        = $2000  ; VPHB SINN
                          ; V: NMI enable
                          ; P: PPU master/slave
                          ; H: Sprite height (0=8x8, 1=8x16)
                          ; B: Background tile select
                          ; S: Sprite tile select
                          ; I: Increment mode (0=+1, 1=+32)
                          ; NN: Base nametable address

PPU_MASK        = $2001  ; BGRs bMmG
                          ; B: Emphasize blue
                          ; G: Emphasize green
                          ; R: Emphasize red
                          ; s: Show sprites
                          ; b: Show background
                          ; M: Show sprites in leftmost 8 pixels
                          ; m: Show background in leftmost 8 pixels
                          ; G: Grayscale

; PPU Status (read)
PPU_STATUS      = $2002  ; VSO- ----
                          ; V: VBlank flag
                          ; S: Sprite 0 hit
                          ; O: Sprite overflow

; PPU OAM (Object Attribute Memory)
OAM_ADDR        = $2003  ; OAM address port (write)
OAM_DATA        = $2004  ; OAM data port (write)

; PPU Scrolling
PPU_SCROLL      = $2005  ; Scroll position (write twice)
PPU_ADDR        = $2006  ; PPU address (write twice)
PPU_DATA        = $2007  ; PPU data port (read/write)

; ============================================================================
; APU (Audio Processing Unit) Registers - $4000-$4017
; ============================================================================

; Pulse 1
APU_P1_VOL      = $4000  ; DDLC VVVV - Duty, loop, constant, volume
APU_P1_SWEEP    = $4001  ; EPPP NSSS - Enable, period, negate, shift
APU_P1_LO       = $4002  ; LLLL LLLL - Low 8 bits of period
APU_P1_HI       = $4003  ; LLLL LHHH - Length counter, high 3 bits

; Pulse 2
APU_P2_VOL      = $4004
APU_P2_SWEEP    = $4005
APU_P2_LO       = $4006
APU_P2_HI       = $4007

; Triangle
APU_TRI_LINEAR  = $4008
APU_TRI_LO      = $400A
APU_TRI_HI      = $400B

; Noise
APU_NOISE_VOL   = $400C
APU_NOISE_LO    = $400E
APU_NOISE_HI    = $400F

; DMC (Delta Modulation Channel)
APU_DMC_CTRL    = $4010
APU_DMC_DA      = $4011
APU_DMC_ADDR    = $4012
APU_DMC_LEN     = $4013

; APU Control
OAM_DMA         = $4014  ; OAM DMA transfer
APU_STATUS      = $4015  ; Channel enable (write) / status (read)

; ============================================================================
; Controller Registers
; ============================================================================

JOYPAD1         = $4016  ; Player 1 controller
JOYPAD2         = $4017  ; Player 2 controller / APU frame counter

; Controller button bits (when reading)
BUTTON_A        = %10000000
BUTTON_B        = %01000000
BUTTON_SELECT   = %00100000
BUTTON_START    = %00010000
BUTTON_UP       = %00001000
BUTTON_DOWN     = %00000100
BUTTON_LEFT     = %00000010
BUTTON_RIGHT    = %00000001

; ============================================================================
; Cartridge Space
; ============================================================================

; PRG-ROM (Program ROM)
PRG_ROM_START   = $8000
PRG_ROM_END     = $FFFF

; Common PRG banks
PRG_BANK_0      = $8000  ; First 16KB bank (or 32KB)
PRG_BANK_1      = $C000  ; Second 16KB bank (or fixed)

; ============================================================================
; Interrupt Vectors
; ============================================================================

NMI_VECTOR      = $FFFA  ; NMI handler address
RESET_VECTOR    = $FFFC  ; Reset handler address
IRQ_VECTOR      = $FFFE  ; IRQ/BRK handler address

; ============================================================================
; PPU Memory Map (accessed via $2006/$2007)
; ============================================================================

; Pattern tables (CHR-ROM/RAM)
CHR_LEFT        = $0000  ; Left pattern table (sprites)
CHR_RIGHT       = $1000  ; Right pattern table (background)

; Name tables (screen data)
NAMETABLE_0     = $2000
NAMETABLE_1     = $2400
NAMETABLE_2     = $2800
NAMETABLE_3     = $2C00

; Attribute tables
ATTRIBUTE_0     = $23C0
ATTRIBUTE_1     = $27C0
ATTRIBUTE_2     = $2BC0
ATTRIBUTE_3     = $2FC0

; Palettes
PALETTE_START   = $3F00
BG_PALETTE      = $3F00  ; Background palette (16 bytes)
SPR_PALETTE     = $3F10  ; Sprite palette (16 bytes)

; ============================================================================
; Common Values and Masks
; ============================================================================

; PPU_CTRL flags
CTRL_NMI_ON     = %10000000
CTRL_NMI_OFF    = %00000000
CTRL_SPR_8X8    = %00000000
CTRL_SPR_8X16   = %00100000
CTRL_INC_1      = %00000000
CTRL_INC_32     = %00000100

; PPU_MASK flags
MASK_SHOW_BG    = %00001000
MASK_SHOW_SPR   = %00010000
MASK_SHOW_ALL   = %00011110  ; Show everything, including leftmost pixels

; Sprite attributes
SPR_FLIP_H      = %01000000
SPR_FLIP_V      = %10000000
SPR_BEHIND_BG   = %00100000

; ============================================================================
; Useful Macros (ca65 syntax)
; ============================================================================

.macro set_ppu_addr addr
    lda #>addr
    sta PPU_ADDR
    lda #<addr
    sta PPU_ADDR
.endmacro

.macro wait_vblank
.local wait
wait:
    bit PPU_STATUS
    bpl wait
.endmacro