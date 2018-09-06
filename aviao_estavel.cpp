#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 90
#define lin 15
#define col 7

struct cliente{
	char nome[30], preferencial[9];
	int dia, mes, ano, idade, cod, ativo, especial, fileira, colunanum;
};

int poltronas[lin][col] = {0};
char letrascolunas[] = {'A','B','C',' ','D','E','F'};
struct cliente c[max];
FILE *f;

void menu();
int cadastra();
int reserva(int *c, int *f, int idade, int especial);
int alteraCliente();
int excluirCliente();
int verificaCliente();
int listarClientes();
int gravaArquivo();
int mostraAviao();
int recuperaArquivo();

int main() {

	menu();
	getchar();	
	return 0;
}

void menu() {
	int op;
	do {
		system("cls");
		printf("1 - Cadastrar cliente\n2 - Alterar cliente");
		printf("\n3 - Excluir cliente\n4 - Verificar cliente");
		printf("\n5 - Listar clientes\n6 - Sair\n7 - Mostra matriz\n8 - Recuperar lista\n");
		scanf("%d", &op);
		getchar();
		switch (op){
			case 1:
				cadastra();
			break;
			case 2:
				alteraCliente();
			break;
			case 3:
				excluirCliente();
			break;
			case 4:
				verificaCliente();
			break;
			case 5:
				listarClientes();
			break;
			case 6:
				gravaArquivo();
			break;
			case 7:
				mostraAviao();
			break;
			case 8:
				recuperaArquivo();
			break;
		}	
	} while(op != 6);
}

int cadastra() {
	int i, j, opcao, dia, mes, ano, idade, cod, especial, ativo, fileira=0, fileirareal, colunanum=0;
	char nome[30], pref[9], coluna[2], letra;
	system("cls");
	do {
		printf("\nNome: ");
		scanf("%[^\n]", &nome);
		setbuf(stdin, NULL);
		printf("\nData de nascimento: ");
		printf("\nDia: ");
		scanf("%d", &dia);
		setbuf(stdin, NULL);
		printf("Mes: ");
		scanf("%d", &mes);
		setbuf(stdin, NULL);
		printf("Ano: ");
		scanf("%d", &ano);
		setbuf(stdin, NULL);
		idade = 2018 - ano;
		setbuf(stdin, NULL);
		printf("\nAssento preferencial? 1 - SIM | 0 - NAO ");
		scanf("%d", &opcao);
		setbuf(stdin, NULL);
		
		if(opcao == 1)
			especial = 1;
		else
			especial = 0;
			
		cod = dia + mes + ano;
		setbuf(stdin, NULL);
		// coluna
		
		reserva(&colunanum, &fileira, idade, especial);
		
		setbuf(stdin, NULL);
		//guarda
		for(i=0; i<max; i++) {
			if(c[i].ativo==0) {
				strcpy(c[i].nome, nome);
				c[i].dia = dia;
				c[i].mes = mes;
				c[i].ano = ano;
				c[i].idade = idade;
				if(especial == 1) {
					c[i].especial = 1;
					strcpy(c[i].preferencial,"Especial");
				} else {
					c[i].especial = 0;
					strcpy(c[i].preferencial,"Comum");
				}
				c[i].cod = cod;
				c[i].fileira = fileira;
				c[i].colunanum = colunanum;
				c[i].ativo = 1;
				setbuf(stdin, NULL);
				break;
			}
		}
		printf("\n1 - Cadastrar outro cliente\n0 - Sair\n");
		scanf("%d", &opcao);
		setbuf(stdin, NULL);
		system("cls");
	} while(opcao!=0);
}

