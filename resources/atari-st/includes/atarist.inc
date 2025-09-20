; atarist.inc - Atari ST Hardware and TOS System Definitions
; For use with vasm or other 68000 assemblers

; ============================================================================
; Memory Map
; ============================================================================

; RAM (depends on model)
RAM_START       EQU $000000 ; RAM start (after vector table)
RAM_520ST       EQU $080000 ; 520ST: 512KB RAM
RAM_1040ST      EQU $100000 ; 1040ST: 1MB RAM
RAM_MEGA        EQU $400000 ; Mega ST: 4MB RAM

; ROM TOS
TOS_ROM         EQU $FC0000 ; TOS ROM start (Atari ST)
TOS_ROM_SIZE    EQU $040000 ; TOS ROM size (256KB)

; Cartridge
CART_ROM        EQU $FA0000 ; Cartridge ROM slot

; Hardware Registers
HW_BASE         EQU $FF8000 ; Hardware register base

; ============================================================================
; Video Hardware (Shifter)
; ============================================================================

; Video base address registers
VIDEOBASE_HI    EQU $FF8201 ; Video base address high byte
VIDEOBASE_MID   EQU $FF8203 ; Video base address middle byte
VIDEO_COUNT_HI  EQU $FF8205 ; Video address counter high byte
VIDEO_COUNT_MID EQU $FF8207 ; Video address counter middle byte
VIDEO_COUNT_LO  EQU $FF8209 ; Video address counter low byte

; Sync mode register
SYNC_MODE       EQU $FF820A ; Video sync mode
SYNC_50HZ       EQU $00     ; 50Hz (PAL)
SYNC_60HZ       EQU $02     ; 60Hz (NTSC)

; Color palette (16 colors in ST Low)
PALETTE_0       EQU $FF8240 ; Color 0
PALETTE_1       EQU $FF8242 ; Color 1
PALETTE_2       EQU $FF8244 ; Color 2
PALETTE_3       EQU $FF8246 ; Color 3
PALETTE_4       EQU $FF8248 ; Color 4
PALETTE_5       EQU $FF824A ; Color 5
PALETTE_6       EQU $FF824C ; Color 6
PALETTE_7       EQU $FF824E ; Color 7
PALETTE_8       EQU $FF8250 ; Color 8
PALETTE_9       EQU $FF8252 ; Color 9
PALETTE_10      EQU $FF8254 ; Color 10
PALETTE_11      EQU $FF8256 ; Color 11
PALETTE_12      EQU $FF8258 ; Color 12
PALETTE_13      EQU $FF825A ; Color 13
PALETTE_14      EQU $FF825C ; Color 14
PALETTE_15      EQU $FF825E ; Color 15

; Video resolution register
RESOLUTION      EQU $FF8260 ; Resolution select
RES_LOW         EQU $00     ; 320x200, 16 colors
RES_MED         EQU $01     ; 640x200, 4 colors
RES_HIGH        EQU $02     ; 640x400, 2 colors (monochrome)

; ============================================================================
; Sound (YM2149 PSG)
; ============================================================================

PSG_SELECT      EQU $FF8800 ; PSG register select
PSG_READ        EQU $FF8800 ; PSG read data
PSG_WRITE       EQU $FF8802 ; PSG write data

; PSG Registers
PSG_A_FINE      EQU $00     ; Channel A fine frequency
PSG_A_COARSE    EQU $01     ; Channel A coarse frequency
PSG_B_FINE      EQU $02     ; Channel B fine frequency
PSG_B_COARSE    EQU $03     ; Channel B coarse frequency
PSG_C_FINE      EQU $04     ; Channel C fine frequency
PSG_C_COARSE    EQU $05     ; Channel C coarse frequency
PSG_NOISE       EQU $06     ; Noise frequency
PSG_MIXER       EQU $07     ; Mixer/I-O control
PSG_A_VOL       EQU $08     ; Channel A volume
PSG_B_VOL       EQU $09     ; Channel B volume
PSG_C_VOL       EQU $0A     ; Channel C volume
PSG_ENV_FINE    EQU $0B     ; Envelope fine frequency
PSG_ENV_COARSE  EQU $0C     ; Envelope coarse frequency
PSG_ENV_SHAPE   EQU $0D     ; Envelope shape
PSG_IO_A        EQU $0E     ; I/O port A (floppy/printer)
PSG_IO_B        EQU $0F     ; I/O port B (parallel port)

; ============================================================================
; MFP (Multi-Function Peripheral) MC68901
; ============================================================================

MFP_BASE        EQU $FFFA01 ; MFP base address

