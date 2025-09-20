; reset.inc - Standard NES initialization code
; Sets up a known state for CPU, PPU, and APU

.macro init_nes
    sei                 ; Disable IRQs
    cld                 ; Disable decimal mode (not on NES but good practice)
    ldx #$FF
    txs                 ; Set stack pointer to $01FF

    ; Disable NMI and rendering
    ldx #$00
    stx PPU_CTRL
    stx PPU_MASK

    ; Disable DMC IRQs
    stx APU_DMC_CTRL

    ; Clear APU frame IRQ
    ldx #$40
    stx JOYPAD2

    ; Wait for first VBlank (PPU warmup)
@vblank1:
    bit PPU_STATUS
    bpl @vblank1

    ; Clear all RAM ($0000-$07FF)
    lda #$00
    ldx #$00
@clear_ram:
    sta $0000,x
    sta $0100,x
    sta $0200,x
    sta $0300,x
    sta $0400,x
    sta $0500,x
    sta $0600,x
    sta $0700,x
    inx
    bne @clear_ram

    ; Clear sprite RAM
    lda #$FE        ; Move sprites off screen
    ldx #$00
@clear_oam:
    sta OAM_DATA
    inx
    bne @clear_oam

    ; Wait for second VBlank (PPU fully ready)
@vblank2:
    bit PPU_STATUS
    bpl @vblank2

    ; PPU is ready, enable NMI if desired
    lda #CTRL_NMI_ON
    sta PPU_CTRL
.endmacro

; Load palettes helper
.macro load_palettes palette_data
    lda PPU_STATUS      ; Reset latch
    lda #>PALETTE_START
    sta PPU_ADDR
    lda #<PALETTE_START
    sta PPU_ADDR

    ldx #$00
@load_pal:
    lda palette_data,x
    sta PPU_DATA
    inx
    cpx #$20            ; 32 bytes (16 bg + 16 sprite)
    bne @load_pal
.endmacro

; Simple controller reading
.macro read_controller_1
    lda #$01
    sta JOYPAD1         ; Latch controller
    sta controller1     ; Store A button
    lsr a
    sta JOYPAD1         ; Now reading B button

    ldx #$08
@read_loop:
    lda JOYPAD1
    lsr a
    ror controller1
    dex
    bne @read_loop
.endmacro