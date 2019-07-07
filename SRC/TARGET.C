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

#define MAX_TARGETS 1024

char mem[16*1024];
int memPtr = 0;

int targetName[MAX_TARGETS];
int targetBody[MAX_TARGETS];
int targetDeps[MAX_TARGETS];
int targetPtr = 0;

getTgtCount() {
    return targetPtr;
}

getTgtName(target) int target; {
    return &mem[targetName[target]];
}

getTgtBody(target) int target; {
    return &mem[targetBody[target]];
}

getTgtDeps(target) int target; {
    return &mem[targetDeps[target]];
}

findTgt(str) char *str; {
    int i;
    for(i = 0; i < targetPtr; i++) {
	if(!stricmp(str, &mem[targetName[i]])) {
	    return i;
	}
    }
    return -1;
}

addToTgt(line) char *line; {
    if(targetPtr == 0) {
	return 0;
    }
    trim(line);
    strcpy(&mem[memPtr-1], line);
    memPtr += strlen(line);
    mem[memPtr - 1] = 0x0a;
    mem[memPtr] = 0;
    memPtr++;
    return 1;
}

newTgt(line) char *line;{
    int ptr;

    ptr = memPtr;

    while(isident(*line) || (*line == '.') || (*line == '-')) {
	mem[memPtr] = *line;
	memPtr++;
	line++;
    }
    mem[memPtr] = 0;
    memPtr++;
    while((*line <= ' ') && (*line != 0)) {
	line++;
    }
    if(*line != ':') {
	return 0;
    }
    targetName[targetPtr] = ptr;
    line++;
    while((*line <= ' ') && (*line != 0)) {
	line++;
    }
    ptr = memPtr;
    while(*line != 0) {
	mem[memPtr] = *line;
	memPtr++;
	line++;
    }
    mem[memPtr] = 0;
    memPtr++;
    targetDeps[targetPtr] = ptr;
    targetBody[targetPtr] = memPtr;
    mem[memPtr] = 0;
    memPtr++;
    targetPtr++;
    return 1;
}