MFP_GPIP        EQU MFP_BASE+$00 ; General purpose I/O
MFP_AER         EQU MFP_BASE+$02 ; Active edge register
MFP_DDR         EQU MFP_BASE+$04 ; Data direction register
MFP_IERA        EQU MFP_BASE+$06 ; Interrupt enable A
MFP_IERB        EQU MFP_BASE+$08 ; Interrupt enable B
MFP_IPRA        EQU MFP_BASE+$0A ; Interrupt pending A
MFP_IPRB        EQU MFP_BASE+$0C ; Interrupt pending B
MFP_ISRA        EQU MFP_BASE+$0E ; Interrupt in-service A
MFP_ISRB        EQU MFP_BASE+$10 ; Interrupt in-service B
MFP_IMRA        EQU MFP_BASE+$12 ; Interrupt mask A
MFP_IMRB        EQU MFP_BASE+$14 ; Interrupt mask B
MFP_VR          EQU MFP_BASE+$16 ; Vector register
MFP_TACR        EQU MFP_BASE+$18 ; Timer A control
MFP_TBCR        EQU MFP_BASE+$1A ; Timer B control
MFP_TCDCR       EQU MFP_BASE+$1C ; Timer C&D control
MFP_TADR        EQU MFP_BASE+$1E ; Timer A data
MFP_TBDR        EQU MFP_BASE+$20 ; Timer B data
MFP_TCDR        EQU MFP_BASE+$22 ; Timer C data
MFP_TDDR        EQU MFP_BASE+$24 ; Timer D data
MFP_SCR         EQU MFP_BASE+$26 ; Sync character register
MFP_UCR         EQU MFP_BASE+$28 ; USART control register
MFP_RSR         EQU MFP_BASE+$2A ; Receiver status register
MFP_TSR         EQU MFP_BASE+$2C ; Transmitter status register
MFP_UDR         EQU MFP_BASE+$2E ; USART data register

; MFP Interrupt bits
MFP_GPIP7       EQU $80     ; Monochrome monitor detect
MFP_GPIP6       EQU $40     ; RS232 ring indicator
MFP_GPIP5       EQU $20     ; FTX/DTR (FDC)
MFP_GPIP4       EQU $10     ; Keyboard/MIDI
MFP_GPIP3       EQU $08     ; FDC/DMA
MFP_GPIP2       EQU $04     ; RS232 clear to send
MFP_GPIP1       EQU $02     ; RS232 data carrier detect
MFP_GPIP0       EQU $01     ; Centronics busy

; ============================================================================
; ACIA (Asynchronous Communications Interface Adapter) MC6850
; ============================================================================

; Keyboard ACIA
KBD_ACIA_CTRL   EQU $FFFC00 ; Keyboard ACIA control
KBD_ACIA_DATA   EQU $FFFC02 ; Keyboard ACIA data

; MIDI ACIA
MIDI_ACIA_CTRL  EQU $FFFC04 ; MIDI ACIA control
MIDI_ACIA_DATA  EQU $FFFC06 ; MIDI ACIA data

; ============================================================================
; DMA (Direct Memory Access)
; ============================================================================

DMA_BASE        EQU $FF8600 ; DMA base address

DMA_MODE        EQU DMA_BASE+$06  ; DMA mode control
DMA_STATUS      EQU DMA_BASE+$06  ; DMA status (read)
DMA_FIFO        EQU DMA_BASE+$02  ; DMA FIFO
DMA_HIGH        EQU DMA_BASE+$09  ; DMA address high
DMA_MID         EQU DMA_BASE+$0B  ; DMA address middle
DMA_LOW         EQU DMA_BASE+$0D  ; DMA address low

; DMA mode bits
DMA_READ        EQU $00     ; Read from device
DMA_WRITE       EQU $01     ; Write to device
DMA_FDC         EQU $02     ; Floppy disk controller
DMA_HDC         EQU $08     ; Hard disk controller

; ============================================================================
; Floppy Disk Controller (FDC)
; ============================================================================

FDC_ACCESS      EQU $FF8604 ; FDC access register
FDC_TRACK       EQU $FF8605 ; Track register
FDC_SECTOR      EQU $FF8607 ; Sector register
FDC_DATA        EQU $FF8609 ; Data register

; ============================================================================
; TOS System Calls (GEMDOS)
; ============================================================================

; Console I/O
Cconin          EQU $01     ; Console input
Cconout         EQU $02     ; Console output
Cauxin          EQU $03     ; Auxiliary input
Cauxout         EQU $04     ; Auxiliary output
Cprnout         EQU $05     ; Printer output
Crawio          EQU $06     ; Raw console I/O
Crawcin         EQU $07     ; Raw console input
Cnecin          EQU $08     ; Console input (no echo)
Cconws          EQU $09     ; Console write string
Cconrs          EQU $0A     ; Console read string
Cconis          EQU $0B     ; Console input status

; Program control
Pterm0          EQU $00     ; Program terminate
Ptermres        EQU $31     ; Terminate and stay resident
Pexec           EQU $4B     ; Execute program

; File operations
Fopen           EQU $3D     ; Open file
Fcreate         EQU $3C     ; Create file
Fclose          EQU $3E     ; Close file
Fread           EQU $3F     ; Read from file
Fwrite          EQU $40     ; Write to file
Fdelete         EQU $41     ; Delete file
Fseek           EQU $42     ; Seek in file
Fattrib         EQU $43     ; Get/set file attributes
Fdup            EQU $45     ; Duplicate file handle
Fforce          EQU $46     ; Force file handle
Dgetpath        EQU $47     ; Get current path
Malloc          EQU $48     ; Allocate memory
Mfree           EQU $49     ; Free memory
Mshrink         EQU $4A     ; Shrink memory block
Fsfirst         EQU $4E     ; Find first file
Fsnext          EQU $4F     ; Find next file

