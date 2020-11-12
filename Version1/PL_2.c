#include <stdio.h>
#include <string.h>
#include "BinaryTree.c"
#include "Replace.c"
int option_1();
void option_2();
void clear_stdin() {
    int ch;
    while((ch = getchar()) != EOF && ch != '\n') {};
}

int main() {
    int input_menu;
    while(1) {
        printf("==================================\n");
        printf("1. File Load\n");
        printf("2. Interactive Mode\n");
        printf("3. Exit\n");
        printf("==================================\n");
        printf("메뉴를 선택하세요 >> ");
        scanf("%d", &input_menu);
        clear_stdin();
        if (input_menu == 1) 
            option_1();
        else if (input_menu == 2)
            option_2();
        else if (input_menu == 3)
            break;
        else 
            printf("\nERROR\n\n");
    }
    return 0;
}
int option_1() {

    char fileName[260], buffer[100];
    FILE *fp;
    char* changedStr;
    int count = 0, i = 0;
    int* result;

    printf("\n파일명을 입력하세요 >> ");
    scanf("%s", fileName);
    getchar();
    if((fp = fopen(fileName, "r")) == NULL) {
        printf("\nERROR\n\n");
        return 1;
    }
    printf("\n파일 내용은\n");
    printf("---------------------------------\n");

    while(1) {
        if(fgets(buffer, 100, fp) == NULL) break;
        fputs(buffer, stdout);
        count++;
    }

    printf("---------------------------------\n");
    printf("입니다.\n");

    treeNode* bt;
    result = malloc(sizeof(int) * count + 1);
    fseek(fp,0,SEEK_SET);
    while(1) {
        if(fgets(buffer, 100, fp) == NULL) break;
        changedStr = replaceValue(buffer, "MINUS", "M");
        changedStr = replaceValue(changedStr, "IF", "I");
        ErrorCheck(changedStr);
        EraseSpace(changedStr);
        ErrorCheck_2(changedStr);
        changedStr = replaceValue(changedStr, "(", " ");
        changedStr = replaceValue(changedStr, ")", " ");
        EraseSpace(changedStr);
        ErrorCheck_3(changedStr);
        for(int i = 1; i < strlen(changedStr); i++) {
            int j = i - 1;
            if(changedStr[i] == '-' && changedStr[j] == '-') {
                printf("ERROR\n");
                exit(0);
            }
        }
        
        bool MINUS = false;
        bt = makeTree(changedStr[0], NULL);
        for(int i = 0; changedStr[i+1] != 0; i++) {
            if(isOperator(changedStr[i+1])) {
                if(isLeftEmpty(bt)) {
                    LeftSubTree(bt, changedStr[i+1], false);
                    bt = GetLeft(bt);
                }
                else if(isRightEmpty(bt)) {
                    RightSubTree(bt, changedStr[i+1], false);
                    bt = GetRight(bt);
                }
            }
            else if(changedStr[i+1] == '-')
                MINUS = true;
            else {
                if(MINUS) {
                    if(isLeftEmpty(bt)) {
                        LeftSubTree(bt, changedStr[i+1], MINUS);
                        MINUS = false;
                    }
                    else if(isRightEmpty(bt)) {
                        RightSubTree(bt, changedStr[i+1], MINUS);
                        MINUS = false;
                        while(isChildPull(bt))
                            bt = GetParent(bt);
                    }
                }
                else {
                    if(isLeftEmpty(bt))
                        LeftSubTree(bt, changedStr[i+1], MINUS);
                    else if(isRightEmpty(bt)) {
                        RightSubTree(bt, changedStr[i+1], MINUS);
                        while(isChildPull(bt)) {
                            if(bt -> parent == NULL) break;
                            bt = GetParent(bt);
                        }
                    }
                }
            }
        }
        while(1) {
            if(isBothNumber(bt)) {
                if(bt -> parent != NULL) {
                    doOperate(bt);
                    bt = bt -> parent;
                }
                else doOperate(bt);
            }
            else if(isLeftNumber(bt)) bt = GetRight(bt);
            else if(isRightNumber(bt)) bt = GetLeft(bt);
            else if(isChildEmpty(bt)) break;
        }
        printf("\n결과 : ");
        if(bt -> MINUS) printf("-");
        printf("%c", bt -> data);
    }
    printf("\n\n");
}
void option_2() {

    char buffer[100];
    char *changedStr;

    printf("\n문장을 입력하세요.\n");
    printf("---------------------------------\n");
    fgets(buffer, 100, stdin);
    
    changedStr = replaceValue(buffer, "MINUS", "M");
    changedStr = replaceValue(changedStr, "IF", "I");
    ErrorCheck(changedStr);
    EraseSpace(changedStr);
    ErrorCheck_2(changedStr);
    changedStr = replaceValue(changedStr, "(", " ");
    changedStr = replaceValue(changedStr, ")", " ");
    EraseSpace(changedStr);
    ErrorCheck_3(changedStr);
    for(int i = 1; i < strlen(changedStr); i++) {
        int j = i - 1;
        if(changedStr[i] == '-' && changedStr[j] == '-') {
            printf("\nERROR\n\n");
            exit(0);
        }
    }   
    bool MINUS = false;
    treeNode* bt = makeTree(changedStr[0], NULL);
    for(int i = 0; changedStr[i+1] != 0; i++) {
        if(isOperator(changedStr[i+1])) {
            if(isLeftEmpty(bt)) {
                LeftSubTree(bt, changedStr[i+1], false);
                bt = GetLeft(bt);
            }
            else if(isRightEmpty(bt)) {
                RightSubTree(bt, changedStr[i+1], false);
                bt = GetRight(bt);
            }
        }
        else if(changedStr[i+1] == '-')
            MINUS = true;
        else {
            if(MINUS) {
               if(isLeftEmpty(bt)) {
                    LeftSubTree(bt, changedStr[i+1], MINUS);
                    MINUS = false;
                }
                else if(isRightEmpty(bt)) {
                    RightSubTree(bt, changedStr[i+1], MINUS);
                    MINUS = false;
                    while(isChildPull(bt))
                        bt = GetParent(bt);
                }
            }
            else {
                if(isLeftEmpty(bt))
                    LeftSubTree(bt, changedStr[i+1], MINUS);
                else if(isRightEmpty(bt)) {
                    RightSubTree(bt, changedStr[i+1], MINUS);
                    while(isChildPull(bt)) {
                        if(bt -> parent == NULL) break;
                        bt = GetParent(bt);
                    }
                }
            }
        }
    }
    while(1) {
        if(isBothNumber(bt)) {
            if(bt -> parent != NULL) {
                doOperate(bt);
                bt = bt -> parent;
            }
            else doOperate(bt);
        }
        else if(isLeftNumber(bt)) bt = GetRight(bt);
        else if(isRightNumber(bt)) bt = GetLeft(bt);
        else if(isChildEmpty(bt)) break;
    }
    printf("\n---------------------------------\n");
    printf("\n결과 : ");
    if(bt -> MINUS) printf("-");
    printf("%c\n\n", bt -> data);
    printf("---------------------------------\n");
}
