/*
 *  (c) Copyright by Viacheslav Komenda
 *  License: public domain
 */

isident(c) char c; {
    return isalpha(c) || isdigit(c) || (c == '_');
}

stricmp(s, t) char *s, *t; {
    while(toupper(*s) == toupper(*t)) {
	if(*s == 0) {
	    return (0);
	}
	s++; t++;
    }
    return toupper(*s) - toupper(*t);
}

rtrim(str) char *str; {
    char *dst;

    dst = str;
    while(*str != 0) {
	str++;
    }
    while((dst != str) && (*str <= ' ')) {
	*str = 0;
	str--;
    }
    if(*str <= ' ') {
	*str = 0;
    }
}

ltrim(str) char *str; {
    char *dst;

    dst = str;
    while((*str <= ' ') && (*str != 0)) {
	str++;
    }
    while(*str != 0) {
	*dst = *str;
	dst++;
	str++;
    }
    *dst = 0;
}

trim(str) char *str; {
    ltrim(str);
    rtrim(str);
}
