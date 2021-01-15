#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status1 {OUT, IN_STRING, LEFT_SLASH, IN_COMMENT, RIGHT_STAR, IN_CPP_COM};

void stage_1 (char *file_name)
{
    /*
        removes ansi-c comments from c files and cpp form (//)
        copies the new content to filename.c1
    */
    int c;
    int state = OUT;
    FILE *cfile, *c1file;
    char c1file_name[128];

    strcpy(c1file_name, file_name);
    strcat(c1file_name, "1");

    cfile = fopen(file_name, "r");
    c1file = fopen(c1file_name, "w");

    if (!cfile){
        printf("ERROR: can't open specified file\n");
        exit(0);
    }

    while (!feof(cfile))
    {
        c = fgetc(cfile);

        if (c == EOF || c == '\0')
        {
            break;
        }
                
        switch (state){
            case OUT:
                if (c == '/'){
                    state = LEFT_SLASH;
                }
                else{
                    fputc(c, c1file);
                    if (c == '\"'){
                        state = IN_STRING;
                    }
                }
                break;
            
            case LEFT_SLASH:
                if (c== '*'){
                    state = IN_COMMENT;
                }
                else if (c=='/'){
                    state = IN_CPP_COM;
                }
                else{
                    fputc('/', c1file);
                    fputc(c, c1file);
                    state = OUT;
                }
                break;

            case IN_COMMENT:
                if (c=='*'){
                    state = RIGHT_STAR;
                }
                break;

            case IN_CPP_COM:
                if (c=='\n'){
                    state = OUT;
                }
                break;

            case RIGHT_STAR:
                if (c=='/'){
                    state = OUT;
                }
                else if (c != '*'){
                    state = IN_COMMENT;
                }
                break;

            case IN_STRING:
                if (c == '\"'){
                    state = OUT;
                }
                fputc(c, c1file);
                break;
        }
    }

    fclose(cfile);
    fclose(c1file);
    printf("stage 1 done \n");

}