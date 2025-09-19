# Workflow Architecture Comparison

## Current Architecture (Sequential)

```mermaid
graph TD
    Start([Push/PR]) --> Base[Build ALL Base Images]
    Base --> Wait1[⏳ Wait for all bases]
    Wait1 --> Systems[Build ALL System Images]
    Systems --> Wait2[⏳ Wait for all systems]
    Wait2 --> Verify[Verify All]
    Verify --> End([Complete])

    style Wait1 fill:#f99
    style Wait2 fill:#f99
```

**Problems:**
- C64 has to wait for 68000-base to build (no dependency)
- All systems build sequentially even though they don't depend on each other
- Total time: Sum of ALL build times

## Proposed Architecture (Parallel by Family)

```mermaid
graph TD
    Start([Push/PR]) --> Root[Build code198x-base]

    Root --> P6502[Build 6502-base]
    Root --> PZ80[Build z80-base]
    Root --> P68K[Build 68000-base]

    P6502 --> C64[Build C64]
    P6502 --> NES[Build NES]

    PZ80 --> ZX[Build Spectrum]

    P68K --> Amiga[Build Amiga]

    C64 --> Summary
    NES --> Summary
    ZX --> Summary
    Amiga --> Summary

    Summary --> End([Complete])

    style P6502 fill:#9f9
    style PZ80 fill:#9f9
    style P68K fill:#9f9
```

**Benefits:**
- Each processor family builds independently
- C64/NES don't wait for 68000 or Z80
- Total time: Max of family build times (not sum)
- Easy to add new systems to existing families

## Implementation Options

### Option 1: Simple Parallel (docker-build-optimized.yml)
- ✅ All logic in one file
- ✅ Easy to understand
- ❌ Lots of duplication
- ❌ Hard to maintain as systems grow

### Option 2: Reusable Workflows (docker-build-parallel.yml + build-processor-family.yml)
- ✅ DRY - no duplication
- ✅ Easy to add new systems
- ✅ Each family can have custom build logic
- ❌ More complex with multiple files

### Option 3: Hybrid with Matrix Strategy
```yaml
strategy:
  matrix:
    include:
      - processor: 6502
        systems: [commodore-64, nintendo-entertainment-system]
      - processor: z80
        systems: [sinclair-zx-spectrum]
      - processor: 68000
        systems: [commodore-amiga]
```
- ✅ Compact configuration
- ✅ Single workflow file
- ❌ Less flexible for family-specific logic

## Performance Comparison

| Scenario | Current (Sequential) | Proposed (Parallel) | Improvement |
|----------|---------------------|--------------------|--------------|
| All systems build | 45-60 min | 15-20 min | 3x faster |
| Single family change | 45-60 min | 5-10 min | 6x faster |
| Add new system | Slows everything | Only affects one family | Scalable |

## Recommendation

Use **Option 2 (Reusable Workflows)** because:
1. **Scalability**: Easy to add systems without touching other families
2. **Maintainability**: Changes to build logic only need updating in one place
3. **Flexibility**: Each processor family can have custom test commands
4. **Performance**: Maximum parallelization within GitHub Actions limits
5. **Future-proof**: Ready for 64+ systems without workflow explosion

## Migration Path

1. Keep existing workflow as fallback
2. Deploy parallel workflow alongside
3. Test with manual triggers
4. Switch default after validation
5. Remove old workflow after 1-2 weeks

## Adding New Systems

With the parallel architecture, adding a new system is simple:

```yaml
# For a new 6502 system (e.g., Apple II)
build-6502-family:
  uses: ./.github/workflows/build-processor-family.yml
  with:
    processor: '6502'
    systems: '["commodore-64", "nintendo-entertainment-system", "apple-ii"]'

# For a new processor family (e.g., 8080)
build-8080-family:
  uses: ./.github/workflows/build-processor-family.yml
  with:
    processor: '8080'
    systems: '["altair-8800", "imsai-8080"]'
```

The new system builds in parallel with its processor siblings, not blocking other families.