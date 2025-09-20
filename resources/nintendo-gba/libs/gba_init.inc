@ gba_init.inc - Game Boy Advance Initialization and Utility Functions
@ ARM assembly macros and functions for GBA development

@ ============================================================================
@ ARM/Thumb Mode Switching
@ ============================================================================

@ Switch to ARM mode
.macro arm_mode
    .arm
    .align 2
.endm

@ Switch to Thumb mode
.macro thumb_mode
    .thumb
    .align 1
.endm

@ ============================================================================
@ Interrupt Vector Table Setup
@ ============================================================================

@ Standard GBA interrupt vector table
.macro setup_vectors
    .arm
    .section ".vectors", "ax"
    .align 2

    @ Exception vectors
    b   _start              @ Reset
    b   _undefined          @ Undefined instruction
    b   _swi                @ Software interrupt
    b   _prefetch_abort     @ Prefetch abort
    b   _data_abort         @ Data abort
    b   _reserved           @ Reserved
    b   _irq                @ IRQ
    b   _fiq                @ FIQ
.endm

@ ============================================================================
@ Basic System Initialization
@ ============================================================================

@ Initialize GBA system (ARM mode)
.macro gba_init
    @ Disable interrupts
    mrs r0, cpsr
    orr r0, r0, #0xC0       @ Disable IRQ and FIQ
    msr cpsr_c, r0

    @ Set up stacks for different modes
    @ IRQ mode stack
    mov r0, #0x12           @ IRQ mode
    orr r0, r0, #0xC0       @ Disable interrupts
    msr cpsr_c, r0
    ldr sp, =0x03007FA0     @ IRQ stack at end of IWRAM

    @ System mode stack
    mov r0, #0x1F           @ System mode
    msr cpsr_c, r0
    ldr sp, =0x03007F00     @ System stack

    @ Clear EWRAM
    mov r0, #0
    ldr r1, =EWRAM
    ldr r2, =EWRAM_SIZE
    bl  memset32

    @ Clear IWRAM (except stack area)
    mov r0, #0
    ldr r1, =IWRAM
    mov r2, #0x7000         @ Clear first 28KB, leave 4KB for stacks
    bl  memset32

    @ Initialize display
    ldr r0, =REG_DISPCNT
    mov r1, #DCNT_BLANK     @ Start with blank screen
    strh r1, [r0]

    @ Clear VRAM
    mov r0, #0
    ldr r1, =VRAM
    ldr r2, =VRAM_SIZE
    bl  memset32

    @ Clear OAM
    mov r0, #0
    ldr r1, =OAM
    mov r2, #OAM_SIZE
    bl  memset32

    @ Clear palettes
    mov r0, #0
    ldr r1, =PALETTE_RAM
    mov r2, #PALETTE_SIZE
    bl  memset32

    @ Set up interrupts
    ldr r0, =REG_IME
    mov r1, #0              @ Disable interrupts initially
    strh r1, [r0]

    ldr r0, =REG_IE
    mov r1, #0              @ No interrupts enabled
    strh r1, [r0]

    ldr r0, =REG_IF
    ldr r1, =0x3FFF         @ Clear all interrupt flags
    strh r1, [r0]
.endm

@ ============================================================================
@ Memory Utilities
@ ============================================================================

@ Fast 32-bit memory set
@ r0 = value, r1 = destination, r2 = size in bytes
.func memset32
memset32:
    cmp r2, #0
    bxeq lr                 @ Return if size is 0

    @ Ensure 4-byte alignment
    ands r3, r1, #3
    bne .memset32_unaligned

    @ Fill in 32-byte chunks when possible
    cmp r2, #32
    blt .memset32_small

.memset32_loop:
    stmia r1!, {r0, r0, r0, r0, r0, r0, r0, r0}
    sub r2, r2, #32
    cmp r2, #32
    bge .memset32_loop

.memset32_small:
    @ Handle remaining words
    cmp r2, #4
    blt .memset32_bytes
    str r0, [r1], #4
    sub r2, r2, #4
    b .memset32_small

