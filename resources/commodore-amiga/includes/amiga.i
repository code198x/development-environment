; amiga.i - Amiga Hardware Registers and System Definitions
; For use with vasm or other 68000 assemblers
; Based on the Amiga Native Development Kit (NDK)

; ============================================================================
; Custom Chip Registers (Agnus, Denise, Paula) - $DFF000
; ============================================================================

CUSTOM          EQU $DFF000

; Blitter registers
BLTDDAT         EQU $000   ; Blitter dest data
DMACONR         EQU $002   ; DMA control (read)
VPOSR           EQU $004   ; Vert position (read)
VHPOSR          EQU $006   ; Vert/Horiz position
DSKDATR         EQU $008   ; Disk data (read)
JOY0DAT         EQU $00A   ; Joystick 0 data
JOY1DAT         EQU $00C   ; Joystick 1 data
CLXDAT          EQU $00E   ; Collision data

; Audio registers (Paula)
ADKCONR         EQU $010   ; Audio/Disk control (read)
POT0DAT         EQU $012   ; Pot 0 data
POT1DAT         EQU $014   ; Pot 1 data
POTINP          EQU $016   ; Pot pin data
SERDATR         EQU $018   ; Serial data (read)
DSKBYTR         EQU $01A   ; Disk byte (read)
INTENAR         EQU $01C   ; Interrupt enable (read)
INTREQR         EQU $01E   ; Interrupt request (read)

; Copper/Display
DSKPTH          EQU $020   ; Disk pointer (high)
DSKPTL          EQU $022   ; Disk pointer (low)
DSKLEN          EQU $024   ; Disk length
DSKDAT          EQU $026   ; Disk data (write)
REFPTR          EQU $028   ; Refresh pointer
VPOSW           EQU $02A   ; Vert position (write)
VHPOSW          EQU $02C   ; V/H position (write)
COPCON          EQU $02E   ; Copper control
SERDAT          EQU $030   ; Serial data (write)
SERPER          EQU $032   ; Serial period
POTGO           EQU $034   ; Pot control
JOYTEST         EQU $036   ; Joystick test
STREQU          EQU $038   ; Strobe equalization
STRVBL          EQU $03A   ; Strobe vertical blank
STRHOR          EQU $03C   ; Strobe horizontal
STRLONG         EQU $03E   ; Strobe long

; Blitter registers
BLTCON0         EQU $040   ; Blitter control 0
BLTCON1         EQU $042   ; Blitter control 1
BLTAFWM         EQU $044   ; Blitter A first word mask
BLTALWM         EQU $046   ; Blitter A last word mask
BLTCPTH         EQU $048   ; Blitter C pointer (high)
BLTCPTL         EQU $04A   ; Blitter C pointer (low)
BLTBPTH         EQU $04C   ; Blitter B pointer (high)
BLTBPTL         EQU $04E   ; Blitter B pointer (low)
BLTAPTH         EQU $050   ; Blitter A pointer (high)
BLTAPTL         EQU $052   ; Blitter A pointer (low)
BLTDPTH         EQU $054   ; Blitter D pointer (high)
BLTDPTL         EQU $056   ; Blitter D pointer (low)
BLTSIZE         EQU $058   ; Blitter size
BLTCMOD         EQU $060   ; Blitter C modulo
BLTBMOD         EQU $062   ; Blitter B modulo
BLTAMOD         EQU $064   ; Blitter A modulo
BLTDMOD         EQU $066   ; Blitter D modulo
BLTCDAT         EQU $070   ; Blitter C data
BLTBDAT         EQU $072   ; Blitter B data
BLTADAT         EQU $074   ; Blitter A data

