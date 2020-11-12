#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

extern FILE* flashfp;

void option_3() {

	char *filename = malloc(sizeof(char) * 100);
	char buff[100];

	memset(filename, '\0', sizeof(filename));
	printf("실행 파일명을 입력하세요 >> ");
	fflush(stdout);
	fgets(filename, 100, stdin);
	filename = "a.txt";
//	printf("filename : %s\n", filename);
	flashfp = fopen(filename, "r");
	printf("\n");


	while(1) {
		if(fgets(buff, 100, flashfp) == NULL) break;
		if(buff[strlen(buff)-1] != ')') buff[strlen(buff)-1] = '\0';
		char *temp = malloc(sizeof(char) * 100);
		char tempBuff[100];
		strcpy(tempBuff, buff);
		printf("**********\n");
		printf("%s", tempBuff);
		printf(" -> ");
		if(isDoubleM(tempBuff)) {
			printf("\'-\'가 연속적으로 사용 되었습니다.\n\n");
		}
		else if(checkB(tempBuff)) {	printf("\n");}
		else if(notDefinedDefun(tempBuff)) { printf("정의되지 않은 함수입니다.\n\n"); }
		else {
			temp = changeDefun(tempBuff);
			while(findDefun(temp) != -1) temp = changeDefun(temp);
			if(isWrongWord(temp)) {
				printf("syntax error\n\n");
			}
			else if(isWrongInput(temp)) { }
			else {
				printf("%s\n\n", temp);
				printf("Prefix To Postfix : ");
				temp = ptop(temp);
				printf("%s\n", temp);
				printf("Result : ");
				int result = caclulate(temp);
				printf("%d\n\n", result);
			}
		}
		free(temp);
		memset(buff, '\0', sizeof(buff));
	}
}
