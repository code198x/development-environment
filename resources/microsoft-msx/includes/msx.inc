; msx.inc - MSX Computer System Hardware and BIOS Definitions
; For use with Z80 assemblers (sjasmplus, etc.)

; ============================================================================
; Memory Map (MSX1 Standard)
; ============================================================================

; BIOS ROM
BIOS_ROM        EQU $0000   ; BIOS ROM (32KB)
BASIC_ROM       EQU $8000   ; BASIC ROM (32KB in slot 0)

; RAM Layout (64KB machine)
RAM_START       EQU $C000   ; Main RAM start (MSX1 minimum)
RAM_END         EQU $FFFF   ; RAM end
PAGE0           EQU $0000   ; Page 0 (16KB)
PAGE1           EQU $4000   ; Page 1 (16KB)
PAGE2           EQU $8000   ; Page 2 (16KB)
PAGE3           EQU $C000   ; Page 3 (16KB)

; Stack
STACK_TOP       EQU $F380   ; Default stack pointer

; ============================================================================
; VDP (Video Display Processor) - TMS9918A/TMS9928A
; ============================================================================

VDP_DATA        EQU $98     ; VDP data port
VDP_STATUS      EQU $99     ; VDP status/register port

; VDP Status flags
VDP_INT         EQU $80     ; Interrupt flag
VDP_5S          EQU $40     ; 5th sprite flag
VDP_5SN         EQU $1F     ; 5th sprite number

; VDP Registers (0-7)
VDP_R0          EQU $00     ; Mode register 0
VDP_R1          EQU $01     ; Mode register 1
VDP_R2          EQU $02     ; Name table base address
VDP_R3          EQU $03     ; Color table base address
VDP_R4          EQU $04     ; Pattern generator base address
VDP_R5          EQU $05     ; Sprite attribute table base address
VDP_R6          EQU $06     ; Sprite pattern generator base address
VDP_R7          EQU $07     ; Text/border color

; Mode register 0 bits
VDP_M1          EQU $02     ; Mode bit 1
VDP_EXTVID      EQU $01     ; External video

; Mode register 1 bits
VDP_4_16K       EQU $80     ; 4/16K selection
VDP_BLANK       EQU $40     ; Blank screen
VDP_INT_EN      EQU $20     ; Interrupt enable
VDP_M1_M2       EQU $18     ; Mode bits 1 and 2
VDP_SIZE        EQU $02     ; Sprite size (0=8x8, 1=16x16)
VDP_MAG         EQU $01     ; Sprite magnification

; Screen modes
SCREEN_40       EQU $00     ; Text mode (40 columns)
SCREEN_32       EQU $01     ; Text mode (32 columns)
SCREEN_1        EQU $00     ; Graphics mode 1
SCREEN_2        EQU $02     ; Graphics mode 2
SCREEN_3        EQU $06     ; Multicolor mode

; Standard VRAM addresses (Screen 1)
NAMETBL         EQU $1800   ; Name table
COLORTBL        EQU $2000   ; Color table
PATTERNTBL      EQU $0000   ; Pattern table
SPRITETBL       EQU $1B00   ; Sprite attribute table
SPRITEPAT       EQU $3800   ; Sprite pattern table

; ============================================================================
; PSG (Programmable Sound Generator) - AY-3-8910
; ============================================================================

PSG_REG         EQU $A0     ; PSG register select
PSG_WRITE       EQU $A1     ; PSG write data
PSG_READ        EQU $A2     ; PSG read data

; PSG Registers
PSG_A_FINE      EQU $00     ; Channel A fine tune
PSG_A_COARSE    EQU $01     ; Channel A coarse tune
PSG_B_FINE      EQU $02     ; Channel B fine tune
PSG_B_COARSE    EQU $03     ; Channel B coarse tune
PSG_C_FINE      EQU $04     ; Channel C fine tune
PSG_C_COARSE    EQU $05     ; Channel C coarse tune
PSG_NOISE       EQU $06     ; Noise period
PSG_MIXER       EQU $07     ; Mixer control
PSG_A_VOL       EQU $08     ; Channel A volume
PSG_B_VOL       EQU $09     ; Channel B volume
PSG_C_VOL       EQU $0A     ; Channel C volume
PSG_ENV_FINE    EQU $0B     ; Envelope fine tune
PSG_ENV_COARSE  EQU $0C     ; Envelope coarse tune
PSG_ENV_SHAPE   EQU $0D     ; Envelope shape
PSG_PORT_A      EQU $0E     ; I/O port A (joystick/printer)
PSG_PORT_B      EQU $0F     ; I/O port B (not used)

; Mixer bits (0 = on, 1 = off)
MIX_IOB         EQU $80     ; I/O port B
MIX_IOA         EQU $40     ; I/O port A
MIX_NC          EQU $20     ; Noise channel C
MIX_NB          EQU $10     ; Noise channel B
MIX_NA          EQU $08     ; Noise channel A
MIX_TC          EQU $04     ; Tone channel C
MIX_TB          EQU $02     ; Tone channel B
MIX_TA          EQU $01     ; Tone channel A

; Volume control
VOL_ENV         EQU $10     ; Use envelope
VOL_MASK        EQU $0F     ; Volume level mask

; ============================================================================
; PPI (Programmable Peripheral Interface) - 8255
; ============================================================================

PPI_A           EQU $A8     ; Port A (primary slot select)
PPI_B           EQU $A9     ; Port B (keyboard row)
PPI_C           EQU $AA     ; Port C (keyboard column/cassette)
PPI_CTRL        EQU $AB     ; Control register

