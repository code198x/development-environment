; dos33.inc - DOS 3.3 File System Interface for Apple II
; Provides high-level interface to DOS 3.3 file operations

; ============================================================================
; DOS 3.3 Command Interface
; ============================================================================

; DOS commands are invoked by calling DOS entry point with command in A
; Some commands require additional parameters in other registers

; DOS command codes
DOS_CMD_INIT        = $00   ; Initialize DOS
DOS_CMD_OPEN        = $01   ; Open file
DOS_CMD_CLOSE       = $02   ; Close file
DOS_CMD_READ        = $03   ; Read from file
DOS_CMD_WRITE       = $04   ; Write to file
DOS_CMD_DELETE      = $05   ; Delete file
DOS_CMD_CATALOG     = $06   ; Display catalog
DOS_CMD_CHAIN       = $07   ; Chain to another program
DOS_CMD_NOMON       = $08   ; Disable monitor commands
DOS_CMD_NOMSG       = $09   ; Disable DOS messages
DOS_CMD_RUN         = $0A   ; Run BASIC program
DOS_CMD_LOAD        = $0B   ; Load BASIC program

; File types
FILE_TYPE_TEXT      = $00   ; Text file
FILE_TYPE_INTEGER   = $01   ; Integer BASIC program
FILE_TYPE_APPLESOFT = $02   ; Applesoft BASIC program
FILE_TYPE_BINARY    = $04   ; Binary file
FILE_TYPE_S_TYPE    = $08   ; S-type file
FILE_TYPE_RELOCATE  = $10   ; Relocatable binary
FILE_TYPE_A_TYPE    = $20   ; A-type file
FILE_TYPE_B_TYPE    = $40   ; B-type file

; ============================================================================
; File Control Block (FCB) Structure
; ============================================================================

; DOS 3.3 uses a 35-byte File Control Block for each open file
FCB_TRACK           = $00   ; Track of first sector
FCB_SECTOR          = $01   ; Sector of first sector
FCB_FILE_TYPE       = $02   ; File type and flags
FCB_FILENAME        = $03   ; Filename (30 characters)
FCB_LENGTH          = $21   ; File length in sectors
FCB_SIZE            = 35    ; Total FCB size

; ============================================================================
; DOS 3.3 Parameter Lists
; ============================================================================

; Standard parameter list for file operations
; Located in memory before calling DOS

; OPEN parameter list
OPEN_FILENAME       = $00   ; Pointer to filename (2 bytes)
OPEN_BUFFER         = $02   ; Pointer to I/O buffer (2 bytes)

; READ/WRITE parameter list
RW_BUFFER           = $00   ; Pointer to data buffer (2 bytes)
RW_LENGTH           = $02   ; Number of bytes to read/write (2 bytes)

; ============================================================================
; DOS 3.3 Macros for Easy File Operations
; ============================================================================

; Open a file for reading
.macro DOS_OPEN_READ filename, buffer
    .local param_list
    lda #<param_list
    sta A1L
    lda #>param_list
    sta A1H
    lda #DOS_CMD_OPEN
    jsr DOS_ENTRY
    bcc :+
    ; Handle error - carry set means error
    jmp file_error
:
    .segment "RODATA"
param_list:
    .addr filename
    .addr buffer
    .segment "CODE"
.endmacro

; Close a file
.macro DOS_CLOSE
    lda #DOS_CMD_CLOSE
    jsr DOS_ENTRY
.endmacro

; Read from file
.macro DOS_READ buffer, length
    .local param_list
    lda #<param_list
    sta A1L
    lda #>param_list
    sta A1H
    lda #DOS_CMD_READ
    jsr DOS_ENTRY
    .segment "RODATA"
param_list:
    .addr buffer
    .word length
    .segment "CODE"
.endmacro

; Write to file
.macro DOS_WRITE buffer, length
    .local param_list
    lda #<param_list
    sta A1L
    lda #>param_list
    sta A1H
    lda #DOS_CMD_WRITE
    jsr DOS_ENTRY
    .segment "RODATA"
param_list:
    .addr buffer
    .word length
    .segment "CODE"
.endmacro

; Delete a file
.macro DOS_DELETE filename
    .local param_list
    lda #<param_list
    sta A1L
    lda #>param_list
    sta A1H
    lda #DOS_CMD_DELETE
    jsr DOS_ENTRY
    .segment "RODATA"
param_list:
    .addr filename
    .segment "CODE"
.endmacro

; ============================================================================
; RWTS (Read Write Track Sector) Interface
; ============================================================================

; RWTS is the low-level disk interface used by DOS 3.3
; RWTS parameter list (16 bytes)
RWTS_TABLE_TYPE     = $00   ; Table type (must be 1)
RWTS_SLOT           = $01   ; Slot number × 16
RWTS_DRIVE          = $02   ; Drive number (1 or 2)
RWTS_VOLUME         = $03   ; Volume number (0 = any)
RWTS_TRACK          = $04   ; Track number
RWTS_SECTOR         = $05   ; Sector number
RWTS_DCT_ADDR       = $06   ; Device characteristics table address (2 bytes)
RWTS_BUFFER_ADDR    = $08   ; Buffer address (2 bytes)
RWTS_PARTIAL_1      = $0A   ; Partial sector (unused)
RWTS_PARTIAL_2      = $0B   ; Partial sector (unused)
RWTS_COMMAND        = $0C   ; Command code
RWTS_ERROR          = $0D   ; Error code (returned)
RWTS_VOLUME_ACTUAL  = $0E   ; Actual volume (returned)
RWTS_SLOT_DRIVE     = $0F   ; Slot and drive (returned)

