; ines_header.inc - Standard iNES ROM header for NES cartridges
; This header tells emulators how to load and run the ROM

; Standard iNES header (16 bytes)
; Must be at the very beginning of the ROM file

.macro ines_header prg_banks, chr_banks, mapper, mirroring
    .byte "NES", $1A        ; iNES signature
    .byte prg_banks         ; Number of 16KB PRG-ROM banks
    .byte chr_banks         ; Number of 8KB CHR-ROM banks
    .byte (mirroring | (mapper << 4))  ; Flags 6
    .byte (mapper & $F0)    ; Flags 7 (upper nibble of mapper)
    .byte 0                 ; Flags 8 (PRG-RAM size, usually 0)
    .byte 0                 ; Flags 9 (TV system, 0=NTSC)
    .byte 0                 ; Flags 10 (unused)
    .byte 0,0,0,0,0        ; Padding (unused)
.endmacro

; Mirroring types
MIRROR_HORIZONTAL = 0
MIRROR_VERTICAL   = 1
MIRROR_FOUR_SCREEN = 8

; Common mappers
MAPPER_NROM     = 0   ; No mapper (32KB PRG + 8KB CHR max)
MAPPER_MMC1     = 1   ; Nintendo MMC1
MAPPER_UNROM    = 2   ; UxROM (common for larger games)
MAPPER_CNROM    = 3   ; CNROM (bankswitch CHR)
MAPPER_MMC3     = 4   ; Nintendo MMC3 (most common)

; Common configurations
.macro ines_header_simple
    ines_header 2, 1, MAPPER_NROM, MIRROR_VERTICAL
.endmacro

.macro ines_header_32k_8k
    ines_header 2, 1, MAPPER_NROM, MIRROR_HORIZONTAL
.endmacro

.macro ines_header_mmc1
    ines_header 8, 0, MAPPER_MMC1, MIRROR_HORIZONTAL
.endmacro

.macro ines_header_mmc3
    ines_header 16, 16, MAPPER_MMC3, MIRROR_VERTICAL
.endmacro