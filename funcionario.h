#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED
typedef struct {
    unsigned long int id;
    char matricula[10];
    char nome[100];
    char dataNascimento[12];
    char CPF[13];
    unsigned long int id_departamento;
    float salario;
    char rua[40];
    char bairro[30];
    unsigned int numero;
    char complemento [30];
    char cidade[40];
    char uf[4];
    char cep[10];
    char email[40];
}TFuncionario;
int pesquisaIdFunc(FILE *,int);
int pesquisaFunc(FILE *,char *);
void cadastroFunc(FILE *,FILE *);
void consultaFunc(FILE *,FILE *);
void listarFunc(FILE *);
void alteraFunc(FILE *,FILE *);
void alteraDepFunc(FILE *,FILE *);
void gerarFolhaPagamento(FILE *);
void alteraSalario(FILE *);
void histSalario(FILE *);


#endif