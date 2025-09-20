; c64.inc - Commodore 64 Memory Map and Constants
; For use with ACME assembler

; ============================================================================
; BASIC and KERNAL ROM
; ============================================================================

; Zero Page
BASIC_FAC1      = $61   ; Floating point accumulator 1
BASIC_FAC2      = $69   ; Floating point accumulator 2

; BASIC ROM
BASIC_START     = $A000
BASIC_END       = $BFFF

; KERNAL ROM
KERNAL_START    = $E000
KERNAL_END      = $FFFF

; ============================================================================
; VIC-II (Video Interface Chip II) - $D000-$D3FF
; ============================================================================

VIC_BASE        = $D000

; Sprite coordinates
VIC_SP0X        = $D000
VIC_SP0Y        = $D001
VIC_SP1X        = $D002
VIC_SP1Y        = $D003
VIC_SP2X        = $D004
VIC_SP2Y        = $D005
VIC_SP3X        = $D006
VIC_SP3Y        = $D007
VIC_SP4X        = $D008
VIC_SP4Y        = $D009
VIC_SP5X        = $D00A
VIC_SP5Y        = $D00B
VIC_SP6X        = $D00C
VIC_SP6Y        = $D00D
VIC_SP7X        = $D00E
VIC_SP7Y        = $D00F

; Sprite MSB for X coordinates
VIC_SPXMSB      = $D010

; Control registers
VIC_CR1         = $D011  ; Control register 1
VIC_RASTER      = $D012  ; Raster counter
VIC_LPENX       = $D013  ; Light pen X
VIC_LPENY       = $D014  ; Light pen Y
VIC_SPEN        = $D015  ; Sprite enabled
VIC_CR2         = $D016  ; Control register 2
VIC_SPYE        = $D017  ; Sprite Y expansion
VIC_MEMPTR      = $D018  ; Memory pointers
VIC_IRR         = $D019  ; Interrupt request register
VIC_IMR         = $D01A  ; Interrupt mask register
VIC_SPPRI       = $D01B  ; Sprite priority
VIC_SPMCM       = $D01C  ; Sprite multicolor mode
VIC_SPXE        = $D01D  ; Sprite X expansion
VIC_SSCOL       = $D01E  ; Sprite-sprite collision
VIC_SBCOL       = $D01F  ; Sprite-background collision

; Colors
VIC_BORDER      = $D020  ; Border color
VIC_BG0         = $D021  ; Background color 0
VIC_BG1         = $D022  ; Background color 1
VIC_BG2         = $D023  ; Background color 2
VIC_BG3         = $D024  ; Background color 3
VIC_SPMC0       = $D025  ; Sprite multicolor 0
VIC_SPMC1       = $D026  ; Sprite multicolor 1

; Sprite colors
VIC_SP0COL      = $D027
VIC_SP1COL      = $D028
VIC_SP2COL      = $D029
VIC_SP3COL      = $D02A
VIC_SP4COL      = $D02B
VIC_SP5COL      = $D02C
VIC_SP6COL      = $D02D
VIC_SP7COL      = $D02E

; ============================================================================
; SID (Sound Interface Device) - $D400-$D7FF
; ============================================================================

SID_BASE        = $D400

; Voice 1
SID_V1FREQ      = $D400  ; Frequency low byte
SID_V1FREQHI    = $D401  ; Frequency high byte
SID_V1PW        = $D402  ; Pulse width low byte
SID_V1PWHI      = $D403  ; Pulse width high byte
SID_V1CR        = $D404  ; Control register
SID_V1AD        = $D405  ; Attack/Decay
SID_V1SR        = $D406  ; Sustain/Release

; Voice 2
SID_V2FREQ      = $D407
SID_V2FREQHI    = $D408
SID_V2PW        = $D409
SID_V2PWHI      = $D40A
SID_V2CR        = $D40B
SID_V2AD        = $D40C
SID_V2SR        = $D40D

; Voice 3
SID_V3FREQ      = $D40E
SID_V3FREQHI    = $D40F
SID_V3PW        = $D410
SID_V3PWHI      = $D411
SID_V3CR        = $D412
SID_V3AD        = $D413
SID_V3SR        = $D414

; Filter
SID_FCLO        = $D415  ; Filter cutoff low byte
SID_FCHI        = $D416  ; Filter cutoff high byte
SID_RESFIL      = $D417  ; Resonance/Filter
SID_MODEVOL     = $D418  ; Mode/Volume

; ============================================================================
; CIA 1 (Complex Interface Adapter) - $DC00-$DCFF
; ============================================================================

CIA1_BASE       = $DC00
CIA1_PRA        = $DC00  ; Port A (keyboard matrix columns)
CIA1_PRB        = $DC01  ; Port B (keyboard matrix rows)
CIA1_DDRA       = $DC02  ; Data direction register A
CIA1_DDRB       = $DC03  ; Data direction register B

; ============================================================================
; CIA 2 - $DD00-$DDFF
; ============================================================================

CIA2_BASE       = $DD00
CIA2_PRA        = $DD00  ; Port A (VIC bank, serial)
CIA2_PRB        = $DD01  ; Port B (user port)

; ============================================================================
; Color RAM - $D800-$DBFF
; ============================================================================

COLOR_RAM       = $D800

; ============================================================================
; KERNAL Jump Table
; ============================================================================

; Essential KERNAL routines
KERNAL_SETLFS   = $FFBA  ; Set logical file
KERNAL_SETNAM   = $FFBD  ; Set file name
KERNAL_OPEN     = $FFC0  ; Open file
KERNAL_CLOSE    = $FFC3  ; Close file
KERNAL_CHKIN    = $FFC6  ; Define input channel
KERNAL_CHKOUT   = $FFC9  ; Define output channel
KERNAL_CLRCHN   = $FFCC  ; Clear channels
KERNAL_CHRIN    = $FFCF  ; Input character
KERNAL_CHROUT   = $FFD2  ; Output character
KERNAL_LOAD     = $FFD5  ; Load from device
KERNAL_SAVE     = $FFD8  ; Save to device
KERNAL_GETIN    = $FFE4  ; Get character from keyboard

; ============================================================================
; Color Constants
; ============================================================================

COLOR_BLACK     = 0
COLOR_WHITE     = 1
COLOR_RED       = 2
COLOR_CYAN      = 3
COLOR_PURPLE    = 4
COLOR_GREEN     = 5
COLOR_BLUE      = 6
COLOR_YELLOW    = 7
COLOR_ORANGE    = 8
COLOR_BROWN     = 9
COLOR_LIGHTRED  = 10
COLOR_DARKGREY  = 11
COLOR_GREY      = 12
COLOR_LIGHTGREEN = 13
COLOR_LIGHTBLUE = 14
COLOR_LIGHTGREY = 15

; ============================================================================
; Screen Constants
; ============================================================================

SCREEN_RAM      = $0400  ; Default screen memory
SCREEN_WIDTH    = 40
SCREEN_HEIGHT   = 25
SCREEN_SIZE     = SCREEN_WIDTH * SCREEN_HEIGHT