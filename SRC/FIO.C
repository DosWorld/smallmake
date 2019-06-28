/*
 *  (c) Copyright by Viacheslav Komenda
 *  License: public domain
 */

/*
 Check if file exists
*/
exists(name) char *name; {
#asm
    mov     ax,4300h
    mov     dx,ss:[bp+4]
    int     21h
    pushf
    xor     ax,ax
    popf
    jc      exists_not
    dec     ax
exists_not:
#endasm
}

/*
 Get file time:

 hours = (getftime("fname") >> 11) & 31
 minutes = (getftime("fname") >> 5) & 63
 seconds = (getftime("fname") & 31) << 1);

 if file not exsits, returns 0.
*/
getftime(name) char *name; {
#asm
    mov     dx,ss:[bp+4]
    mov     ax,3d00h
    int     21h
    jc      gftime_not
    mov     bx,ax
    mov     ax,5700h
    push    bx
    int     21h
    pop     bx
    push    cx
    mov     ah,3eh
    int     21h
    pop     ax
    jmp     short gftime_end
gftime_not:
    xor     ax,ax
gftime_end:
#endasm
}

/*
 Get file date
*/
getfdate(name) char *name; {
#asm
    mov     dx,ss:[bp+4]
    mov     ax,3d00h
    int     21h
    jc      gfdate_not
    mov     bx,ax
    mov     ax,5700h
    push    bx
    int     21h
    pop     bx
    push    dx
    mov     ah,3eh
    int     21h
    pop     ax
    jmp     short gfdate_end
gfdate_not:
    xor     ax,ax
gfdate_end:
#endasm
}

/*
setftime(name, time) char *name; int time; {
#asm
    mov     dx,ss:[bp+6]
    mov     ax,3D00h
    int     21h
    jc      setftime_not
    mov     bx,ax
    mov     ax,5700h
    push    bx
    int     21h
    pop     bx
    push    bx
    mov     CX,ss:[bp+4]
    mov     ax,5701h
    int     21h
    pop     bx
    mov     ah,3Eh
    int     21h
setftime_not:
#endasm
}

setfdate(name, time) char *name; int time; {
#asm
    mov     dx,ss:[bp+6]
    mov     ax,3D00h
    int     21h
    jc      setfdate_not
    mov     bx,ax
    mov     ax,5700h
    push    bx
    int     21h
    pop     bx
    push    bx
    mov     dx,ss:[bp+4]
    mov     ax,5701h
    int     21h
    pop     bx
    mov     ah,3Eh
    int     21h
setfdate_not:
#endasm
}

*/
