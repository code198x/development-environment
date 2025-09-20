; hello_world.asm - Simple Game Boy "Hello World" example
; Demonstrates using the resource files for a complete program

; Include our Game Boy definitions
INCLUDE "gameboy.inc"
INCLUDE "rom_header.inc"
INCLUDE "init.inc"

; ============================================================================
; ROM Header
; ============================================================================

SECTION "Header", ROM0[$100]
    SIMPLE_HEADER "HELLO"

; ============================================================================
; Main Program
; ============================================================================

SECTION "Main", ROM0[$150]
main:
    ; Initialize the Game Boy
    INIT_GAMEBOY

    ; Clear the background tilemap
    call clear_background

    ; Load our simple font
    call load_font

    ; Write "HELLO WORLD!" to the background
    call write_hello

    ; Turn on LCD with background enabled
    ld a, LCDCF_ON | LCDCF_BGON
    ldh [rLCDC], a

    ; Main loop - just wait for interrupts
.main_loop:
    halt                ; Wait for interrupt
    jr .main_loop

; ============================================================================
; VBlank interrupt handler
; ============================================================================

SECTION "VBlank", ROM0[$40]
vblank_handler:
    ; Simple VBlank handler - just return
    reti

; ============================================================================
; Helper Functions
; ============================================================================

; Clear the background tilemap
clear_background:
    ; Set VRAM address to start of background map
    ld a, $98
    ldh [rVBK], a       ; VRAM bank 0
    ld a, $00
    ldh [rVBK+1], a

    ; Wait for VBlank to access VRAM safely
    call wait_vblank

    ; Clear 32x32 tilemap (1024 bytes)
    ld hl, $9800        ; Background map start
    ld bc, 32*32        ; 32x32 tiles
    ld a, 0             ; Fill with tile 0

.clear_loop:
    ld [hl+], a
    dec bc
    ld a, b
    or c
    jr nz, .clear_loop
    ret

; Load a simple font (just enough for "HELLO WORLD!")
load_font:
    call wait_vblank

    ; Copy font data to VRAM tile area
    ld hl, $8000        ; Tile data start
    ld de, font_data
    ld bc, font_data_end - font_data

.copy_loop:
    ld a, [de]
    ld [hl+], a
    inc de
    dec bc
    ld a, b
    or c
    jr nz, .copy_loop
    ret

; Write "HELLO WORLD!" to background
write_hello:
    call wait_vblank

    ; Position on screen (roughly centered)
    ld hl, $9800 + 32*8 + 5  ; Row 8, column 5
    ld de, hello_text
    ld b, hello_text_end - hello_text

.write_loop:
    ld a, [de]
    ld [hl+], a
    inc de
    dec b
    jr nz, .write_loop
    ret

; ============================================================================
; Data
; ============================================================================

SECTION "Data", ROM0

hello_text:
    DB 8,5,12,12,15,0,23,15,18,12,4,33  ; "HELLO WORLD!"
hello_text_end:

