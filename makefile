prep: stage1.c stage2.c preprocessor.c
	gcc -Wall -ansi -pedantic stage1.c stage2.c preprocessor.c -o prep