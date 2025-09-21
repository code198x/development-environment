; Commodore 64 Hello World
; Assembled with ACME or CA65
; Output: "HELLO WORLD!" on screen

        * = $0801       ; BASIC start address

        ; BASIC header
        !byte $0c,$08,$0a,$00,$9e,$20
        !byte $32,$30,$36,$32,$00,$00,$00

        * = $080e       ; Program start

start:
        lda #$93        ; Clear screen
        jsr $ffd2       ; CHROUT

        ldx #$00        ; String index
print:
        lda message,x   ; Load character
        beq done        ; End if zero
        jsr $ffd2       ; Print character
        inx
        jmp print

done:
        rts             ; Return to BASIC

message:
        !scr "hello world!"
        !byte $0d       ; Newline
        !byte $00       ; String terminator