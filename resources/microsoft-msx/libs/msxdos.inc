; msxdos.inc - MSX-DOS system calls and file handling
; For MSX-DOS 1.x and 2.x compatibility

; ============================================================================
; MSX-DOS System Calls (Function Call 5)
; ============================================================================

; To call MSX-DOS functions:
; LD C, function_number
; LD DE, parameter_address (if needed)
; CALL 0005h

BDOS            EQU $0005   ; BDOS entry point

; ============================================================================
; File and Directory Functions
; ============================================================================

; Basic file operations
_TERM0          EQU $00     ; Program terminate
_CONIN          EQU $01     ; Console input
_CONOUT         EQU $02     ; Console output
_AUXIN          EQU $03     ; Auxiliary input
_AUXOUT         EQU $04     ; Auxiliary output
_LSTOUT         EQU $05     ; List output
_DIRIO          EQU $06     ; Direct console I/O
_DIRIN          EQU $07     ; Direct console input
_INNOE          EQU $08     ; Console input without echo
_STROUT         EQU $09     ; String output
_BUFIN          EQU $0A     ; Buffered line input
_CONST          EQU $0B     ; Console status
_CPMVER         EQU $0C     ; Get CP/M version
_DSKRST         EQU $0D     ; Disk reset
_SELDSK         EQU $0E     ; Select disk
_FOPEN          EQU $0F     ; Open file (FCB)
_FCLOSE         EQU $10     ; Close file (FCB)
_SFIRST         EQU $11     ; Search first (FCB)
_SNEXT          EQU $12     ; Search next (FCB)
_FDEL           EQU $13     ; Delete file (FCB)
_FREAD          EQU $14     ; Sequential read (FCB)
_FWRITE         EQU $15     ; Sequential write (FCB)
_FMAKE          EQU $16     ; Create file (FCB)
_FREN           EQU $17     ; Rename file (FCB)
_LOGIN          EQU $18     ; Get login vector
_CURDRV         EQU $19     ; Get current drive
_SETDTA         EQU $1A     ; Set DTA address
_ALLOC          EQU $1B     ; Get allocation info
_RREAD          EQU $21     ; Random read (FCB)
_RWRITE         EQU $22     ; Random write (FCB)
_FSIZE          EQU $23     ; Get file size (FCB)
_SETRND         EQU $24     ; Set random record (FCB)

; MSX-DOS 2.x extended functions
_DOSVER         EQU $6F     ; Get DOS version
_GETDTA         EQU $2F     ; Get DTA address

; New file handle functions (MSX-DOS 2.x)
_OPEN           EQU $43     ; Open file (handle)
_CREATE         EQU $44     ; Create file (handle)
_CLOSE          EQU $45     ; Close file (handle)
_ENSDIR         EQU $46     ; Ensure directory
_WHOLFI         EQU $47     ; Get whole path
_READ           EQU $48     ; Read from file (handle)
_WRITE          EQU $49     ; Write to file (handle)
_SEEK           EQU $4A     ; Seek in file (handle)
_IOCTL          EQU $4B     ; I/O control
_HTEST          EQU $4C     ; Test file handle
_DELETE         EQU $4D     ; Delete file
_RENAME         EQU $4E     ; Rename file
_MOVE           EQU $4F     ; Move file
_ATTR           EQU $50     ; Get/set file attributes
_FTIME          EQU $51     ; Get/set file time
_HDUP           EQU $52     ; Duplicate file handle
_HDUP2          EQU $53     ; Duplicate file handle 2
_CURDIR         EQU $54     ; Get current directory
_CHDIR          EQU $55     ; Change directory
_PARSE          EQU $56     ; Parse pathname
_PFILE          EQU $57     ; Parse filename
_CHKCHR         EQU $58     ; Check character
_WPATH          EQU $59     ; Get whole path
_FLUSH          EQU $5A     ; Flush disk buffers
_FORK           EQU $5B     ; Fork process
_JOIN           EQU $5C     ; Join process

; ============================================================================
; Memory Management
; ============================================================================

_TERM           EQU $62     ; Terminate with error code
_DEFAB          EQU $63     ; Define abort exit routine
_DEFER          EQU $64     ; Define error handler
_ERROR          EQU $65     ; Print error message
_EXPLAIN        EQU $66     ; Explain error code
_FORMAT         EQU $67     ; Format string
_RAMD           EQU $68     ; Assign/get RAM disk
_BUFFER         EQU $69     ; Assign/get disk buffer
_ASSIGN         EQU $6A     ; Assign/get assign table
_GENV           EQU $6B     ; Get environment string
_SENV           EQU $6C     ; Set environment string
_FENV           EQU $6D     ; Find environment string
_DSKCHK         EQU $6E     ; Check disk change
_DOSVER         EQU $6F     ; Get DOS version

