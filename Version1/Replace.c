#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ErrorCheck_3(char* str) {
    for(int i = 0; i < strlen(str) -1; i++) {
        if(str[i] != 'M' && str[i] != 'I' && str[i] != '1' && str[i] != '2'
                && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6'
                && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '0'
                && str[i] != '-' && str[i] != '\0' && str[i] != ' ') {
            printf("\nERROR\n\n");
            exit(0);
        }
    }
}

void ErrorCheck_2(char* str) {
    for(int i = 1; i < strlen(str); i++) {
       int j = i - 1;
       if(str[j] == '(') {
           if(str[i] != 'M' && str[i] != 'I') {
               printf("\nundefined\n\n");
               exit(0);
            }
       }
    }
}

void ErrorCheck(char* str) {
    int openCount = 0;
    int closeCount = 0;
    for(int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') openCount++;
        else if (str[i] == ')') closeCount++;
    }
    if(openCount > closeCount) printf("\n \"(\"의 위치가 잘못되었습니다.\n\n");
    else if(openCount < closeCount) printf("\n \")\"의 위치가 잘못되었습니다.\n\n");
}

char *replaceValue(char *strInput, const char *strTarget, const char *strChange)
{
    char* strResult;
    char* strTemp;
    int i = 0;
    int nCount = 0;
    int nTargetLength = strlen(strTarget);

    if (nTargetLength < 1)
        return strInput;

    int nChangeLength = strlen(strChange);

    if (nChangeLength != nTargetLength)
    {
        for (i = 0; strInput[i] != '\0';)
        {
            if (memcmp(&strInput[i], strTarget, nTargetLength) == 0)
            {
                nCount++;
                i += nTargetLength;
            }
            else i++;
        }
    }
    else
    {
        i = strlen(strInput);
    }

    strResult = (char *) malloc(i + 1 + nCount * (nChangeLength - nTargetLength));
    if (strResult == NULL) return NULL;


    strTemp = strResult;
    while (*strInput)
    {
        if (memcmp(strInput, strTarget, nTargetLength) == 0)
        {
            memcpy(strTemp, strChange, nChangeLength);
            strTemp += nChangeLength;
            strInput  += nTargetLength;
        }
        else
        {
            *strTemp++ = *strInput++;
        }
    }

    *strTemp = '\0';

    return strResult;
}

void Eliminate(char* str, char ch) {
    for (; *str != '\0'; str++) {
        if (*str == ch) {
            strcpy (str, str + 1);
            str--;
        }
    }
}

void EraseSpace(char a_string[]) {
    char temp[100];
    int index = 0;
    for(int i = 0; a_string[i] != 0; i++) {
        if(a_string[i] != ' ') {
            temp[index] = a_string[i];
            index++;
        }
    }
    temp[index] = 0;
    index = 0;
    for(int i = 0; temp[i] != 0; i++) {
        a_string[index] = temp[i];
        index++;
    }
    a_string[index] = 0;
}
