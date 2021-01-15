#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status2 {OUTT, HASH, I, N, C, L, U, D, INCLUDE, LEFT_BRACKET, RIGHT_BRACKET, IN_STRINGG};


void stage_2 (char *file_name)
{
    /*
        copies header files's content to filename.c2
    */
    FILE *c1file, *c2file, *header;
    char c1file_name[128], c2file_name[128], header_name[64];
    int c, i, state = OUTT;
    strcpy(c1file_name, file_name);
    strcpy(c2file_name, file_name);
    strcat(c1file_name, "1");
    strcat(c2file_name, "2");
    memset(header_name, 0, sizeof header_name);
    c1file = fopen(c1file_name, "r");
    c2file = fopen(c2file_name, "w");
    if(!c1file){
        printf("can't open %s in stage 2\n", c1file_name);
    }
    if(!c2file){
        printf("can't open %s in stage 2\n", c2file_name);
    }
    
    while (!feof(c1file))
    {
        c = fgetc(c1file);
        if (c == EOF || c == '\0')
        {
            break;
        }
        switch (state){
            case OUTT:
                if (c == '#'){
                    state = HASH;
                }
                else{
                    fputc(c, c2file);
                    if (c == '\"'){
                        state = IN_STRINGG;
                    }
                }
                break;
            
            case HASH:
                if (c== 'i'){
                    state = I;
                }
                else{
                    fputc('#', c2file);
                    fputc(c, c2file);
                    state = OUTT;
                }
                break;
            
            case I:
                if (c== 'n'){
                    state = N;
                }
                else{
                    fputc('#', c2file);
                    fputc('i', c2file);
                    fputc(c, c2file);
                    state = OUTT;
                }
                break;

            case N:
                if (c== 'c'){
                    state = C;
                }
                else{
                    fputc('#', c2file);
                    fputc('i', c2file);
                    fputc('n', c2file);
                    fputc(c, c2file);
                    state = OUTT;
                }
                break;

            case C:
                if (c== 'l'){
                    state = L;
                }
                else{
                    fputc('#', c2file);
                    fputc('i', c2file);
                    fputc('n', c2file);
                    fputc('c', c2file);
                    fputc(c, c2file);
                    state = OUTT;
                }
                break;

            case L:
                if (c== 'u'){
                    state = U;
                }
                else{
                    fputc('#', c2file);
                    fputc('i', c2file);
                    fputc('n', c2file);
                    fputc('c', c2file);
                    fputc('l', c2file);
                    fputc(c, c2file);
                    state = OUTT;
                }
                break;

            case U:
                if (c== 'd'){
                    state = D;
                }
                else{
                    fputc('#', c2file);
                    fputc('i', c2file);
                    fputc('n', c2file);
                    fputc('c', c2file);
                    fputc('l', c2file);
                    fputc('u', c2file);
                    fputc(c, c2file);
                    state = OUTT;
                }
                break;

            case D:
                if (c== 'e'){
                    state = INCLUDE;
                }
                else{
                    fputc('#', c2file);
                    fputc('i', c2file);
                    fputc('n', c2file);
                    fputc('c', c2file);
                    fputc('l', c2file);
                    fputc('u', c2file);
                    fputc('d', c2file);
                    fputc(c, c2file);
                    state = OUTT;
                }
                break;

            case INCLUDE:
                if (c == '\"'){
                    state = LEFT_BRACKET;
                    i=0;
                }
                break;
            
            case LEFT_BRACKET:
                if (c == '\"'){
                    state = OUTT;

                    header = fopen(header_name, "r");
                    if (!header)
                    {
                        printf("ERROR: can't open %s\n", header_name);
                        exit(0);
                    }
                    
                    while (!feof(header)){
                        c = fgetc(header);
                        if (c == EOF || c == '\0')
                        {
                            break;
                        }
                        fputc(c, c2file);
                    }

                    memset(header_name, 0, sizeof header_name);
                }
                else{
                    header_name[i] = c;
                    i++;
                }
                break;

            case IN_STRINGG:
                if (c == '\"'){
                    state = OUTT;
                }
                fputc(c, c2file);
                break;
        }
    }
    fclose(c1file);
    fclose(c2file);
    printf("stage 2 done \n");
}

