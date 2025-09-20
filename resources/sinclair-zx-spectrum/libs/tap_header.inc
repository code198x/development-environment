; tap_header.inc - TAP file format for ZX Spectrum
; Creates proper TAP headers for loading on real hardware or emulators

; TAP file structure:
; - Header block (19 bytes = 2 length + 17 data)
; - Data block (N bytes = 2 length + data)

; Standard header for code files
TAP_HEADER MACRO name, start_addr, code_len
    ; TAP block length (19 bytes: flag + header)
    DW 19

    ; Header flag byte
    DB 0            ; 0 = header block

    ; Header data (17 bytes)
    DB 3            ; Type: 3 = code file

    ; Filename (10 bytes, padded with spaces)
    DB name
    REPT 10-($-name)
    DB ' '
    ENDR

    ; Data block length
    DW code_len

    ; Start address (for code files)
    DW start_addr

    ; Parameter 2 (32768 for code files)
    DW 32768

    ; Checksum (XOR of all header bytes)
    LOCAL checksum_start
checksum_start:
    DB 0 ^ 3        ; Will be calculated
ENDM

; Data block for TAP file
TAP_DATA MACRO
    LOCAL data_start, data_end

    ; Length of data block + flag byte + checksum
    DW (data_end - data_start)

data_start:
    DB 255          ; 255 = data block flag

    ; Your code goes here
ENDM

TAP_DATA_END MACRO
    LOCAL checksum

    ; Calculate checksum
checksum:
    DB 0            ; Placeholder - tools will calculate
data_end:
ENDM

; Optimized BASIC loader that loads and runs machine code
BASIC_LOADER MACRO start_addr, code_len
    ; BASIC program that does:
    ; 10 CLEAR start_addr-1
    ; 20 LOAD ""CODE start_addr
    ; 30 RANDOMIZE USR start_addr

    ; TAP header for BASIC
    DW 19
    DB 0            ; Header
    DB 0            ; Program type
    DB "loader    " ; Name (10 bytes)
    DW basic_end - basic_start  ; Length
    DW 10           ; Line 10
    DW basic_end - basic_start  ; Length again
    DB 0            ; Checksum placeholder

    ; BASIC program data
    DW basic_end - basic_start + 2
    DB 255          ; Data block
basic_start:
    ; Line 10: CLEAR start_addr-1
    DB 0, 10        ; Line number 10
    DW line20 - line10_start
line10_start:
    DB $FD          ; CLEAR
    DB $B0          ; VAL
    DB '"'
    .asciz start_addr-1
    DB '"'
    DB $0D          ; End of line

    ; Line 20: LOAD ""CODE
line20:
    DB 0, 20        ; Line number 20
    DW line30 - line20_start
line20_start:
    DB $EF          ; LOAD
    DB '"','"'      ; ""
    DB $AF          ; CODE
    DB $0D          ; End of line

    ; Line 30: RANDOMIZE USR start_addr
line30:
    DB 0, 30        ; Line number 30
    DW basic_end - line30_start
line30_start:
    DB $F9          ; RANDOMIZE
    DB $C0          ; USR
    DB $B0          ; VAL
    DB '"'
    .asciz start_addr
    DB '"'
    DB $0D          ; End of line

basic_end:
    DB 0            ; Checksum placeholder
ENDM

; Simple macro for creating a complete TAP file
CREATE_TAP MACRO name, start_addr
    LOCAL code_start, code_end

    ; Generate header
    TAP_HEADER name, start_addr, (code_end - code_start)

    ; Generate data block
    DW (code_end - code_start) + 2
    DB 255          ; Data flag
code_start:
    ; Your code here
ENDM

END_TAP MACRO
code_end:
    DB 0            ; Checksum
ENDM