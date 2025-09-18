; Simple ZX Spectrum test program
; Tests that sjasmplus assembler is working correctly

    ORG 32768

start:
    ; Set border to red
    ld a, 2
    out (254), a

    ; Clear screen with green paper
    ld a, 4         ; Green paper, black ink
    ld (23693), a   ; Set permanent colors
    call 3503       ; ROM clear screen routine

    ; Print message
    ld hl, message
    call print_string

    ; Infinite loop
loop:
    jr loop

print_string:
    ld a, (hl)
    or a
    ret z
    rst 16          ; Print character
    inc hl
    jr print_string

message:
    defb "SJASMPLUS WORKS!", 13, 0

    ; Export as TAP file
    SAVETAP "test.tap", start