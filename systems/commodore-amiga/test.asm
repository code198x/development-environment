; Test program for VASM assembler
; Simple Amiga program using OS calls

    SECTION code,CODE

start:
    ; Open DOS library
    move.l  #39,d0          ; Version 39
    lea     dosname,a1      ; Library name
    move.l  4.w,a6          ; ExecBase
    jsr     -552(a6)        ; OpenLibrary
    
    ; Exit cleanly
    moveq   #0,d0           ; Return code 0
    move.l  4.w,a6          ; ExecBase  
    jsr     -146(a6)        ; CloseLibrary
    rts

    SECTION data,DATA
dosname:
    dc.b    "dos.library",0
