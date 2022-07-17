#ifndef HISTORICOS_H_INCLUDED
#define HISTORICOS_H_INCLUDED

typedef struct{
    unsigned long int id_funcionario;
    unsigned long int id_departamento;
    char data[12];

}HistoricoFuncionario;

typedef struct{
    unsigned long int id_departamento;
    unsigned long int id_gerente;
    char data[12];
}HistoricoDepartamento;

typedef struct{
    unsigned long int id_funcionario;
    float salario;
    unsigned short int mes;
    unsigned short int ano;

}HistoricoSalario;

#endif