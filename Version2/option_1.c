#include <stdio.h>
#include <string.h>
#include "head.h"

extern FILE* flashfp;

void option_1() {

	flashfp = fopen("defun.txt", "a");

	char input[100], save[100];
	fgets(input, 100, stdin);

	for(int i = 0; i < 94; i++)
		save[i] = input[i+6];

	fseek(flashfp,0,SEEK_END);


	fputs(save, flashfp);

	fclose(flashfp);

	if(isDefined(save)) {
		printf("�̹� ���ǵǾ� �ֽ��ϴ�.\n");
		memset(save,'\0',strlen(save));
	}
	else if(isNoV(save)) {
		printf("�Ű������� �Ѱ��� �����ϴ�.\n");
		memset(save,'\0',strlen(save));
	}

	else {
		saveDefun(save);
	}

}