; Copper registers
COP1LCH         EQU $080   ; Copper 1 location (high)
COP1LCL         EQU $082   ; Copper 1 location (low)
COP2LCH         EQU $084   ; Copper 2 location (high)
COP2LCL         EQU $086   ; Copper 2 location (low)
COPJMP1         EQU $088   ; Copper jump 1
COPJMP2         EQU $08A   ; Copper jump 2
COPINS          EQU $08C   ; Copper instruction
DIWSTRT         EQU $08E   ; Display window start
DIWSTOP         EQU $090   ; Display window stop
DDFSTRT         EQU $092   ; Display data fetch start
DDFSTOP         EQU $094   ; Display data fetch stop
DMACON          EQU $096   ; DMA control (write)
CLXCON          EQU $098   ; Collision control
INTENA          EQU $09A   ; Interrupt enable (write)
INTREQ          EQU $09C   ; Interrupt request (write)
ADKCON          EQU $09E   ; Audio/Disk control

; Audio channels
AUD0LCH         EQU $0A0   ; Audio 0 location (high)
AUD0LCL         EQU $0A2   ; Audio 0 location (low)
AUD0LEN         EQU $0A4   ; Audio 0 length
AUD0PER         EQU $0A6   ; Audio 0 period
AUD0VOL         EQU $0A8   ; Audio 0 volume
AUD0DAT         EQU $0AA   ; Audio 0 data

AUD1LCH         EQU $0B0   ; Audio 1 location (high)
AUD1LCL         EQU $0B2   ; Audio 1 location (low)
AUD1LEN         EQU $0B4   ; Audio 1 length
AUD1PER         EQU $0B6   ; Audio 1 period
AUD1VOL         EQU $0B8   ; Audio 1 volume
AUD1DAT         EQU $0BA   ; Audio 1 data

AUD2LCH         EQU $0C0   ; Audio 2 location (high)
AUD2LCL         EQU $0C2   ; Audio 2 location (low)
AUD2LEN         EQU $0C4   ; Audio 2 length
AUD2PER         EQU $0C6   ; Audio 2 period
AUD2VOL         EQU $0C8   ; Audio 2 volume
AUD2DAT         EQU $0CA   ; Audio 2 data

AUD3LCH         EQU $0D0   ; Audio 3 location (high)
AUD3LCL         EQU $0D2   ; Audio 3 location (low)
AUD3LEN         EQU $0D4   ; Audio 3 length
AUD3PER         EQU $0D6   ; Audio 3 period
AUD3VOL         EQU $0D8   ; Audio 3 volume
AUD3DAT         EQU $0DA   ; Audio 3 data

; Bitplane pointers
BPL1PTH         EQU $0E0   ; Bitplane 1 pointer (high)
BPL1PTL         EQU $0E2   ; Bitplane 1 pointer (low)
BPL2PTH         EQU $0E4   ; Bitplane 2 pointer (high)
BPL2PTL         EQU $0E6   ; Bitplane 2 pointer (low)
BPL3PTH         EQU $0E8   ; Bitplane 3 pointer (high)
BPL3PTL         EQU $0EA   ; Bitplane 3 pointer (low)
BPL4PTH         EQU $0EC   ; Bitplane 4 pointer (high)
BPL4PTL         EQU $0EE   ; Bitplane 4 pointer (low)
BPL5PTH         EQU $0F0   ; Bitplane 5 pointer (high)
BPL5PTL         EQU $0F2   ; Bitplane 5 pointer (low)
BPL6PTH         EQU $0F4   ; Bitplane 6 pointer (high)
BPL6PTL         EQU $0F6   ; Bitplane 6 pointer (low)

; Display control
BPLCON0         EQU $100   ; Bitplane control 0
BPLCON1         EQU $102   ; Bitplane control 1
BPLCON2         EQU $104   ; Bitplane control 2
BPLCON3         EQU $106   ; Bitplane control 3 (AGA)
BPL1MOD         EQU $108   ; Bitplane 1 modulo (odd)
BPL2MOD         EQU $10A   ; Bitplane 2 modulo (even)

