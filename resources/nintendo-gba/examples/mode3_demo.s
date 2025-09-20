@ mode3_demo.s - Game Boy Advance Mode 3 Graphics Demo
@ Demonstrates bitmap graphics and input handling using resource files

.include "gba.inc"
.include "gba_init.inc"

.arm
.section ".text"
.global _start

_start:
    @ Initialize GBA system
    gba_init

    @ Set up Mode 3 (bitmap graphics)
    set_mode3

    @ Initialize the demo
    bl init_demo

    @ Main loop
main_loop:
    @ Wait for vertical blank
    bl wait_vblank

    @ Handle input
    bl handle_input

    @ Update graphics
    bl update_graphics

    @ Loop forever
    b main_loop

@ ============================================================================
@ Demo Initialization
@ ============================================================================

init_demo:
    push {lr}

    @ Set up a basic palette
    mov r0, #15             @ Red component
    mov r1, #15             @ Green component
    mov r2, #15             @ Blue component
    bl rgb15
    mov r4, r0              @ Save white color

    mov r0, #31             @ Full red
    mov r1, #0              @ No green
    mov r2, #0              @ No blue
    bl rgb15
    mov r5, r0              @ Save red color

    mov r0, #0              @ No red
    mov r1, #31             @ Full green
    mov r2, #0              @ No blue
    bl rgb15
    mov r6, r0              @ Save green color

    mov r0, #0              @ No red
    mov r1, #0              @ No green
    mov r2, #31             @ Full blue
    bl rgb15
    mov r7, r0              @ Save blue color

    @ Clear screen to black
    mov r0, #0              @ Black
    ldr r1, =MODE3_FRAME_0
    mov r2, #(SCREEN_WIDTH * SCREEN_HEIGHT * 2)  @ 16-bit pixels
    bl memset32

    @ Draw initial graphics
    bl draw_border
    bl draw_title

    @ Initialize variables
    ldr r0, =player_x
    mov r1, #120            @ Center X
    str r1, [r0]

    ldr r0, =player_y
    mov r1, #80             @ Center Y
    str r1, [r0]

    pop {pc}

@ ============================================================================
@ Input Handling
@ ============================================================================

handle_input:
    push {r4-r7, lr}

    @ Read current keys
    bl read_keys
    mov r4, r0              @ Save key state

    @ Load current player position
    ldr r5, =player_x
    ldr r6, [r5]            @ Current X
    ldr r7, =player_y
    ldr r0, [r7]            @ Current Y

    @ Check for movement
    mov r1, #KEY_LEFT
    and r1, r4, r1
    cmp r1, #0
    beq .check_right
    @ Move left
    subs r6, r6, #2
    movmi r6, #0            @ Clamp to left edge

.check_right:
    mov r1, #KEY_RIGHT
    and r1, r4, r1
    cmp r1, #0
    beq .check_up
    @ Move right
    add r6, r6, #2
    cmp r6, #(SCREEN_WIDTH - 8)
    movge r6, #(SCREEN_WIDTH - 8)  @ Clamp to right edge

.check_up:
    mov r1, #KEY_UP
    and r1, r4, r1
    cmp r1, #0
    beq .check_down
    @ Move up
    subs r0, r0, #2
    movmi r0, #0            @ Clamp to top edge

.check_down:
    mov r1, #KEY_DOWN
    and r1, r4, r1
    cmp r1, #0
    beq .input_done
    @ Move down
    add r0, r0, #2
    cmp r0, #(SCREEN_HEIGHT - 8)
    movge r0, #(SCREEN_HEIGHT - 8)  @ Clamp to bottom edge

.input_done:
    @ Store updated position
    str r6, [r5]            @ Store X
    str r0, [r7]            @ Store Y

    pop {r4-r7, pc}

@ ============================================================================
@ Graphics Updates
@ ============================================================================

update_graphics:
    push {r4-r8, lr}

    @ Erase old player position (draw black square)
    ldr r4, =old_player_x
    ldr r5, [r4]            @ Old X
    ldr r6, =old_player_y
    ldr r7, [r6]            @ Old Y
    mov r8, #RGB_BLACK
    bl draw_square

    @ Draw player at new position
    ldr r4, =player_x
    ldr r5, [r4]            @ Current X
    ldr r6, =player_y
    ldr r7, [r6]            @ Current Y
    mov r8, #RGB_RED        @ Player color
    bl draw_square

    @ Update old position for next frame
    ldr r4, =old_player_x
    str r5, [r4]
    ldr r4, =old_player_y
    str r7, [r4]

    pop {r4-r8, pc}

@ ============================================================================
@ Drawing Functions
@ ============================================================================

