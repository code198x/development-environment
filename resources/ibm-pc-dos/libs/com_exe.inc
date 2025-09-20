; com_exe.inc - DOS COM and EXE File Format Creation
; Utilities for creating DOS executables

; ============================================================================
; COM File Format
; ============================================================================

; COM files are simple memory images loaded at offset 0x100 in a segment
; Maximum size: 65536 - 256 = 65280 bytes
; No header, no relocation, code starts immediately

; Create a COM file header
%macro COM_START 0
    BITS 16
    ORG 0x100                   ; COM files start at offset 0x100
%endmacro

; End COM file (optional - can just use RET or INT 20h)
%macro COM_END 0
    ; Terminate program
    mov ah, DOS_TERMINATE_CODE
    mov al, 0                   ; Exit code 0
    int 0x21
%endmacro

; Simple COM file termination
%macro COM_EXIT 1
    mov ah, DOS_TERMINATE_CODE
    mov al, %1                  ; Exit code
    int 0x21
%endmacro

; ============================================================================
; EXE File Format (MZ Header)
; ============================================================================

; EXE header structure (28 bytes minimum)
struc EXE_HEADER
    .signature      resw 1      ; 'MZ' or 'ZM'
    .bytes_in_last  resw 1      ; Bytes in last 512-byte page
    .pages_in_file  resw 1      ; Pages in file (512 bytes each)
    .relocations    resw 1      ; Number of relocation entries
    .header_size    resw 1      ; Header size in paragraphs
    .min_alloc      resw 1      ; Minimum extra paragraphs
    .max_alloc      resw 1      ; Maximum extra paragraphs
    .initial_ss     resw 1      ; Initial SS value (relative)
    .initial_sp     resw 1      ; Initial SP value
    .checksum       resw 1      ; Checksum (usually 0)
    .initial_ip     resw 1      ; Initial IP value
    .initial_cs     resw 1      ; Initial CS value (relative)
    .reloc_table    resw 1      ; Relocation table offset
    .overlay_num    resw 1      ; Overlay number (0 for main program)
endstruc

; EXE file signature
EXE_SIGNATURE       equ 0x5A4D      ; 'MZ'
EXE_SIGNATURE_ALT   equ 0x4D5A      ; 'ZM' (alternative)

; Relocation table entry
struc RELOCATION
    .offset         resw 1      ; Offset within segment
    .segment        resw 1      ; Segment
endstruc

; ============================================================================
; EXE File Creation Macros
; ============================================================================

; Start an EXE file with proper header
%macro EXE_START 4
    ; Parameters: entry_point, stack_size, min_memory, max_memory

    BITS 16

    ; EXE header
    section .header
    exe_header:
        dw EXE_SIGNATURE            ; Signature 'MZ'
        dw 0                        ; Bytes in last page (filled by linker)
        dw 0                        ; Pages in file (filled by linker)
        dw 0                        ; Number of relocations
        dw exe_header_size / 16     ; Header size in paragraphs
        dw %3                       ; Minimum allocation (paragraphs)
        dw %4                       ; Maximum allocation (paragraphs)
        dw stack_segment            ; Initial SS (relative)
        dw %2                       ; Initial SP
        dw 0                        ; Checksum
        dw %1                       ; Initial IP
        dw code_segment             ; Initial CS (relative)
        dw relocation_table         ; Relocation table offset
        dw 0                        ; Overlay number

    exe_header_size equ $ - exe_header

    ; Relocation table (empty for simple programs)
    relocation_table:
        ; No relocations needed for simple programs

    ; Pad to paragraph boundary
    times (16 - ($ - $$) % 16) % 16 db 0

    ; Code segment
    section .text
    code_segment equ ($ - $$) / 16
%1:
%endmacro

; Define stack segment for EXE
%macro EXE_STACK 1
    section .stack
    stack_segment equ ($ - $$) / 16
    resb %1                     ; Stack size in bytes
