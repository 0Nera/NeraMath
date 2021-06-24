#include <stdio.h>
#include <string.h>
#include "messages.h"

void process_op(char op, int *x, int *y) {
	if (op == '+') {
		*x += *y; *y = 0;
	} else if (op == '-') {
		*x -= *y; *y = 0;
	} else if (op == '*') {
		*x *= *y; *y = 0;
	} else if (op == '/') {
		if (*x != 0 || *y != 0) {
			*x /= *y; *y = 0;
		} else {
			printf("%s\n",ZERO_DIVISION);
		}
	}
}

int eval_expr(char *inp){
	
	int size, i, x = 0, y = 0;
	
	char op = '+';
	//Узнаем размер массива
	size = strlen(inp); // strlen посчитает столько там ЕСТЬ символов сейчас
	//Парсинг строк
	for (i = 0; i < size; i++){
		char c = inp[i];
		// если встретили знак операции
		if (c == '+' || c == '-' || c == '*' || c == '/'){
			// обрабатываем прошлую операцию
			process_op(op, &x, &y);
			op = c; // запоминаем новую операцию
		} else if (c == '\n' || c == '\t' || c == '\a' || c == ' '){
			printf("%s '%c'\n", INVALID_CHARACTER, inp[i]);
		} else {
			y= y*10 + (c - '0');
			printf("y = %d\n", y);
		}
	}
	process_op(op, &x, &y);
	
	return x;
}

/// TODO
// Чтение кода из файла

int main(int argc, char *argv[]){
	printf("Argc = %d, argv[1] = %s\n", argc, argv[1]);
	//Входные данные
	char input_text[255];
	
	//Сигнал выхода
	int exit_signal = 0;
	
	printf("%s", info);
	printf("%s", help);
	if(argc == 2){
		exit_signal = 1;
		FILE *fin;
		char file_str[255];
		char *estr;
		fin = fopen (argv[1],"r");
		if (fin == NULL) {
			printf("%s1\n",FILE_READ_ERROR); return -1;
		} else{
			while (1){
				// Чтение одной строки  из файла
				estr = fgets (file_str,sizeof(file_str),fin);
				if (estr == NULL){
					if ( feof (fin) != 0){
						printf("done");
						break;
					} else {
						printf("%s2\n",FILE_READ_ERROR);
						break;
					}
				}
				printf("\nResult: %d\n", eval_expr(file_str));
			}
			if ( fclose (fin) == EOF) {
				printf ("%s3\n",FILE_READ_ERROR);
			}else{
				return 0;
			}
		}
	}else{
		while (exit_signal == 0){
			printf("\n > ");
			scanf("%s", input_text);
			
			//Выход из программы
			if (input_text[0] == 'e'){
				exit_signal =  1;
			} else if (input_text[0] == '?'){ 
				//Справка
				printf("%s", info);
				printf("%s", help);
			} else {
				printf("\nResult: %d\n", eval_expr(input_text));
			}
		}
	}
	
	return 0;
}