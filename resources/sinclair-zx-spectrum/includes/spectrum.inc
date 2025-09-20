; spectrum.inc - ZX Spectrum 48K Memory Map and ROM Routines
; For use with SjASMPlus or other Z80 assemblers

; ============================================================================
; Memory Map
; ============================================================================

ROM_START       EQU $0000   ; ROM start
ROM_END         EQU $3FFF   ; ROM end (16KB)

SCREEN_START    EQU $4000   ; Screen display file (bitmap)
SCREEN_END      EQU $57FF   ; End of bitmap (6KB)
ATTR_START      EQU $5800   ; Screen attributes (colors)
ATTR_END        EQU $5AFF   ; End of attributes (768 bytes)

PRINTER_BUFFER  EQU $5B00   ; Printer buffer (256 bytes)

SYSVARS_START   EQU $5C00   ; System variables
SYSVARS_END     EQU $5CBF   ; End of system variables

FREE_RAM        EQU $5CCB   ; Start of free RAM
PROG_START      EQU $5CCB   ; BASIC program starts here
SP_INIT         EQU $FF50   ; Initial stack pointer

; ============================================================================
; Important System Variables
; ============================================================================

; $5C00 area
KSTATE          EQU $5C00   ; Keyboard state (8 bytes)
LAST_K          EQU $5C08   ; Last key pressed
REPDEL          EQU $5C09   ; Delay before key repeat
REPPER          EQU $5C0A   ; Period between repeats
DEFADD          EQU $5C0B   ; Default argument address
K_DATA          EQU $5C0D   ; Second byte of color
TVDATA          EQU $5C0E   ; TV data
STRMS           EQU $5C10   ; Stream addresses (38 bytes)
CHARS           EQU $5C36   ; 256 less than address of charset
RASP            EQU $5C38   ; Buzzer timing
PIP             EQU $5C39   ; Key click timing
ERR_NR          EQU $5C3A   ; BASIC error number
FLAGS           EQU $5C3B   ; Various flags
TV_FLAG         EQU $5C3C   ; TV flags
ERR_SP          EQU $5C3D   ; Error stack pointer
LIST_SP         EQU $5C3F   ; LIST stack pointer
MODE            EQU $5C41   ; Input mode
NEWPPC          EQU $5C42   ; New program counter
NSPPC           EQU $5C44   ; New statement
PPC             EQU $5C45   ; Program counter
SUBPPC          EQU $5C47   ; Statement number
BORDCR          EQU $5C48   ; Border color (and attributes)
E_PPC           EQU $5C49   ; Edit line number
VARS            EQU $5C4B   ; Variables area
DEST            EQU $5C4D   ; Destination
CHANS           EQU $5C4F   ; Channel information
CURCHL          EQU $5C51   ; Current channel
PROG            EQU $5C53   ; BASIC program area
NXTLIN          EQU $5C55   ; Next line
DATADD          EQU $5C57   ; DATA address
E_LINE          EQU $5C59   ; Edit line
K_CUR           EQU $5C5B   ; Cursor address
CH_ADD          EQU $5C5D   ; Character position
X_PTR           EQU $5C5F   ; X pointer
WORKSP          EQU $5C61   ; Workspace
STKBOT          EQU $5C63   ; Stack bottom
STKEND          EQU $5C65   ; Stack end
B_FONT          EQU $5C67   ; Bold font flag
RAMTOP          EQU $5C69   ; Top of RAM
P_RAMT          EQU $5C6B   ; Physical RAM top
MEM             EQU $5C68   ; Memory
FLAGS2          EQU $5C6A   ; More flags
DF_SZ           EQU $5C6B   ; Display file size
S_TOP           EQU $5C6C   ; Screen top
OLDPPC          EQU $5C6E   ; Old program counter
OSPCC           EQU $5C70   ; Old statement
FLAGX           EQU $5C71   ; Extra flags
STRLEN          EQU $5C72   ; String length
T_ADDR          EQU $5C74   ; Temp address
SEED            EQU $5C76   ; Random seed
FRAMES          EQU $5C78   ; Frame counter (3 bytes)
UDG             EQU $5C7B   ; User defined graphics
COORDS_X        EQU $5C7D   ; X coordinate
COORDS_Y        EQU $5C7E   ; Y coordinate
P_FLAG          EQU $5C7F   ; Permanent flag
ATTR_P          EQU $5C8D   ; Permanent attributes
ATTR_T          EQU $5C8F   ; Temporary attributes
MASK_P          EQU $5C8E   ; Permanent mask
MASK_T          EQU $5C90   ; Temporary mask

