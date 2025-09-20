; hello_world.asm - Minimal C64 Hello World
; Shows proper use of system resources
; Build: acme -o hello.prg hello_world.asm

!source "../includes/c64.inc"      ; System constants
!source "../libs/startup.inc"      ; BASIC stub macro

        +basic_startup_compact     ; 10 SYS 2061

        ; Code starts at $080D (no wasted bytes!)
start:
        ; Set border to green
        lda #COLOR_GREEN
        sta VIC_BORDER

        ; Print message using KERNAL
        ldx #0
.loop:  lda message,x
        beq .done
        jsr KERNAL_CHROUT
        inx
        bne .loop

.done:  rts                         ; Back to BASIC

message:
        !scr "HELLO WORLD!"
        !byte 13                    ; Carriage return
        !byte 0                     ; String terminator