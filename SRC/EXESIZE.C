/*
 *  (c) Copyright by Viacheslav Komenda
 *  License: public domain
 */

#include <stdio.h>

char exeh[32];

main(argc, argv) int argc, *argv; {
    FILE *f;
    unsigned i;

    if(argc != 2) {
	puts("Use EXESIZE.EXE exefile");
	exit(1);
    }

    if((f = fopen(argv[1], "r")) == NULL) {
	exit(1);
    }
    fread(exeh, sizeof(exeh), 1, f);
    fclose(f);

    exeh[0x0c] = 0xff;
    exeh[0x0d] = 0x0f;

    f = fopen(argv[1], "r+");
    fwrite(f, exeh, sizeof(exeh), 1, f);
    fclose(f);

    exit(0);
}
