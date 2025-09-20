; gameboy.inc - Nintendo Game Boy Hardware Registers and Memory Map
; For use with RGBASM or other Z80-like assemblers

; ============================================================================
; Memory Map
; ============================================================================

; ROM Banks (32KB visible)
ROM_BANK_0      EQU $0000   ; ROM Bank 0 (16KB - always visible)
ROM_BANK_N      EQU $4000   ; ROM Bank 1-N (16KB - switchable)

; Video RAM
VRAM_START      EQU $8000   ; Video RAM start
VRAM_END        EQU $9FFF   ; Video RAM end (8KB)

; External RAM (if cartridge has it)
ERAM_START      EQU $A000   ; External RAM start
ERAM_END        EQU $BFFF   ; External RAM end (8KB)

; Work RAM
WRAM_START      EQU $C000   ; Work RAM start
WRAM_MIRROR     EQU $E000   ; Mirror of C000-DDFF
WRAM_END        EQU $FDFF   ; Work RAM end

; High RAM and I/O
HRAM_START      EQU $FF80   ; High RAM start (127 bytes)
HRAM_END        EQU $FFFE   ; High RAM end

IE_REGISTER     EQU $FFFF   ; Interrupt Enable register

; ============================================================================
; LCD/PPU Registers
; ============================================================================

rLCDC           EQU $FF40   ; LCD Control register
rSTAT           EQU $FF41   ; LCD Status register
rSCY            EQU $FF42   ; Scroll Y
rSCX            EQU $FF43   ; Scroll X
rLY             EQU $FF44   ; LCD Y coordinate (read-only)
rLYC            EQU $FF45   ; LY Compare
rDMA            EQU $FF46   ; DMA Transfer register
rBGP            EQU $FF47   ; Background Palette
rOBP0           EQU $FF48   ; Object Palette 0
rOBP1           EQU $FF49   ; Object Palette 1
rWY             EQU $FF4A   ; Window Y position
rWX             EQU $FF4B   ; Window X position

; LCDC bits
LCDCF_OFF       EQU %00000000 ; LCD off
LCDCF_ON        EQU %10000000 ; LCD on
LCDCF_WIN9800   EQU %00000000 ; Window tilemap $9800-$9BFF
LCDCF_WIN9C00   EQU %01000000 ; Window tilemap $9C00-$9FFF
LCDCF_WINOFF    EQU %00000000 ; Window off
LCDCF_WINON     EQU %00100000 ; Window on
LCDCF_BG8800    EQU %00000000 ; BG & Window tiles $8800-$97FF
LCDCF_BG8000    EQU %00010000 ; BG & Window tiles $8000-$8FFF
LCDCF_BG9800    EQU %00000000 ; BG tilemap $9800-$9BFF
LCDCF_BG9C00    EQU %00001000 ; BG tilemap $9C00-$9FFF
LCDCF_OBJ8      EQU %00000000 ; OBJ 8x8
LCDCF_OBJ16     EQU %00000100 ; OBJ 8x16
LCDCF_OBJOFF    EQU %00000000 ; OBJ off
LCDCF_OBJON     EQU %00000010 ; OBJ on
LCDCF_BGOFF     EQU %00000000 ; BG off
LCDCF_BGON      EQU %00000001 ; BG on

; STAT bits
STATF_LYC       EQU %01000000 ; LYC=LY Coincidence interrupt
STATF_MODE10    EQU %00100000 ; Mode 2 OAM interrupt
STATF_MODE01    EQU %00010000 ; Mode 1 VBlank interrupt
STATF_MODE00    EQU %00001000 ; Mode 0 HBlank interrupt
STATF_LYCF      EQU %00000100 ; LYC=LY Coincidence flag
STATF_BUSY      EQU %00000010 ; PPU is accessing VRAM
STATF_VBL       EQU %00000001 ; VBlank flag

; ============================================================================
; Sound Registers
; ============================================================================

; Channel 1 - Square wave with envelope and sweep
rNR10           EQU $FF10   ; Channel 1 sweep
rNR11           EQU $FF11   ; Channel 1 length/duty
rNR12           EQU $FF12   ; Channel 1 envelope
rNR13           EQU $FF13   ; Channel 1 frequency low
rNR14           EQU $FF14   ; Channel 1 frequency high

; Channel 2 - Square wave with envelope
rNR21           EQU $FF16   ; Channel 2 length/duty
rNR22           EQU $FF17   ; Channel 2 envelope
rNR23           EQU $FF18   ; Channel 2 frequency low
rNR24           EQU $FF19   ; Channel 2 frequency high

; Channel 3 - Wave
rNR30           EQU $FF1A   ; Channel 3 on/off
rNR31           EQU $FF1B   ; Channel 3 length
rNR32           EQU $FF1C   ; Channel 3 volume
rNR33           EQU $FF1D   ; Channel 3 frequency low
rNR34           EQU $FF1E   ; Channel 3 frequency high

; Channel 4 - Noise
rNR41           EQU $FF20   ; Channel 4 length
rNR42           EQU $FF21   ; Channel 4 envelope
rNR43           EQU $FF22   ; Channel 4 frequency
rNR44           EQU $FF23   ; Channel 4 control

