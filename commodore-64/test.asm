; Test program for ACME assembler
; Simple C64 program that changes border color

* = $0801
    !byte $0c,$08,$0a,$00,$9e,$32
    !byte $30,$36,$34,$00,$00,$00

main:
    lda #$02        ; Load red color
    sta $d020       ; Store to border color register
    lda #$06        ; Load blue color
    sta $d021       ; Store to background color register
    rts             ; Return to BASIC
