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