@ Draw a border around the screen
draw_border:
    push {r4-r7, lr}

    mov r4, #RGB_WHITE      @ Border color

    @ Top border
    mov r5, #0              @ X start
    mov r6, #0              @ Y start
    mov r7, #SCREEN_WIDTH   @ Width
    mov r8, #2              @ Height
    bl draw_rect

    @ Bottom border
    mov r5, #0              @ X start
    mov r6, #(SCREEN_HEIGHT - 2)  @ Y start
    mov r7, #SCREEN_WIDTH   @ Width
    mov r8, #2              @ Height
    bl draw_rect

    @ Left border
    mov r5, #0              @ X start
    mov r6, #0              @ Y start
    mov r7, #2              @ Width
    mov r8, #SCREEN_HEIGHT  @ Height
    bl draw_rect

    @ Right border
    mov r5, #(SCREEN_WIDTH - 2)  @ X start
    mov r6, #0              @ Y start
    mov r7, #2              @ Width
    mov r8, #SCREEN_HEIGHT  @ Height
    bl draw_rect

    pop {r4-r7, pc}

@ Draw title text (simple pixel font)
draw_title:
    push {r4-r6, lr}

    @ Draw "GBA DEMO" at top of screen
    mov r4, #RGB_YELLOW
    mov r5, #80             @ X position
    mov r6, #8              @ Y position

    @ This would normally load font data and draw characters
    @ For simplicity, just draw some colored rectangles
    bl draw_simple_text

    pop {r4-r6, pc}

draw_simple_text:
    @ Draw simple blocks representing text
    push {lr}

    @ "G"
    mov r5, #80
    mov r6, #8
    mov r7, #8
    mov r8, #12
    mov r4, #RGB_YELLOW
    bl draw_rect

    @ "B"
    mov r5, #92
    mov r6, #8
    mov r7, #8
    mov r8, #12
    mov r4, #RGB_GREEN
    bl draw_rect

    @ "A"
    mov r5, #104
    mov r6, #8
    mov r7, #8
    mov r8, #12
    mov r4, #RGB_CYAN
    bl draw_rect

    pop {pc}

@ Draw a square at position (r5, r7) with color r8
draw_square:
    push {r4, r7, r8, lr}
    mov r4, r8              @ Color
    mov r7, #8              @ Width
    mov r8, #8              @ Height
    bl draw_rect
    pop {r4, r7, r8, pc}

@ Draw filled rectangle
@ r4 = color, r5 = x, r6 = y, r7 = width, r8 = height
draw_rect:
    push {r0-r3, r9-r11, lr}

    @ Calculate starting address
    ldr r0, =MODE3_FRAME_0
    mov r1, #SCREEN_WIDTH
    mul r2, r6, r1          @ Y * screen width
    add r2, r2, r5          @ Add X
    lsl r2, r2, #1          @ Multiply by 2 (16-bit pixels)
    add r0, r0, r2          @ Starting address

    @ Draw each row
    mov r9, #0              @ Current Y

.rect_y_loop:
    cmp r9, r8              @ Check if done with height
    bge .rect_done

    @ Draw current row
    mov r10, #0             @ Current X
    mov r11, r0             @ Current line address

.rect_x_loop:
    cmp r10, r7             @ Check if done with width
    bge .rect_next_line

    @ Draw pixel
    strh r4, [r11]
    add r11, r11, #2        @ Next pixel
    add r10, r10, #1        @ Increment X
    b .rect_x_loop

.rect_next_line:
    add r0, r0, #(SCREEN_WIDTH * 2)  @ Next line
    add r9, r9, #1          @ Increment Y
    b .rect_y_loop

.rect_done:
    pop {r0-r3, r9-r11, pc}

@ ============================================================================
@ Data Section
@ ============================================================================

.section ".data"
.align 2

player_x:       .word 120
player_y:       .word 80
old_player_x:   .word 120
old_player_y:   .word 80

@ ============================================================================
@ ROM Header (GBA cartridge header)
@ ============================================================================

.section ".header", "ax"
.arm
.align 2

rom_header:
    b _start                @ Branch to start
    .fill 156, 1, 0         @ Nintendo logo placeholder (filled by tools)
    .ascii "MODE3DEMO"      @ Game title (12 chars)
    .ascii "ABCD"           @ Game code (4 chars)
    .ascii "01"             @ Maker code (2 chars)
    .byte 0x96              @ Fixed value
    .byte 0x00              @ Main unit code
    .byte 0x00              @ Device type
    .fill 7, 1, 0           @ Reserved
    .byte 0x01              @ Software version
    .byte 0x00              @ Complement check (filled by tools)
    .fill 2, 1, 0           @ Reserved