; Sprites
SPR0PTH         EQU $120   ; Sprite 0 pointer (high)
SPR0PTL         EQU $122   ; Sprite 0 pointer (low)
SPR1PTH         EQU $124   ; Sprite 1 pointer (high)
SPR1PTL         EQU $126   ; Sprite 1 pointer (low)
SPR2PTH         EQU $128   ; Sprite 2 pointer (high)
SPR2PTL         EQU $12A   ; Sprite 2 pointer (low)
SPR3PTH         EQU $12C   ; Sprite 3 pointer (high)
SPR3PTL         EQU $12E   ; Sprite 3 pointer (low)
SPR4PTH         EQU $130   ; Sprite 4 pointer (high)
SPR4PTL         EQU $132   ; Sprite 4 pointer (low)
SPR5PTH         EQU $134   ; Sprite 5 pointer (high)
SPR5PTL         EQU $136   ; Sprite 5 pointer (low)
SPR6PTH         EQU $138   ; Sprite 6 pointer (high)
SPR6PTL         EQU $13A   ; Sprite 6 pointer (low)
SPR7PTH         EQU $13C   ; Sprite 7 pointer (high)
SPR7PTL         EQU $13E   ; Sprite 7 pointer (low)

; Sprite positions and control
SPR0POS         EQU $140   ; Sprite 0 position
SPR0CTL         EQU $142   ; Sprite 0 control
SPR0DATA        EQU $144   ; Sprite 0 data A
SPR0DATB        EQU $146   ; Sprite 0 data B

; Color registers
COLOR00         EQU $180   ; Color 0 (background)
COLOR01         EQU $182   ; Color 1
COLOR02         EQU $184   ; Color 2
COLOR03         EQU $186   ; Color 3
COLOR04         EQU $188   ; Color 4
COLOR05         EQU $18A   ; Color 5
COLOR06         EQU $18C   ; Color 6
COLOR07         EQU $18E   ; Color 7
COLOR08         EQU $190   ; Color 8
COLOR09         EQU $192   ; Color 9
COLOR10         EQU $194   ; Color 10
COLOR11         EQU $196   ; Color 11
COLOR12         EQU $198   ; Color 12
COLOR13         EQU $19A   ; Color 13
COLOR14         EQU $19C   ; Color 14
COLOR15         EQU $19E   ; Color 15
COLOR16         EQU $1A0   ; Color 16
COLOR17         EQU $1A2   ; Color 17 (sprite 0/1)
COLOR18         EQU $1A4   ; Color 18 (sprite 0/1)
COLOR19         EQU $1A6   ; Color 19 (sprite 0/1)
COLOR20         EQU $1A8   ; Color 20 (sprite 2/3)
COLOR21         EQU $1AA   ; Color 21 (sprite 2/3)
COLOR22         EQU $1AC   ; Color 22 (sprite 2/3)
COLOR23         EQU $1AE   ; Color 23 (sprite 2/3)
COLOR24         EQU $1B0   ; Color 24 (sprite 4/5)
COLOR25         EQU $1B2   ; Color 25 (sprite 4/5)
COLOR26         EQU $1B4   ; Color 26 (sprite 4/5)
COLOR27         EQU $1B6   ; Color 27 (sprite 4/5)
COLOR28         EQU $1B8   ; Color 28 (sprite 6/7)
COLOR29         EQU $1BA   ; Color 29 (sprite 6/7)
COLOR30         EQU $1BC   ; Color 30 (sprite 6/7)
COLOR31         EQU $1BE   ; Color 31 (sprite 6/7)

; ============================================================================
; CIA Registers - $BFE001 (CIA-A) and $BFD000 (CIA-B)
; ============================================================================

CIAA            EQU $BFE001
CIAB            EQU $BFD000

; CIA offsets
CIAPRA          EQU $0000   ; Port A data
CIAPRB          EQU $0100   ; Port B data
CIADDRA         EQU $0200   ; Port A direction
CIADDRB         EQU $0300   ; Port B direction
CIATALO         EQU $0400   ; Timer A low
CIATAHI         EQU $0500   ; Timer A high
CIATBLO         EQU $0600   ; Timer B low
CIATBHI         EQU $0700   ; Timer B high
CIATODLO        EQU $0800   ; TOD low
CIATODMID       EQU $0900   ; TOD mid
CIATODHI        EQU $0A00   ; TOD high
CIASDR          EQU $0C00   ; Serial data
CIAICR          EQU $0D00   ; Interrupt control
CIACRA          EQU $0E00   ; Control A
CIACRB          EQU $0F00   ; Control B

