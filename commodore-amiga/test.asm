; Simple Amiga test program
; Tests that vasm assembler is working correctly

    section code,code

start:
    ; Get custom chip base
    lea     $dff000,a6

    ; Set background to purple
    move.w  #$0808,$180(a6)     ; COLOR00 = purple

    ; Simple copper list
    lea     copper_list,a0
    move.l  a0,$80(a6)          ; COP1LC
    move.w  #0,$88(a6)          ; COPJMP1

    ; Wait for left mouse button
wait_loop:
    btst    #6,$bfe001          ; Check left mouse button
    bne.s   wait_loop

    ; Restore system
    rts

copper_list:
    dc.w    $2c01,$fffe         ; Wait for line 44
    dc.w    $0180,$0f0f         ; COLOR00 = pink
    dc.w    $6c01,$fffe         ; Wait for line 108
    dc.w    $0180,$00ff         ; COLOR00 = blue
    dc.w    $ac01,$fffe         ; Wait for line 172
    dc.w    $0180,$0ff0         ; COLOR00 = yellow
    dc.w    $ffff,$fffe         ; End of copper list

    end