%endmacro

; ============================================================================
; DOS Program Structure Macros
; ============================================================================

; Standard DOS program initialization
%macro DOS_INIT 0
    ; Save original DS and ES
    push ds
    push es

    ; Set up segments (for EXE files)
    mov ax, cs
    mov ds, ax
    mov es, ax
%endmacro

; Standard DOS program cleanup
%macro DOS_CLEANUP 0
    ; Restore original segments
    pop es
    pop ds
%endmacro

; Print string (DS:DX points to '$' terminated string)
%macro PRINT_STRING 1
    mov dx, %1
    mov ah, DOS_STRING_OUTPUT
    int 0x21
%endmacro

; Print character
%macro PRINT_CHAR 1
    mov dl, %1
    mov ah, DOS_CHAR_OUTPUT
    int 0x21
%endmacro

; Read character with echo
%macro READ_CHAR 0
    mov ah, DOS_CHAR_INPUT
    int 0x21
    ; Character returned in AL
%endmacro

; Read character without echo
%macro READ_CHAR_NO_ECHO 0
    mov ah, DOS_CHAR_INPUT_NE
    int 0x21
    ; Character returned in AL
%endmacro

; ============================================================================
; File Operations Macros
; ============================================================================

; Open file for reading
%macro OPEN_FILE_READ 1
    mov dx, %1                  ; Filename
    mov ah, DOS_OPEN_FILE
    mov al, FILE_READ_ONLY
    int 0x21
    ; Handle returned in AX, carry set on error
%endmacro

; Open file for writing
%macro OPEN_FILE_WRITE 1
    mov dx, %1                  ; Filename
    mov ah, DOS_OPEN_FILE
    mov al, FILE_WRITE_ONLY
    int 0x21
    ; Handle returned in AX, carry set on error
%endmacro

; Create new file
%macro CREATE_FILE 1
    mov dx, %1                  ; Filename
    mov ah, DOS_CREATE_FILE
    mov cx, ATTR_NORMAL         ; Normal file attributes
    int 0x21
    ; Handle returned in AX, carry set on error
%endmacro

; Close file
%macro CLOSE_FILE 1
    mov bx, %1                  ; File handle
    mov ah, DOS_CLOSE_FILE
    int 0x21
    ; Carry set on error
%endmacro

; Read from file
%macro READ_FILE 3
    mov bx, %1                  ; File handle
    mov cx, %2                  ; Bytes to read
    mov dx, %3                  ; Buffer address
    mov ah, DOS_READ_FILE
    int 0x21
    ; Bytes read returned in AX, carry set on error
%endmacro

; Write to file
%macro WRITE_FILE 3
    mov bx, %1                  ; File handle
    mov cx, %2                  ; Bytes to write
    mov dx, %3                  ; Buffer address
    mov ah, DOS_WRITE_FILE
    int 0x21
    ; Bytes written returned in AX, carry set on error
%endmacro

; ============================================================================
; Memory Management Macros
; ============================================================================

; Allocate memory
%macro ALLOCATE_MEMORY 1
    mov bx, %1                  ; Paragraphs to allocate
    mov ah, DOS_ALLOCATE_MEM
    int 0x21
    ; Segment returned in AX, carry set on error
%endmacro

; Free memory
%macro FREE_MEMORY 1
    mov es, %1                  ; Segment to free
    mov ah, DOS_FREE_MEM
    int 0x21
    ; Carry set on error
%endmacro

; Resize memory block
%macro RESIZE_MEMORY 2
    mov es, %1                  ; Segment to resize
    mov bx, %2                  ; New size in paragraphs
    mov ah, DOS_RESIZE_MEM
    int 0x21
    ; Carry set on error
%endmacro

; ============================================================================
; Program Execution Macros
; ============================================================================

; Execute program
%macro EXEC_PROGRAM 2
    mov dx, %1                  ; Program name
    mov bx, %2                  ; Parameter block
    mov ah, DOS_EXEC
    mov al, 0                   ; Load and execute
    int 0x21
    ; Carry set on error
