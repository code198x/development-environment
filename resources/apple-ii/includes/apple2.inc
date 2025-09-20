; apple2.inc - Apple II Hardware and ROM Definitions
; For use with ca65 or other 6502 assemblers
; Covers Apple II, II+, IIe, and IIc systems

; ============================================================================
; Memory Map
; ============================================================================

; Zero Page (most important for 6502 programming)
ZP_START        = $00       ; Zero page start
ZP_END          = $FF       ; Zero page end

; System zero page locations
WNDLFT          = $20       ; Left edge of text window
WNDWDTH         = $21       ; Width of text window
WNDTOP          = $22       ; Top edge of text window
WNDBTM          = $23       ; Bottom edge of text window
CH              = $24       ; Cursor horizontal position
CV              = $25       ; Cursor vertical position
GBASL           = $26       ; Graphics base address low
GBASH           = $27       ; Graphics base address high
BASL            = $28       ; Text base address low
BASH            = $29       ; Text base address high
BAS2L           = $2A       ; Text base address low (aux)
BAS2H           = $2B       ; Text base address high (aux)
H2              = $2C       ; High-res graphics page 2 base
V2              = $2D       ; High-res graphics vertical position
MASK            = $2E       ; Graphics drawing mask
COLOR           = $30       ; Graphics color
INVFLG          = $32       ; Inverse text flag
PROMPT          = $33       ; Input prompt character
YSAV            = $34       ; Y register save
YSAV1           = $35       ; Y register save 1
CSWL            = $36       ; Character output vector low
CSWH            = $37       ; Character output vector high
KSWL            = $38       ; Character input vector low
KSWH            = $39       ; Character input vector high

; DOS 3.3 zero page usage
DOSBUFL         = $3A       ; DOS buffer address low
DOSBUFH         = $3B       ; DOS buffer address high
FILEMGR         = $3D       ; File manager work area
RWTSL           = $3E       ; RWTS parameter list low
RWTSH           = $3F       ; RWTS parameter list high

; Monitor zero page usage
A1L             = $3C       ; Monitor arg 1 low
A1H             = $3D       ; Monitor arg 1 high
A2L             = $3E       ; Monitor arg 2 low
A2H             = $3F       ; Monitor arg 2 high
A3L             = $40       ; Monitor arg 3 low
A3H             = $41       ; Monitor arg 3 high
A4L             = $42       ; Monitor arg 4 low
A4H             = $43       ; Monitor arg 4 high

; Stack
STACK           = $0100     ; Stack page (6502 standard)

; Text/Graphics Pages
TEXT_PAGE1      = $0400     ; Primary text page (1KB)
TEXT_PAGE2      = $0800     ; Secondary text page (1KB)
HIRES_PAGE1     = $2000     ; Primary hi-res page (8KB)
HIRES_PAGE2     = $4000     ; Secondary hi-res page (8KB)

; System areas
DOS_BUFFERS     = $9600     ; DOS 3.3 file buffers
DOS_CODE        = $9D00     ; DOS 3.3 code area
BASIC_PROGRAM   = $0801     ; BASIC program storage
BASIC_VARS      = $0900     ; BASIC variables (typical)

; High memory
MONITOR_ROM     = $F800     ; Monitor ROM start
BASIC_ROM       = $D000     ; BASIC ROM start (floating point)
ROM_START       = $C000     ; System ROM start

; ============================================================================
; I/O Locations (Memory Mapped)
; ============================================================================

; Keyboard
KBD             = $C000     ; Keyboard data
KBDSTRB         = $C010     ; Keyboard strobe (clear bit 7)

; Graphics mode switches
GR_OFF          = $C050     ; Graphics off (text mode)
GR_ON           = $C051     ; Graphics on (mixed mode)
FULL_GR         = $C052     ; Full graphics (no text)
MIX_GR          = $C053     ; Mixed graphics (4 lines text)
PAGE1           = $C054     ; Display page 1
PAGE2           = $C055     ; Display page 2
LORES           = $C056     ; Lo-res graphics
HIRES           = $C057     ; Hi-res graphics

; Apple IIe/IIc extended switches
COL80_OFF       = $C00C     ; 80-column off (IIe)
COL80_ON        = $C00D     ; 80-column on (IIe)
ALTCHAR_OFF     = $C00E     ; Alt charset off (IIe)
ALTCHAR_ON      = $C00F     ; Alt charset on (IIe)

; Memory switches (IIe/IIc)
MAIN_ZP         = $C008     ; Main zero page/stack
AUX_ZP          = $C009     ; Aux zero page/stack
MAIN_RAM        = $C002     ; Main RAM read
AUX_RAM         = $C003     ; Aux RAM read
MAIN_WRITE      = $C004     ; Main RAM write
AUX_WRITE       = $C005     ; Aux RAM write

