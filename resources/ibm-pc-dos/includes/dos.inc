; dos.inc - IBM PC DOS System Definitions and Hardware
; For use with NASM, MASM, or other x86 assemblers
; Covers DOS 1.x through 6.x, BIOS, and hardware interfaces

; ============================================================================
; Memory Map (Real Mode)
; ============================================================================

; Interrupt Vector Table
IVT_BASE            equ 0x0000      ; Interrupt vectors (1KB)

; BIOS Data Area
BIOS_DATA           equ 0x0400      ; BIOS data area (256 bytes)

; DOS Data Areas
DOS_DATA            equ 0x0500      ; DOS data area start
COMMAND_LINE        equ 0x0080      ; Command line parameters (128 bytes)

; Conventional Memory
CONV_MEM_START      equ 0x0600      ; Start of available conventional memory
CONV_MEM_END        equ 0xA0000     ; End of conventional memory (640KB)

; Video Memory
VIDEO_MEM_MONO      equ 0xB0000     ; Monochrome video memory
VIDEO_MEM_CGA       equ 0xB8000     ; CGA/EGA/VGA color video memory
VIDEO_MEM_EGA       equ 0xA0000     ; EGA/VGA graphics memory

; ROM Areas
ROM_BIOS_START      equ 0xF0000     ; ROM BIOS start
ROM_BIOS_END        equ 0xFFFFF     ; ROM BIOS end

; ============================================================================
; DOS Function Calls (INT 21h)
; ============================================================================

; Character I/O
DOS_TERMINATE       equ 0x00        ; Program terminate
DOS_CHAR_INPUT      equ 0x01        ; Character input with echo
DOS_CHAR_OUTPUT     equ 0x02        ; Character output
DOS_AUX_INPUT       equ 0x03        ; Auxiliary input
DOS_AUX_OUTPUT      equ 0x04        ; Auxiliary output
DOS_PRINTER_OUTPUT  equ 0x05        ; Printer output
DOS_DIRECT_IO       equ 0x06        ; Direct console I/O
DOS_DIRECT_INPUT    equ 0x07        ; Direct console input (no echo)
DOS_CHAR_INPUT_NE   equ 0x08        ; Character input without echo
DOS_STRING_OUTPUT   equ 0x09        ; String output
DOS_BUFFERED_INPUT  equ 0x0A        ; Buffered keyboard input
DOS_CHECK_INPUT     equ 0x0B        ; Check keyboard status

; Drive and Directory
DOS_SELECT_DRIVE    equ 0x0E        ; Select drive
DOS_CURRENT_DRIVE   equ 0x19        ; Get current drive
DOS_SET_DTA         equ 0x1A        ; Set Disk Transfer Area
DOS_GET_DEFAULT     equ 0x2F        ; Get Disk Transfer Area
DOS_GET_VERSION     equ 0x30        ; Get DOS version
DOS_KEEP_RESIDENT   equ 0x31        ; Terminate and stay resident
DOS_GET_DRIVE_INFO  equ 0x36        ; Get drive allocation info
DOS_MKDIR           equ 0x39        ; Make directory
DOS_RMDIR           equ 0x3A        ; Remove directory
DOS_CHDIR           equ 0x3B        ; Change directory
DOS_GET_CWD         equ 0x47        ; Get current working directory

; File Operations
DOS_CREATE_FILE     equ 0x3C        ; Create file
DOS_OPEN_FILE       equ 0x3D        ; Open file
DOS_CLOSE_FILE      equ 0x3E        ; Close file
DOS_READ_FILE       equ 0x3F        ; Read from file
DOS_WRITE_FILE      equ 0x40        ; Write to file
DOS_DELETE_FILE     equ 0x41        ; Delete file
DOS_SEEK_FILE       equ 0x42        ; Move file pointer
DOS_GET_ATTRIBUTES  equ 0x43        ; Get/set file attributes
DOS_IOCTL           equ 0x44        ; I/O control
DOS_DUPLICATE_HANDLE equ 0x45       ; Duplicate file handle
DOS_FORCE_DUPLICATE equ 0x46        ; Force duplicate handle
DOS_GET_CWD_PATH    equ 0x47        ; Get current directory
DOS_ALLOCATE_MEM    equ 0x48        ; Allocate memory
DOS_FREE_MEM        equ 0x49        ; Free memory
DOS_RESIZE_MEM      equ 0x4A        ; Resize memory block
DOS_EXEC            equ 0x4B        ; Execute program
DOS_TERMINATE_CODE  equ 0x4C        ; Terminate with return code
DOS_GET_RETURN_CODE equ 0x4D        ; Get return code
DOS_FIND_FIRST      equ 0x4E        ; Find first file
DOS_FIND_NEXT       equ 0x4F        ; Find next file
DOS_SET_PSP         equ 0x50        ; Set PSP segment
DOS_GET_PSP         equ 0x51        ; Get PSP segment
DOS_GET_LIST        equ 0x52        ; Get list of lists (undocumented)
DOS_CREATE_PSP      equ 0x55        ; Create PSP
DOS_RENAME_FILE     equ 0x56        ; Rename file
DOS_GET_SET_TIME    equ 0x57        ; Get/set file date and time