; RWTS command codes
RWTS_CMD_SEEK       = $00   ; Seek to track
RWTS_CMD_READ       = $01   ; Read sector
RWTS_CMD_WRITE      = $02   ; Write sector
RWTS_CMD_FORMAT     = $04   ; Format track

; RWTS error codes
RWTS_NO_ERROR       = $00   ; No error
RWTS_BAD_DEVICE     = $08   ; Bad device number
RWTS_WRITE_PROTECT  = $10   ; Write protected
RWTS_VOLUME_MISMATCH = $20  ; Volume mismatch
RWTS_DRIVE_ERROR    = $40   ; Drive error
RWTS_NO_SYNC        = $80   ; No sync found

; ============================================================================
; Utility Functions
; ============================================================================

; Convert ASCII filename to DOS 3.3 format (space-padded, 30 chars)
.proc convert_filename
    ; Input: A1L/A1H points to null-terminated filename
    ; Output: Filename converted in place

    ldy #0
    ldx #30

copy_loop:
    lda (A1L),y
    beq pad_spaces      ; End of string
    cmp #'a'
    bcc store_char
    cmp #'z'+1
    bcs store_char
    sbc #$1F            ; Convert to uppercase
store_char:
    sta (A1L),y
    iny
    dex
    bne copy_loop
    rts

pad_spaces:
    lda #' '
pad_loop:
    sta (A1L),y
    iny
    dex
    bne pad_loop
    rts
.endproc

; Check if file exists
.proc file_exists
    ; Input: A1L/A1H points to filename
    ; Output: Carry clear if exists, set if not found

    ; Try to open the file
    lda #DOS_CMD_OPEN
    jsr DOS_ENTRY
    bcs not_found

    ; File exists, close it
    lda #DOS_CMD_CLOSE
    jsr DOS_ENTRY
    clc
    rts

not_found:
    sec
    rts
.endproc

; Get file size
.proc get_file_size
    ; Input: A1L/A1H points to open file
    ; Output: File size in sectors in A

    ; This would require reading the catalog entry
    ; Implementation depends on specific DOS 3.3 internals
    lda #0              ; Placeholder
    rts
.endproc

; ============================================================================
; Error Handling
; ============================================================================

; Standard error handler
.proc file_error
    ; DOS error codes in A register
    ; Print appropriate error message

    cmp #$01
    bne :+
    jsr print_string
    .addr error_language_not_available
    rts
:
    cmp #$02
    bne :+
    jsr print_string
    .addr error_range_error
    rts
:
    cmp #$04
    bne :+
    jsr print_string
    .addr error_write_protected
    rts
:
    cmp #$05
    bne :+
    jsr print_string
    .addr error_end_of_data
    rts
:
    cmp #$06
    bne :+
    jsr print_string
    .addr error_file_not_found
    rts
:
    cmp #$07
    bne :+
    jsr print_string
    .addr error_volume_mismatch
    rts
:
    cmp #$08
    bne :+
    jsr print_string
    .addr error_io_error
    rts
:
    cmp #$09
    bne :+
    jsr print_string
    .addr error_disk_full
    rts
:
    cmp #$0A
    bne :+
    jsr print_string
    .addr error_file_locked
    rts
:
    ; Unknown error
    jsr print_string
    .addr error_unknown
    rts
.endproc

; Print null-terminated string
.proc print_string
    sta A1L
    stx A1H
    ldy #0
loop:
    lda (A1L),y
    beq done
    jsr COUT
    iny
    bne loop
done:
    rts
.endproc

; ============================================================================
; Error Messages
; ============================================================================

.segment "RODATA"

error_language_not_available:
    .asciiz "LANGUAGE NOT AVAILABLE"
error_range_error:
    .asciiz "RANGE ERROR"
error_write_protected:
    .asciiz "WRITE PROTECTED"
error_end_of_data:
    .asciiz "END OF DATA"
error_file_not_found:
    .asciiz "FILE NOT FOUND"
error_volume_mismatch:
    .asciiz "VOLUME MISMATCH"
error_io_error:
    .asciiz "I/O ERROR"
error_disk_full:
    .asciiz "DISK FULL"
error_file_locked:
    .asciiz "FILE LOCKED"
error_unknown:
    .asciiz "UNKNOWN ERROR"

; ============================================================================
; Constants
; ============================================================================

; Standard DOS entry point (this may vary by system)
DOS_ENTRY           = $03D0 ; Standard DOS 3.3 entry point

; Standard file buffer size
FILE_BUFFER_SIZE    = 256   ; One sector

; Maximum filename length
MAX_FILENAME        = 30    ; DOS 3.3 limit