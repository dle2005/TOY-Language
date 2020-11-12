#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

extern char defunName[100][100];
extern int defunVNum[100];
extern char defunV[100][100];
extern char defunFunction[100][100];
extern int funCount;

int notDefinedDefun(char *buff) {
	char *temp = malloc(sizeof(char) * 100);
	strcpy(temp, buff);
	char *ptr = strtok(temp, " ");

	if(!strcmp(ptr, "(MINUS") || !strcmp(ptr, "(IF")) {
		return 0;
	}
	else {
		for(int i = 0; i < funCount; i++) {
			if(!strcmp(ptr, defunName[i])) return 0;
		}
	}
	return 1;
}

int isWrongInput(char* buff) {

	char *temp = malloc(sizeof(char) * 100);
	strcpy(temp, buff);

	temp = replaceValue(temp, "MINUS", "M");
	temp = replaceValue(temp, "IF", "I");

    for(int i = 0; i < strlen(temp) -1; i++) {
        if(temp[i] != 'M' && temp[i] != 'I' && temp[i] != '1' && temp[i] != '2'
                && temp[i] != '3' && temp[i] != '4' && temp[i] != '5' && temp[i] != '6'
                && temp[i] != '7' && temp[i] != '8' && temp[i] != '9' && temp[i] != '0'
                && temp[i] != '-' && temp[i] != '\0' && temp[i] != ' ' && temp[i] != '(' && temp[i] != ')') {
            printf("syntax error\n");
            return 1;
        }
    }
    return 0;
}

int checkB(char *buff) {

	int steck[10];
	int tap = -1;

	for(int i = 0; i < strlen(buff); i++) {
		if(buff[i] == '(') steck[++tap] = i;
		else if(buff[i] == ')') {
			if(tap == -1) {
				printf("%d번째 \')\'의 위치가 잘못되었습니다.\n", i);
				return 1;
			}
			else {
				tap--;
			}
		}
	}
	while(tap != -1) {
		printf("%d번째 \'(\'의 위치가 잘못되었습니다.\n", steck[tap]);
		tap--;
		if(tap == -1) return 1;
	}
	return 0;
}

int isWrongWord(char *buff) {

	char* temp[100] = {};

	for(int i = 1; i < strlen(buff); i++) {
		int j = i - 1;
		if(buff[j] == '(') {
			if(buff[i] != 'I' && buff[i] != 'M') return 1;
		}
	}
	return 0;
}

int isDefined(char *buff) {

	char temp[100] = {};
	temp[0] = '(';
	for(int i = 1; i < strlen(buff); i++) {
		if(buff[i-1] == ' ') break;
		temp[i] = buff[i-1];
	}

	for(int i = 0; i < funCount; i++) {
		if(!strcmp(temp, defunName[i])) {
			return 1;
		}
	}

	return 0;
}

int isNoV(char *buff) {

	int openCount = 0;
	int count = 0;

	for(int i = 0; i < strlen(buff); i++) {
		if(buff[i] == '(') openCount++;
		else if(buff[i] == ')') break;
		else if(openCount != 0) {
			if(buff[i] != ' ') count++;
		}
	}

	if(count == 0) {
		return 1;
	}
	else return 0;
}

int isDoubleM(char *buff) {

	for(int i = 1; i < strlen(buff); i++) {
		int j = i - 1;
		if(buff[j] == '-' && buff[i] == '-') return 1;
	}
	return 0;
}
