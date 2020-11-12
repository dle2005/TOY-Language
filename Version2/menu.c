#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "head.h"

extern char defunName[100][100];
extern int defunVNum[100];
extern char defunV[100][100];
extern char defunFunction[100][100];
extern int funCount;
extern FILE* flashfp;

char stack[100];
int top = -1;

int istack[100];
int itop = -1;

int caclulate(char *buff) {

	buff = replaceValue(buff, "MINUS", "M");
	buff = replaceValue(buff, "IF", "I");

	int j = 0;
	char temp[10] = {};
	for(int i = 0; i < strlen(buff); i++) {
		if(buff[i] == ' ') {}
		else if (buff[i] == 'M') {
			int y = ipop();
			int x = ipop();
			int result = x - y;
			ipush(result);
		}
		else if (buff[i] == 'I') {
			int y = ipop();
			int x = ipop();
			int result = 0;
			if(x >= 0) result = y;
			else result = 0;
			ipush(result);
		}
		else {
			if(buff[i+1] == ' ') {
				temp[j] = buff[i];
				j=0;
				ipush(atoi(temp));
				memset(temp, '\0', sizeof(temp));
			}
			else {
				temp[j] = buff[i];
				j++;
			}
		}

	}

	int lastResult = ipop();
	return lastResult;

}
void ipush(int value){
	stack[++itop]=value;
}

int ipop(){
	return stack[itop--];
}

void push(char value){
	stack[++top]=value;
}

char pop(){
	return stack[top--];
}

char* ptop(char *buff) {

	char ptop[100] = {};
	int j = 0;

	buff = replaceValue(buff, "MINUS", "M");
	buff = replaceValue(buff, "IF", "I");

	//printf("%s\n", buff);

	for(int i = 0; i < strlen(buff); i++) {
		if(buff[i] == 'M' || buff[i] == 'I') {
			push(buff[i]);
		}
		else if(buff[i] == ')') {
			ptop[j] = pop();
			j++;
			ptop[j] = ' ';
			j++;
		}
		else if(buff[i] == ' ') {}
		else if(buff[i] == '(') {}
		else {
			if(buff[i+1] == ' ' || buff[i+1] == ')') {
				ptop[j] = buff[i];
				j++;
				ptop[j] = ' ';
				j++;
			}
			else {
				ptop[j] = buff[i];
				j++;
			}
		}
	}

	char *result = malloc(sizeof(char) * 100);
	strcpy(result, ptop);

	result = replaceValue(result, "I", "IF");
	result = replaceValue(result, "M", "MINUS");

	top = -1;
	//printf("ptop: %s\n", result);
	return result;
}

char* changeDefun(char *buff) {

		char temp[100];
		strcpy(temp, buff);
//		printf("buff: %s\n", buff);
		int changeDefunNum = findDefun(temp);
//		printf("test: %d\n", changeDefunNum);
		if(changeDefunNum == -1) return buff;
		strcpy(temp, buff);
		char *changePart = findChange(temp, changeDefunNum);
//		printf("test: %s\n", changePart);
		changePart = trimChange(changePart);
//		printf("test: %s\n", changePart);
		char *changedPart = changedStr(changePart, changeDefunNum);
		char *result = replaceValue(buff, changePart, changedPart);
		return result;
}

char* changedStr(char *buff, int defunNum) {

	int variableNum = defunVNum[defunNum];
	char variable[variableNum][100];
	memset(variable, '\0', variableNum*100);
	char temp[100];
	strcpy(temp, buff);

	char *ptr = strtok(temp, " ");
	ptr = strtok(NULL, "\0");
	strcpy(temp,ptr);
	temp[strlen(temp)-1] = '\0';

	int count=0, i=0;
	int openCount = 0;
	int closeCount = 0;

	while(1) {
		if(i == strlen(temp)) break;
		if(temp[i] == '(') {
			int k = 0;
			for(int j = i; j < strlen(temp); j++, i++) {
				variable[count][k] = temp[j];
				k++;
				if(temp[j] == '(') openCount++;
				else if(temp[j] == ')') closeCount++;
				if(openCount == closeCount) {
					openCount = 0;
					closeCount = 0;
					count++;
					i++;
					break;
				}

			}
		}
		else if(temp[i] == ' ') i++;
		else {
			int k = 0;
			for(int j = i; j < strlen(temp); j++, i++) {
				if(temp[j] == ' ') {
					count++;
					break;
				}
				variable[count][k] = temp[j];
				k++;
			}
		}
	}

	int vCount = 0;
	char *savedChange = malloc(sizeof(char) * 100);
	char tempV[100];
	strcpy(savedChange, defunFunction[defunNum]);
	strcpy(tempV, defunV[defunNum]);
	char* str = strtok(tempV, " ");
	while(str != NULL) {
		savedChange = replaceValue(savedChange, str, variable[vCount]);
		str = strtok(NULL, " ");
		vCount++;
	}
	return savedChange;
}

