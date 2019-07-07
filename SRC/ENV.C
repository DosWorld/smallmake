/*
    (c) 2019 Copyright by Viacheslav Komenda

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>

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