; Directory operations
Dsetdrv         EQU $0E     ; Set drive
Dgetdrv         EQU $19     ; Get current drive
Dsetpath        EQU $3B     ; Set path
Dcreate         EQU $39     ; Create directory
Ddelete         EQU $3A     ; Delete directory

; ============================================================================
; XBIOS System Calls
; ============================================================================

Initmous        EQU $00     ; Initialize mouse
Ssbrk           EQU $01     ; Set/get system break
Physbase        EQU $02     ; Get physical screen base
Logbase         EQU $03     ; Get logical screen base
Getrez          EQU $04     ; Get screen resolution
Setscreen       EQU $05     ; Set screen
Setpalette      EQU $06     ; Set palette
Setcolor        EQU $07     ; Set color
Floprd          EQU $08     ; Read floppy sectors
Flopwr          EQU $09     ; Write floppy sectors
Flopfmt         EQU $0A     ; Format floppy track
Midiws          EQU $0C     ; MIDI write string
Mfpint          EQU $0D     ; Set MFP interrupt
Iorec           EQU $0E     ; Get I/O record
Rsconf          EQU $0F     ; RS232 configuration
Keytbl          EQU $10     ; Set keyboard table
Random          EQU $11     ; Random number
Protobt         EQU $12     ; Prototype boot sector
Flopver         EQU $13     ; Verify floppy sectors
Scrdmp          EQU $14     ; Screen dump
Cursconf        EQU $15     ; Configure cursor
Settime         EQU $16     ; Set time
Gettime         EQU $17     ; Get time
Bioskeys        EQU $18     ; Set BIOS key table
Ikbdws          EQU $19     ; IKBD write string
Jdisint         EQU $1A     ; Disable interrupts
Jenabint        EQU $1B     ; Enable interrupts
Giaccess        EQU $1C     ; Access GI sound chip
Offgibit        EQU $1D     ; Disable GI bit
Ongibit         EQU $1E     ; Enable GI bit
Xbtimer         EQU $1F     ; Set/get timer
Dosound         EQU $20     ; Execute sound
Setprt          EQU $21     ; Set printer configuration
Kbdvbase        EQU $22     ; Get keyboard vectors
Kbrate          EQU $23     ; Set keyboard repeat rate
Prtblk          EQU $24     ; Print block
Vsync           EQU $25     ; Wait for vertical sync
Supexec         EQU $26     ; Execute in supervisor mode

; ============================================================================
; BIOS System Calls
; ============================================================================

Getmpb          EQU $00     ; Get memory parameter block
Bconstat        EQU $01     ; Console input status
Bconin          EQU $02     ; Console input
Bconout         EQU $03     ; Console output
Rwabs           EQU $04     ; Read/write absolute sectors
Setexc          EQU $05     ; Set exception vector
Tickcal         EQU $06     ; Get timer calibration
Getbpb          EQU $07     ; Get BIOS parameter block
Bcostat         EQU $08     ; Console output status
Mediach         EQU $09     ; Media change
Drvmap          EQU $0A     ; Get drive map
Kbshift         EQU $0B     ; Get/set keyboard shift state

; ============================================================================
; Standard Colors (ST Low Resolution)
; ============================================================================

; RGB values (0-7 per component, format: $0RGB)
COL_WHITE       EQU $0777
COL_BLACK       EQU $0000
COL_RED         EQU $0700
COL_GREEN       EQU $0070
COL_BLUE        EQU $0007
COL_CYAN        EQU $0077
COL_YELLOW      EQU $0770
COL_MAGENTA     EQU $0707
COL_GRAY        EQU $0444
COL_DARK_GRAY   EQU $0222
COL_LIGHT_GRAY  EQU $0555
COL_DARK_RED    EQU $0400
COL_DARK_GREEN  EQU $0040
COL_DARK_BLUE   EQU $0004
COL_ORANGE      EQU $0740
COL_BROWN       EQU $0530

; ============================================================================
; Useful Constants
; ============================================================================

; Screen dimensions
SCREEN_W_LOW    EQU 320     ; Width in low resolution
SCREEN_H_LOW    EQU 200     ; Height in low resolution
SCREEN_W_MED    EQU 640     ; Width in medium resolution
SCREEN_H_MED    EQU 200     ; Height in medium resolution
SCREEN_W_HIGH   EQU 640     ; Width in high resolution
SCREEN_H_HIGH   EQU 400     ; Height in high resolution

; Memory sizes
SCREEN_SIZE_LOW EQU 32000   ; Screen memory low res
SCREEN_SIZE_MED EQU 32000   ; Screen memory medium res
SCREEN_SIZE_HIGH EQU 32000  ; Screen memory high res

; System variables
SYSBASE         EQU $004F2  ; Pointer to system base