; atari2600.inc - Atari 2600 VCS Hardware Definitions
; For use with DASM or other 6502 assemblers
; Comprehensive TIA, RIOT, and banking definitions

; ============================================================================
; Memory Map Overview
; ============================================================================

; The Atari 2600 has a unique memory architecture:
; $0000-$002C : TIA (Television Interface Adapter) registers
; $0080-$00FF : RAM (128 bytes total - RIOT RAM)
; $0200-$02FF : RIOT I/O and timer registers (mirrored)
; $F000-$FFFF : ROM cartridge space (4K base, bankswitch possible)

; ============================================================================
; TIA (Television Interface Adapter) Write Registers
; ============================================================================

; Strobe registers (write only)
VSYNC           = $00       ; Vertical sync (bit 1)
VBLANK          = $01       ; Vertical blank (bits 7,6,1)
WSYNC           = $02       ; Wait for horizontal sync (strobe)
RSYNC           = $03       ; Reset horizontal sync counter (strobe)
NUSIZ0          = $04       ; Number-size player 0
NUSIZ1          = $05       ; Number-size player 1
COLUP0          = $06       ; Color-luminance player 0
COLUP1          = $07       ; Color-luminance player 1
COLUPF          = $08       ; Color-luminance playfield
COLUBK          = $09       ; Color-luminance background
CTRLPF          = $0A       ; Control playfield
REFP0           = $0B       ; Reflect player 0
REFP1           = $0C       ; Reflect player 1
PF0             = $0D       ; Playfield register 0
PF1             = $0E       ; Playfield register 1
PF2             = $0F       ; Playfield register 2
RESP0           = $10       ; Reset player 0 position (strobe)
RESP1           = $11       ; Reset player 1 position (strobe)
RESM0           = $12       ; Reset missile 0 position (strobe)
RESM1           = $13       ; Reset missile 1 position (strobe)
RESBL           = $14       ; Reset ball position (strobe)
AUDC0           = $15       ; Audio control 0
AUDC1           = $16       ; Audio control 1
AUDF0           = $17       ; Audio frequency 0
AUDF1           = $18       ; Audio frequency 1
AUDV0           = $19       ; Audio volume 0
AUDV1           = $1A       ; Audio volume 1
GRP0            = $1B       ; Graphics player 0
GRP1            = $1C       ; Graphics player 1
ENAM0           = $1D       ; Enable missile 0
ENAM1           = $1E       ; Enable missile 1
ENABL           = $1F       ; Enable ball
HMP0            = $20       ; Horizontal motion player 0
HMP1            = $21       ; Horizontal motion player 1
HMM0            = $22       ; Horizontal motion missile 0
HMM1            = $23       ; Horizontal motion missile 1
HMBL            = $24       ; Horizontal motion ball
VDELP0          = $25       ; Vertical delay player 0
VDELP1          = $26       ; Vertical delay player 1
VDELBL          = $27       ; Vertical delay ball
RESMP0          = $28       ; Reset missile 0 to player 0
RESMP1          = $29       ; Reset missile 1 to player 1
HMOVE           = $2A       ; Apply horizontal motion (strobe)
HMCLR           = $2B       ; Clear horizontal motion (strobe)
CXCLR           = $2C       ; Clear collision latches (strobe)

; ============================================================================
; TIA Read Registers (Collision Detection)
; ============================================================================

CXM0P           = $00       ; Collision M0-P1, M0-P0 (read)
CXM1P           = $01       ; Collision M1-P0, M1-P1 (read)
CXP0FB          = $02       ; Collision P0-PF, P0-BL (read)
CXP1FB          = $03       ; Collision P1-PF, P1-BL (read)
CXM0FB          = $04       ; Collision M0-PF, M0-BL (read)
CXM1FB          = $05       ; Collision M1-PF, M1-BL (read)
CXBLPF          = $06       ; Collision BL-PF (read)
CXPPMM          = $07       ; Collision P0-P1, M0-M1 (read)
INPT0           = $08       ; Input port 0 (read)
INPT1           = $09       ; Input port 1 (read)
INPT2           = $0A       ; Input port 2 (read)
INPT3           = $0B       ; Input port 3 (read)
INPT4           = $0C       ; Input port 4 (read)
INPT5           = $0D       ; Input port 5 (read)

; ============================================================================
; NUSIZ (Number-Size) Bit Patterns
; ============================================================================

; Player/missile size and number
ONE_COPY        = %000      ; One copy
TWO_COPIES_CLOSE = %001     ; Two copies close
TWO_COPIES_MED  = %010      ; Two copies medium
THREE_COPIES    = %011      ; Three copies close
TWO_COPIES_WIDE = %100      ; Two copies wide
DOUBLE_SIZE     = %101      ; One copy, double width
THREE_COPIES_MED = %110     ; Three copies medium
QUAD_SIZE       = %111      ; One copy, quad width

; Missile width (bits 4-5)
MISSILE_1CLK    = %00000000 ; 1 clock width
MISSILE_2CLK    = %00010000 ; 2 clock width
MISSILE_4CLK    = %00100000 ; 4 clock width
MISSILE_8CLK    = %00110000 ; 8 clock width

