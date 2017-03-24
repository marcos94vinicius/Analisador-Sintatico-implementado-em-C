#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 1000000
#define max2 5000
#define ID 0
#define PLUS 1
#define MULT 2
#define PLUSPLUS 3
#define LP 4
#define RP 5
#define dolar 6

void S(int tokens[max2], int *cont, int *erro);
void E(int tokens[max2], int *cont, int *erro);
void Elinha(int tokens[max2], int *cont, int *erro);
void T(int tokens[max2], int *cont, int *erro);
void Tlinha(int tokens[max2], int *cont, int *erro);
void F(int tokens[max2], int *cont, int *erro);
void P(int tokens[max2], int *cont, int *erro);

int help = 0;

char* converte(int num){

	if(num == ID)
		return("id ");
	else if(num == PLUS)
		return("+ ");
	else if(num == MULT)
		return("* ");
	else if(num == PLUSPLUS)
		return("++ ");
	else if(num == LP)
		return("( ");
	else if(num == RP)
		return(") ");
	else if(num == dolar)
		return("$ ");
	else
		return("");
}

char* converte2(int num){

	if(num == ID)
		return("id");
	else if(num == PLUS)
		return("+");
	else if(num == MULT)
		return("*");
	else if(num == PLUSPLUS)
		return("++");
	else if(num == LP)
		return("(");
	else if(num == RP)
		return(")");
	else if(num == dolar)
		return("$");
	else
		return("");
}

void eat(int token, int vt, int *cont, int *erro){

	if(*erro == 1)
		return;
	if(token == vt)
		*cont = *cont + 1;
	else{

		*erro = 1;
		printf("ERRO SINTATICO EM: %sESPERADO: %s", converte(token), converte2(vt));
	}
}

void sintatico(int tokens[max]){

	int cont = 0, erro = 0;
	S(tokens, &cont, &erro);
	if(erro == 0)
		//if(tokens[cont] == -1)
			printf("CADEIA ACEITA");
}

void S(int tokens[max2], int *cont, int *erro){

	if(*erro == 1)
		return;
	switch(tokens[*cont]){

		case ID :
		case LP :
			E(tokens, cont, erro);
			eat(tokens[*cont], dolar, cont, erro);
			break;
		default :
			printf("ERRO SINTATICO EM: %sESPERADO: id, (", converte(tokens[*cont]));
			*erro = 1;
	}
}

void E(int tokens[max2], int *cont, int *erro){

	if(*erro == 1)
		return;
	switch(tokens[*cont]){

		case ID :
		case LP :
			T(tokens, cont, erro);
			Elinha(tokens, cont, erro);
			break;
		default :
			printf("ERRO SINTATICO EM: %sESPERADO: id, (", converte(tokens[*cont]));
			*erro = 1;
	}
}

void Elinha(int tokens[max2], int *cont, int *erro){

	if(*erro == 1)
		return;
	switch(tokens[*cont]){

		case PLUS :
			eat(tokens[*cont], PLUS, cont, erro);
			T(tokens, cont, erro);
			Elinha(tokens, cont, erro);
			break;
		case RP:
		case dolar :
			break;
		default :
			printf("ERRO SINTATICO EM: %sESPERADO: +, ), $", converte(tokens[*cont]));
			*erro = 1;
	}
}

void T(int tokens[max2], int *cont, int *erro){

	if(*erro == 1)
		return;
	switch(tokens[*cont]){

		case ID :
		case LP :
			F(tokens, cont, erro);
			Tlinha(tokens, cont, erro);
			break;
		default :
			printf("ERRO SINTATICO EM: %sESPERADO: id, (", converte(tokens[*cont]));
			*erro = 1;
	}
}

void Tlinha(int tokens[max2], int *cont, int *erro){

	if(*erro == 1)
		return;
	switch(tokens[*cont]){

		case MULT :
			eat(tokens[*cont], MULT, cont, erro);
			F(tokens, cont, erro);
			Tlinha(tokens, cont, erro);
			break;
		case PLUS :
		case RP :
		case dolar :
			break;
		default :
			printf("ERRO SINTATICO EM: %sESPERADO: +, *, ), $", converte(tokens[*cont]));
			*erro = 1;
	}
}

void F(int tokens[max2], int *cont, int *erro){

	if(*erro == 1)
		return;
	switch(tokens[*cont]){

		case ID :
			eat(tokens[*cont], ID, cont, erro);
			P(tokens, cont, erro);
			break;
		case LP :
			eat(tokens[*cont], LP, cont, erro);
			E(tokens, cont, erro);
			eat(tokens[*cont], RP, cont, erro);
			P(tokens, cont, erro);
			break;
		default :
			printf("ERRO SINTATICO EM: %sESPERADO: id, (", converte(tokens[*cont]));
			*erro = 1;
	}
}

void P(int tokens[max2], int *cont, int *erro){

	if(*erro == 1)
		return;
	switch(tokens[*cont]){

		case PLUSPLUS :
			eat(tokens[*cont], PLUSPLUS, cont, erro);
			break;
		case PLUS :
		case MULT :
		case RP :
		case dolar :
			break;
		default :
			printf("ERRO SINTATICO EM: %sESPERADO: +, *, ++, ), $", converte(tokens[*cont]));
			*erro = 1;
	}
}

int main(){

	char entrada[max], aux[50];
	int tokens[max2];
	int i = 0, j = 0;
	
	while(scanf("%c", &entrada[i]) != -1)
		i++;
	entrada[i] = '\0';
	//printf("#%s#\n", entrada);
	i = 0;

	while(i <= strlen(entrada)){

		if(entrada[i] != '\n' && entrada[i] != '\0'){

			aux[0] = entrada[i];
			aux[1] = '\0';
			tokens[j] = atoi(aux);
			j++;
		}
		else{

			/*if(entrada[i+1] == '\n'){

				i++;
			}*/
			//else{

			tokens[j] = -1;
			j = 0;

			if(help == 1)
				printf("\n");
			sintatico(tokens);
			help = 1;
		}
		i++;
	}

	return 0;
}
