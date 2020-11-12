#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "head.h"


char defunName[100][100];
int defunVNum[100];
char defunV[100][100];
char defunFunction[100][100];
int funCount = 0;

FILE *flashfp;


int main(void) {
	loadDefun();
	char input_menu;

	while(1) {
		print_menu();
		fflush(stdout);
		input_menu = getchar();
		fseek(stdin,0,SEEK_END);
		switch(input_menu){
		    case '1' :
		    	option_1();
		    	break;
		    case '2' :
		        option_2();
		        break;
		    case '3' :
		    	option_3();
		    	break;
		    case '4' :
		    	exit(1);
		}
	}

	return 0;
}
