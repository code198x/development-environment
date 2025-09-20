; Toshiba TLCS-900H Microprocessor - Assembly Include File
; 16-bit microprocessor with advanced features
; Used in: SNK Neo Geo Pocket, Neo Geo Pocket Color

; =============================================================================
; PROCESSOR CONSTANTS
; =============================================================================

; CPU Clock speeds (Hz)
.equ TLCS_CLOCK_6MHZ, 6144000     ; Neo Geo Pocket
.equ TLCS_CLOCK_12MHZ, 12288000   ; Neo Geo Pocket Color

; =============================================================================
; MEMORY ORGANIZATION
; =============================================================================

; Neo Geo Pocket Memory Layout
.equ INTERNAL_RAM, 0x00004000     ; 12KB internal RAM
.equ INTERNAL_RAM_SIZE, 0x3000
.equ CART_ROM, 0x00200000         ; Cartridge ROM space
.equ CART_ROM_SIZE, 0x200000      ; Up to 2MB
.equ IO_PORTS, 0x00008000         ; I/O port area

; Stack and interrupt vectors
.equ STACK_TOP, 0x00006FFF        ; Top of internal RAM
.equ VECTOR_TABLE, 0x00000000     ; Interrupt vector table

; =============================================================================
; STATUS REGISTER FLAGS
; =============================================================================

.equ FLAG_CARRY, 0x01             ; Carry flag
.equ FLAG_ZERO, 0x02              ; Zero flag
.equ FLAG_SIGN, 0x04              ; Sign flag
.equ FLAG_OVERFLOW, 0x08          ; Overflow flag
.equ FLAG_HALF_CARRY, 0x10        ; Half carry flag
.equ FLAG_PARITY, 0x20            ; Parity/Overflow flag
.equ FLAG_SUBTRACT, 0x40          ; Subtract flag
.equ FLAG_EXTEND, 0x80            ; Extend flag

; =============================================================================
; INTERRUPT VECTORS
; =============================================================================

; Hardware interrupts
.equ INT_RESET, 0x00              ; Reset vector
.equ INT_SWI, 0x10                ; Software interrupt
.equ INT_NMI, 0x20                ; Non-maskable interrupt
.equ INT_INTWD, 0x30              ; Watchdog timer
.equ INT_INT0, 0x40               ; External interrupt 0
.equ INT_INT4, 0x50               ; External interrupt 4
.equ INT_INT5, 0x60               ; External interrupt 5

; Timer interrupts
.equ INT_INTT0, 0x70              ; Timer 0
.equ INT_INTT1, 0x80              ; Timer 1
.equ INT_INTT2, 0x90              ; Timer 2
.equ INT_INTT3, 0xA0              ; Timer 3

; Serial interrupts
.equ INT_INTRX0, 0xB0             ; Serial receive 0
.equ INT_INTTX0, 0xC0             ; Serial transmit 0
.equ INT_INTRX1, 0xD0             ; Serial receive 1
.equ INT_INTTX1, 0xE0             ; Serial transmit 1

; =============================================================================
; I/O PORT DEFINITIONS
; =============================================================================

; System control
.equ PORT_SYSCR, 0x8000           ; System control register
.equ PORT_OSCR, 0x8001            ; Oscillator control
.equ PORT_P1CR, 0x8004            ; Port 1 control
.equ PORT_P1, 0x8005              ; Port 1 data
.equ PORT_P2, 0x8006              ; Port 2 data

; Timer ports
.equ PORT_T0MOD, 0x8010           ; Timer 0 mode
.equ PORT_T0, 0x8011              ; Timer 0 data
.equ PORT_T1MOD, 0x8012           ; Timer 1 mode
.equ PORT_T1, 0x8013              ; Timer 1 data

; Serial ports
.equ PORT_SC0MOD, 0x8020          ; Serial 0 mode
.equ PORT_SC0BUF, 0x8021          ; Serial 0 buffer
.equ PORT_SC1MOD, 0x8022          ; Serial 1 mode
.equ PORT_SC1BUF, 0x8023          ; Serial 1 buffer

; =============================================================================
; COMMON MACROS
; =============================================================================

; Save processor state
.macro SAVE_STATE
    push af
    push bc
    push de
    push hl
    push ix
    push iy
.endm

; Restore processor state
.macro RESTORE_STATE
    pop iy
    pop ix
    pop hl
    pop de
    pop bc
    pop af
.endm

; Enable interrupts
.macro ENABLE_INTS
    ei
.endm

; Disable interrupts
.macro DISABLE_INTS
    di
.endm

; =============================================================================
; SYSTEM CONSTANTS
; =============================================================================

.equ BYTE_SIZE, 1
.equ WORD_SIZE, 2
.equ LONG_SIZE, 4

; Character constants
.equ NULL_CHAR, 0x00
.equ CR_CHAR, 0x0D
.equ LF_CHAR, 0x0A

; Common delays
.equ DELAY_SHORT, 50
.equ DELAY_MEDIUM, 500
.equ DELAY_LONG, 5000