#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 90
#define lin 15
#define col 7

struct cliente{
	char nome[20], preferencial[9];
	int dia, mes, ano, idade, cod, especial, ativo, fileira, colunanum;
};

int poltronas[lin][col] = {0};
char letrascolunas[] = {'A','B','C',' ','D','E','F'};
struct cliente c[max];
FILE *f;

void menu();
int cadastra();
int gravaArquivo();
int recuperaDado();
int mostraAviao();
int lerArquivo();
//int altera();

//int lerArquivo();

int main() {

	menu();
	getchar();	
	return 0;
}

void menu() {
	int op;
	system("cls");
	do {
		printf("1 - Cadastrar cliente\n2 - Alterar cliente");
		printf("\n3 - Excluir cliente\n4 - Verificar cliente");
		printf("\n5 - Listar clientes\n6 - Sair\n7 - Mostra matriz\n");
		scanf("%d", &op);
		getchar();
		switch (op){
			case 1:
				cadastra();
				gravaArquivo();
				recuperaDado();
			break;
			case 2:
				
			break;
			case 5:
				lerArquivo();
				getchar();
				//listar();
			break;
			case 7:
				mostraAviao();
			break;
		}	
	} while(op != 6);
}

int cadastra() {
	int i, opcao, dia, mes, ano, idade, cod, especial, ativo, fileira, fileirareal, continuar=0, colunanum;
	char nome[30], pref[9], coluna[2], letra;
	
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
		printf("\nAssento preferencial? 1 - SIM | 0 - NAO ");
		scanf("%d", &opcao);
		setbuf(stdin, NULL);
		if(opcao == 1) 
			especial = 1;
		else
			especial = 0;
		cod = dia + mes + ano;
		// coluna
		
		do {
			printf("\nColuna (A-F): ");
			scanf(" %c", &letra);
			coluna = toupper(coluna);
			for(i=0; i<col; i++) {
				if(letra == letrascolunas[i]) { //{'A','B','C',' ','D','E','F'};
					colunanum = i;
					break;
				}
			}
			
//		for(i=0; coluna[i] != '\0'; i++)
//			coluna[i] = toupper(coluna[i]);
//		setbuf(stdin, NULL);

			printf("\nFileira (1-15): ");
			scanf("%d", &fileirareal);
			fileira = fileirareal - 1;
			if((colunanum < 0 || colunanum > 6) || (fileira < 0 || > 14)) {
				printf("Essa poltrona nao existe! Escolha outra");
			} else {
				if(poltronas[fileira][colunanum] == 1) {
					printf("Esta poltrona esta ocupada! Escolha outra");
				} else {
						if(fileira == 1 || fileira == 2) {
							if(especial == 1) {
								poltronas[fileira][colunanum] = 1;
								continuar = 1;
							} else {
								printf("Esta poltrona e preferencial! Escolha outra");
							}
						}
						if(fileira == 7) {
							if(idade >= 18) {
								poltronas[fileira][colunanum] = 1;
								continuar = 1;
							} else {
								printf("Esta poltrona e para maiores de 18 anos! Escolha outra"); 
							}
						}
						if ((fileira > 2 && fileira < 7) || (fileira > 7 && fileira < 16)){
							poltronas[fileira][colunanum] = 1;
							continuar = 1;
						}
				}
			}
		} while(continuar == 0);
		setbuf(stdin, NULL);
		//guarda
		for(i=0; i<max; i++) {
			if(c[i].ativo==0) {
				strcpy(c[i].nome, nome);
				c[i].dia = dia;
				c[i].mes = mes;
				c[i].ano = ano;
				c[i].idade = idade;
				c[i].especial = especial;
				if(especial == 1)
					strcpy(c[i].preferencial,"Especial");
				else
					strcpy(c[i].preferencial,"Comum");
				c[i].cod = cod;
				c[i].fileira = fileira;
				c[i].colunanum = colunanum;
				c[i].ativo = 1;
				//strcpy(c[i].coluna, coluna);
				break;
			}
		}
		printf("\n1 - Cadastrar outro cliente\n0 - Sair\n");
		scanf("%d", &opcao);
		setbuf(stdin, NULL);
	} while(opcao!=0);
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
			fprintf(f,"%d", c[i].cod);
			fprintf(f,"%s",c[i].nome);
			fprintf(f,"%d/%d/%d",c[i].dia, c[i].mes, c[i].ano);
			fprintf(f,"%s", c[i].coluna);
			fprintf(f,"%d",c[i].fileira);
			fprintf(f,"%s", c[i].preferencial);
			fputc('\n', f);
		}
	}
	fclose(f);
}


int recuperaDado() {
	char nome[20], preferencial[9], coluna[2], letra;
	int idade, cod, fileira, i, j, dia, mes, ano, colunanum;
	char texto[1000];
	f = fopen("clientes2.txt", "r");
	if(f==NULL) {
		printf("Erro na abertura\n");
		return 0;
	} 
	while(1) {
		fscanf(f, "%d %[^0123456789\n] %d/%d/%d %s %d %s", &cod, nome, &dia, &mes, &ano, coluna, &fileira, preferencial);
		if (feof(f)) break;
		setbuf(stdin, NULL);
		//printf("%d %s%d/%d/%d %s %d %s", cod, nome, dia, mes, ano, coluna, fileira, preferencial);
		//printf("\n");
		letra = coluna[0];
		for(i=0;i<col;i++) {
			if(colunas[i] == letra) {
				colunanum = i;
			}
		}
		for(i=0;i<lin;i++){
			for(j=0;j<col;j++)
				poltronas[fileira-1][colunanum] = 1;
		}
	}
	fclose(f);
}

int lerArquivo() {
	char c, texto[3000];
	int i;
	f = fopen("clientes2.txt", "r");
	if(f==NULL) {
		printf("Erro na abertura\n");
		return 0;
	} 	
	i=0;
	while((c = fgetc(f)) != EOF) { //lendo o texto do arquivo
		texto[i] = c;	
		i++;
	}
	texto[i] = '\0'; 
	printf("%s", texto);
	fclose(f);
}

int mostraAviao() {
	int i, j;
	printf("A B C D E F\n");
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
}


//***********LE ARQUIVO*************


//int listar() {
//	int i;
//	for(i=0; i<max; i++) {
//		if(c[i].ativo == 1) {
//			printf("%d %s %d/%d/%d %s%d %s", c[i].cod, c[i].nome, c[i].dia, c[i].mes, c[i].ano, c[i].coluna, c[i].fileira, c[i].preferencial);
//			printf("\n");
//		}
//	}
//}