; Sound
SPEAKER         = $C030     ; Speaker toggle

; Game controllers
PADDLE0         = $C064     ; Paddle 0 (0-255)
PADDLE1         = $C065     ; Paddle 1 (0-255)
PADDLE2         = $C066     ; Paddle 2 (0-255)
PADDLE3         = $C067     ; Paddle 3 (0-255)
BUTTON0         = $C061     ; Button 0 (bit 7)
BUTTON1         = $C062     ; Button 1 (bit 7)
BUTTON2         = $C063     ; Button 2 (bit 7)

; Cassette tape
TAPEOUT         = $C020     ; Cassette output
TAPEIN          = $C060     ; Cassette input

; Serial/parallel (Super Serial Card)
ACIA_DATA       = $C088     ; ACIA data register
ACIA_STATUS     = $C089     ; ACIA status register
ACIA_COMMAND    = $C08A     ; ACIA command register
ACIA_CONTROL    = $C08B     ; ACIA control register

; Disk II controller (slot 6 standard)
DISK_PHASE0_OFF = $C0C0     ; Stepper motor phase 0 off
DISK_PHASE0_ON  = $C0C1     ; Stepper motor phase 0 on
DISK_PHASE1_OFF = $C0C2     ; Stepper motor phase 1 off
DISK_PHASE1_ON  = $C0C3     ; Stepper motor phase 1 on
DISK_PHASE2_OFF = $C0C4     ; Stepper motor phase 2 off
DISK_PHASE2_ON  = $C0C5     ; Stepper motor phase 2 on
DISK_PHASE3_OFF = $C0C6     ; Stepper motor phase 3 off
DISK_PHASE3_ON  = $C0C7     ; Stepper motor phase 3 on
DISK_MOTOR_OFF  = $C0C8     ; Drive motor off
DISK_MOTOR_ON   = $C0C9     ; Drive motor on
DISK_DRIVE1     = $C0CA     ; Select drive 1
DISK_DRIVE2     = $C0CB     ; Select drive 2
DISK_Q6L        = $C0CC     ; Q6 low (read)
DISK_Q6H        = $C0CD     ; Q6 high (write)
DISK_Q7L        = $C0CE     ; Q7 low
DISK_Q7H        = $C0CF     ; Q7 high (write protect)

; ============================================================================
; Monitor ROM Entry Points
; ============================================================================

; Character I/O
COUT            = $FDED     ; Character output
COUT1           = $FDF0     ; Character output (no setup)
CROUT           = $FD8E     ; Carriage return output
PRBYTE          = $FDDA     ; Print byte in hex
PRHEX           = $FDE3     ; Print hex digit
RDKEY           = $FD0C     ; Read key (wait for keypress)
RDCHAR          = $FD35     ; Read character
GETLN           = $FD6A     ; Get line of input
GETLN1          = $FD6F     ; Get line (alt entry)

; Screen control
HOME            = $FC58     ; Clear screen, home cursor
CLREOL          = $FC9C     ; Clear to end of line
CLREOP          = $FC42     ; Clear to end of page
VTAB            = $FC22     ; Vertical tab (set CV)
VTABZ           = $FC24     ; Vertical tab (no range check)
SCROLL          = $FC70     ; Scroll screen up one line
SETINV          = $FE80     ; Set inverse video
SETNORM         = $FE84     ; Set normal video
SETKBD          = $FE89     ; Set input to keyboard
SETVID          = $FE93     ; Set output to video

; Graphics
PLOT            = $F800     ; Plot point in hi-res
HPLOT           = $F457     ; Plot point (same as PLOT)
HLINE           = $F53A     ; Draw horizontal line
HPOSN           = $F411     ; Position hi-res cursor
HCOLOR          = $F6F0     ; Set hi-res color
COLDSW          = $F1D9     ; Color mapping
HCLR            = $F3F2     ; Clear hi-res screen
HGR             = $F3E2     ; Initialize hi-res graphics
HGR2            = $F3D8     ; Initialize hi-res page 2
HFIND           = $F9B4     ; Find hi-res byte
DRAW            = $F601     ; Draw line to point

; Lo-res graphics
GR              = $FB40     ; Initialize lo-res graphics
COLOR_EQ        = $F864     ; Set lo-res color
PLOT_LO         = $F800     ; Plot lo-res point
SCRN            = $F871     ; Read lo-res point

; Utility
WAIT            = $FCA8     ; Wait for keypress
BELL            = $FF3A     ; Ring bell (beep)
MOVE            = $FE2C     ; Move memory block
VERIFY          = $FE36     ; Verify memory block

