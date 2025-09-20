; init.inc - Game Boy initialization routines
; Sets up a known state for the Game Boy hardware

; Standard Game Boy initialization
INIT_GAMEBOY MACRO
    ; Disable interrupts during init
    di

    ; Initialize stack pointer
    ld sp, $FFFE

    ; Turn off LCD (required for VRAM access)
    call lcd_off

    ; Clear VRAM ($8000-$9FFF)
    ld hl, $8000
    ld bc, $2000
    ld a, $00
    call mem_set

    ; Clear OAM ($FE00-$FE9F)
    ld hl, $FE00
    ld bc, $A0
    ld a, $00
    call mem_set

    ; Initialize sound system
    call sound_init

    ; Initialize joypad
    call joypad_init

    ; Clear work RAM ($C000-$DFFF)
    ld hl, $C000
    ld bc, $2000
    ld a, $00
    call mem_set

    ; Clear high RAM ($FF80-$FFFE)
    ld hl, $FF80
    ld bc, $7F
    ld a, $00
    call mem_set

    ; Set up default palettes
    ld a, %11100100     ; Default palette (white to black)
    ldh [rBGP], a       ; Background palette
    ldh [rOBP0], a      ; Object palette 0
    ldh [rOBP1], a      ; Object palette 1

    ; Reset scroll positions
    xor a
    ldh [rSCX], a       ; Scroll X = 0
    ldh [rSCY], a       ; Scroll Y = 0

    ; Position window off-screen initially
    ld a, 7
    ldh [rWX], a        ; Window X = 7 (leftmost visible position)
    ld a, 144
    ldh [rWY], a        ; Window Y = 144 (off bottom of screen)

    ; Enable interrupts we want
    ld a, IEF_VBLANK
    ldh [rIE], a        ; Enable VBlank interrupt

    ; Turn LCD back on with basic settings
    ld a, LCDCF_ON | LCDCF_BGON
    ldh [rLCDC], a

    ; Enable interrupts
    ei
ENDM

; Turn LCD off safely (must be done during VBlank)
lcd_off:
    ; Check if LCD is already off
    ldh a, [rLCDC]
    bit 7, a
    ret z               ; Already off, return

    ; Wait for VBlank
.wait_vblank:
    ldh a, [rLY]
    cp 144
    jr c, .wait_vblank

    ; Turn off LCD
    ldh a, [rLCDC]
    res 7, a
    ldh [rLCDC], a
    ret

; Turn LCD on with specified settings
lcd_on:
    ld a, LCDCF_ON | LCDCF_BGON | LCDCF_OBJON
    ldh [rLCDC], a
    ret

; Initialize sound system (turn off all channels)
sound_init:
    ; Turn off sound
    xor a
    ldh [rNR52], a

    ; Reset all sound registers
    ld hl, rNR10
    ld c, $26           ; Number of sound registers
.clear_sound:
    ld [hl+], a
    dec c
    jr nz, .clear_sound

    ; Turn sound back on
    ld a, $80
    ldh [rNR52], a

    ; Set master volume
    ld a, $77           ; Max volume on both channels
    ldh [rNR50], a

    ; Enable all channels
    ld a, $FF
    ldh [rNR51], a
    ret

; Initialize joypad (no special setup needed)
joypad_init:
    ret

; Memory set function (HL = address, BC = count, A = value)
mem_set:
    ld [hl+], a
    dec bc
    ld a, b
    or c
    jr nz, mem_set
    ret

; Memory copy function (HL = source, DE = dest, BC = count)
mem_copy:
    ld a, [hl+]
    ld [de], a
    inc de
    dec bc
    ld a, b
    or c
    jr nz, mem_copy
    ret

; Wait for VBlank (useful for timing)
wait_vblank:
    ldh a, [rLY]
    cp 144
    jr c, wait_vblank
    ret

; Read joypad state into A register
; Returns: A = joypad state (bit 0-7: right,left,up,down,a,b,select,start)
read_joypad:
    ; Read direction pad
    ld a, P1F_5         ; Select direction buttons
    ldh [rP1], a
    ldh a, [rP1]        ; Read twice for stability
    ldh a, [rP1]
    cpl                 ; Invert (0 = pressed)
    and $0F
    swap a              ; Move to upper nibble
    ld b, a

    ; Read action buttons
    ld a, P1F_4         ; Select action buttons
    ldh [rP1], a
    ldh a, [rP1]        ; Read twice for stability
    ldh a, [rP1]
    cpl                 ; Invert (0 = pressed)
    and $0F
    or b                ; Combine with direction buttons

    ; Deselect all buttons
    ld b, a
    ld a, P1F_5 | P1F_4
    ldh [rP1], a
    ld a, b
    ret

; Simple delay loop (A = delay multiplier)
delay:
    ld b, a
.outer:
    ld c, $FF
.inner:
    dec c
    jr nz, .inner
    dec b
    jr nz, .outer
    ret