; Global sound control
rNR50           EQU $FF24   ; Channel control/volume
rNR51           EQU $FF25   ; Sound output terminal selection
rNR52           EQU $FF26   ; Sound on/off

; Wave pattern RAM
_AUD3WAVERAM    EQU $FF30   ; Wave pattern (16 bytes)

; ============================================================================
; Joypad Register
; ============================================================================

rP1             EQU $FF00   ; Joypad register

; Joypad bits
P1F_5           EQU %00100000 ; P15 out port
P1F_4           EQU %00010000 ; P14 out port
P1F_3           EQU %00001000 ; P13 in port
P1F_2           EQU %00000100 ; P12 in port
P1F_1           EQU %00000010 ; P11 in port
P1F_0           EQU %00000001 ; P10 in port

; When P14 is low (action buttons)
P1F_A           EQU P1F_0
P1F_B           EQU P1F_1
P1F_SELECT      EQU P1F_2
P1F_START       EQU P1F_3

; When P15 is low (direction buttons)
P1F_RIGHT       EQU P1F_0
P1F_LEFT        EQU P1F_1
P1F_UP          EQU P1F_2
P1F_DOWN        EQU P1F_3

; ============================================================================
; Timer Registers
; ============================================================================

rDIV            EQU $FF04   ; Divider register
rTIMA           EQU $FF05   ; Timer counter
rTMA            EQU $FF06   ; Timer modulo
rTAC            EQU $FF07   ; Timer control

; Timer control bits
TACF_START      EQU %00000100 ; Timer start
TACF_STOP       EQU %00000000 ; Timer stop
TACF_4KHZ       EQU %00000000 ; 4096 Hz
TACF_262KHZ     EQU %00000001 ; 262144 Hz
TACF_65KHZ      EQU %00000010 ; 65536 Hz
TACF_16KHZ      EQU %00000011 ; 16384 Hz

; ============================================================================
; Interrupt Registers
; ============================================================================

rIF             EQU $FF0F   ; Interrupt Flag register
rIE             EQU $FFFF   ; Interrupt Enable register

; Interrupt bits
IEF_VBLANK      EQU %00000001 ; VBlank interrupt
IEF_LCDC        EQU %00000010 ; LCD STAT interrupt
IEF_TIMER       EQU %00000100 ; Timer interrupt
IEF_SERIAL      EQU %00001000 ; Serial interrupt
IEF_HILO        EQU %00010000 ; Joypad interrupt

; ============================================================================
; Memory Bank Controllers (MBC)
; ============================================================================

; MBC1 registers
MBC1_ROM_BANK   EQU $2000   ; ROM bank number (write)
MBC1_RAM_BANK   EQU $4000   ; RAM bank number (write)
MBC1_MODE       EQU $6000   ; Banking mode (write)

; MBC3 registers (with RTC)
MBC3_ROM_BANK   EQU $2000   ; ROM bank number (write)
MBC3_RAM_BANK   EQU $4000   ; RAM bank/RTC register (write)
MBC3_LATCH      EQU $6000   ; Latch clock data (write)

; MBC5 registers
MBC5_ROM_BANK_LO EQU $2000  ; ROM bank low byte (write)
MBC5_ROM_BANK_HI EQU $3000  ; ROM bank high bit (write)
MBC5_RAM_BANK   EQU $4000   ; RAM bank number (write)

; ============================================================================
; Useful Constants
; ============================================================================

; Screen dimensions
SCRN_X          EQU 160     ; Screen width in pixels
SCRN_Y          EQU 144     ; Screen height in pixels
SCRN_VX         EQU 256     ; Virtual screen width
SCRN_VY         EQU 256     ; Virtual screen height

; Tile/map dimensions
SCRN_X_B        EQU 20      ; Screen width in tiles
SCRN_Y_B        EQU 18      ; Screen height in tiles
SCRN_VX_B       EQU 32      ; Virtual screen width in tiles
SCRN_VY_B       EQU 32      ; Virtual screen height in tiles

; Sprite counts
MAX_SPRITES     EQU 40      ; Maximum sprites in OAM
MAX_SPRITES_LINE EQU 10     ; Maximum sprites per line

; OAM (Object Attribute Memory)
OAM_START       EQU $FE00   ; OAM start address
OAM_END         EQU $FE9F   ; OAM end address

; ============================================================================
; Color Palettes (4 shades per palette)
; ============================================================================

; Standard grayscale palette values
PAL_WHITE       EQU %00000000 ; Lightest
PAL_LIGHT_GRAY  EQU %00000001 ; Light gray
PAL_DARK_GRAY   EQU %00000010 ; Dark gray
PAL_BLACK       EQU %00000011 ; Darkest

; Standard palette (white to black)
PALETTE_DEFAULT EQU %11100100

; High contrast palette
PALETTE_HIGH    EQU %11000000

; ============================================================================
; Boot ROM Constants
; ============================================================================

; Nintendo logo check location
NINTENDO_LOGO   EQU $0104   ; Nintendo logo in cartridge header (48 bytes)
HEADER_CHECKSUM EQU $014D   ; Header checksum location
GLOBAL_CHECKSUM EQU $014E   ; Global checksum location (2 bytes)