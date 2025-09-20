; rom_header.inc - Sega Genesis/Mega Drive ROM header
; Creates proper Sega Genesis cartridge header

; Genesis ROM header structure
GENESIS_HEADER MACRO title, serial, checksum, rom_size
    ; Vector table (first 256 bytes)
    dc.l    RAM_END         ; Initial stack pointer ($000000)
    dc.l    main            ; Reset vector ($000004)
    dc.l    bus_error       ; Bus error ($000008)
    dc.l    address_error   ; Address error ($00000C)
    dc.l    illegal_inst    ; Illegal instruction ($000010)
    dc.l    divide_zero     ; Division by zero ($000014)
    dc.l    chk_inst        ; CHK instruction ($000018)
    dc.l    trapv_inst      ; TRAPV instruction ($00001C)
    dc.l    privilege_viol  ; Privilege violation ($000020)
    dc.l    trace_except    ; Trace exception ($000024)
    dc.l    line_a_emu      ; Line A emulator ($000028)
    dc.l    line_f_emu      ; Line F emulator ($00002C)
    ds.l    3               ; Reserved ($000030-$00003B)
    dc.l    unint_int       ; Uninitialized interrupt ($00003C)
    ds.l    8               ; Reserved ($000040-$00005F)
    dc.l    spurious_int    ; Spurious interrupt ($000060)
    dc.l    irq1            ; IRQ level 1 ($000064)
    dc.l    irq2            ; IRQ level 2 - external ($000068)
    dc.l    irq3            ; IRQ level 3 ($00006C)
    dc.l    irq4            ; IRQ level 4 - horizontal blank ($000070)
    dc.l    irq5            ; IRQ level 5 ($000074)
    dc.l    irq6            ; IRQ level 6 - vertical blank ($000078)
    dc.l    irq7            ; IRQ level 7 ($00007C)
    ds.l    32              ; User vectors ($000080-$0000FF)

    ; Sega header starts at $100
    dc.b    'SEGA MEGA DRIVE '  ; Console name ($000100-$00010F)

    ; Copyright and build date ($000110-$00011F)
    dc.b    '(C)HOMEBREW2025'   ; Copyright

    ; Domestic title ($000120-$00014F) - 48 characters
    LOCAL title_len
title_len = len('\title\')
    IF title_len > 48
        FAIL "Title too long (max 48 characters)"
    ENDIF

    dc.b    '\title\'
    REPT 48 - title_len
        dc.b    ' '
    ENDR

    ; International title ($000150-$00017F) - same as domestic
    dc.b    '\title\'
    REPT 48 - title_len
        dc.b    ' '
    ENDR

    ; Serial number ($000180-$00018D)
    dc.b    'GM '               ; Game type
    dc.b    '\serial\'          ; Serial number (8 chars)
    dc.w    0000                ; Version

    ; Checksum ($00018E-$00018F)
    dc.w    \checksum\

    ; Device support ($000190-$00019F)
    dc.b    'J               '  ; I/O device support

    ; ROM info ($0001A0-$0001AF)
    dc.l    ROM_START           ; ROM start address
    dc.l    \rom_size\          ; ROM end address

    ; RAM info ($0001B0-$0001B7)
    dc.l    RAM_START           ; RAM start address
    dc.l    RAM_END             ; RAM end address

    ; SRAM info ($0001B8-$0001C7)
    dc.b    '            '      ; No SRAM by default

    ; Notes ($0001C8-$0001F1)
    dc.b    '                              '  ; 42 spaces

    ; Country codes ($0001F0-$0001FF)
    dc.b    'JUE             '  ; Japan, USA, Europe
ENDM

; Simple header macro for basic homebrew
SIMPLE_GENESIS_HEADER MACRO title
    GENESIS_HEADER \title\, 'HOMEBREW', $0000, ROM_END
ENDM

; Default exception handlers (can be overridden)
bus_error:
    rte

address_error:
    rte

illegal_inst:
    rte

divide_zero:
    rte

chk_inst:
    rte

trapv_inst:
    rte

privilege_viol:
    rte

trace_except:
    rte

line_a_emu:
    rte

line_f_emu:
    rte

unint_int:
    rte

spurious_int:
    rte

irq1:
    rte

irq2:
    rte

irq3:
    rte

; Horizontal interrupt (commonly used)
irq4:
    rte

irq5:
    rte

; Vertical interrupt (commonly used)
irq6:
    rte

irq7:
    rte

; Macro to enable horizontal interrupts
ENABLE_HINT MACRO line_count
    move.b  #\line_count\, d0
    move.w  #(VDP_R10+$100), VDP_CTRL  ; Set H-interrupt counter
    move.b  d0, VDP_DATA

    ; Enable H-interrupt in mode register 1
    move.w  #VDP_R0, VDP_CTRL
    move.w  #(M1_DISPLAY_ON+M1_VINT_ON+M1_DMA_ON), VDP_DATA
ENDM

; Macro to enable vertical interrupts
ENABLE_VINT MACRO
    ; Enable V-interrupt in mode register 2
    move.w  #VDP_R1, VDP_CTRL
    move.w  #(M2_DISPLAY_ON+M2_VINT_ON+M2_DMA_ON), VDP_DATA
ENDM