char* trimChange(char *buff) {
	char temp[100];
	char *str = malloc(sizeof(char) * 100);
	int openCount = 1;
	int closeCount = 0;

	temp[0] = '(';
	for(int i = 1; i < strlen(buff); i++) {
		temp[i] = buff[i];
		if(buff[i] == '(') openCount++;
		else if(buff[i] == ')') closeCount++;
		if(openCount == closeCount) {
			temp[i+1] = '\0';
			break;
		}
	}
	strcpy(str, temp);
	return str;
}

char* findChange(char *buff, int num) {
	char *before = malloc(sizeof(char) * 100);
	char *ptr = strtok(buff, " ");
	while(ptr != NULL) {
		if(!strcmp(ptr, defunName[num])) {
			strcpy(before, ptr);
			strcat(before, " ");
			ptr = strtok(NULL, "\0");
			strcat(before, ptr);
			return before;
		}
		ptr = strtok(NULL, " ");
	}
	return NULL;
}

int findDefun(char *buff) {
	char temp[100];
	strcpy(temp, buff);
	char *ptr = strtok(temp, " ");
	while(ptr != NULL) {
		for(int i = 0; i < funCount; i++) {
			if(!strcmp(ptr, defunName[i])) return i;
		}
		ptr = strtok(NULL, " ");
	}

	return -1;
}

void print_menu() {
	printf("==================\n");
	printf("1. Define DEFUN\n");
	printf("2. Print DEFUN\n");
	printf("3. Interpreter\n");
	printf("4. Exit\n");
	printf("==================\n");
	printf("메뉴를 선택하세요>> ");
}

void loadDefun() {
	flashfp = fopen("defun.txt", "r");
	char buff[100];
	while(1) {
		if(fgets(buff, 100, flashfp) == NULL) break;
		buff[strlen(buff)-1] = '\0';
		saveDefun(buff);
	}
	fclose(flashfp);
}

void saveDefun(char *buff) {

	int openCount = 0;
	int j = 0;

	for(int i = 0; i < strlen(buff); i++) {
		if(buff[i] == '(') openCount++;
		else if(buff[i] == ')') break;
		else if(openCount != 0) {
			defunV[funCount][j] = buff[i];
			j++;
		}
	}

	char temp[100];
	strcpy(temp, buff);
	char *ptr;
	defunName[funCount][0] = '(';
	ptr = strtok(temp, " ");
	strncpy(defunName[funCount]+1, ptr, strlen(ptr));
	ptr = strtok(NULL, " ");
	int count = -1;
	while(strcmp(ptr,")")) {
		ptr = strtok(NULL, " ");
		count++;
	}
	defunVNum[funCount] = count;
	ptr = strtok(NULL, "\0");
	strcpy(defunFunction[funCount], ptr);
	funCount++;
}

char *replaceValue(char *strInput, const char *strTarget, const char *strChange) {
    char* strResult;
    char* strTemp;
    int i = 0;
    int nCount = 0;
    int nTargetLength = strlen(strTarget);
    if (nTargetLength < 1) return strInput;
    int nChangeLength = strlen(strChange);
    if (nChangeLength != nTargetLength) {
        for (i = 0; strInput[i] != '\0';) {
            if (memcmp(&strInput[i], strTarget, nTargetLength) == 0) {
                nCount++;
                i += nTargetLength;
            }
            else i++;
        }
    }
    else {
        i = strlen(strInput);
    }
    strResult = (char *) malloc(i + 1 + nCount * (nChangeLength - nTargetLength));
    if (strResult == NULL) return NULL;
    strTemp = strResult;
    while (*strInput) {
        if (memcmp(strInput, strTarget, nTargetLength) == 0) {
            memcpy(strTemp, strChange, nChangeLength);
            strTemp += nChangeLength;
            strInput  += nTargetLength;
        }
        else {
            *strTemp++ = *strInput++;
        }
    }
    *strTemp = '\0';
    return strResult;
}

void clear_stdin() {
    int ch;
    while((ch = getchar()) != EOF && ch != '\n') {};
}