int reserva(int *c, int *f, int idade, int especial) {
	char coluna[2], letra, continuar=0;
	int i, j;
	
	do {
		mostraAviao();
		printf("\nColuna (A-F): ");
		fgets(coluna, sizeof(coluna), stdin);
		setbuf(stdin, NULL);
		
		for(i=0; coluna[i] != '\0'; i++)
			coluna[i] = toupper(coluna[i]);
		
		(*c) = 9;
		setbuf(stdin, NULL);
		letra = coluna[0];
		setbuf(stdin, NULL);
		for(j=0;j<col;j++) {
			if(letrascolunas[j] == letra) {
				(*c) = j;
				break;
			}
		}
		
		printf("\nFileira (1-15): ");
		scanf("%d", &(*f));
		setbuf(stdin, NULL);

		if(((*c) < 0 || (*c) > 6) || ((*f) < 0 || (*f) > 15)) {
			printf("\nEssa poltrona nao existe! Escolha outra\n");
		} else {
			if(poltronas[(*f)-1][(*c)] == 1) {
				printf("\nEsta poltrona esta ocupada! Escolha outra\n");
			} else {
				if((*f) == 1 || (*f) == 2) {
					if(especial == 1) {
						poltronas[(*f)-1][(*c)] = 1;
						continuar = 1;
					} else {
						printf("\nEsta poltrona e preferencial! Escolha outra\n");
					}
				}
				if((*f) == 7) {
					if(idade >= 18) {
						poltronas[(*f)-1][(*c)] = 1;
						continuar = 1;
					} else {
						printf("\nEsta poltrona e para maiores de 18 anos! Escolha outra\n"); 
					}
				}
				if (((*f) > 2 && (*f) < 7) || ((*f) > 7 && (*f) < 16)){
					poltronas[(*f)-1][(*c)] = 1;
					continuar = 1;
				}
			}
		}
	} while(continuar == 0);
	mostraAviao();
	printf("\nPoltrona cadastrada com sucesso!\n");
}

int gravaArquivo() {
	int i;
	f = fopen("clientes.txt", "w+");
	if(f == NULL) {
		printf("Erro na abertura!");
		return 0;
	}
	for(i=0; i<max; i++) {
		if(c[i].ativo == 1) { //código, nome, data de nascimento e se tem prerrogativa de acessibilidade
			fprintf(f,"%d\n", c[i].cod);
			fprintf(f,"%s\n", c[i].nome);
			fprintf(f,"%d/%d/%d\n", c[i].dia, c[i].mes, c[i].ano);
			fprintf(f,"%c", letrascolunas[c[i].colunanum]);
			fprintf(f,"%d\n", c[i].fileira);
			fprintf(f,"%s\n", c[i].preferencial);
			fputc('\n', f);
		}
	}
	fclose(f);
}

int procuraCliente() {
	char pesq[30];
	int i;
	system("cls");
	printf("Nome do cliente: ");
	gets(pesq);
	setbuf(stdin, NULL);
	for(i=0; i<max; i++) {
		if(strcmp(c[i].nome, pesq) == 0) {
			printf("Dado disponivel!\n");
			getchar();
			system("cls");
			return i;
		}
	}
	return max+1;
}

int alteraCliente() {
	int posicao, i, dia, mes, ano, colunanum, fileira;
	char op, nome[20], opcao, letra;
	posicao = procuraCliente();
	if(posicao == max+1) {
		printf("Dado indisponivel!");
		getchar();
		system("cls");
		return 0;
	}
	system("cls");
	do {
		printf("Alterar Cadastro");
		printf("\n1 - Nome\n2 - Data de nascimento\n3 - Acessibilidade\n4 - Poltrona\n5 - Voltar\n");
		scanf("%d", &op);
		setbuf(stdin, NULL);
		switch (op){
			case 1:
				printf("Novo nome: ");
				scanf("%[^\n]", nome);
				setbuf(stdin, NULL);
				strcpy(c[posicao].nome, nome);
				printf("Alterado com sucesso!");
				getchar();
				system("cls");
			break;
			case 2:
				printf("Novo dia: ");
				scanf("%d", &dia);
				setbuf(stdin, NULL);
				printf("Novo mes: ");
				scanf("%d", &mes);
				setbuf(stdin, NULL);
				printf("Novo ano: ");
				scanf("%d", &ano);
				setbuf(stdin, NULL);
				c[posicao].dia = dia;
				c[posicao].mes = mes;
				c[posicao].ano = ano;
				printf("Alterado com sucesso!");
				getchar();
				system("cls");
			break;
			case 3:
				printf("Poltrona preferencial? <1 SIM / 0 NAO> ");
				scanf("%d", &opcao);
				setbuf(stdin, NULL);
				if(opcao == 1)
					strcpy(c[posicao].preferencial,"Especial");
				else
					strcpy(c[posicao].preferencial,"Comum");
				printf("Alterado com sucesso!");
				getchar();
				system("cls");
			break;
			case 4: 
				printf("Poltrona: %c%d", letrascolunas[c[posicao].colunanum], c[posicao].fileira);
				getchar();
				poltronas[(c[posicao].fileira-1)][(c[posicao].colunanum)] = 0;
				reserva(&c[posicao].colunanum, &c[posicao].fileira, c[posicao].idade, c[posicao].especial);
				printf("Alterado com sucesso!");
				system("cls");
			break;
		}	
	} while(op != 5);
	system("cls");
}