.memset32_bytes:
    @ Handle remaining bytes
    cmp r2, #0
    bxeq lr
    strb r0, [r1], #1
    sub r2, r2, #1
    b .memset32_bytes

.memset32_unaligned:
    @ Handle unaligned destination
    strb r0, [r1], #1
    sub r2, r2, #1
    b memset32
.endfunc

@ Fast 32-bit memory copy
@ r0 = source, r1 = destination, r2 = size in bytes
.func memcpy32
memcpy32:
    cmp r2, #0
    bxeq lr

    @ Check alignment
    orr r3, r0, r1
    ands r3, r3, #3
    bne .memcpy32_unaligned

    @ Copy in 32-byte chunks
    cmp r2, #32
    blt .memcpy32_small

.memcpy32_loop:
    ldmia r0!, {r3, r4, r5, r6, r7, r8, r9, r10}
    stmia r1!, {r3, r4, r5, r6, r7, r8, r9, r10}
    sub r2, r2, #32
    cmp r2, #32
    bge .memcpy32_loop

.memcpy32_small:
    cmp r2, #4
    blt .memcpy32_bytes
    ldr r3, [r0], #4
    str r3, [r1], #4
    sub r2, r2, #4
    b .memcpy32_small

.memcpy32_bytes:
    cmp r2, #0
    bxeq lr
    ldrb r3, [r0], #1
    strb r3, [r1], #1
    sub r2, r2, #1
    b .memcpy32_bytes

.memcpy32_unaligned:
    @ Byte-by-byte copy for unaligned
    ldrb r3, [r0], #1
    strb r3, [r1], #1
    subs r2, r2, #1
    bne .memcpy32_unaligned
    bx lr
.endfunc

@ ============================================================================
@ Display Mode Setup
@ ============================================================================

@ Set video mode 0 (4 text backgrounds)
.macro set_mode0
    ldr r0, =REG_DISPCNT
    mov r1, #(DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3)
    strh r1, [r0]
.endm

@ Set video mode 3 (240x160 bitmap, 15-bit color)
.macro set_mode3
    ldr r0, =REG_DISPCNT
    mov r1, #(DCNT_MODE3 | DCNT_BG2)
    strh r1, [r0]
.endm

@ Set video mode 4 (240x160 bitmap, 8-bit color, page flipping)
.macro set_mode4
    ldr r0, =REG_DISPCNT
    mov r1, #(DCNT_MODE4 | DCNT_BG2)
    strh r1, [r0]
.endm

@ Set video mode 5 (160x128 bitmap, 15-bit color, page flipping)
.macro set_mode5
    ldr r0, =REG_DISPCNT
    mov r1, #(DCNT_MODE5 | DCNT_BG2)
    strh r1, [r0]
.endm

@ ============================================================================
@ Input Handling
@ ============================================================================

@ Read current key state
@ Returns key state in r0 (0 = pressed, 1 = not pressed)
.func read_keys
read_keys:
    ldr r1, =REG_KEYINPUT
    ldrh r0, [r1]
    mvn r0, r0              @ Invert so 1 = pressed
    ldr r1, =KEY_MASK
    and r0, r0, r1          @ Mask to valid keys
    bx lr
.endfunc

@ Check if specific key is pressed
@ r0 = key mask to check
@ Returns: r0 = 1 if pressed, 0 if not
.func key_pressed
key_pressed:
    push {r1, lr}
    mov r1, r0              @ Save key mask
    bl read_keys
    and r0, r0, r1          @ Check if key is set
    cmp r0, #0
    movne r0, #1            @ Return 1 if pressed
    moveq r0, #0            @ Return 0 if not pressed
    pop {r1, pc}
.endfunc

@ ============================================================================
@ VSync and Timing
@ ============================================================================

@ Wait for vertical blank
.func wait_vblank
wait_vblank:
    ldr r0, =REG_VCOUNT
.wait_vblank_loop:
    ldrh r1, [r0]
    cmp r1, #160            @ VBlank starts at line 160
    blt .wait_vblank_loop
    bx lr