; PPI Port C bits
PPI_CAPS        EQU $40     ; Caps lock LED
PPI_CASSETTE    EQU $20     ; Cassette motor relay
PPI_SOUND       EQU $10     ; Sound output
PPI_COL_MASK    EQU $0F     ; Keyboard column mask

; ============================================================================
; Slot System
; ============================================================================

; Primary slot select register (port A8h)
SLOT0_MASK      EQU $03     ; Page 0 slot
SLOT1_MASK      EQU $0C     ; Page 1 slot
SLOT2_MASK      EQU $30     ; Page 2 slot
SLOT3_MASK      EQU $C0     ; Page 3 slot

; Slot numbers
SLOT_0          EQU $00
SLOT_1          EQU $01
SLOT_2          EQU $02
SLOT_3          EQU $03

; ============================================================================
; BIOS Entry Points
; ============================================================================

; Main BIOS routines
CHKRAM          EQU $0000   ; Check RAM and initialize
SYNCHR          EQU $0008   ; Check syntax
RDSLT           EQU $000C   ; Read from slot
CHRGTR          EQU $0010   ; Get next character
WRSLT           EQU $0014   ; Write to slot
OUTDO           EQU $0018   ; Output to current device
CALSLT          EQU $001C   ; Call routine in slot
DCOMPR          EQU $0020   ; Compare HL with DE
ENASLT          EQU $0024   ; Enable slot
GETYPR          EQU $0028   ; Get variable type
CALLF           EQU $0030   ; Call routine

; Character I/O
CHPUT           EQU $00A2   ; Output character
CHGET           EQU $009F   ; Input character (wait)
CHSNS           EQU $009C   ; Check character available
KEYINT          EQU $0038   ; Keyboard interrupt

; Screen routines
POSIT           EQU $00C6   ; Position cursor
CLS             EQU $00C3   ; Clear screen
BEEP            EQU $00C0   ; Beep sound
TOTEXT          EQU $00D2   ; Switch to text mode

; Cassette routines
TAPION          EQU $00E1   ; Tape input on
TAPIN           EQU $00E4   ; Tape input byte
TAPIOF          EQU $00E7   ; Tape input off
TAPOON          EQU $00EA   ; Tape output on
TAPOUT          EQU $00ED   ; Tape output byte
TAPOOF          EQU $00F0   ; Tape output off

; Graphics routines
GRPPRT          EQU $0093   ; Print graphics character
GTSTCK          EQU $00D5   ; Get joystick status
GTTRIG          EQU $00D8   ; Get trigger status
GTPAD           EQU $00DB   ; Get touch pad status
GTPDL           EQU $00DE   ; Get paddle status

; ============================================================================
; System Variables (in RAM)
; ============================================================================

; Important system variables
LINL40          EQU $F3AE   ; Line length (40 or 80)
LINL32          EQU $F3AF   ; Line length (32)
JIFFY           EQU $FC9E   ; Jiffy counter (interrupt count)
INTFLG          EQU $FC9B   ; Interrupt flag
CURSAV          EQU $F3DD   ; Cursor save area
FRGCOL          EQU $F3E9   ; Foreground color
BAKCLR          EQU $F3EA   ; Background color
BDRCLR          EQU $F3EB   ; Border color

; VDP registers save area
RG0SAV          EQU $F3DF   ; VDP register 0 save
RG1SAV          EQU $F3E0   ; VDP register 1 save
RG2SAV          EQU $F3E1   ; VDP register 2 save
RG3SAV          EQU $F3E2   ; VDP register 3 save
RG4SAV          EQU $F3E3   ; VDP register 4 save
RG5SAV          EQU $F3E4   ; VDP register 5 save
RG6SAV          EQU $F3E5   ; VDP register 6 save
RG7SAV          EQU $F3E6   ; VDP register 7 save

; Keyboard variables
NEWKEY          EQU $FBE5   ; New key code
OLDKEY          EQU $FBDB   ; Previous key matrix
KEYBUF          EQU $FBF0   ; Keyboard buffer (40 bytes)

; ============================================================================
; Colors
; ============================================================================

BLACK           EQU $01
MEDIUM_GREEN    EQU $02
LIGHT_GREEN     EQU $03
DARK_BLUE       EQU $04
LIGHT_BLUE      EQU $05
DARK_RED        EQU $06
CYAN            EQU $07
MEDIUM_RED      EQU $08
LIGHT_RED       EQU $09
DARK_YELLOW     EQU $0A
LIGHT_YELLOW    EQU $0B
DARK_GREEN      EQU $0C
MAGENTA         EQU $0D
GRAY            EQU $0E
WHITE           EQU $0F

; ============================================================================
; Joystick/Keyboard Constants
; ============================================================================

; Joystick directions (GTSTCK return values)
STICK_UP        EQU $01
STICK_UP_RIGHT  EQU $02
STICK_RIGHT     EQU $03
STICK_DOWN_RIGHT EQU $04
STICK_DOWN      EQU $05
STICK_DOWN_LEFT EQU $06
STICK_LEFT      EQU $07
STICK_UP_LEFT   EQU $08
STICK_CENTER    EQU $00

; Trigger bits
TRIG_A          EQU $01     ; Trigger A (space bar/button 1)
TRIG_B          EQU $02     ; Trigger B (button 2)

; Common key codes
KEY_SPACE       EQU $20
KEY_ENTER       EQU $0D
KEY_ESC         EQU $1B
KEY_BS          EQU $08
KEY_TAB         EQU $09