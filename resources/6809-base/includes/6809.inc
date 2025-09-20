; Motorola 6809 Microprocessor - Assembly Include File
; 8-bit microprocessor with advanced addressing modes
; Used in: TRS-80 CoCo, Dragon computers, Vectrex, arcade systems

; =============================================================================
; PROCESSOR CONSTANTS
; =============================================================================

; Direct Page Register default
.equ DP_DEFAULT, 0x00

; Stack Pointers
.equ STACK_DEFAULT, 0xFEFF
.equ USER_STACK, 0x7FFF

; =============================================================================
; MEMORY ORGANIZATION
; =============================================================================

; Zero Page (Direct Page)
.equ ZERO_PAGE, 0x0000
.equ ZERO_PAGE_SIZE, 256

; Standard Memory Layout
.equ RAM_START, 0x0000
.equ RAM_SIZE, 0x8000        ; 32K typical
.equ ROM_START, 0x8000
.equ ROM_SIZE, 0x8000        ; 32K typical

; =============================================================================
; CONDITION CODE REGISTER BITS
; =============================================================================

.equ CC_CARRY, 0x01          ; Carry
.equ CC_OVERFLOW, 0x02       ; Overflow
.equ CC_ZERO, 0x04           ; Zero
.equ CC_NEGATIVE, 0x08       ; Negative
.equ CC_IRQ_MASK, 0x10       ; IRQ Mask
.equ CC_HALF_CARRY, 0x20     ; Half Carry
.equ CC_FIRQ_MASK, 0x40      ; Fast IRQ Mask
.equ CC_ENTIRE, 0x80         ; Entire flag

; =============================================================================
; INTERRUPT VECTORS
; =============================================================================

.equ VECTOR_SWI3, 0xFFF2
.equ VECTOR_SWI2, 0xFFF4
.equ VECTOR_FIRQ, 0xFFF6
.equ VECTOR_IRQ, 0xFFF8
.equ VECTOR_SWI, 0xFFFA
.equ VECTOR_NMI, 0xFFFC
.equ VECTOR_RESET, 0xFFFE

; =============================================================================
; ADDRESSING MODE HELPERS
; =============================================================================

; Extended addressing range
.equ EXTENDED_MIN, 0x0000
.equ EXTENDED_MAX, 0xFFFF

; Direct page addressing
.equ DIRECT_MIN, 0x00
.equ DIRECT_MAX, 0xFF

; =============================================================================
; COMMON MACROS
; =============================================================================

; Set Direct Page Register
.macro SET_DP addr
    lda #(addr >> 8)
    tfr a,dp
.endm

; Push multiple registers
.macro PUSH_ALL
    pshs cc,a,b,dp,x,y,u,pc
.endm

; Pull multiple registers
.macro PULL_ALL
    puls cc,a,b,dp,x,y,u,pc
.endm

; =============================================================================
; SYSTEM CONSTANTS
; =============================================================================

.equ BYTES_PER_ROW, 16
.equ BITS_PER_BYTE, 8
.equ NIBBLES_PER_BYTE, 2

; Common delays
.equ DELAY_SHORT, 10
.equ DELAY_MEDIUM, 100
.equ DELAY_LONG, 1000