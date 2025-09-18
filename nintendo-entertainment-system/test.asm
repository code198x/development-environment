; Simple NES test program
; Tests that ca65 assembler is working correctly

.segment "HEADER"
    .byte "NES", $1A    ; iNES header identifier
    .byte 2             ; 2x 16KB PRG-ROM banks
    .byte 1             ; 1x 8KB CHR-ROM bank
    .byte $00           ; Mapper 0
    .byte $00           ; No special flags
    .byte 0,0,0,0,0,0,0 ; Padding

.segment "STARTUP"

.segment "CODE"

reset:
    sei                 ; Disable interrupts
    cld                 ; Clear decimal mode

    ; Wait for PPU to stabilize
    ldx #$40
    stx $4017           ; Disable APU frame IRQ

    ; Set up stack
    ldx #$ff
    txs

    ; Clear PPU registers
    lda #$00
    sta $2000
    sta $2001

    ; Set background color to blue
    lda #$3F
    sta $2006
    lda #$00
    sta $2006
    lda #$12            ; Blue color
    sta $2007

infinite_loop:
    jmp infinite_loop

nmi:
    rti

irq:
    rti

.segment "VECTORS"
    .word nmi           ; NMI vector
    .word reset         ; Reset vector
    .word irq           ; IRQ vector

.segment "CHARS"
    ; CHR-ROM data would go here
    .res $2000, $00