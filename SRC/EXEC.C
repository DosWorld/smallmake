/*
 *  (c) Copyright by Viacheslav Komenda
 *  License: public domain
 */

int ep[0x10];

getExitCode() {
#asm
    mov     ah,4dh
    int     21h
    xor     ah,ah
#endasm
}

getDs() {
#asm
    mov     ax,ds
#endasm
}

exec(cmd, params) char *cmd, *params; {
    ep[0] = 0;
    ep[1] = params;
    ep[2] = getDs();
    ep[3] = 0;
    ep[4] = 0;
    ep[5] = 0;
    ep[6] = 0;

#asm
    push    ds
    push    es
    push    bp
    mov     ax,ss
    mov     cs:mss,ax
    mov     cs:msp,sp
    push    ds
    pop     es
    mov     ax,4B00h
    mov     dx,[bp+6]
    mov     bx,offset _ep
    int     21h
    jmp     short cont1
mss:
    dw 0
msp:
    dw 0
cont1:
    cli
    mov     cx,cs:mss
    mov     ss,cx
    mov     sp,cs:msp
    sti

    pop     bp
    pop     es
    pop     ds
    jc      end1
    xor     ax,ax
end1:
#endasm
}

findInPath(path, name, res) char *path, *name, *res; {
    char *str, c;
    char tpath[256];

    *res = 0;

    str = name;
    while(*str != 0) {
	str++;
    }

    while(str != name) {
	c = *str;
	if(c == '.') {
	    *str = 0;
	    break;
	}
	if(c == '\\' || c == '/' || c == ':') {
	    break;
	}
	str--;
    }
    strcpy(res, name);
    strcat(res, ".exe");
    if(exists(res)) {
	return 1;
    }
    strcpy(res, name);
    strcat(res, ".com");
    if(exists(res)) {
	return 1;
    }
    while(*path != 0) {
	str = tpath;
	while(*path != 0 && *path != ';') {
	*str = c = *path;
	str++;
	path++;
	}
	if(*path == ';') {
	    path++;
	}
	if(c != '\\') {
	    *str = '\\';
	    str++;
	}
	*str = 0;
	strcpy(res, tpath);
	strcat(res, name);
	strcat(res, ".exe");
	if(exists(res)) {
	    return 1;
	}
	strcpy(res, tpath);
	strcat(res, name);
	strcat(res, ".com");
	if(exists(res)) {
	    return 1;
	}
    }
    return 0;
}

system(cmd) char *cmd; {
    char ccmd[256], params[256], *src, *dst;
    char comspec[256], path[4096];
    int r;
    getEnv("COMSPEC", comspec, 256);
    getEnv("PATH", path, 4096);
    src = cmd;
    dst = params;
    while(*src > ' ') {
	*dst = *src;
	dst++;
	src++;
    }
    *dst = 0;
    if(findInPath(path, params, ccmd)) {
	strcpy(&params[1], src);
    } else {
        strcpy(ccmd, comspec);
	strcpy(&params[1], " /C ");
	strcat(&params[1], cmd);
    }
    r = strlen(&params[1]);
    params[0] = r;
    params[r + 1] = 0x0d;
    params[r + 2] = 0x0;
    if(!(r = exec(ccmd, params))) {
        return getExitCode();
    } else {
        printf("DOS error %d\n", r);
        return -1;
    }
}