; ============================================================================
; DMA Control Bits
; ============================================================================

DMAF_SETCLR     EQU $8000   ; Set/Clear bit
DMAF_MASTER     EQU $0200   ; Master DMA enable
DMAF_COPPER     EQU $0080   ; Copper DMA
DMAF_BLITTER    EQU $0040   ; Blitter DMA
DMAF_SPRITE     EQU $0020   ; Sprite DMA
DMAF_DISK       EQU $0010   ; Disk DMA
DMAF_AUD3       EQU $0008   ; Audio 3 DMA
DMAF_AUD2       EQU $0004   ; Audio 2 DMA
DMAF_AUD1       EQU $0002   ; Audio 1 DMA
DMAF_AUD0       EQU $0001   ; Audio 0 DMA
DMAF_AUDIO      EQU $000F   ; All audio DMA
DMAF_ALL        EQU $03FF   ; All DMA channels

; ============================================================================
; Interrupt Bits
; ============================================================================

INTF_SETCLR     EQU $8000   ; Set/Clear bit
INTF_INTEN      EQU $4000   ; Master interrupt enable
INTF_EXTER      EQU $2000   ; External interrupt
INTF_DSKSYNC    EQU $1000   ; Disk sync
INTF_RBF        EQU $0800   ; Serial receive buffer full
INTF_AUD3       EQU $0400   ; Audio 3
INTF_AUD2       EQU $0200   ; Audio 2
INTF_AUD1       EQU $0100   ; Audio 1
INTF_AUD0       EQU $0080   ; Audio 0
INTF_BLIT       EQU $0040   ; Blitter finished
INTF_VERTB      EQU $0020   ; Vertical blank
INTF_COPER      EQU $0010   ; Copper
INTF_PORTS      EQU $0008   ; I/O ports
INTF_SOFTINT    EQU $0004   ; Software interrupt
INTF_DSKBLK     EQU $0002   ; Disk block done
INTF_TBE        EQU $0001   ; Serial transmit buffer empty

; ============================================================================
; Exec Library Base
; ============================================================================

EXECBASE        EQU 4       ; Exec library base pointer

; Important exec offsets (negative from base)
Supervisor      EQU -30
Forbid          EQU -132
Permit          EQU -138
AllocMem        EQU -198
FreeMem         EQU -210
WaitTOF         EQU -270
OpenLibrary     EQU -552
CloseLibrary    EQU -414

; Memory allocation flags
MEMF_ANY        EQU 0
MEMF_PUBLIC     EQU $0001
MEMF_CHIP       EQU $0002
MEMF_FAST       EQU $0004
MEMF_CLEAR      EQU $10000

; ============================================================================
; Common Screen Modes
; ============================================================================

; BPLCON0 bits
HIRES           EQU $8000   ; High resolution
BPU_0           EQU $0000   ; 0 bitplanes
BPU_1           EQU $1000   ; 1 bitplane
BPU_2           EQU $2000   ; 2 bitplanes
BPU_3           EQU $3000   ; 3 bitplanes
BPU_4           EQU $4000   ; 4 bitplanes
BPU_5           EQU $5000   ; 5 bitplanes
BPU_6           EQU $6000   ; 6 bitplanes (AGA/ECS)
HOMOD           EQU $0800   ; Hold and modify
DBLPF           EQU $0400   ; Dual playfield
COLOR           EQU $0200   ; Color burst
GAUD            EQU $0100   ; Genlock audio
LPEN            EQU $0008   ; Light pen

; Common display modes
LORES_KEY       EQU $0000   ; 320x256
HIRES_KEY       EQU $8000   ; 640x256
HAM_KEY         EQU $0800   ; Hold and modify