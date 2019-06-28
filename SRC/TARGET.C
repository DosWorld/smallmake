/*
 *  (c) Copyright by Viacheslav Komenda
 *  License: public domain
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