; ============================================================================
; Standard File Handles
; ============================================================================

STDIN           EQU 0       ; Standard input
STDOUT          EQU 1       ; Standard output
STDERR          EQU 2       ; Standard error
STDAUX          EQU 3       ; Standard auxiliary
STDPRN          EQU 4       ; Standard printer

; ============================================================================
; File Attributes
; ============================================================================

ATTR_NORMAL     EQU $00     ; Normal file
ATTR_RDONLY     EQU $01     ; Read-only
ATTR_HIDDEN     EQU $02     ; Hidden
ATTR_SYSTEM     EQU $04     ; System
ATTR_VOLUME     EQU $08     ; Volume label
ATTR_DIRECTORY  EQU $10     ; Directory
ATTR_ARCHIVE    EQU $20     ; Archive

; ============================================================================
; Error Codes
; ============================================================================

ERR_NOFIL       EQU $.NOFIL ; File not found
ERR_NODIR       EQU $.NODIR ; Directory not found
ERR_DRFUL       EQU $.DRFUL ; Directory full
ERR_DKFUL       EQU $.DKFUL ; Disk full
ERR_DUPF        EQU $.DUPF  ; Duplicate filename
ERR_DIRE        EQU $.DIRE  ; Invalid directory move
ERR_FILRO       EQU $.FILRO ; Read-only file
ERR_DIRNE       EQU $.DIRNE ; Directory not empty
ERR_IPATH       EQU $.IPATH ; Invalid pathname
ERR_PLONG       EQU $.PLONG ; Pathname too long
ERR_NHAND       EQU $.NHAND ; No spare file handles
ERR_IHAND       EQU $.IHAND ; Invalid file handle
ERR_NOPEN       EQU $.NOPEN ; File not open
ERR_IDEV        EQU $.IDEV  ; Invalid device operation
ERR_ELONG       EQU $.ELONG ; Environment string too long
ERR_IENV        EQU $.IENV  ; Invalid environment string
ERR_IFORM       EQU $.IFORM ; Invalid format
ERR_IACCS       EQU $.IACCS ; Invalid access code
ERR_IPROC       EQU $.IPROC ; Invalid process ID
ERR_NPROC       EQU $.NPROC ; No child processes

; ============================================================================
; FCB (File Control Block) Structure
; ============================================================================

FCB_DRIVE       EQU 0       ; Drive number (0=default, 1=A:, etc.)
FCB_NAME        EQU 1       ; Filename (8 bytes)
FCB_EXT         EQU 9       ; Extension (3 bytes)
FCB_CURBLK      EQU 12      ; Current block number
FCB_RECSIZE     EQU 14      ; Record size
FCB_FILESIZE    EQU 16      ; File size (4 bytes)
FCB_DATE        EQU 20      ; Date stamp
FCB_TIME        EQU 22      ; Time stamp
FCB_DEVICE      EQU 24      ; Device ID
FCB_DIRPOS      EQU 25      ; Directory position
FCB_CLUSTER     EQU 26      ; First cluster
FCB_LASTCLUS    EQU 28      ; Last cluster accessed
FCB_CLSPOS      EQU 30      ; Position in cluster
FCB_CURREC      EQU 32      ; Current record number
FCB_RANREC      EQU 33      ; Random record number (3 bytes)

FCB_SIZE        EQU 37      ; Total FCB size

; ============================================================================
; Useful Macros
; ============================================================================

; Print string terminated by '$'
PRINT_STRING MACRO string_addr
    LD DE, string_addr
    LD C, _STROUT
    CALL BDOS
ENDM

; Print character in A
PRINT_CHAR MACRO
    LD E, A
    LD C, _CONOUT
    CALL BDOS
ENDM

; Read character into A
READ_CHAR MACRO
    LD C, _CONIN
    CALL BDOS
ENDM

; Open file using filename string
OPEN_FILE MACRO filename, mode
    LD DE, filename
    LD A, mode
    LD C, _OPEN
    CALL BDOS
ENDM

; Close file handle in A
CLOSE_FILE MACRO
    LD B, A
    LD C, _CLOSE
    CALL BDOS
ENDM

; Exit program with code in A
EXIT_PROGRAM MACRO
    LD B, A
    LD C, _TERM
    CALL BDOS
ENDM

; ============================================================================
; Common File Operations
; ============================================================================

; Simple file copy template
; Copy file from DE (source) to HL (destination)
copy_file:
    ; Implementation would go here
    ; Open source, create destination, read/write loop, close both
    ret

; Get file size (returns size in DEHL)
get_file_size:
    ; Implementation would go here
    ; Use _OPEN and _SEEK to end, then get position
    ret

; Check if file exists (returns Z flag set if exists)
file_exists:
    ; Implementation would go here
    ; Try to open file, check for success
    ret