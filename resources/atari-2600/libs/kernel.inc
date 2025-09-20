; kernel.inc - Atari 2600 Display Kernel Utilities
; Common patterns and macros for 2600 display kernels

; ============================================================================
; Standard Frame Structure Macros
; ============================================================================

; Start vertical sync (beginning of frame)
.macro VERTICAL_SYNC
    lda #%00000010      ; Start vertical sync
    sta VSYNC
    sta WSYNC           ; Wait 3 scanlines for vsync
    sta WSYNC
    sta WSYNC
    lda #0
    sta VSYNC           ; End vertical sync
.endmacro

; Vertical blank period (37 scanlines total, 3 used for vsync)
.macro VERTICAL_BLANK lines
    .if lines < 2
        .error "Vertical blank must be at least 2 lines"
    .endif

    lda #%00000010      ; Enable VBLANK
    sta VBLANK

    ; Set timer for remaining vblank time
    ; Each timer count = 64 CPU cycles = ~1.37 scanlines
    lda #(.lobyte((lines-2)*76/64))
    sta TIM64T

    ; Your vblank code goes here (game logic, etc.)
    ; ...

.wait_vblank:
    lda INTIM           ; Check timer
    bne .wait_vblank    ; Wait until timer expires

    lda #0
    sta VBLANK          ; Disable VBLANK (enable display)
.endmacro

; Overscan period (30 scanlines)
.macro OVERSCAN lines
    lda #%00000010      ; Enable VBLANK (no display)
    sta VBLANK

    ; Set timer for overscan
    lda #(.lobyte(lines*76/64))
    sta TIM64T

.wait_overscan:
    lda INTIM
    bne .wait_overscan
.endmacro

; ============================================================================
; Object Positioning Macros
; ============================================================================

; Position an object at specific X coordinate
; Input: A = desired X position (0-159)
; Trashes: A, X
.macro POSITION_OBJECT object_reset
    sta WSYNC           ; Start at beginning of scanline
    sec                 ; Set carry for subtraction
.divide_loop:
    sbc #15             ; Subtract 15 (one positioning loop)
    bcs .divide_loop    ; Keep going if result positive

    ; A now contains -(fine adjustment needed)
    eor #%11111111      ; Convert to positive fine adjustment
    asl                 ; Shift to upper nibble
    asl
    asl
    asl
    sta HMP0,X          ; Store fine adjustment (assume X = object index)

    adc #7              ; Coarse position loops (7 minimum)
    tax
.coarse_loop:
    dex
    bpl .coarse_loop    ; Burn cycles for coarse positioning

    sta object_reset    ; Reset object position
.endmacro

; Position player 0 at X coordinate in A
.macro POSITION_P0
    POSITION_OBJECT RESP0
.endmacro

; Position player 1 at X coordinate in A
.macro POSITION_P1
    POSITION_OBJECT RESP1
.endmacro

; Position missile 0 at X coordinate in A
.macro POSITION_M0
    POSITION_OBJECT RESM0
.endmacro

; Position missile 1 at X coordinate in A
.macro POSITION_M1
    POSITION_OBJECT RESM1
.endmacro

; Position ball at X coordinate in A
.macro POSITION_BALL
    POSITION_OBJECT RESBL
.endmacro

; Apply all fine positioning adjustments
.macro APPLY_POSITIONING
    sta WSYNC           ; Start of scanline
    sta HMOVE           ; Apply fine positioning
.endmacro

; ============================================================================
; Sprite Display Macros
; ============================================================================

; Display a sprite with height in Y register
; sprite_data points to sprite graphics
; Assumes GRP0 for display
.macro DISPLAY_SPRITE sprite_data
    ldy #0              ; Start at top of sprite
.sprite_loop:
    lda sprite_data,y   ; Get sprite line
    sta WSYNC           ; Wait for horizontal sync
    sta GRP0            ; Display sprite line
    iny                 ; Next sprite line
    cpy #8              ; Assuming 8-line sprites
    bne .sprite_loop
.endmacro

; Two-player sprite display with proper timing
.macro DISPLAY_TWO_SPRITES sprite0_data, sprite1_data, height
    ldy #0
.two_sprite_loop:
    lda sprite0_data,y  ; Get player 0 sprite line
    sta WSYNC           ; Start scanline
    sta GRP0            ; Display player 0
    lda sprite1_data,y  ; Get player 1 sprite line
    sta GRP1            ; Display player 1
    iny
    cpy height
    bne .two_sprite_loop
.endmacro

; ============================================================================
; Playfield Macros
; ============================================================================

; Set up a symmetrical playfield
.macro SET_PLAYFIELD_SYM pf0_val, pf1_val, pf2_val
    lda #pf0_val
    sta PF0
    lda #pf1_val
    sta PF1
    lda #pf2_val
    sta PF2
    lda #PF_REFLECT     ; Set playfield to reflect
    sta CTRLPF
.endmacro

; Set up an asymmetrical playfield
.macro SET_PLAYFIELD_ASYM pf0_val, pf1_val, pf2_val
    lda #pf0_val
    sta PF0
    lda #pf1_val
    sta PF1
    lda #pf2_val
    sta PF2
    lda #0              ; No reflection
    sta CTRLPF
.endmacro

