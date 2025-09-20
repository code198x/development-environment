; NEC V30 Microprocessor - Assembly Include File
; Enhanced 8086-compatible processor with additional features
; Used in: Bandai WonderSwan, some PC-9801 systems

; =============================================================================
; PROCESSOR CONSTANTS
; =============================================================================

; CPU Clock speeds (Hz)
.equ V30_CLOCK_3MHZ, 3072000      ; WonderSwan V30MZ
.equ V30_CLOCK_4MHZ, 4000000
.equ V30_CLOCK_8MHZ, 8000000

; =============================================================================
; MEMORY ORGANIZATION
; =============================================================================

; Standard Memory Layout (WonderSwan)
.equ RAM_START, 0x00000
.equ INTERNAL_RAM, 0x00000        ; 64KB internal RAM
.equ INTERNAL_RAM_SIZE, 0x10000
.equ CART_ROM, 0x20000            ; Cartridge ROM space
.equ CART_SRAM, 0x10000           ; Cartridge SRAM

; Memory segments
.equ SEGMENT_SIZE, 0x10000        ; 64KB per segment
.equ SEGMENT_SHIFT, 4             ; Shift for segment calculation

; =============================================================================
; FLAGS REGISTER
; =============================================================================

.equ FLAG_CARRY, 0x0001           ; Carry flag
.equ FLAG_PARITY, 0x0004          ; Parity flag
.equ FLAG_AUX_CARRY, 0x0010       ; Auxiliary carry
.equ FLAG_ZERO, 0x0040            ; Zero flag
.equ FLAG_SIGN, 0x0080            ; Sign flag
.equ FLAG_TRAP, 0x0100            ; Trap flag
.equ FLAG_INTERRUPT, 0x0200       ; Interrupt enable
.equ FLAG_DIRECTION, 0x0400       ; Direction flag
.equ FLAG_OVERFLOW, 0x0800        ; Overflow flag

; =============================================================================
; INTERRUPT VECTORS
; =============================================================================

; Standard 8086-compatible interrupts
.equ INT_DIVIDE_ERROR, 0x00
.equ INT_SINGLE_STEP, 0x01
.equ INT_NMI, 0x02
.equ INT_BREAKPOINT, 0x03
.equ INT_OVERFLOW, 0x04

; WonderSwan-specific interrupts
.equ INT_SERIAL_TX, 0x10
.equ INT_KEY_INPUT, 0x11
.equ INT_CARTRIDGE, 0x12
.equ INT_SERIAL_RX, 0x13
.equ INT_LINE, 0x14
.equ INT_VBLANK, 0x15
.equ INT_VBLANK_TIMER, 0x16
.equ INT_DRAWING_TIMER, 0x17
.equ INT_TIMER_LO, 0x18
.equ INT_TIMER_HI, 0x19

; =============================================================================
; COMMON MACROS
; =============================================================================

; Push all general purpose registers
.macro PUSHA_ALL
    pusha
.endm

; Pop all general purpose registers
.macro POPA_ALL
    popa
.endm

; Load segment:offset address
.macro LOAD_SEG_OFFSET seg, offset
    mov ax, seg
    mov ds, ax
    mov si, offset
.endm

; =============================================================================
; SYSTEM CONSTANTS
; =============================================================================

.equ BYTE_SIZE, 1
.equ WORD_SIZE, 2
.equ PARAGRAPH, 16                ; 16 bytes

; Character constants
.equ NULL_CHAR, 0x00
.equ CR_CHAR, 0x0D
.equ LF_CHAR, 0x0A
.equ EOF_CHAR, 0x1A

; Common delays
.equ DELAY_SHORT, 100
.equ DELAY_MEDIUM, 1000
.equ DELAY_LONG, 10000