; NES Hello World
; Assembled with CA65
; Output: "HELLO" on screen using background tiles

.segment "HEADER"
    .byte "NES", $1A    ; iNES header
    .byte 2             ; 2 * 16KB PRG ROM
    .byte 1             ; 1 * 8KB CHR ROM
    .byte $00           ; mapper 0
    .byte $00

.segment "VECTORS"
    .addr nmi
    .addr reset
    .addr 0

.segment "STARTUP"

.segment "CODE"
reset:
    sei                 ; Disable interrupts
    cld                 ; Disable decimal mode

    ; Wait for PPU to warm up
    bit $2002
vblankwait1:
    bit $2002
    bpl vblankwait1

vblankwait2:
    bit $2002
    bpl vblankwait2

    ; Clear PPU
    lda #$00
    sta $2000           ; Disable NMI
    sta $2001           ; Disable rendering

    ; Load palette
    lda #$3F
    sta $2006
    lda #$00
    sta $2006

    lda #$0F            ; Black
    sta $2007
    lda #$30            ; White
    sta $2007

    ; Print "HELLO"
    lda #$21
    sta $2006
    lda #$C5
    sta $2006

    lda #'H'
    sta $2007
    lda #'E'
    sta $2007
    lda #'L'
    sta $2007
    lda #'L'
    sta $2007
    lda #'O'
    sta $2007

    ; Enable rendering
    lda #$1E
    sta $2001

forever:
    jmp forever

nmi:
    rti

.segment "CHARS"
    ; Character ROM data would go here