.endfunc

@ Wait for end of vertical blank
.func wait_vblank_end
wait_vblank_end:
    ldr r0, =REG_VCOUNT
.wait_vblank_end_loop:
    ldrh r1, [r0]
    cmp r1, #160
    bge .wait_vblank_end_loop
    bx lr
.endfunc

@ ============================================================================
@ Interrupt Setup
@ ============================================================================

@ Enable specific interrupt
@ r0 = interrupt mask
.func enable_interrupt
enable_interrupt:
    push {r1, r2}

    @ Add to interrupt enable register
    ldr r1, =REG_IE
    ldrh r2, [r1]
    orr r2, r2, r0
    strh r2, [r1]

    @ Enable master interrupt
    ldr r1, =REG_IME
    mov r2, #1
    strh r2, [r1]

    pop {r1, r2}
    bx lr
.endfunc

@ Disable specific interrupt
@ r0 = interrupt mask
.func disable_interrupt
disable_interrupt:
    push {r1, r2}

    ldr r1, =REG_IE
    ldrh r2, [r1]
    bic r2, r2, r0          @ Clear interrupt bit
    strh r2, [r1]

    pop {r1, r2}
    bx lr
.endfunc

@ ============================================================================
@ DMA Utilities
@ ============================================================================

@ DMA copy (32-bit transfers)
@ r0 = source, r1 = destination, r2 = word count, r3 = DMA channel (0-3)
.func dma_copy32
dma_copy32:
    push {r4, r5}

    @ Calculate DMA register base
    mov r4, #12             @ Each DMA channel is 12 bytes
    mul r5, r3, r4
    ldr r4, =REG_DMA0SAD
    add r4, r4, r5

    @ Set source address
    str r0, [r4]

    @ Set destination address
    str r1, [r4, #4]

    @ Set count and control (32-bit, enable)
    orr r2, r2, #(DMA_32 | DMA_ON)
    strh r2, [r4, #10]

    pop {r4, r5}
    bx lr
.endfunc

@ Fast VRAM copy using DMA3
@ r0 = source, r1 = destination, r2 = word count
.func dma_vram_copy
dma_vram_copy:
    push {lr}
    mov r3, #3              @ Use DMA channel 3
    bl dma_copy32
    pop {pc}
.endfunc

@ ============================================================================
@ Default Interrupt Handlers
@ ============================================================================

.arm
.align 2

_undefined:
    b _undefined

_swi:
    bx lr

_prefetch_abort:
    b _prefetch_abort

_data_abort:
    b _data_abort

_reserved:
    b _reserved

_irq:
    @ Simple IRQ handler - acknowledge and return
    ldr r0, =REG_IF
    ldrh r1, [r0]
    strh r1, [r0]          @ Acknowledge interrupts
    bx lr

_fiq:
    b _fiq

@ ============================================================================
@ Palette Utilities
@ ============================================================================

@ Set background palette color
@ r0 = color index (0-255), r1 = RGB15 color value
.func set_bg_color
set_bg_color:
    ldr r2, =BG_PALETTE
    lsl r0, r0, #1          @ Colors are 2 bytes each
    strh r1, [r2, r0]
    bx lr
.endfunc

@ Set object palette color
@ r0 = color index (0-255), r1 = RGB15 color value
.func set_obj_color
set_obj_color:
    ldr r2, =OBJ_PALETTE
    lsl r0, r0, #1
    strh r1, [r2, r0]
    bx lr
.endfunc

@ Convert RGB components to RGB15
@ r0 = red (0-31), r1 = green (0-31), r2 = blue (0-31)
@ Returns RGB15 value in r0
.func rgb15
rgb15:
    and r0, r0, #31         @ Mask red
    and r1, r1, #31         @ Mask green
    and r2, r2, #31         @ Mask blue
    lsl r1, r1, #5          @ Shift green
    lsl r2, r2, #10         @ Shift blue
    orr r0, r0, r1
    orr r0, r0, r2
    bx lr
.endfunc