; Extended Functions (DOS 3.0+)
DOS_GET_VERIFY      equ 0x54        ; Get verify flag
DOS_SET_VERIFY      equ 0x2E        ; Set verify flag
DOS_CREATE_TEMP     equ 0x5A        ; Create temporary file
DOS_CREATE_NEW      equ 0x5B        ; Create new file
DOS_LOCK_UNLOCK     equ 0x5C        ; Lock/unlock file region
DOS_NETWORK         equ 0x5F        ; Network functions

; File Access Modes
FILE_READ_ONLY      equ 0x00        ; Read only
FILE_WRITE_ONLY     equ 0x01        ; Write only
FILE_READ_WRITE     equ 0x02        ; Read/write
FILE_DENY_NONE      equ 0x40        ; Deny none (sharing)
FILE_DENY_READ      equ 0x30        ; Deny read
FILE_DENY_WRITE     equ 0x20        ; Deny write
FILE_DENY_ALL       equ 0x10        ; Deny all

; File Attributes
ATTR_NORMAL         equ 0x00        ; Normal file
ATTR_READ_ONLY      equ 0x01        ; Read only
ATTR_HIDDEN         equ 0x02        ; Hidden
ATTR_SYSTEM         equ 0x04        ; System
ATTR_VOLUME_LABEL   equ 0x08        ; Volume label
ATTR_DIRECTORY      equ 0x10        ; Directory
ATTR_ARCHIVE        equ 0x20        ; Archive

; ============================================================================
; BIOS Interrupts
; ============================================================================

; Video Services (INT 10h)
VIDEO_SET_MODE      equ 0x00        ; Set video mode
VIDEO_SET_CURSOR    equ 0x01        ; Set cursor type
VIDEO_SET_CURSOR_POS equ 0x02       ; Set cursor position
VIDEO_GET_CURSOR_POS equ 0x03       ; Get cursor position
VIDEO_GET_LIGHT_PEN equ 0x04        ; Get light pen position
VIDEO_SELECT_PAGE   equ 0x05        ; Select active display page
VIDEO_SCROLL_UP     equ 0x06        ; Scroll window up
VIDEO_SCROLL_DOWN   equ 0x07        ; Scroll window down
VIDEO_READ_CHAR     equ 0x08        ; Read character and attribute
VIDEO_WRITE_CHAR    equ 0x09        ; Write character and attribute
VIDEO_WRITE_CHAR_ONLY equ 0x0A      ; Write character only
VIDEO_SET_COLOR     equ 0x0B        ; Set color palette
VIDEO_WRITE_PIXEL   equ 0x0C        ; Write pixel
VIDEO_READ_PIXEL    equ 0x0D        ; Read pixel
VIDEO_WRITE_TTY     equ 0x0E        ; Write character in TTY mode
VIDEO_GET_MODE      equ 0x0F        ; Get current video mode

; Keyboard Services (INT 16h)
KB_READ_KEY         equ 0x00        ; Read keyboard key
KB_CHECK_KEY        equ 0x01        ; Check for keystroke
KB_GET_STATUS       equ 0x02        ; Get keyboard status flags
KB_SET_RATE         equ 0x03        ; Set typematic rate
KB_READ_KEY_EXT     equ 0x10        ; Read extended keystroke
KB_CHECK_KEY_EXT    equ 0x11        ; Check extended keystroke
KB_GET_STATUS_EXT   equ 0x12        ; Get extended keyboard status