; Monitor command line
MONITOR         = $FF69     ; Enter monitor
MONZ            = $FF65     ; Monitor warm start

; ============================================================================
; BASIC ROM Entry Points
; ============================================================================

; Error handling
ERROR           = $D412     ; Handle BASIC error
SYNERR          = $DEC9     ; Syntax error

; Variable handling
FRMNUM          = $DD67     ; Evaluate numeric expression
FRMEVL          = $DD7B     ; Evaluate expression
CHKNUM          = $DD6A     ; Check for number
GETADR          = $E752     ; Get address from expression

; String handling
FREFAC          = $D391     ; Free string in FAC
STROUT          = $DB3A     ; Output string

; Math routines (Floating Point)
FADD            = $E7BE     ; Floating add
FSUB            = $E7AA     ; Floating subtract
FMULT           = $E982     ; Floating multiply
FDIV            = $EA66     ; Floating divide
FPWR            = $EE97     ; Floating power
FCOMP           = $E847     ; Floating compare

; ============================================================================
; DOS 3.3 Entry Points
; ============================================================================

; File operations (typical locations - may vary)
DOS_INIT        = $9D84     ; Initialize DOS
DOS_OPEN        = $A000     ; Open file
DOS_CLOSE       = $A004     ; Close file
DOS_READ        = $A008     ; Read file
DOS_WRITE       = $A00C     ; Write file
DOS_DELETE      = $A010     ; Delete file
DOS_CATALOG     = $A014     ; Show catalog
DOS_LOCK        = $A018     ; Lock file
DOS_UNLOCK      = $A01C     ; Unlock file
DOS_RENAME      = $A020     ; Rename file

; ProDOS entry points (for ProDOS systems)
PRODOS          = $BF00     ; ProDOS MLI entry
PRODOS_QUIT     = $65       ; Quit command
PRODOS_CREATE   = $C0       ; Create file
PRODOS_DESTROY  = $C1       ; Delete file
PRODOS_RENAME   = $C2       ; Rename file
PRODOS_OPEN     = $C8       ; Open file
PRODOS_NEWLINE  = $C9       ; Set newline
PRODOS_READ     = $CA       ; Read file
PRODOS_WRITE    = $CB       ; Write file
PRODOS_CLOSE    = $CC       ; Close file
PRODOS_GET_INFO = $C4       ; Get file info

; ============================================================================
; Graphics Colors (Lo-Res)
; ============================================================================

BLACK           = $00       ; Color 0
MAGENTA         = $01       ; Color 1
DARK_BLUE       = $02       ; Color 2
PURPLE          = $03       ; Color 3
DARK_GREEN      = $04       ; Color 4
GRAY1           = $05       ; Color 5
MEDIUM_BLUE     = $06       ; Color 6
LIGHT_BLUE      = $07       ; Color 7
BROWN           = $08       ; Color 8
ORANGE          = $09       ; Color 9
GRAY2           = $0A       ; Color 10
PINK            = $0B       ; Color 11
GREEN           = $0C       ; Color 12
YELLOW          = $0D       ; Color 13
AQUA            = $0E       ; Color 14
WHITE           = $0F       ; Color 15

; ============================================================================
; Hi-Res Colors
; ============================================================================

; Hi-res plotting (color depends on X position)
HI_BLACK        = $00       ; Black
HI_GREEN        = $01       ; Green (odd columns)
HI_PURPLE       = $02       ; Purple (even columns)
HI_WHITE        = $03       ; White

; ============================================================================
; ASCII Values
; ============================================================================

CR              = $0D       ; Carriage return
LF              = $0A       ; Line feed
ESC             = $1B       ; Escape
SPACE           = $20       ; Space
CTRL_C          = $03       ; Control-C (break)
CTRL_G          = $07       ; Control-G (bell)
CTRL_H          = $08       ; Control-H (backspace)
CTRL_L          = $0C       ; Control-L (form feed)

; ============================================================================
; Useful Constants
; ============================================================================

SCREEN_WIDTH    = 40        ; Text screen width
SCREEN_HEIGHT   = 24        ; Text screen height (25 with bottom line)
HIRES_WIDTH     = 280       ; Hi-res width
HIRES_HEIGHT    = 192       ; Hi-res height
LORES_WIDTH     = 40        ; Lo-res width
LORES_HEIGHT    = 48        ; Lo-res height (with mixed mode)

; Memory sizes
TEXT_SIZE       = $400      ; Text page size (1K)
HIRES_SIZE      = $2000     ; Hi-res page size (8K)

; DOS sector size
SECTOR_SIZE     = 256       ; Standard sector size