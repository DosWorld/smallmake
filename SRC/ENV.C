/*
 *  (c) Copyright by Viacheslav Komenda
 *  License: public domain
 */

getEnvSeg() {
#asm
    push    es
    mov     ah,51h
    int     21h
    mov     es,bx
    mov     ax,es:[2Ch]
    pop     es
#endasm
}

getEnv(name, dst, count) char *name, *dst; int count; {
#asm
    push    es
    push    ds
    mov     bx,ss:[bp+6]
    mov     byte ptr [bx],0
    mov     ah,51h
    int     21h
    mov     es,bx
    mov     ax,es:[2Ch]
    mov     es,ax
    xor     bx,bx
genv1:
    cmp     byte ptr es:[bx],0
    je      genv_end
    mov     si,ss:[bp+8]
    xor     ax,ax
    jmp     short genv5
genv2:
    mov     al,es:[bx]
    inc     bx
    mov     ah,[si]
    inc     si
    cmp     ax,'='
    jne     genv5
    mov     si,ss:[bp+6]
    xor     cx,cx
    mov     dx,ss:[bp+4]
    dec     dx
genv3:
    mov     al,es:[bx]
    inc     bx
    cmp     cx,dx
    jbe     genv4
    mov     al,0
genv4:
    mov     [si],al
    inc     si
    test    al,al
    je      genv_end
    inc     cx
    jmp     short genv3
genv5:
    cmp     al,ah
    je      genv2
    jmp     short genv7
genv6:
    inc     bx
genv7:
    cmp     byte ptr es:[bx],0
    jne     genv6
    inc     bx
    jmp     short genv1
genv_end:
    pop     ds
    pop     es
#endasm
}
