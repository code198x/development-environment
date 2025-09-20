; Intel 8080 Microprocessor - Assembly Include File
; 8-bit microprocessor, predecessor to 8086
; Used in: Altair 8800, IMSAI 8080, CP/M systems

; =============================================================================
; PROCESSOR CONSTANTS
; =============================================================================

; CPU Clock speeds (Hz)
.equ CPU_CLOCK_2MHZ, 2000000
.equ CPU_CLOCK_4MHZ, 4000000

; =============================================================================
; MEMORY ORGANIZATION
; =============================================================================

; Standard Memory Layout
.equ RAM_START, 0x0000
.equ RAM_SIZE, 0x8000        ; 32K typical
.equ ROM_START, 0xF000       ; High memory
.equ ROM_SIZE, 0x1000        ; 4K typical

; Stack
.equ STACK_TOP, 0x8000
.equ STACK_SIZE, 0x100

; =============================================================================
; STATUS FLAGS (Flags Register)
; =============================================================================

.equ FLAG_CARRY, 0x01        ; Carry flag
.equ FLAG_PARITY, 0x04       ; Parity flag
.equ FLAG_AUX_CARRY, 0x10    ; Auxiliary carry
.equ FLAG_ZERO, 0x40         ; Zero flag
.equ FLAG_SIGN, 0x80         ; Sign flag

; =============================================================================
; I/O PORT DEFINITIONS
; =============================================================================

; Standard I/O ports (system dependent)
.equ PORT_DATA, 0x00
.equ PORT_STATUS, 0x01
.equ PORT_CONTROL, 0x02

; Serial I/O
.equ UART_DATA, 0x10
.equ UART_STATUS, 0x11

; =============================================================================
; INTERRUPT VECTORS
; =============================================================================

; RST instructions vector to these addresses
.equ RST_0, 0x0000
.equ RST_1, 0x0008
.equ RST_2, 0x0010
.equ RST_3, 0x0018
.equ RST_4, 0x0020
.equ RST_5, 0x0028
.equ RST_6, 0x0030
.equ RST_7, 0x0038

; Interrupt vector
.equ INT_VECTOR, 0x0038

; =============================================================================
; COMMON MACROS
; =============================================================================

; Save all registers
.macro SAVE_ALL
    push psw
    push b
    push d
    push h
.endm

; Restore all registers
.macro RESTORE_ALL
    pop h
    pop d
    pop b
    pop psw
.endm

; 16-bit load immediate
.macro LXI_16 reg, value
    lxi reg, value
.endm

; =============================================================================
; SYSTEM CONSTANTS
; =============================================================================

.equ BYTES_PER_ROW, 16
.equ BITS_PER_BYTE, 8
.equ NULL_CHAR, 0x00
.equ CR_CHAR, 0x0D
.equ LF_CHAR, 0x0A

; Common delays
.equ DELAY_SHORT, 10
.equ DELAY_MEDIUM, 100
.equ DELAY_LONG, 1000