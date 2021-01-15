#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stage_1 (char *file_name);
void stage_2 (char *file_name);


int main(int argc, char *argv[])
{
    /* 
        main function
        checks the the input is valid and calls to stage_1 and stage_2
    */
    if (argc != 2){
        printf("ERROR: supply only 1 argument - file path\n");
        exit(1);
    }

    if (argv[1] && argv[1][strlen(argv[1])-1] != 'c'){
        printf("ERROR: supply a c file\n");
        exit(1);
    }

    stage_1(argv[1]);
    stage_2(argv[1]);
    
    return 0;
    
}

