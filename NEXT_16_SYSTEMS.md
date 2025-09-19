# Next 16 Systems - New Processor Families

## Current Coverage (16 systems)
- **6502**: 8 systems
- **Z80**: 5 systems
- **68000**: 3 systems

## Proposed Next 16 Systems

### 1. Intel 8080/8085 Family (3 systems)
**Base Image**: `8080-base`
**Assembler**: asm8080, z80asm (8080 mode)

Systems:
- `altair-8800` (1975) - The computer that started the PC revolution
- `imsai-8080` (1975) - Featured in WarGames movie
- `intel-sdk-85` (1977) - Intel's own development system

### 2. Motorola 6809 Family (3 systems)
**Base Image**: `6809-base`
**Assembler**: asm6809, lwasm

Systems:
- `tandy-coco` (1980) - TRS-80 Color Computer
- `dragon-32` (1982) - UK's answer to the CoCo
- `vectrex` (1982) - Unique vector graphics console

### 3. Intel x86 Family (3 systems)
**Base Image**: `x86-base`
**Assembler**: NASM, MASM compatible

Systems:
- `ibm-pc` (1981) - The original IBM PC (8088)
- `tandy-1000` (1984) - Popular PC clone
- `ibm-pc-at` (1984) - 80286-based AT

### 4. TMS9900 Family (2 systems)
**Base Image**: `tms9900-base`
**Assembler**: xas99

Systems:
- `ti-99-4a` (1981) - Texas Instruments home computer
- `geneve-9640` (1987) - TI-99/4A successor

### 5. MOS 6510 Family (2 systems)
**Base Image**: Use existing `6502-base` (6510 is 6502 variant)

Systems:
- `commodore-128` (1985) - C64's big brother
- `commodore-plus4` (1984) - The business-oriented Commodore

### 6. ARM Family (2 systems)
**Base Image**: `arm-base`
**Assembler**: GNU ARM assembler, FASMARM

Systems:
- `acorn-archimedes` (1987) - First ARM-based computer
- `acorn-risc-pc` (1994) - Later ARM system

### 7. WDC 65C816 Family (1 system)
**Base Image**: `65816-base` or extend `6502-base`
**Assembler**: ca65 (with 65816 support)

Systems:
- `apple-iigs` (1986) - 16-bit Apple II

## Directory Structure
```
base-images/
├── 8080-base/       # New
├── 6809-base/       # New
├── x86-base/        # New
├── tms9900-base/    # New
├── arm-base/        # New
├── 65816-base/      # New (or extend 6502-base)
└── [existing bases]

systems/
├── altair-8800/
├── imsai-8080/
├── intel-sdk-85/
├── tandy-coco/
├── dragon-32/
├── vectrex/
├── ibm-pc/
├── tandy-1000/
├── ibm-pc-at/
├── ti-99-4a/
├── geneve-9640/
├── commodore-128/
├── commodore-plus4/
├── acorn-archimedes/
├── acorn-risc-pc/
├── apple-iigs/
└── [existing systems]
```

## Workflow Impact

With 32 total systems across 9 processor families:
- **Total Jobs**: 36 (1 root + 9 processor bases + 26 systems)
- **Max Parallelism**: Would exceed GitHub's free tier limit (20 jobs)
- **Solution**: May need to implement waves or use matrix strategy

## Alternative Systems to Consider

If we want to stay within existing processor families:
- **More 6502**: Oric-1, Acorn Atom, Commodore PET
- **More Z80**: TRS-80, Sinclair ZX81, Sam Coupé
- **More 68000**: Sinclair QL, Macintosh 128K, Sega Genesis

## Assembler Considerations

New assemblers needed:
1. **asm8080**: For 8080/8085
2. **lwasm**: For 6809
3. **NASM**: For x86
4. **xas99**: For TMS9900
5. **FASMARM**: For ARM

## Build Complexity

Each new processor family requires:
1. Research and find reliable assembler sources
2. Create base image with assembler
3. Test with simple programs
4. Add to CI/CD pipeline
5. Document assembly syntax differences

## Recommended Approach

**Phase 1**: Add systems using existing bases (6502, Z80, 68000)
- Faster to implement
- Tests scaling without new dependencies
- Proves 32-system viability

**Phase 2**: Add 2-3 new processor families
- Start with 8080 and 6809 (similar to existing)
- Well-documented assemblers available
- Good community support

**Phase 3**: Add exotic architectures
- TMS9900, ARM, etc.
- More complex build processes
- May need custom toolchains