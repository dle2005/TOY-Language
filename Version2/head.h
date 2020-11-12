
#ifndef HEAD_H_
#define HEAD_H_

void print_menu();
void clear_stdin();
void loadDefun();
void saveDefun(char*);
char* findChange(char*, int);
int findDefun(char*);
char* trimChange(char*);
char* changeDefun(char*);
char* changedStr(char *buff, int defunNum);
int caclulate(char *buff);
void clear_stdin();
char* ptop(char *buff);
char *replaceValue(char *strInput, const char *strTarget, const char *strChange);

int isNoV(char *buff);
int isDefined(char *buff);
int isDoubleM(char *buff);
int isWrongWord(char *buff);
int checkB(char *buff);
int isWrongInput(char* buff);
int notDefinedDefun(char *buff);


void option_1();
void option_2();
void option_3();


#endif /* HEAD_H_ */