; Disk Services (INT 13h)
DISK_RESET          equ 0x00        ; Reset disk system
DISK_GET_STATUS     equ 0x01        ; Get disk status
DISK_READ_SECTORS   equ 0x02        ; Read sectors
DISK_WRITE_SECTORS  equ 0x03        ; Write sectors
DISK_VERIFY_SECTORS equ 0x04        ; Verify sectors
DISK_FORMAT_TRACK   equ 0x05        ; Format track
DISK_GET_PARAMS     equ 0x08        ; Get drive parameters
DISK_INIT_FIXED     equ 0x09        ; Initialize fixed disk
DISK_READ_LONG      equ 0x0A        ; Read long sectors
DISK_WRITE_LONG     equ 0x0B        ; Write long sectors
DISK_SEEK           equ 0x0C        ; Seek to cylinder
DISK_RESET_FIXED    equ 0x0D        ; Reset fixed disk
DISK_READ_SECTOR_BUFFER equ 0x0E    ; Read sector buffer
DISK_WRITE_SECTOR_BUFFER equ 0x0F   ; Write sector buffer
DISK_TEST_READY     equ 0x10        ; Test for drive ready
DISK_RECALIBRATE    equ 0x11        ; Recalibrate drive
DISK_RAM_DIAGNOSTIC equ 0x14        ; Controller RAM diagnostic

; Serial Port Services (INT 14h)
SERIAL_INIT         equ 0x00        ; Initialize serial port
SERIAL_SEND_CHAR    equ 0x01        ; Send character
SERIAL_RECEIVE_CHAR equ 0x02        ; Receive character
SERIAL_GET_STATUS   equ 0x03        ; Get port status

; Parallel Port Services (INT 17h)
PARALLEL_SEND_CHAR  equ 0x00        ; Send character to printer
PARALLEL_INIT_PORT  equ 0x01        ; Initialize printer port
PARALLEL_GET_STATUS equ 0x02        ; Get printer status

; System Services (INT 15h)
SYS_CASSETTE        equ 0x0F        ; Cassette services
SYS_GET_CONFIG      equ 0xC0        ; Get system configuration
SYS_GET_MEMORY_SIZE equ 0x88        ; Get extended memory size
SYS_MOVE_BLOCK      equ 0x87        ; Move memory block
SYS_GET_A20_STATE   equ 0x2400      ; Get A20 gate state
SYS_SET_A20_STATE   equ 0x2401      ; Set A20 gate state

; Time Services (INT 1Ah)
TIME_GET_CLOCK      equ 0x00        ; Get system clock count
TIME_SET_CLOCK      equ 0x01        ; Set system clock count
TIME_GET_TIME       equ 0x02        ; Get real-time clock time
TIME_SET_TIME       equ 0x03        ; Set real-time clock time
TIME_GET_DATE       equ 0x04        ; Get real-time clock date
TIME_SET_DATE       equ 0x05        ; Set real-time clock date
TIME_SET_ALARM      equ 0x06        ; Set alarm
TIME_RESET_ALARM    equ 0x07        ; Reset alarm

; ============================================================================
; Hardware Ports
; ============================================================================

; 8259 Programmable Interrupt Controller
PIC1_COMMAND        equ 0x20        ; Master PIC command port
PIC1_DATA           equ 0x21        ; Master PIC data port
PIC2_COMMAND        equ 0xA0        ; Slave PIC command port
PIC2_DATA           equ 0xA1        ; Slave PIC data port

; 8253/8254 Programmable Interval Timer
PIT_COUNTER0        equ 0x40        ; Counter 0 (system timer)
PIT_COUNTER1        equ 0x41        ; Counter 1 (DRAM refresh)
PIT_COUNTER2        equ 0x42        ; Counter 2 (speaker)
PIT_CONTROL         equ 0x43        ; Control register

; 8255 Programmable Peripheral Interface (System Board)
PPI_PORT_A          equ 0x60        ; Keyboard data
PPI_PORT_B          equ 0x61        ; System control port
PPI_PORT_C          equ 0x62        ; Configuration switches
PPI_CONTROL         equ 0x63        ; Control register

; DMA Controller (8237)
DMA_CH0_ADDR        equ 0x00        ; Channel 0 address
DMA_CH0_COUNT       equ 0x01        ; Channel 0 count
DMA_CH1_ADDR        equ 0x02        ; Channel 1 address
DMA_CH1_COUNT       equ 0x03        ; Channel 1 count
DMA_CH2_ADDR        equ 0x04        ; Channel 2 address
DMA_CH2_COUNT       equ 0x05        ; Channel 2 count
DMA_CH3_ADDR        equ 0x06        ; Channel 3 address
DMA_CH3_COUNT       equ 0x07        ; Channel 3 count
DMA_STATUS          equ 0x08        ; Status register
DMA_COMMAND         equ 0x08        ; Command register
DMA_REQUEST         equ 0x09        ; Request register
DMA_MASK            equ 0x0A        ; Single channel mask
DMA_MODE            equ 0x0B        ; Mode register
DMA_CLEAR_FF        equ 0x0C        ; Clear flip-flop
DMA_TEMP            equ 0x0D        ; Temporary register
DMA_MASTER_CLEAR    equ 0x0D        ; Master clear
DMA_CLEAR_MASK      equ 0x0E        ; Clear mask register
DMA_WRITE_MASK      equ 0x0F        ; Write all mask bits