; ============================================================================
; CTRLPF (Control Playfield) Bits
; ============================================================================

PF_REFLECT      = %00000001 ; Reflect playfield
PF_SCORE        = %00000010 ; Score mode (different colors)
PF_PRIORITY     = %00000100 ; Playfield priority over players
BALL_1CLK       = %00000000 ; Ball 1 clock width
BALL_2CLK       = %00010000 ; Ball 2 clock width
BALL_4CLK       = %00100000 ; Ball 4 clock width
BALL_8CLK       = %00110000 ; Ball 8 clock width

; ============================================================================
; VBLANK Bits
; ============================================================================

VBLANK_ON       = %00000010 ; Turn on vertical blank
VBLANK_OFF      = %00000000 ; Turn off vertical blank
DUMP_PORTS      = %10000000 ; Dump input ports to ground
LATCH_PORTS     = %01000000 ; Latch input ports

; ============================================================================
; RIOT (RAM I/O Timer) Registers
; ============================================================================

; The RIOT chip provides 128 bytes of RAM, I/O ports, and timers
; Base addresses (mirrored throughout $0280-$02FF range)

; Timer registers
TIM1T           = $0294     ; Set 1 clock interval timer
TIM8T           = $0295     ; Set 8 clock interval timer
TIM64T          = $0296     ; Set 64 clock interval timer
T1024T          = $0297     ; Set 1024 clock interval timer
INTIM           = $0284     ; Read timer (time remaining)
TIMINT          = $0285     ; Read timer interrupt flag

; I/O ports
SWCHA           = $0280     ; Port A data register (joysticks)
SWACNT          = $0281     ; Port A data direction register
SWCHB           = $0282     ; Port B data register (console switches)
SWBCNT          = $0283     ; Port B data direction register

; ============================================================================
; Console Switch Definitions (SWCHB)
; ============================================================================

; Console switches (read from SWCHB, 0=pressed)
P1_DIFF_A       = %10000000 ; Player 1 difficulty A (0=A, 1=B)
P1_DIFF_B       = %00000000 ; Player 1 difficulty B
P2_DIFF_A       = %01000000 ; Player 2 difficulty A (0=A, 1=B)
P2_DIFF_B       = %00000000 ; Player 2 difficulty B
TV_COLOR        = %00001000 ; TV type (0=B&W, 1=Color)
TV_BW           = %00000000 ; TV type B&W
SELECT_PRESSED  = %00000010 ; SELECT switch (0=pressed)
RESET_PRESSED   = %00000001 ; RESET switch (0=pressed)

; ============================================================================
; Joystick Definitions (SWCHA)
; ============================================================================

; Right joystick (bits 0-3)
P0_RIGHT_MOVE   = %01111111 ; Player 0 right (0=pressed)
P0_LEFT_MOVE    = %10111111 ; Player 0 left (0=pressed)
P0_DOWN_MOVE    = %11011111 ; Player 0 down (0=pressed)
P0_UP_MOVE      = %11101111 ; Player 0 up (0=pressed)

; Left joystick (bits 4-7)
P1_RIGHT_MOVE   = %01111111 ; Player 1 right (0=pressed)
P1_LEFT_MOVE    = %10111111 ; Player 1 left (0=pressed)
P1_DOWN_MOVE    = %11011111 ; Player 1 down (0=pressed)
P1_UP_MOVE      = %11101111 ; Player 1 up (0=pressed)

; Fire buttons (read from INPT4 and INPT5)
FIRE_PRESSED    = %00000000 ; Fire button bit when pressed
FIRE_NOT_PRESSED = %10000000 ; Fire button bit when not pressed

; ============================================================================
; Standard Colors (NTSC)
; ============================================================================

; Colors for NTSC systems (add 1 for PAL)
BLACK           = $00
WHITE           = $0E
GREY            = $06
YELLOW          = $1E
BROWN           = $1C
ORANGE          = $2C
RED             = $36
MAGENTA         = $46
PURPLE          = $56
BLUE            = $66
LIGHT_BLUE      = $76
CYAN            = $86
TURQUOISE       = $96
GREEN           = $A6
YELLOW_GREEN    = $B6
PINK            = $C6

; Luminance values (add to color)
LUM_MIN         = $00       ; Darkest
LUM_MAX         = $0E       ; Brightest

; ============================================================================
; Audio Waveforms
; ============================================================================

; AUDC0/AUDC1 waveform types
SILENT          = $00       ; No sound
SQUARE_4BIT     = $01       ; 4-bit square wave
SQUARE_DIV15    = $02       ; Square wave divided by 15
SQUARE_4BIT_P   = $03       ; 4-bit square wave (different phase)
PURE_TONE       = $04       ; Pure tone (single frequency)
PURE_TONE_2     = $05       ; Pure tone (different phase)
SAWTOOTH        = $06       ; Sawtooth wave
SAWTOOTH_2      = $07       ; Sawtooth wave (different phase)
NOISE           = $08       ; White noise
NOISE_2         = $09       ; White noise (different phase)
PURE_BASS       = $0C       ; Pure bass tone
NOISE_BASS      = $0D       ; Bass + noise
PURE_BUZZ       = $0E       ; Pure buzzing
NOISE_BUZZ      = $0F       ; Buzzing + noise

