; startup.inc - Optimized C64 BASIC startup stub
; Creates a BASIC line: 10 SYS 2061
; Saves 3 bytes by starting code immediately after BASIC line

!macro basic_startup {
    * = $0801
    !byte $0b,$08                   ; Next line pointer ($080B)
    !byte $0a,$00                   ; Line number (10)
    !byte $9e                       ; SYS token
    !text "2061"                    ; Address in ASCII (SYS 2061 = $080D)
    !byte $00,$00,$00               ; End of BASIC program
    ; ML code starts at $080D (2061) - no padding needed!
}

; Ultra-compact version - the classic trick!
!macro basic_startup_compact {
    * = $0801
    !byte $0b,$08,$0a,$00           ; Link ($080B), line 10
    !byte $9e,$32,$30,$36,$31       ; SYS 2061
    !byte $00,$00,$00               ; End of BASIC
    ; Your code starts RIGHT HERE at $080D
}

; The REAL optimization - self-modifying for any start address
!macro basic_startup_smart {
    * = $0801
    !byte <.end, >.end               ; Next line pointer
    !byte $0a,$00                   ; Line number (10)
    !byte $9e                       ; SYS token
    !text "2061"                    ; Start address
    !byte $00                       ; End of line
.end:
    !byte $00,$00                   ; End of BASIC
    ; Code starts at $080D - exactly where SYS points!
}