%endmacro

; Terminate and stay resident
%macro TSR 1
    mov dx, %1                  ; Paragraphs to keep resident
    mov ah, DOS_KEEP_RESIDENT
    mov al, 0                   ; Exit code
    int 0x21
%endmacro

; ============================================================================
; String and Data Utilities
; ============================================================================

; Define a DOS string (terminated with '$')
%macro DOS_STRING 1
    db %1, '$'
%endmacro

; Define a newline sequence
%macro NEWLINE 0
    db 13, 10, '$'
%endmacro

; Define an ASCIIZ string (null-terminated)
%macro ASCIIZ 1
    db %1, 0
%endmacro

; ============================================================================
; Error Handling Macros
; ============================================================================

; Check for DOS error and jump if error occurred
%macro DOS_ERROR_CHECK 1
    jc %1                       ; Jump to error handler if carry set
%endmacro

; Print error message and exit
%macro DOS_ERROR_EXIT 1
    PRINT_STRING %1
    mov ah, DOS_TERMINATE_CODE
    mov al, 1                   ; Error exit code
    int 0x21
%endmacro

; ============================================================================
; Interrupt Handler Utilities
; ============================================================================

; Get interrupt vector
%macro GET_INTERRUPT_VECTOR 2
    mov ah, 0x35               ; Get interrupt vector
    mov al, %1                 ; Interrupt number
    int 0x21
    ; ES:BX points to interrupt handler
    mov word [%2], bx          ; Store offset
    mov word [%2+2], es        ; Store segment
%endmacro

; Set interrupt vector
%macro SET_INTERRUPT_VECTOR 2
    mov ah, 0x25               ; Set interrupt vector
    mov al, %1                 ; Interrupt number
    mov dx, %2                 ; New handler address
    int 0x21
%endmacro

; ============================================================================
; Disk and Directory Utilities
; ============================================================================

; Change directory
%macro CHANGE_DIRECTORY 1
    mov dx, %1                 ; Directory name
    mov ah, DOS_CHDIR
    int 0x21
    ; Carry set on error
%endmacro

; Make directory
%macro MAKE_DIRECTORY 1
    mov dx, %1                 ; Directory name
    mov ah, DOS_MKDIR
    int 0x21
    ; Carry set on error
%endmacro

; Remove directory
%macro REMOVE_DIRECTORY 1
    mov dx, %1                 ; Directory name
    mov ah, DOS_RMDIR
    int 0x21
    ; Carry set on error
%endmacro

; Get current directory
%macro GET_CURRENT_DIRECTORY 2
    mov dl, %1                 ; Drive (0=current, 1=A:, 2=B:, etc.)
    mov si, %2                 ; Buffer for directory name
    mov ah, DOS_GET_CWD
    int 0x21
    ; Carry set on error
%endmacro

; Find first file
%macro FIND_FIRST_FILE 2
    mov dx, %1                 ; File specification
    mov cx, %2                 ; File attributes
    mov ah, DOS_FIND_FIRST
    int 0x21
    ; Carry set if no files found
%endmacro

; Find next file
%macro FIND_NEXT_FILE 0
    mov ah, DOS_FIND_NEXT
    int 0x21
    ; Carry set if no more files
%endmacro

; ============================================================================
; Common Program Templates
; ============================================================================

; Simple COM program template
%macro SIMPLE_COM_PROGRAM 0
    COM_START
    ; Program code goes here
    COM_END
%endmacro

; Simple EXE program template
%macro SIMPLE_EXE_PROGRAM 0
    EXE_START start, 1024, 64, 0xFFFF
start:
    DOS_INIT
    ; Program code goes here
    DOS_CLEANUP
    mov ah, DOS_TERMINATE_CODE
    mov al, 0
    int 0x21

    EXE_STACK 1024
%endmacro