; ============================================================================
; ROM Routines (useful entry points)
; ============================================================================

; Display routines
CLS             EQU $0D6B   ; Clear screen (attr in A)
CL_ALL          EQU $0DAF   ; Clear whole display
PRINT_A         EQU $0010   ; Print character in A register
PRINT_STR       EQU $203C   ; Print string (DE = address)
AT_CONTROL      EQU $0ADC   ; AT control (B=Y, C=X)

; Keyboard routines
KEY_SCAN        EQU $028E   ; Scan keyboard
WAIT_KEY        EQU $15D4   ; Wait for key press
BREAK_KEY       EQU $1F54   ; Test BREAK key

; Sound routines
BEEP            EQU $03B5   ; Beep (DE = duration, HL = pitch)
BEEPER          EQU $03B5   ; Alternative name

; Math routines
MULT_8x8        EQU $30A9   ; Multiply H * E -> HL
DIV_16x8        EQU $31AF   ; Divide HL / C -> HL rem A

; Utility routines
DELAY           EQU $1F3D   ; Delay BC * 26 T-states
RANDOM          EQU $2596   ; Random number generator

; ============================================================================
; I/O Ports
; ============================================================================

PORT_FE         EQU $FE     ; ULA port (border, speaker, keyboard)
PORT_KEMPSTON   EQU $1F     ; Kempston joystick

; Keyboard half-rows (for IN A,($FE) with A containing row)
KB_ROW_VCXZ_CS  EQU $FEFE   ; V,C,X,Z,Caps Shift
KB_ROW_GFDSA    EQU $FDFE   ; G,F,D,S,A
KB_ROW_TREWQ    EQU $FBFE   ; T,R,E,W,Q
KB_ROW_54321    EQU $F7FE   ; 5,4,3,2,1
KB_ROW_67890    EQU $EFFE   ; 6,7,8,9,0
KB_ROW_YUIOP    EQU $DFFE   ; Y,U,I,O,P
KB_ROW_HJKL_EN  EQU $BFFE   ; H,J,K,L,Enter
KB_ROW_BNM_SS   EQU $7FFE   ; B,N,M,Sym Shift,Space

; ============================================================================
; Colors and Attributes
; ============================================================================

; Attribute byte format: FBPPPIII
; F=Flash, B=Bright, P=Paper (background), I=Ink (foreground)

BLACK           EQU 0
BLUE            EQU 1
RED             EQU 2
MAGENTA         EQU 3
GREEN           EQU 4
CYAN            EQU 5
YELLOW          EQU 6
WHITE           EQU 7

BRIGHT          EQU 64      ; Bright bit
FLASH           EQU 128     ; Flash bit

; Attribute calculation
ATTR            MACRO paper, ink, bright, flash
                DB (flash*128) + (bright*64) + (paper*8) + ink
                ENDM

; Border colors (OUT ($FE),A with color in bits 0-2)
BORDER_BLACK    EQU 0
BORDER_BLUE     EQU 1
BORDER_RED      EQU 2
BORDER_MAGENTA  EQU 3
BORDER_GREEN    EQU 4
BORDER_CYAN     EQU 5
BORDER_YELLOW   EQU 6
BORDER_WHITE    EQU 7