; Serial Ports (8250/16450/16550)
COM1_BASE           equ 0x3F8       ; COM1 base address
COM2_BASE           equ 0x2F8       ; COM2 base address
COM3_BASE           equ 0x3E8       ; COM3 base address
COM4_BASE           equ 0x2E8       ; COM4 base address

; Parallel Ports
LPT1_DATA           equ 0x378       ; LPT1 data port
LPT1_STATUS         equ 0x379       ; LPT1 status port
LPT1_CONTROL        equ 0x37A       ; LPT1 control port
LPT2_DATA           equ 0x278       ; LPT2 data port
LPT2_STATUS         equ 0x279       ; LPT2 status port
LPT2_CONTROL        equ 0x27A       ; LPT2 control port

; Floppy Disk Controller
FDC_STATUS_A        equ 0x3F0       ; Status register A
FDC_STATUS_B        equ 0x3F1       ; Status register B
FDC_DOR             equ 0x3F2       ; Digital output register
FDC_TDR             equ 0x3F3       ; Tape drive register
FDC_MSR             equ 0x3F4       ; Main status register
FDC_DSR             equ 0x3F4       ; Data rate select register
FDC_DATA            equ 0x3F5       ; Data register
FDC_DIR             equ 0x3F7       ; Digital input register
FDC_CCR             equ 0x3F7       ; Configuration control register

; Hard Disk Controller (XT)
HDC_DATA            equ 0x320       ; Data register
HDC_ERROR           equ 0x321       ; Error register
HDC_PRECOMP         equ 0x321       ; Write precompensation
HDC_SECTOR_COUNT    equ 0x322       ; Sector count
HDC_SECTOR_NUM      equ 0x323       ; Sector number
HDC_CYL_LOW         equ 0x324       ; Cylinder low
HDC_CYL_HIGH        equ 0x325       ; Cylinder high
HDC_DRIVE_HEAD      equ 0x326       ; Drive/head select
HDC_STATUS          equ 0x327       ; Status register
HDC_COMMAND         equ 0x327       ; Command register

; ============================================================================
; Video Modes
; ============================================================================

; Text modes
MODE_40x25_BW       equ 0x00        ; 40x25 B&W text
MODE_40x25_COLOR    equ 0x01        ; 40x25 16-color text
MODE_80x25_BW       equ 0x02        ; 80x25 B&W text
MODE_80x25_COLOR    equ 0x03        ; 80x25 16-color text
MODE_80x43_COLOR    equ 0x03        ; 80x43 EGA text (with font change)
MODE_80x50_COLOR    equ 0x03        ; 80x50 VGA text (with font change)

; Graphics modes
MODE_320x200_4COLOR equ 0x04        ; 320x200 4-color graphics (CGA)
MODE_320x200_BW     equ 0x05        ; 320x200 B&W graphics (CGA)
MODE_640x200_BW     equ 0x06        ; 640x200 B&W graphics (CGA)
MODE_80x25_MONO     equ 0x07        ; 80x25 monochrome text
MODE_160x200_16COLOR equ 0x08       ; 160x200 16-color graphics (PCjr)
MODE_320x200_16COLOR equ 0x09       ; 320x200 16-color graphics (PCjr)
MODE_640x200_4COLOR equ 0x0A        ; 640x200 4-color graphics (PCjr)
MODE_320x200_256COLOR equ 0x13      ; 320x200 256-color graphics (VGA)
MODE_640x480_16COLOR equ 0x12       ; 640x480 16-color graphics (VGA)
MODE_640x480_BW     equ 0x11        ; 640x480 B&W graphics (VGA)
MODE_640x350_16COLOR equ 0x10       ; 640x350 16-color graphics (EGA)
MODE_640x350_BW     equ 0x0F        ; 640x350 B&W graphics (EGA)
MODE_640x200_16COLOR equ 0x0E       ; 640x200 16-color graphics (EGA)
MODE_320x200_EGA    equ 0x0D        ; 320x200 16-color graphics (EGA)