; Simple 8x8 font data for A-Z, 0-9, space, exclamation
font_data:
    ; Tile 0: Space
    DB $00,$00,$00,$00,$00,$00,$00,$00
    DB $00,$00,$00,$00,$00,$00,$00,$00

    ; Tile 1: A
    DB $18,$18,$24,$24,$42,$42,$7E,$7E
    DB $42,$42,$42,$42,$42,$42,$00,$00

    ; Tile 2: B
    DB $7C,$7C,$42,$42,$42,$42,$7C,$7C
    DB $42,$42,$42,$42,$7C,$7C,$00,$00

    ; Tile 3: C
    DB $3C,$3C,$42,$42,$40,$40,$40,$40
    DB $40,$40,$42,$42,$3C,$3C,$00,$00

    ; Tile 4: D
    DB $78,$78,$44,$44,$42,$42,$42,$42
    DB $42,$42,$44,$44,$78,$78,$00,$00

    ; Tile 5: E
    DB $7E,$7E,$40,$40,$40,$40,$7C,$7C
    DB $40,$40,$40,$40,$7E,$7E,$00,$00

    ; Tile 6: F
    DB $7E,$7E,$40,$40,$40,$40,$7C,$7C
    DB $40,$40,$40,$40,$40,$40,$00,$00

    ; Tile 7: G
    DB $3C,$3C,$42,$42,$40,$40,$4E,$4E
    DB $42,$42,$42,$42,$3C,$3C,$00,$00

    ; Tile 8: H
    DB $42,$42,$42,$42,$42,$42,$7E,$7E
    DB $42,$42,$42,$42,$42,$42,$00,$00

    ; Tile 9: I
    DB $3C,$3C,$18,$18,$18,$18,$18,$18
    DB $18,$18,$18,$18,$3C,$3C,$00,$00

    ; Tile 10: J
    DB $1E,$1E,$08,$08,$08,$08,$08,$08
    DB $08,$08,$48,$48,$30,$30,$00,$00

    ; Tile 11: K
    DB $42,$42,$44,$44,$48,$48,$70,$70
    DB $48,$48,$44,$44,$42,$42,$00,$00

    ; Tile 12: L
    DB $40,$40,$40,$40,$40,$40,$40,$40
    DB $40,$40,$40,$40,$7E,$7E,$00,$00

    ; Tile 13: M
    DB $42,$42,$66,$66,$5A,$5A,$42,$42
    DB $42,$42,$42,$42,$42,$42,$00,$00

    ; Tile 14: N
    DB $42,$42,$62,$62,$52,$52,$4A,$4A
    DB $46,$46,$42,$42,$42,$42,$00,$00

    ; Tile 15: O
    DB $3C,$3C,$42,$42,$42,$42,$42,$42
    DB $42,$42,$42,$42,$3C,$3C,$00,$00

    ; Tile 16: P
    DB $7C,$7C,$42,$42,$42,$42,$7C,$7C
    DB $40,$40,$40,$40,$40,$40,$00,$00

    ; Tile 17: Q
    DB $3C,$3C,$42,$42,$42,$42,$42,$42
    DB $4A,$4A,$44,$44,$3A,$3A,$00,$00

    ; Tile 18: R
    DB $7C,$7C,$42,$42,$42,$42,$7C,$7C
    DB $48,$48,$44,$44,$42,$42,$00,$00

    ; Tile 19: S
    DB $3C,$3C,$42,$42,$40,$40,$3C,$3C
    DB $02,$02,$42,$42,$3C,$3C,$00,$00

    ; Tile 20: T
    DB $7E,$7E,$18,$18,$18,$18,$18,$18
    DB $18,$18,$18,$18,$18,$18,$00,$00

    ; Tile 21: U
    DB $42,$42,$42,$42,$42,$42,$42,$42
    DB $42,$42,$42,$42,$3C,$3C,$00,$00

    ; Tile 22: V
    DB $42,$42,$42,$42,$42,$42,$42,$42
    DB $24,$24,$24,$24,$18,$18,$00,$00

    ; Tile 23: W
    DB $42,$42,$42,$42,$42,$42,$42,$42
    DB $5A,$5A,$66,$66,$42,$42,$00,$00

    ; Tile 24: X
    DB $42,$42,$24,$24,$18,$18,$18,$18
    DB $24,$24,$42,$42,$42,$42,$00,$00

    ; Tile 25: Y
    DB $42,$42,$42,$42,$24,$24,$18,$18
    DB $18,$18,$18,$18,$18,$18,$00,$00

    ; Tile 26: Z
    DB $7E,$7E,$04,$04,$08,$08,$10,$10
    DB $20,$20,$40,$40,$7E,$7E,$00,$00

    ; Tiles 27-32: Numbers 0-5
    ; Tile 27: 0
    DB $3C,$3C,$42,$42,$46,$46,$4A,$4A
    DB $52,$52,$62,$62,$3C,$3C,$00,$00

    ; Tile 28: 1
    DB $18,$18,$38,$38,$18,$18,$18,$18
    DB $18,$18,$18,$18,$7E,$7E,$00,$00

    ; Tile 29: 2
    DB $3C,$3C,$42,$42,$02,$02,$0C,$0C
    DB $30,$30,$40,$40,$7E,$7E,$00,$00

    ; Tile 30: 3
    DB $3C,$3C,$42,$42,$02,$02,$1C,$1C
    DB $02,$02,$42,$42,$3C,$3C,$00,$00

    ; Tile 31: 4
    DB $08,$08,$18,$18,$28,$28,$48,$48
    DB $7E,$7E,$08,$08,$08,$08,$00,$00

    ; Tile 32: 5
    DB $7E,$7E,$40,$40,$7C,$7C,$02,$02
    DB $02,$02,$42,$42,$3C,$3C,$00,$00

    ; Tile 33: ! (exclamation)
    DB $18,$18,$18,$18,$18,$18,$18,$18
    DB $00,$00,$00,$00,$18,$18,$00,$00

font_data_end: