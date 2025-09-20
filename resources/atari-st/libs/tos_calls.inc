; tos_calls.inc - TOS system call macros for Atari ST
; Convenient macros for calling GEMDOS, XBIOS, and BIOS functions

; ============================================================================
; System Call Macros
; ============================================================================

; GEMDOS system call
gemdos MACRO func
    move.w  #\func\,-(sp)
    trap    #1
    addq.l  #2,sp
ENDM

; GEMDOS with 16-bit parameter
gemdos_w MACRO func,param
    move.w  \param\,-(sp)
    move.w  #\func\,-(sp)
    trap    #1
    addq.l  #4,sp
ENDM

; GEMDOS with 32-bit parameter
gemdos_l MACRO func,param
    move.l  \param\,-(sp)
    move.w  #\func\,-(sp)
    trap    #1
    addq.l  #6,sp
ENDM

; XBIOS system call
xbios MACRO func
    move.w  #\func\,-(sp)
    trap    #14
    addq.l  #2,sp
ENDM

; XBIOS with 16-bit parameter
xbios_w MACRO func,param
    move.w  \param\,-(sp)
    move.w  #\func\,-(sp)
    trap    #14
    addq.l  #4,sp
ENDM

; XBIOS with 32-bit parameter
xbios_l MACRO func,param
    move.l  \param\,-(sp)
    move.w  #\func\,-(sp)
    trap    #14
    addq.l  #6,sp
ENDM

; BIOS system call
bios MACRO func
    move.w  #\func\,-(sp)
    trap    #13
    addq.l  #2,sp
ENDM

; BIOS with 16-bit parameter
bios_w MACRO func,param
    move.w  \param\,-(sp)
    move.w  #\func\,-(sp)
    trap    #13
    addq.l  #4,sp
ENDM

; ============================================================================
; Common GEMDOS Operations
; ============================================================================

; Print string (null-terminated)
print_string MACRO string_addr
    move.l  \string_addr\,-(sp)
    gemdos  Cconws
    addq.l  #4,sp
ENDM

; Print character
print_char MACRO char
    move.w  \char\,-(sp)
    gemdos  Cconout
    addq.l  #2,sp
ENDM

; Read character (with wait)
read_char MACRO
    gemdos  Cconin
ENDM

; Check if key available
key_available MACRO
    gemdos  Cconis
ENDM

; Terminate program
exit_program MACRO
    gemdos  Pterm0
ENDM

; Terminate with error code
exit_with_code MACRO code
    move.w  \code\,-(sp)
    gemdos  Pterm
    addq.l  #2,sp
ENDM

; Open file
open_file MACRO filename,mode
    move.w  \mode\,-(sp)
    move.l  \filename\,-(sp)
    gemdos  Fopen
    addq.l  #6,sp
ENDM

; Close file
close_file MACRO handle
    move.w  \handle\,-(sp)
    gemdos  Fclose
    addq.l  #2,sp
ENDM

; Read from file
read_file MACRO handle,count,buffer
    move.l  \buffer\,-(sp)
    move.l  \count\,-(sp)
    move.w  \handle\,-(sp)
    gemdos  Fread
    lea     10(sp),sp
ENDM

; Write to file
write_file MACRO handle,count,buffer
    move.l  \buffer\,-(sp)
    move.l  \count\,-(sp)
    move.w  \handle\,-(sp)
    gemdos  Fwrite
    lea     10(sp),sp
ENDM

; ============================================================================
; Common XBIOS Operations
; ============================================================================

; Wait for vertical sync
wait_vbl MACRO
    xbios   Vsync
ENDM

; Get screen resolution
get_resolution MACRO
    xbios   Getrez
ENDM

; Set screen resolution and buffers
set_screen MACRO log_addr,phys_addr,resolution
    move.w  \resolution\,-(sp)
    move.l  \phys_addr\,-(sp)
    move.l  \log_addr\,-(sp)
    xbios   Setscreen
    lea     10(sp),sp
ENDM

; Set single palette color
set_color MACRO color_num,rgb_value
    move.w  \rgb_value\,-(sp)
    move.w  \color_num\,-(sp)
    xbios   Setcolor
    addq.l  #4,sp
ENDM

; Set entire palette
set_palette MACRO palette_addr
    move.l  \palette_addr\,-(sp)
    xbios   Setpalette
    addq.l  #4,sp
ENDM

; Execute supervisor mode code
supervisor MACRO code_addr
    move.l  \code_addr\,-(sp)
    xbios   Supexec
    addq.l  #4,sp
