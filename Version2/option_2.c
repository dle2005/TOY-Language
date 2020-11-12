#include <stdio.h>
#include <string.h>

void saveDefun(char *buff);

extern FILE* flashfp;

void option_2() {

	flashfp = fopen("defun.txt", "r");

	char buff[100] = {};

	while(1) {
		if(fgets(buff, 100, flashfp) == NULL) break;

		fputs(buff, stdout);

		saveDefun(buff);
	}

	printf("\n");

	fclose(flashfp);
}
