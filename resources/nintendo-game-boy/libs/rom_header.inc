; rom_header.inc - Game Boy ROM header creation
; Creates proper cartridge header with Nintendo logo and checksums

; Game Boy cartridge header structure (at $0100-$014F)
HEADER_START MACRO title, cart_type, rom_size, ram_size
    ; Entry point (4 bytes at $0100)
    nop
    jp main

    ; Nintendo logo (48 bytes at $0104) - REQUIRED!
    ; This logo MUST be exactly correct or the Game Boy won't boot
    db $CE,$ED,$66,$66,$CC,$0D,$00,$0B,$03,$73,$00,$83,$00,$0C,$00,$0D
    db $00,$08,$11,$1F,$88,$89,$00,$0E,$DC,$CC,$6E,$E6,$DD,$DD,$D9,$99
    db $BB,$BB,$67,$63,$6E,$0E,$EC,$CC,$DD,$DC,$99,$9F,$BB,$B9,$33,$3E

    ; Game title (11 bytes at $0134, pad with zeros)
    LOCAL title_len
title_len = strlen("{title}")
    IF title_len > 11
        fail "Title too long (max 11 characters)"
    ENDIF

    db "{title}"
    REPT 11 - title_len
        db 0
    ENDR

    ; Manufacturer code (4 bytes at $013F, usually zeros)
    db 0, 0, 0, 0

    ; CGB flag (1 byte at $0143)
    db $00          ; $00 = DMG only, $80 = CGB compatible, $C0 = CGB only

    ; New licensee code (2 bytes at $0144)
    db $00, $00     ; Use old licensee code instead

    ; SGB flag (1 byte at $0146)
    db $00          ; $00 = No SGB, $03 = SGB support

    ; Cartridge type (1 byte at $0147)
    db cart_type

    ; ROM size (1 byte at $0148)
    db rom_size

    ; RAM size (1 byte at $0149)
    db ram_size

    ; Destination code (1 byte at $014A)
    db $01          ; $00 = Japan, $01 = Non-Japan

    ; Old licensee code (1 byte at $014B)
    db $33          ; Use new licensee code

    ; ROM version (1 byte at $014C)
    db $00

    ; Header checksum (1 byte at $014D) - calculated by assembler
    LOCAL checksum
    checksum = 0
    ; Calculate checksum of $0134-$014C
    ; This will be patched by build tools
    db $00

    ; Global checksum (2 bytes at $014E) - usually not checked
    dw $0000
ENDM

; Cartridge type constants
CART_ROM_ONLY           EQU $00
CART_MBC1               EQU $01
CART_MBC1_RAM           EQU $02
CART_MBC1_RAM_BATTERY   EQU $03
CART_MBC2               EQU $05
CART_MBC2_BATTERY       EQU $06
CART_ROM_RAM            EQU $08
CART_ROM_RAM_BATTERY    EQU $09
CART_MBC3_TIMER_BATTERY EQU $0F
CART_MBC3_TIMER_RAM_BAT EQU $10
CART_MBC3               EQU $11
CART_MBC3_RAM           EQU $12
CART_MBC3_RAM_BATTERY   EQU $13
CART_MBC5               EQU $19
CART_MBC5_RAM           EQU $1A
CART_MBC5_RAM_BATTERY   EQU $1B
CART_MBC5_RUMBLE        EQU $1C
CART_MBC5_RUMBLE_RAM    EQU $1D
CART_MBC5_RUMBLE_RAM_BAT EQU $1E

; ROM size constants (actual size = 32KB << value)
ROM_32KB                EQU $00  ; 32KB (2 banks)
ROM_64KB                EQU $01  ; 64KB (4 banks)
ROM_128KB               EQU $02  ; 128KB (8 banks)
ROM_256KB               EQU $03  ; 256KB (16 banks)
ROM_512KB               EQU $04  ; 512KB (32 banks)
ROM_1MB                 EQU $05  ; 1MB (64 banks)
ROM_2MB                 EQU $06  ; 2MB (128 banks)
ROM_4MB                 EQU $07  ; 4MB (256 banks)
ROM_8MB                 EQU $08  ; 8MB (512 banks)

; RAM size constants
RAM_NONE                EQU $00  ; No RAM
RAM_2KB                 EQU $01  ; 2KB
RAM_8KB                 EQU $02  ; 8KB (1 bank)
RAM_32KB                EQU $03  ; 32KB (4 banks)
RAM_128KB               EQU $04  ; 128KB (16 banks)
RAM_64KB                EQU $05  ; 64KB (8 banks)

; Simple header macro for basic ROMs
SIMPLE_HEADER MACRO title
    HEADER_START title, CART_ROM_ONLY, ROM_32KB, RAM_NONE
ENDM

; Header for MBC1 cartridge with save RAM
MBC1_HEADER MACRO title, rom_size
    HEADER_START title, CART_MBC1_RAM_BATTERY, rom_size, RAM_8KB
ENDM

; Header for MBC3 cartridge with RTC and save RAM
MBC3_RTC_HEADER MACRO title, rom_size
    HEADER_START title, CART_MBC3_TIMER_RAM_BAT, rom_size, RAM_32KB
ENDM

; Header for MBC5 cartridge (large ROMs)
MBC5_HEADER MACRO title, rom_size, ram_size
    HEADER_START title, CART_MBC5_RAM_BATTERY, rom_size, ram_size
ENDM