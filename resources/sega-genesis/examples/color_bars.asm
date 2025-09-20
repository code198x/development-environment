; color_bars.asm - Sega Genesis color bars demo
; Demonstrates VDP setup and basic graphics using resource files

    include "genesis.inc"
    include "rom_header.inc"

; ============================================================================
; ROM Header
; ============================================================================

    org ROM_START
    SIMPLE_GENESIS_HEADER "COLOR BARS DEMO"

; ============================================================================
; Main Program Entry Point
; ============================================================================

main:
    ; Disable interrupts during setup
    move.w  #$2700,sr

    ; Initialize the VDP
    bsr     init_vdp

    ; Set up basic color palette
    bsr     setup_palette

    ; Create color bar pattern
    bsr     create_color_bars

    ; Enable display and interrupts
    move.w  #VDP_R1,VDP_CTRL
    move.w  #(M2_DISPLAY_ON|M2_VINT_ON),VDP_DATA

    ; Enable VBlank interrupt
    move.w  #$2000,sr

main_loop:
    ; Simple main loop - could add controller input here
    bra     main_loop

; ============================================================================
; VDP Initialization
; ============================================================================

init_vdp:
    ; Set up basic VDP registers for 40-cell mode
    lea     vdp_init_data(pc),a0
    move.w  #(vdp_init_end-vdp_init_data)/4-1,d0

.init_loop:
    move.l  (a0)+,VDP_CTRL
    dbra    d0,.init_loop
    rts

vdp_init_data:
    dc.l    VDP_R0|$04     ; Mode register 1: H-interrupt off
    dc.l    VDP_R1|$04     ; Mode register 2: Display off, V-interrupt off, DMA on
    dc.l    VDP_R2|$30     ; Scroll A name table at $C000
    dc.l    VDP_R3|$3C     ; Window name table at $F000
    dc.l    VDP_R4|$07     ; Scroll B name table at $E000
    dc.l    VDP_R5|$6C     ; Sprite table at $D800
    dc.l    VDP_R6|$00     ; Sprite pattern base
    dc.l    VDP_R7|$00     ; Background color: palette 0, color 0
    dc.l    VDP_R10|$00    ; H-interrupt counter: off
    dc.l    VDP_R11|$00    ; Mode register 3: full scroll
    dc.l    VDP_R12|$81    ; Mode register 4: 40-cell mode
    dc.l    VDP_R13|$37    ; H-scroll table at $DC00
    dc.l    VDP_R15|$02    ; Auto-increment: 2 bytes
    dc.l    VDP_R16|$01    ; Scroll size: 64x32
    dc.l    VDP_R17|$00    ; Window H position: 0
    dc.l    VDP_R18|$00    ; Window V position: 0
vdp_init_end:

; ============================================================================
; Palette Setup
; ============================================================================

setup_palette:
    ; Set up CRAM write command
    move.l  #VDP_CMD_CRAM_W,VDP_CTRL

    ; Write a simple palette with different colors for each bar
    move.w  #COLOR_BLACK,VDP_DATA      ; Color 0: Black
    move.w  #COLOR_BLUE,VDP_DATA       ; Color 1: Blue
    move.w  #COLOR_RED,VDP_DATA        ; Color 2: Red
    move.w  #COLOR_MAGENTA,VDP_DATA    ; Color 3: Magenta
    move.w  #COLOR_GREEN,VDP_DATA      ; Color 4: Green
    move.w  #COLOR_CYAN,VDP_DATA       ; Color 5: Cyan
    move.w  #COLOR_YELLOW,VDP_DATA     ; Color 6: Yellow
    move.w  #COLOR_WHITE,VDP_DATA      ; Color 7: White

    ; Fill rest of palette 0 with variations
    move.w  #$0444,VDP_DATA            ; Color 8: Dark gray
    move.w  #$0888,VDP_DATA            ; Color 9: Medium gray
    move.w  #$0CCC,VDP_DATA            ; Color 10: Light gray
    move.w  #$000E,VDP_DATA            ; Color 11: Bright red
    move.w  #$00E0,VDP_DATA            ; Color 12: Bright green
    move.w  #$0E00,VDP_DATA            ; Color 13: Bright blue
    move.w  #$0EE0,VDP_DATA            ; Color 14: Bright cyan
    move.w  #$0E0E,VDP_DATA            ; Color 15: Bright magenta

    rts

; ============================================================================
; Create Color Bars Pattern
; ============================================================================

create_color_bars:
    ; Create a simple tile pattern for color bars
    ; Each tile will be a solid color

    ; Set up VRAM write to pattern area
    move.l  #(VDP_CMD_WRITE|TILES_START),VDP_CTRL

    ; Create 8 solid color tiles (one for each basic color)
    move.w  #7,d0           ; 8 tiles (0-7)

.tile_loop:
    move.w  #7,d1           ; 8 rows per tile

.row_loop:
    ; Each row is 4 bytes (32 pixels / 8 pixels per byte)
    ; For solid color, we want the palette index in every pixel
    move.b  d0,d2           ; Get color index
    lsl.b   #4,d2           ; Shift to upper nibble
    or.b    d0,d2           ; Add to lower nibble (same color both pixels)

    move.l  d2,d3           ; Copy to all 4 bytes
    lsl.l   #8,d3
    or.l    d2,d3
    lsl.l   #8,d3
    or.l    d2,d3
    lsl.l   #8,d3
    or.l    d2,d3

    move.l  d3,VDP_DATA     ; Write the row

    dbra    d1,.row_loop
    dbra    d0,.tile_loop

    ; Now set up the name table to display color bars
    move.l  #(VDP_CMD_WRITE|SCROLL_A),VDP_CTRL

    ; Create horizontal color bars
    move.w  #27,d0          ; 28 rows visible

.name_row_loop:
    move.w  #39,d1          ; 40 columns

.name_col_loop:
    ; Calculate which color bar this is (8 bars total)
    move.w  d0,d2
    lsr.w   #2,d2           ; Divide row by 4 (28 rows / 8 bars ≈ 3.5)
    andi.w  #7,d2           ; Keep in range 0-7

    move.w  d2,VDP_DATA     ; Write tile number (matches color)

    dbra    d1,.name_col_loop
    dbra    d0,.name_row_loop

    rts

; ============================================================================
; Interrupt Handlers
; ============================================================================

; Vertical interrupt handler
irq6:
    ; Simple VBlank handler - could update animations here
    ; Read VDP status to acknowledge interrupt
    move.w  VDP_CTRL,d0
    rte

; Default interrupt handlers (just return)
bus_error:
address_error:
illegal_inst:
divide_zero:
chk_inst:
trapv_inst:
privilege_viol:
trace_except:
line_a_emu:
line_f_emu:
unint_int:
spurious_int:
irq1:
irq2:
irq3:
irq4:
irq5:
irq7:
    rte