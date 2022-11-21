#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#define DATA_ "C:\\Ling_C\\clientes.txt"

 
void ERRO(int code, char *msg) {
  puts(msg);
  exit(code);
}

struct Reg
{
  char nome[20];
  char tel[20];
  char email[30];
};

struct Reg regs[100];
int qtdRegs = -1;

FILE *FILE_REGS;

/* 
 * na primeira linha é a quantidade de registros
 * na proxima os registros
 * */

void removerPorId() {
  int id;

  printf("Digite o id a ser removido: \n");
  scanf("%d", &id);

  id--;

  /* 0 pedro */
  /* 1 marcos */
  /* 2 maria */

  if( id < 0 && id > qtdRegs) {
    ERRO(0, "ID não encontrado");
  }


  if(qtdRegs > 99) {
    return;
  }


  int i; 
  /* Ineficiente deveria usar o endereço de memoria */

  printf("NUMERO DO ID %d: " , id );

  for( i = id; i < qtdRegs -1; i++ ) {
    regs[i] = regs[i+1];
  }

  qtdRegs--;
}

void readRegs() {
  FILE_REGS = fopen(DATA_, "r");

  if(FILE_REGS == NULL) {
    puts("Não tem arquivo de registro");
    return;
  }

  fscanf(FILE_REGS, "%d", &qtdRegs);

  if(qtdRegs < 0 || qtdRegs > 100) {
    ERRO(1, "Quantidade de registros incompativel");
  }
  int i;

  for(i = 0; i < qtdRegs; i++) {
    fscanf(FILE_REGS, "\n%[^;];%[^;];%[^;];", regs[i].nome, regs[i].tel, regs[i].email);
  }

  fclose(FILE_REGS);
}
void writeRegs() {

  if(qtdRegs < 0 || qtdRegs > 100) {
    ERRO(1, "\nQuantidade de registros imcompatível!!!\n");
  }

  FILE_REGS = fopen(DATA_, "w");

  if(FILE_REGS == NULL) {
    ERRO(1, "\nErro ao escrever arquivo\n");
  }

  fprintf(FILE_REGS, "%d", qtdRegs);

  int i;
  for( i = 0; i < qtdRegs; i++) {
    fprintf(FILE_REGS, "\nNome:%s\t Telefone:%s\t Email%s\t", regs[i].nome, regs[i].tel, regs[i].email);
  }

  printf("\nSucesso!!! %d cadastrados\n", qtdRegs); 

  fclose(FILE_REGS);
}

void removeRegs() {

  getchar();
  printf("Confirmar digite s :\n");
  char s = getchar();

  if ( s != 's' ) { return; }

  if(remove(DATA_) == -1) {
    ERRO(-1, "Erro ao remover arquivo");
  };
}

void print_Reg(struct Reg r) {
  printf("Nome: %s\n", r.nome);
  printf("Tel: %s\n", r.tel);
  printf("Email: %s\n", r.email);
}

void cadastrar()
{ 

  if(qtdRegs == -1)
   { qtdRegs = 1; }
    else { qtdRegs++; }

  printf("Cadastrando Registro %d:", qtdRegs);
   /*
  printf("Cadastrando novo Registro:\n");
  */
  printf("\nNome............: ");
  scanf("%s",regs[qtdRegs -1].nome);
  printf("\nTelefone.........: ");
  scanf("%s",regs[qtdRegs -1].tel);
  printf("\ne-mail...........: ");
  scanf("%s",regs[qtdRegs -1].email);

}

void consultarTodos() {
  int i;
  for (i = 0; i < qtdRegs; i++) {
    printf("\nID: %d\n", i+1);
    print_Reg(regs[i]);
  }
}

void consultaPorId() {
  int id;

  puts("Digite o id:");

  scanf("%d", &id);
  id--;

  if( id > qtdRegs || id < 0) {
    ERRO(0, "Não encontrado\n");
  }
  print_Reg(regs[id]);
}


int main()
{
  
	setlocale(LC_ALL, "Portuguese");
  int op;

  readRegs();

   FILE *arq;
   
   if  ((arq=fopen("C:\\Ling_C\\clientes.dat","rb+"))==NULL)
   {
   	if((arq=fopen("C:\\Ling_C\\clientes.dat","wb+"))==NULL)
   	{
   	     printf("Falha ao abrir o arquivo!\n");
		   system("pause");
	}
   }


  do
  {
    printf("==========Design Sobrancelha==========\n");
    printf("1 Cadastrar\n");
    printf("2 Consultar\n");
    printf("3 Gerar arquivo\n");
    printf("4 Remover arquivo\n");
    printf("5 consulta por id\n");
    printf("6 Remover por id\n");
    printf("7 Sair\n");
    
    printf("Opcao:");
    scanf("%d", &op);
    
    switch (op)
    {
      case 1: /*cadastrar novo contato*/
        cadastrar();
        break;
      case 2: /*consultar contato por código*/
        consultarTodos();
        break;
      case 3: /*gera arquivo txt com todos os contatos*/
        writeRegs();
        break;
      case 4:
        removeRegs();
        break;
      case 5:
        consultaPorId();
        break;
      case 6:
        removerPorId();
        break;
    }
  } while (op != 7);
}



