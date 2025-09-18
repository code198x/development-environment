; Simple C64 test program
; Tests that ACME assembler is working correctly

!cpu 6502
!to "test.prg", cbm

* = $0801

; BASIC header: 10 SYS 2061
!byte $0c,$08,$0a,$00,$9e,$20,$32,$30,$36,$31,$00,$00,$00

* = $080d

start:
    lda #$00        ; Black border
    sta $d020
    lda #$05        ; Green screen
    sta $d021

    ; Print message
    ldx #$00
print_loop:
    lda message,x
    beq done
    jsr $ffd2       ; CHROUT
    inx
    bne print_loop

done:
    rts

message:
    !text "ACME ASSEMBLER WORKS!"
    !byte $0d, $00