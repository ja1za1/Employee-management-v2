#ifndef DEPARTAMENTO_H_INCLUDED
#define DEPARTAMENTO_H_INCLUDED
typedef struct{
    unsigned long int id;
    unsigned short int cod;
    char nome[40];
    unsigned long int id_gerente;
    char sigla[10];
    unsigned short int ramal;
}TDepartamento;

int pesquisaDep(FILE *,int);
int pesquisaIdDep(FILE *,int);
void cadastroDep(FILE *,FILE *);
void listarDep(FILE *);
void alteraGerente(FILE *,FILE *);
void relatorioFunc(FILE *,FILE *); 
void gerentesDep(FILE *,FILE *);

#endif //DEPARTAMENTO_H_INCLUDED
