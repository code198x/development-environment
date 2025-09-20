; SuperH (SH) Microprocessor - Assembly Include File
; 32-bit RISC processor by Hitachi/Renesas
; Used in: Sega Saturn (SH-2), Sega Dreamcast (SH-4)

; =============================================================================
; PROCESSOR CONSTANTS
; =============================================================================

; CPU Clock speeds (Hz)
.equ SH2_CLOCK, 28636363     ; Saturn SH-2
.equ SH4_CLOCK, 200000000    ; Dreamcast SH-4

; =============================================================================
; MEMORY ORGANIZATION
; =============================================================================

; Standard Memory Layout (Saturn SH-2)
.equ WORKRAM_LOW, 0x00200000    ; 1MB Work RAM
.equ WORKRAM_HIGH, 0x06000000   ; 1MB Work RAM (High)
.equ VDP1_VRAM, 0x05C00000      ; Video RAM
.equ VDP2_VRAM, 0x05E00000      ; Video RAM
.equ SOUND_RAM, 0x05A00000      ; Sound RAM

; Dreamcast Memory Layout (SH-4)
.equ DC_MAIN_RAM, 0x8C000000    ; 16MB Main RAM
.equ DC_VIDEO_RAM, 0xA5000000   ; 8MB Video RAM
.equ DC_SOUND_RAM, 0xA0800000   ; 2MB Sound RAM

; =============================================================================
; STATUS REGISTER (SR) BITS
; =============================================================================

.equ SR_T, 0x00000001           ; T bit
.equ SR_S, 0x00000002           ; S bit
.equ SR_I0, 0x00000010          ; Interrupt mask bit 0
.equ SR_I1, 0x00000020          ; Interrupt mask bit 1
.equ SR_I2, 0x00000040          ; Interrupt mask bit 2
.equ SR_I3, 0x00000080          ; Interrupt mask bit 3
.equ SR_Q, 0x00000100           ; Q bit
.equ SR_M, 0x00000200           ; M bit
.equ SR_FD, 0x00008000          ; FPU disable
.equ SR_BL, 0x10000000          ; Block interrupts
.equ SR_RB, 0x20000000          ; Register bank select
.equ SR_MD, 0x40000000          ; Privileged mode

; =============================================================================
; INTERRUPT VECTORS
; =============================================================================

; Exception/Interrupt vectors
.equ VEC_RESET, 0x00000000
.equ VEC_GENERAL, 0x00000100
.equ VEC_TLB_MISS, 0x00000400
.equ VEC_INTERRUPT, 0x00000600

; =============================================================================
; CACHE CONTROL
; =============================================================================

.equ CCR, 0xFF00001C            ; Cache Control Register
.equ CCR_ICE, 0x00000001        ; Instruction cache enable
.equ CCR_DCE, 0x00000004        ; Data cache enable
.equ CCR_ICINV, 0x00000800      ; Instruction cache invalidate
.equ CCR_DCINV, 0x00001000      ; Data cache invalidate

; =============================================================================
; COMMON MACROS
; =============================================================================

; Save registers to stack
.macro SAVE_REGS
    mov.l r0, @-r15
    mov.l r1, @-r15
    mov.l r2, @-r15
    mov.l r3, @-r15
    sts.l pr, @-r15
.endm

; Restore registers from stack
.macro RESTORE_REGS
    lds.l @r15+, pr
    mov.l @r15+, r3
    mov.l @r15+, r2
    mov.l @r15+, r1
    mov.l @r15+, r0
.endm

; No operation delay
.macro NOP_DELAY count
    .rept count
    nop
    .endr
.endm

; =============================================================================
; SYSTEM CONSTANTS
; =============================================================================

.equ LONGWORD_SIZE, 4
.equ WORD_SIZE, 2
.equ BYTE_SIZE, 1

; Common values
.equ NULL_PTR, 0x00000000
.equ STACK_ALIGN, 4

; Timing constants
.equ DELAY_SHORT, 100
.equ DELAY_MEDIUM, 1000
.equ DELAY_LONG, 10000