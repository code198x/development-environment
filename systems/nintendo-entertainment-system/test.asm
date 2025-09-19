; Test program for cc65/ca65 assembler
; Simple NES program structure

.segment "HEADER"
    .byte "NES", $1A    ; NES magic number
    .byte $02           ; 2 * 16KB PRG ROM
    .byte $01           ; 1 * 8KB CHR ROM
    .byte $00, $00      ; Flags
    .res 8, $00         ; Padding

.segment "CODE"
reset:
    sei                 ; Disable interrupts
    cld                 ; Clear decimal mode
    ldx #$ff
    txs                 ; Set stack pointer
    
    lda #%10000000      ; Enable NMI
    sta $2000           ; PPU Control Register
    
forever:
    jmp forever

.segment "VECTORS"
    .word 0, reset, 0   ; NMI, Reset, IRQ vectors
