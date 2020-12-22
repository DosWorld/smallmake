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

#include <stdio.h>

runTgt(target) int target; {
    char line[512], *str, c;
    int i;

    if(target == -1) {
        return 1;
    }

    str = getTgtBody(target);
    while(*str != 0) {
        while(*str == 0x0a) {
            str++;
        }
        i = 0;
        while((c = *str != 0) && (*str != 0x0a)) {
            line[i] = *str;
            str++;
            i++;
        }
        line[i] = 0;
        if(strlen(line) > 0) {
            printf("%s\n", line);
            if(i = system(line)) {
                printf("Exit code %d\n", i);
                return i;
            }
        }
    }
    return 0;
}

makeIt(target) int target; {
    char *str, *d, c, tmp[128], needRun;
    int i;
    unsigned tftime, tfdate, dftime, dfdate;

    if(target == -1) {
        return 1;
    }

    if(getTgtVisited(target)) {
            return 0;
    }

    setTgtVisited(target);
    str = getTgtName(target);
    if(needRun = !exists(str)) {
        tfdate = 0;
        tftime = 0;
    } else {
        tfdate = getfdate(str);
        tftime = getftime(str);
    }

    str = getTgtDeps(target);

    while(*str != 0) {
        d = tmp;
        while(*str > ' ') {
            *d = *str;
            d++; str++;
        }
        *d = 0;
        if(strlen(tmp) > 0) {
            if((i = findTgt(tmp)) != -1) {
                if((i = makeIt(i)) != 0) {
                    return i;
                }
            }
            if(exists(tmp)) {
                dfdate = getfdate(tmp);
                dftime = getftime(tmp);
                if(dfdate > tfdate) {
                    needRun = 1;
                } else if((dfdate == tfdate) && (dftime > tftime)) {
                    needRun = 1;
                }
            }
        }
        while((*str <= ' ') && (*str != 0)) {
            str++;
        }
    }
    i = 0;
    if(needRun) {
        return runTgt(target);
    }
    return 0;
}

stripcmt(str) char *str; {
    char quote, c;

    quote = 0;
    while((c = *str) != 0) {
        if(c == '\"') {
            quote = !quote;
        } else if(!quote && (c == '#')) {
            *str = 0;
            return;
        }
        str++;
    }
}

readMakeFile(f) FILE *f; {
    char line[1024];
    while(fgets(line, 1024, f) != NULL) {
        stripcmt(line);
        rtrim(line);
        if(strlen(line) != 0) {
            if(isspace(line[0])) {
                if(!addToTgt(line)) {
                    return 0;
                }
            } else if(!newTgt(line)) {
                return 0;
            }
        }
    }
    return 1;
}
main(argc, argv) int argc, *argv; {
    FILE *f;
    int i, target;

    if((f = fopen("Makefile", "r")) == NULL) {
        printf("No Makefile\n");
        exit(2);
    }
    i = readMakeFile(f);
    fclose(f);

    target = -1;

    if(argc > 1) {
        target = findTgt(argv[1]);
        if(target == -1) {
            printf("Target %s not found\n", argv[1]);
            exit(1);
        }
    }

    if(target == -1) {
        target = 0;
    }

    if(i && (getTgtCount() > 0)) {
        exit(makeIt(target));
    }
    exit(1);
}