; ============================================================================
; Common ASCII Codes
; ============================================================================

ASCII_NULL          equ 0x00        ; Null character
ASCII_BELL          equ 0x07        ; Bell
ASCII_BACKSPACE     equ 0x08        ; Backspace
ASCII_TAB           equ 0x09        ; Horizontal tab
ASCII_LF            equ 0x0A        ; Line feed
ASCII_CR            equ 0x0D        ; Carriage return
ASCII_EOF           equ 0x1A        ; End of file (Ctrl+Z)
ASCII_ESC           equ 0x1B        ; Escape
ASCII_SPACE         equ 0x20        ; Space

; ============================================================================
; Error Codes
; ============================================================================

ERROR_SUCCESS       equ 0x00        ; Success
ERROR_INVALID_FUNC  equ 0x01        ; Invalid function
ERROR_FILE_NOT_FOUND equ 0x02       ; File not found
ERROR_PATH_NOT_FOUND equ 0x03       ; Path not found
ERROR_TOO_MANY_OPEN equ 0x04        ; Too many open files
ERROR_ACCESS_DENIED equ 0x05        ; Access denied
ERROR_INVALID_HANDLE equ 0x06       ; Invalid handle
ERROR_ARENA_TRASHED equ 0x07        ; Memory control blocks destroyed
ERROR_NOT_ENOUGH_MEM equ 0x08       ; Not enough memory
ERROR_INVALID_BLOCK equ 0x09        ; Invalid memory block address
ERROR_BAD_ENVIRONMENT equ 0x0A      ; Invalid environment
ERROR_BAD_FORMAT    equ 0x0B        ; Invalid format
ERROR_INVALID_ACCESS equ 0x0C       ; Invalid access code
ERROR_INVALID_DATA  equ 0x0D        ; Invalid data
ERROR_INVALID_DRIVE equ 0x0F        ; Invalid drive specified
ERROR_CURRENT_DIR   equ 0x10        ; Attempt to remove current directory
ERROR_NOT_SAME_DEVICE equ 0x11      ; Not same device
ERROR_NO_MORE_FILES equ 0x12        ; No more files

; ============================================================================
; PSP (Program Segment Prefix) Structure
; ============================================================================

PSP_INT20           equ 0x00        ; INT 20h instruction
PSP_MEM_TOP         equ 0x02        ; Top of memory (segment)
PSP_RESERVED1       equ 0x04        ; Reserved
PSP_DOS_CALL        equ 0x05        ; Far call to DOS
PSP_TERM_ADDR       equ 0x0A        ; Terminate address
PSP_CTRL_BREAK_ADDR equ 0x0E        ; Ctrl+Break address
PSP_CRITICAL_ADDR   equ 0x12        ; Critical error address
PSP_PARENT_PSP      equ 0x16        ; Parent PSP segment
PSP_FILE_TABLE      equ 0x18        ; File handle table
PSP_ENV_SEG         equ 0x2C        ; Environment segment
PSP_SS_SP           equ 0x2E        ; SS:SP on entry
PSP_FILE_COUNT      equ 0x32        ; File handle count
PSP_FILE_PTR        equ 0x34        ; File handle table pointer
PSP_PREV_PSP        equ 0x38        ; Previous PSP pointer
PSP_RESERVED2       equ 0x3C        ; Reserved
PSP_DOS_VERSION     equ 0x40        ; DOS version
PSP_RESERVED3       equ 0x41        ; Reserved
PSP_INT21_RETF      equ 0x50        ; INT 21h RETF instruction
PSP_RESERVED4       equ 0x53        ; Reserved
PSP_FCB1            equ 0x5C        ; FCB #1
PSP_FCB2            equ 0x6C        ; FCB #2
PSP_COMMAND_COUNT   equ 0x80        ; Command line length
PSP_COMMAND_LINE    equ 0x81        ; Command line (127 bytes)

; ============================================================================
; Useful Constants
; ============================================================================

SECTOR_SIZE         equ 512         ; Standard sector size
MAX_PATH            equ 260         ; Maximum path length
MAX_FILENAME        equ 12          ; 8.3 filename format
STDIN               equ 0           ; Standard input handle
STDOUT              equ 1           ; Standard output handle
STDERR              equ 2           ; Standard error handle
STDAUX              equ 3           ; Standard auxiliary handle
STDPRN              equ 4           ; Standard printer handle