; Clear playfield
.macro CLEAR_PLAYFIELD
    lda #0
    sta PF0
    sta PF1
    sta PF2
.endmacro

; ============================================================================
; Color and Graphics Utilities
; ============================================================================

; Set colors for all objects
.macro SET_COLORS bg_color, pf_color, p0_color, p1_color
    lda #bg_color
    sta COLUBK          ; Background
    lda #pf_color
    sta COLUPF          ; Playfield
    lda #p0_color
    sta COLUP0          ; Player 0
    lda #p1_color
    sta COLUP1          ; Player 1
.endmacro

; Flash an object by alternating colors
.macro FLASH_OBJECT object_color, color1, color2, frame_counter
    lda frame_counter
    and #%00001000      ; Flash every 8 frames
    beq .use_color1
    lda #color2
    bne .set_color      ; Branch always
.use_color1:
    lda #color1
.set_color:
    sta object_color
.endmacro

; ============================================================================
; Sound Macros
; ============================================================================

; Play a simple tone
.macro PLAY_TONE channel, frequency, volume, duration
    lda #PURE_TONE
    sta AUDC0,X         ; Assume X = channel offset
    lda #frequency
    sta AUDF0,X
    lda #volume
    sta AUDV0,X
.endmacro

; Stop sound on a channel
.macro STOP_SOUND channel
    lda #0
    sta AUDV0,X         ; Assume X = channel offset
.endmacro

; ============================================================================
; Input Reading Macros
; ============================================================================

; Read joystick for player (0 or 1)
; Returns direction bits in A
.macro READ_JOYSTICK player
    .if player = 0
        lda SWCHA
        and #%00001111      ; Mask player 0 bits
    .else
        lda SWCHA
        lsr                 ; Shift player 1 to lower bits
        lsr
        lsr
        lsr
        and #%00001111
    .endif
.endmacro

; Read fire button for player (0 or 1)
; Sets zero flag if pressed
.macro READ_FIRE player
    .if player = 0
        bit INPT4
    .else
        bit INPT5
    .endif
.endmacro

; Read console switches
; Returns switch states in A
.macro READ_CONSOLE_SWITCHES
    lda SWCHB
.endmacro

; ============================================================================
; Banking Macros (for larger cartridges)
; ============================================================================

; Switch to bank (F8 scheme - 8K)
.macro SWITCH_BANK_F8 bank
    .if bank = 0
        bit F8_BANK0
    .else
        bit F8_BANK1
    .endif
.endmacro

; Switch to bank (F6 scheme - 16K)
.macro SWITCH_BANK_F6 bank
    .if bank = 0
        bit F6_BANK0
    .elseif bank = 1
        bit F6_BANK1
    .elseif bank = 2
        bit F6_BANK2
    .else
        bit F6_BANK3
    .endif
.endmacro

; ============================================================================
; Collision Detection Utilities
; ============================================================================

; Check for collision between objects
; Sets flags based on collision registers
.macro CHECK_COLLISION collision_reg
    bit collision_reg   ; Check collision
    ; BMI/BVC to branch on collision result
.endmacro

; Clear all collision latches
.macro CLEAR_COLLISIONS
    sta CXCLR           ; Strobe to clear
.endmacro

; ============================================================================
; Timing and Synchronization
; ============================================================================

; Waste specific number of cycles
.macro WASTE_CYCLES cycles
    .if cycles = 2
        nop
    .elseif cycles = 3
        nop
        nop
    .elseif cycles = 4
        nop
        nop
        nop
    .elseif cycles = 5
        nop
        nop
        nop
        nop
    .else
        ; For longer delays, use a loop
        ldx #(.lobyte(cycles/5))
.waste_loop:
        dex
        bne .waste_loop
    .endif
.endmacro

; Precise timing for object updates
.macro TIMED_UPDATE cycles_before, update_code, cycles_after
    WASTE_CYCLES cycles_before
    update_code
    WASTE_CYCLES cycles_after
.endmacro

; ============================================================================
; Common Game Patterns
; ============================================================================

; Simple score display (BCD)
.macro DISPLAY_SCORE score_var, tens_sprite, ones_sprite
    lda score_var
    and #%11110000      ; Get tens digit
    lsr
    lsr
    lsr
    lsr
    tax
    lda tens_sprite,x   ; Get tens sprite
    sta GRP0

    lda score_var
    and #%00001111      ; Get ones digit
    tax
    lda ones_sprite,x   ; Get ones sprite
    sta GRP1
.endmacro

; Lives display using repeated sprites
.macro DISPLAY_LIVES lives_count, life_sprite
    ldx lives_count
    beq .no_lives
.life_loop:
    lda life_sprite     ; Display life icon
    sta WSYNC
    sta GRP0
    dex
    bne .life_loop
.no_lives:
.endmacro

; Simple AI movement toward target
.macro MOVE_TOWARD_TARGET current_pos, target_pos, speed
    lda target_pos
    cmp current_pos
    beq .no_move        ; Already at target
    bcc .move_left
    ; Move right
    lda current_pos
    clc
    adc #speed
    sta current_pos
    jmp .no_move
.move_left:
    lda current_pos
    sec
    sbc #speed
    sta current_pos
.no_move:
.endmacro