int excluirCliente() {
	int i, j;
	char posicao = procuraCliente();
	if(posicao == max+1) {
		printf("Dado indisponivel!\n");
		getchar();
		system("cls");
		return 0;
	}
	c[posicao].ativo = 0;
	poltronas[(c[posicao].fileira-1)][(c[posicao].colunanum)] = 0;
	
	printf("Dado removido!");
	getchar();
	system("cls");
}

int verificaCliente() {
	int i;
	char posicao = procuraCliente();
	if(posicao == max+1) {
		printf("Dado indisponivel!");
		getchar();
		system("cls");
		return 0;
	}
	printf("%d %s %d/%d/%d %c%d %s", c[posicao].cod, c[posicao].nome, c[posicao].dia, c[posicao].mes, c[posicao].ano, letrascolunas[c[posicao].colunanum], c[posicao].fileira, c[posicao].preferencial);
	getchar();
	system("cls");
}

int recuperaArquivo() {
	char nome[20], poltrona[9], letra, letra2, comum[6] = "Comum", especial[9] = "Especial";
	int i, j, dia, mes, ano, idade, cod, ativo, fileira, colunanum;
	
	f = fopen("clientes.txt", "r");
	if(f == NULL) {
		printf("Erro na abertura!");
		return 0;
	}
	for(i=0; i<max; i++) {
		if(c[i].ativo == 0) {
			if (feof(f)) break;
			fscanf(f, "%d\n", &cod);
			setbuf(stdin, NULL);
			fscanf(f, "%[^0123456789\n]", nome);
			setbuf(stdin, NULL);
			fscanf(f, "%d/%d/%d\n", &dia, &mes, &ano);
			setbuf(stdin, NULL);
			fscanf(f, "%c%d\n", &letra, &fileira);
			setbuf(stdin, NULL);
			fscanf(f, "%s\n", poltrona);
			setbuf(stdin, NULL);
			
			for(j=0;j<col;j++) {
				if(letrascolunas[j] == letra) {
					colunanum = j;
					break;
				}
			}
			c[i].cod = cod;
			strcpy(c[i].nome, nome);
			c[i].dia = dia;
			c[i].mes = mes;
			c[i].ano = ano;
			c[i].colunanum = colunanum;
			c[i].fileira = fileira;
			strcpy(c[i].preferencial, poltrona);
			if (strcmp(poltrona, comum) == 0) 
				c[i].especial = 0;
			else
				c[i].especial = 1;
			c[i].ativo = 1;
			poltronas[fileira-1][colunanum] = 1;
		}
	}
	fclose(f);
	printf("Dados recuperados!");
	getchar();
	system("cls");
}

int listarClientes() {
	int i;
	system("cls");
	for(i=0; i<max; i++) {
		if(c[i].ativo == 1) {
			printf("%d %s %d/%d/%d %c%d %s", c[i].cod, c[i].nome, c[i].dia, c[i].mes, c[i].ano, letrascolunas[c[i].colunanum], c[i].fileira, c[i].preferencial);
			printf("\n");
		}
	}
	getchar();
	system("cls");
}

int mostraAviao() {
	int i, j;
	system("cls");
	printf("   A B C     D E F\n");
	for(i=0; i<lin; i++) {
		printf("%02d ", i+1);
		for(j=0; j<col; j++) {
			if(j == 3) 
				printf("[ ] ");
			else {
				printf("%d ", poltronas[i][j]);
			}
		}
		printf("\n");
	}
	printf("\nFILEIRAS 1 E 2: PREFERENCIAL\nFILEIRA 7: PARA MAIORES DE 18 ANOS.\n");
}