; ============================================================================
; Memory Organization
; ============================================================================

; Zero page equivalent (but it's actually $80-$FF)
RAM_START       = $80       ; Start of RAM
RAM_END         = $FF       ; End of RAM (128 bytes total)

; Stack simulation (6502 stack not available due to memory map)
STACK_BASE      = $F0       ; Base for simulated stack
STACK_TOP       = $FF       ; Top of simulated stack

; Typical variable locations
TEMP_VAR1       = $80       ; Temporary variable 1
TEMP_VAR2       = $81       ; Temporary variable 2
FRAME_COUNTER   = $82       ; Frame counter
SCORE_P1        = $83       ; Player 1 score (BCD)
SCORE_P2        = $84       ; Player 2 score (BCD)
LIVES_P1        = $85       ; Player 1 lives
LIVES_P2        = $86       ; Player 2 lives

; Object positions (common pattern)
P0_X            = $87       ; Player 0 X position
P0_Y            = $88       ; Player 0 Y position
P1_X            = $89       ; Player 1 X position
P1_Y            = $8A       ; Player 1 Y position
BALL_X          = $8B       ; Ball X position
BALL_Y          = $8C       ; Ball Y position

; ============================================================================
; ROM Cartridge Memory Map
; ============================================================================

; Standard 4K cartridge
ROM_BASE        = $F000     ; ROM start address
VECTORS         = $FFFA     ; 6502 interrupt vectors

; Interrupt vectors
NMI_VECTOR      = $FFFA     ; Non-maskable interrupt (not used)
RESET_VECTOR    = $FFFC     ; Reset vector (main entry point)
IRQ_VECTOR      = $FFFE     ; Interrupt request (not used)

; ============================================================================
; Banking Constants (for larger cartridges)
; ============================================================================

; Standard bankswitching schemes

; F8 Banking (8K)
F8_BANK0        = $FFF8     ; Select bank 0
F8_BANK1        = $FFF9     ; Select bank 1

; F6 Banking (16K)
F6_BANK0        = $FFF6     ; Select bank 0
F6_BANK1        = $FFF7     ; Select bank 1
F6_BANK2        = $FFF8     ; Select bank 2
F6_BANK3        = $FFF9     ; Select bank 3

; F4 Banking (32K)
F4_BANK0        = $FFF4     ; Select bank 0
F4_BANK1        = $FFF5     ; Select bank 1
F4_BANK2        = $FFF6     ; Select bank 2
F4_BANK3        = $FFF7     ; Select bank 3
F4_BANK4        = $FFF8     ; Select bank 4
F4_BANK5        = $FFF9     ; Select bank 5
F4_BANK6        = $FFFA     ; Select bank 6
F4_BANK7        = $FFFB     ; Select bank 7

; ============================================================================
; Timing Constants
; ============================================================================

; NTSC timing
SCANLINES_TOTAL = 262       ; Total scanlines per frame
SCANLINES_VBLANK = 37       ; Vertical blank scanlines
SCANLINES_VISIBLE = 192     ; Visible scanlines
SCANLINES_OVERSCAN = 30     ; Overscan scanlines

; Cycles per scanline
CYCLES_PER_LINE = 76        ; TIA cycles per scanline
CPU_CYCLES_LINE = 76        ; CPU cycles per scanline (same)

; Frame timing
FRAMES_PER_SEC  = 60        ; NTSC frame rate

; ============================================================================
; Kernel Constants
; ============================================================================

; Common kernel patterns
LINES_PER_OBJECT = 8        ; Typical sprite height
KERNEL_LINES    = 192       ; Lines in display kernel
SPRITE_HEIGHT   = 8         ; Standard sprite height

; Position calculation constants
HMOVE_L7        = $70       ; Move left 7 pixels
HMOVE_L6        = $60       ; Move left 6 pixels
HMOVE_L5        = $50       ; Move left 5 pixels
HMOVE_L4        = $40       ; Move left 4 pixels
HMOVE_L3        = $30       ; Move left 3 pixels
HMOVE_L2        = $20       ; Move left 2 pixels
HMOVE_L1        = $10       ; Move left 1 pixel
HMOVE_0         = $00       ; No movement
HMOVE_R1        = $F0       ; Move right 1 pixel
HMOVE_R2        = $E0       ; Move right 2 pixels
HMOVE_R3        = $D0       ; Move right 3 pixels
HMOVE_R4        = $C0       ; Move right 4 pixels
HMOVE_R5        = $B0       ; Move right 5 pixels
HMOVE_R6        = $A0       ; Move right 6 pixels
HMOVE_R7        = $90       ; Move right 7 pixels
HMOVE_R8        = $80       ; Move right 8 pixels