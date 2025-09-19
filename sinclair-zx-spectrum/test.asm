; Test program for sjasmplus assembler
; Simple ZX Spectrum program that changes border color

    ORG 32768       ; Standard user program start

start:
    LD A, 2         ; Load red border color
    OUT (254), A    ; Output to border register
    
    LD A, 4         ; Load green border color  
    OUT (254), A    ; Output to border register
    
    RET             ; Return to BASIC

    SAVESNA "test.sna", start   ; Save as snapshot
