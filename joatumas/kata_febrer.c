#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Adds n letters to the end of a string
int add_letter(char letter, char *out_str, int n){
	int len = strlen(out_str);
	int i;
	for(i = 0; i<n; i++)
		out_str[len+i] = letter;
	out_str[len + i] = 0;
	return(len + i);
}

int numeral_to_roman(int num, char *str_out){
	int i;
	char symbols[7] = {'M','D', 'C', 'L', 'X', 'V', 'I'};
	int symbols_num[7] = {1000, 500, 100, 50, 10, 5, 1};
	int divided_num[7];
	//First, divide out the number into interesting divisors:
	divided_num[0] = num/symbols_num[0];
	for(i=1; i<7; i++){
		divided_num[i] = (num % symbols_num[i-1])/symbols_num[i];
	}
	//Begin adding letters to the end of the string:
	add_letter(symbols[0], str_out, divided_num[0]);
	for(i=1; i<7; i = i+2){
		if(divided_num[i+1] == 4){
			add_letter(symbols[i+1], str_out, 1);
			if(divided_num[i])
				add_letter(symbols[i-1], str_out, 1);
			else
				add_letter(symbols[i], str_out, 1);
			divided_num[i] = divided_num[i+1] = 0;
		}
		add_letter(symbols[i], str_out, divided_num[i]);
		add_letter(symbols[i+1], str_out, divided_num[i+1]);
	}
	return(0);
}

int roman_to_numeral(char *roman){
	int res=0, i, aux, aux_ant=0;
	int len = strlen(roman);
	for(i=len; i--;){
		switch(roman[i]){
			case 'I':
				aux = 1;
				break;
			case 'V':
				aux = 5;
				break;
			case 'X':
				aux = 10;
				break;
			case 'L':
				aux = 50;
				break;
			case 'C':
				aux = 100;
				break;
			case 'D':
				aux = 500;
				break;
			case 'M':
				aux = 1000;
				break;
			default:
				break;
		}
		if(aux_ant>aux)
			aux = -aux;
		else
			aux_ant = aux;
		res += aux;
	}
	return(res);
}

int main(int argc, char **argv){
	int num;
	char str_out[20];
	str_out[0] = 0;
	if(argc != 3){
		fprintf(stderr,"ERROR: Wrong arg numbers\n\tUSAGE: %s [r,n] number\n", argv[0]);
		exit(-1);
	}
	if(argv[1][0] == 'n'){
		num = atoi(argv[2]);
		if(num<0){
			fprintf(stderr,"ERROR: Please, insert a positive number\n");
			exit(-1);
		}else if(num>3000){
			fprintf(stderr,"ERROR: Please, do NOT exceed the number 3000\n");
			exit(-1);
		}
		numeral_to_roman(num, str_out);
		printf("%s\n", str_out);
	}else if(argv[1][0] == 'r'){
		num = roman_to_numeral(argv[2]);
		printf("%d\n", num);
	}else{
		fprintf(stderr,"ERROR: Wrong arg numbers\n\tUSAGE: %s [r,n] number\n", argv[0]);
	}	
	exit(0);
}