ENDM

; ============================================================================
; Common BIOS Operations
; ============================================================================

; Console input status
console_status MACRO device
    move.w  \device\,-(sp)
    bios    Bconstat
    addq.l  #2,sp
ENDM

; Console input
console_input MACRO device
    move.w  \device\,-(sp)
    bios    Bconin
    addq.l  #2,sp
ENDM

; Console output
console_output MACRO device,char
    move.w  \char\,-(sp)
    move.w  \device\,-(sp)
    bios    Bconout
    addq.l  #4,sp
ENDM

; Get keyboard shift state
get_shift_state MACRO mode
    move.w  \mode\,-(sp)
    bios    Kbshift
    addq.l  #2,sp
ENDM

; ============================================================================
; File I/O Helper Macros
; ============================================================================

; Create new file
create_file MACRO filename,attributes
    move.w  \attributes\,-(sp)
    move.l  \filename\,-(sp)
    gemdos  Fcreate
    addq.l  #6,sp
ENDM

; Delete file
delete_file MACRO filename
    move.l  \filename\,-(sp)
    gemdos  Fdelete
    addq.l  #4,sp
ENDM

; Seek in file
seek_file MACRO handle,offset,mode
    move.w  \mode\,-(sp)
    move.w  \handle\,-(sp)
    move.l  \offset\,-(sp)
    gemdos  Fseek
    addq.l  #8,sp
ENDM

; ============================================================================
; Memory Management
; ============================================================================

; Allocate memory
allocate_memory MACRO size
    move.l  \size\,-(sp)
    gemdos  Malloc
    addq.l  #4,sp
ENDM

; Free memory
free_memory MACRO address
    move.l  \address\,-(sp)
    gemdos  Mfree
    addq.l  #4,sp
ENDM

; Shrink memory block
shrink_memory MACRO address,new_size
    move.l  \new_size\,-(sp)
    move.l  \address\,-(sp)
    move.w  #0,-(sp)
    gemdos  Mshrink
    lea     10(sp),sp
ENDM

; ============================================================================
; Screen and Graphics Helpers
; ============================================================================

; Clear screen with color
clear_screen MACRO color
    move.l  #SCREEN_SIZE_LOW/4-1,d0  ; Assume low res
    move.l  \color\,d1
    swap    d1
    move.w  \color\,d1               ; Fill pattern
    xbios   Physbase                 ; Get screen address
    move.l  d0,a0
.clear_loop\@:
    move.l  d1,(a0)+
    dbra    d0,.clear_loop\@
ENDM

; Set low resolution with 16 colors
set_low_res MACRO
    move.w  #RES_LOW,-(sp)
    move.l  #-1,-(sp)
    move.l  #-1,-(sp)
    xbios   Setscreen
    lea     10(sp),sp
ENDM

; Set medium resolution with 4 colors
set_med_res MACRO
    move.w  #RES_MED,-(sp)
    move.l  #-1,-(sp)
    move.l  #-1,-(sp)
    xbios   Setscreen
    lea     10(sp),sp
ENDM

; Set high resolution monochrome
set_high_res MACRO
    move.w  #RES_HIGH,-(sp)
    move.l  #-1,-(sp)
    move.l  #-1,-(sp)
    xbios   Setscreen
    lea     10(sp),sp
ENDM

; ============================================================================
; Sound Generation
; ============================================================================

; Play simple tone on PSG channel A
play_tone MACRO frequency,duration
    ; Set frequency
    move.w  #PSG_A_FINE,d0
    move.w  \frequency\,d1
    andi.w  #$FF,d1
    bsr     write_psg

    move.w  #PSG_A_COARSE,d0
    move.w  \frequency\,d1
    lsr.w   #8,d1
    andi.w  #$0F,d1
    bsr     write_psg

    ; Set volume
    move.w  #PSG_A_VOL,d0
    move.w  #15,d1          ; Max volume
    bsr     write_psg

    ; Enable tone
    move.w  #PSG_MIXER,d0
    move.w  #$FE,d1         ; Enable tone A, disable all others
    bsr     write_psg

    ; Wait for duration
    move.l  \duration\,d0
.delay_loop\@:
    subq.l  #1,d0
    bne.s   .delay_loop\@

    ; Turn off sound
    move.w  #PSG_A_VOL,d0
    move.w  #0,d1
    bsr     write_psg
ENDM

; Write to PSG register (d0=register, d1=value)
write_psg:
    move.w  d0,PSG_SELECT
    move.w  d1,PSG_WRITE
    rts