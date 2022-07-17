#include <stdio.h>
#include <stdlib.h>
#include "departamento.h"
#include "funcionario.h"
#include "funcoes.h"
#include "historicos.h"

int pesquisaIdDep(FILE *arqDep,int id){
    int posicao = 0;
    TDepartamento reg;
    fseek(arqDep,0,SEEK_SET);
    while(fread(&reg,sizeof(TDepartamento),1,arqDep)==1){
        if(reg.id == id){
            return posicao;
        }
        else{
            posicao++;
        }
    }
    return -1;
}

void listarDep(FILE *arqDep){
    TDepartamento LD;
    fseek(arqDep,0,SEEK_END);
    if(ftell(arqDep)>0){
        printf("\n-------- Departamentos Existentes --------\n");
        fseek(arqDep,0,SEEK_SET);
        while(fread(&LD,sizeof(TDepartamento),1,arqDep)==1){
            printf("\n\nID = %lu",LD.id);
            printf("\nCodigo = %d",LD.cod);
            printf("\nNome = %s",LD.nome);
            printf("\nID do gerente = %lu",LD.id_gerente);
            printf("\nSigla = %s",LD.sigla);
            printf("\nRamal = %d",LD.ramal);
        }
        
    }
    else{
        printf("\nNenhum departamento cadastrado!!!");
    }
    printf("\n\nAperte ENTER para continuar...");
    setbuf(stdin,NULL);
    getchar();
    setbuf(stdin,NULL);
}

int pesquisaDep(FILE *arqDep,int cod){
    int posicao = 0;
    TDepartamento reg;
    fseek(arqDep,0,SEEK_SET);
    while(fread(&reg,sizeof(TDepartamento),1,arqDep)==1){
        if(reg.cod == cod){
            return posicao;
        }
        else{
            posicao++;
        }
    }
    return -1;
}

void cadastroDep(FILE *arqDep,FILE *arqFunc){
    FILE *historicoDepartamento;
    TDepartamento regDep, ID;
    TFuncionario funcionarios;
    HistoricoDepartamento histDep;
    int sair,cod,achou;
    char ramal[6];

    do{
        printf("\n------------ Cadastro de Departamento ------------\n");
        printf("\nCódigo do departamento: ");
        scanf("%d",&cod);

        if(pesquisaDep(arqDep,cod)==-1){
            fseek(arqDep,0,SEEK_END);
            if(ftell(arqDep)>0){
                fseek(arqDep,0,SEEK_SET);
                while(fread(&ID,sizeof(TDepartamento),1,arqDep)==1){
                        ;
                }
            }
            else{
                ID.id = 0;
            }
            regDep.id = ++(ID.id);
            regDep.cod = cod;
            printf("\nDigite o nome do departamento: ");
            setbuf(stdin,NULL);
            fgets(regDep.nome,40,stdin);
            setbuf(stdin,NULL);
            while(verificaVazio(regDep.nome)==1){
                printf("\nNão é permitido nome vazio ou com espaço no início!!\n\nDigite um nome válido: ");
                setbuf(stdin,NULL);
                fgets(regDep.nome,40,stdin);
                setbuf(stdin,NULL);
            }
            retiraEnter(regDep.nome);
            
            fseek(arqFunc,0,SEEK_END);
            if(ftell(arqFunc)>0){
                do{
                    
                    rewind(arqFunc);
                    printf("\nID\tNome Funcionário\n");

                    while(fread(&funcionarios,sizeof(TFuncionario),1,arqFunc)==1){
                        printf("\n%lu\t%s\n",funcionarios.id,funcionarios.nome);
                    }
                
                    printf("\n\nForneça o ID do gerente: ");
                    scanf("%ld",&regDep.id_gerente);
                    
                    achou = pesquisaIdFunc(arqFunc,regDep.id_gerente);
                    if(achou==-1)
                        printf("\nID de funcionário inexistente!!!\n\n");
                }while(achou==-1);
            }
            else{
                printf("\nID do gerente = 0 pois não há funcionários cadastrados\n");
                regDep.id_gerente = 0;
            }
        
            printf("\nDigite a sigla do departamento: ");
            setbuf(stdin,NULL);
            fgets(regDep.sigla,10,stdin);
            while(verificaVazio(regDep.sigla)==1){
                printf("\nNão é permitido sigla vazia ou com espaço no início!!\n\nDigite uma sigla válida: ");
                setbuf(stdin,NULL);
                fgets(regDep.sigla,10,stdin);
                setbuf(stdin,NULL);
            }
            retiraEnter(regDep.sigla);
            setbuf(stdin,NULL);
            printf("\nOBS: Digite números de até 4 digitos\n");
            printf("\nDigite o ramal do departamento: ");
            setbuf(stdin,NULL);
            fgets(ramal,6,stdin);
            setbuf(stdin,NULL);
            retiraEnter(ramal);
            while(apenasNumero(ramal)==1){
                printf("\nNão é permitido letras no campo ramal!!\n\nDigite apenas números: ");
                setbuf(stdin,NULL);
                fgets(ramal,6,stdin);
                setbuf(stdin,NULL);
            }
            regDep.ramal = atoi(ramal);
            fseek(arqDep,0,SEEK_END);
            fwrite(&regDep,sizeof(TDepartamento),1,arqDep);

            historicoDepartamento=fopen("historicoDepartamento.dat","rb+");
                if(!historicoDepartamento)
                    historicoDepartamento=fopen("historicoDepartamento.dat","wb+");

                histDep.id_departamento = regDep.id;
                histDep.id_gerente = regDep.id_gerente;
                printf("\nDigite a data desse registro(dd/mm/aaaa): ");
                setbuf(stdin,NULL);
                fgets(histDep.data,12,stdin);
                setbuf(stdin,NULL);
                retiraEnter(histDep.data);
                while(verificaData(histDep.data)==1){
                    printf("\nData inválida!!!\n\nDigite uma data válida(dd/mm/aaaa): ");
                    setbuf(stdin,NULL);
                    fgets(histDep.data,12,stdin);
                    retiraEnter(histDep.data);
                    setbuf(stdin,NULL);
                }
                retiraBarra(histDep.data);
                fseek(historicoDepartamento,0,SEEK_END);
                fwrite(&histDep,sizeof(HistoricoDepartamento),1,historicoDepartamento);
                fclose(historicoDepartamento);
        }
        else{
            printf("\nCódigo Repetido!!!");
        }

        printf("\n\nDeseja sair do Cadastro de Departamento?\n1- Sim 2- Não ");
        scanf("%d",&sair);
    }while(sair != 1);

}

void alteraGerente(FILE *arqDep,FILE *arqFunc){
    FILE *historicoDepartamento;
    int sair,ID,achou,posicao;
    TFuncionario funcionarios;
    TDepartamento altGer;
    HistoricoDepartamento histDep;

    fseek(arqDep,0,SEEK_END);
    if(ftell(arqDep) > 0){
        if(ftell(arqFunc)>0){
            do{
                printf("\nDigite o ID do departamento para alterar o ID de gerente: ");
                scanf("%d",&ID);
                posicao = pesquisaIdDep(arqDep,ID);
                if(posicao !=-1){
                    fseek(arqDep,posicao*sizeof(TDepartamento),SEEK_SET);
                    fread(&altGer,sizeof(TDepartamento),1,arqDep);
                    do{
                        rewind(arqFunc);
                        printf("\nFuncionários Cadastrados\n");
                        printf("\nID\tNome Funcionário\n");

                        while(fread(&funcionarios,sizeof(TFuncionario),1,arqFunc)==1){
                            printf("\n%lu\t%s\n",funcionarios.id,funcionarios.nome);
                        }
                            printf("\n\nForneça o ID do gerente: ");
                            scanf("%ld",&altGer.id_gerente);

                            achou = pesquisaIdFunc(arqFunc,altGer.id_gerente);
                            if(achou==-1)
                                printf("\nID de funcionário inexistente!!!\n\n");
                    }while(achou == -1);
                    fseek(arqDep,posicao*sizeof(TDepartamento),SEEK_SET);
                    fwrite(&altGer,sizeof(TDepartamento),1,arqDep);

                    historicoDepartamento=fopen("historicoDepartamento.dat","rb+");
                    if(!historicoDepartamento)
                        historicoDepartamento=fopen("historicoDepartamento.dat","wb+");

                    histDep.id_departamento = altGer.id;
                    histDep.id_gerente = altGer.id_gerente;
                    printf("\nDigite a data dessa alteração(dd/mm/aaaa): ");
                    setbuf(stdin,NULL);
                    fgets(histDep.data,12,stdin);
                    setbuf(stdin,NULL);
                    retiraEnter(histDep.data);
                    while(verificaData(histDep.data)==1){
                        printf("\nData inválida!!!\n\nDigite uma data válida(dd/mm/aaaa): ");
                        setbuf(stdin,NULL);
                        fgets(histDep.data,12,stdin);
                        retiraEnter(histDep.data);
                        setbuf(stdin,NULL);
                    }
                    retiraBarra(histDep.data);
                    fseek(historicoDepartamento,0,SEEK_END);
                    fwrite(&histDep,sizeof(HistoricoDepartamento),1,historicoDepartamento);
                    fclose(historicoDepartamento);
                }
                else{
                    printf("\nNão há departamento com esse ID!!!");
                }
                printf("\nDeseja sair da alteração de gerente de um departamento?\n1- Sim 2- Não ");
                scanf("%d",&sair);
            }while(sair != 1);
        }
        else{
            printf("\nNenhum Funcionário cadastrado!!!");
            printf("\n\nAperte ENTER para continuar...");
            setbuf(stdin,NULL);
            getchar();
            setbuf(stdin,NULL);
        }
    }
    else{
        printf("\nNenhum Departamento cadastrado!!!");
        printf("\n\nAperte ENTER para continuar...");
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}

void relatorioFunc(FILE *arqFunc,FILE *arqDep){
    int sair;
    float totalSalario=0;
    TFuncionario func;
    TDepartamento dep;

    fseek(arqDep,0,SEEK_END);
    fseek(arqFunc,0,SEEK_END);
    if(ftell(arqDep)>0){
        if(ftell(arqFunc)>0){
            do{
                fseek(arqDep,0,SEEK_SET);
                while(fread(&dep,sizeof(TDepartamento),1,arqDep)==1){
                    fseek(arqFunc,0,SEEK_SET);
                    printf("\n\nCódigo departamento: %d",dep.cod);
                    printf("\nNome Departamento: %s",dep.nome);
                    printf("\n\nMatrícula\tNome\tSalário");
                    while(fread(&func,sizeof(TFuncionario),1,arqFunc)==1){
                        if(func.id_departamento == dep.id){
                            printf("\n%s\t\t%s\tR$%.2f",func.matricula,func.nome,func.salario);
                            totalSalario += func.salario;
                        }
                    }
                    printf("\n\nTotal da folha do Departamento: R$%.2f",totalSalario);
                    totalSalario = 0;
                } 
                printf("\n\nDeseja sair do relatório de funcionário por departamento?\n1- Sim 2- Não ");
                scanf("%d",&sair);
            }while(sair != 1);
        }
        else{
            printf("\n\nNenhum funcionário cadastrado!!!");
            printf("\n\nAperte ENTER para continuar...");
            setbuf(stdin,NULL);
            getchar();
            setbuf(stdin,NULL);
        }
    }
    else{
        printf("\n\nNenhum departamento cadastrado!!!");
        printf("\n\nAperte ENTER para continuar...");
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }


}

void gerentesDep(FILE *arqFunc,FILE *arqDep){
    int posicao,id,sair;
    TFuncionario func;
    TDepartamento dep;

    fseek(arqDep,0,SEEK_END);
    if(ftell(arqDep)>0){
        fseek(arqFunc,0,SEEK_END);
        if(ftell(arqFunc)>0){
            do{
                printf("\nDigite o ID do departamento para listar os gerentes: ");
                scanf("%d",&id);
                posicao = pesquisaIdDep(arqDep,id);
                if(posicao != -1){
                    fseek(arqDep,posicao*sizeof(TDepartamento),SEEK_SET);
                    fread(&dep,sizeof(TDepartamento),1,arqDep);
                    printf("\nGerentes do departamento %s\n",dep.nome);
                    fseek(arqFunc,0,SEEK_SET);
                    while(fread(&func,sizeof(TFuncionario),1,arqFunc) == 1){
                        if(func.id == dep.id_gerente){
                            printf("\n\nID = %ld",func.id);
                            printf("\nMatrícula = %s",func.matricula);
                            printf("\nNome = %s",func.nome);
                            printf("\nData Nascimento = %s",func.dataNascimento);
                            printf("\nCPF = %s",func.CPF);
                            printf("\nID departamento = %ld",func.id_departamento);
                            printf("\nSalário = R$%.2f",func.salario);
                            printf("\nRua = %s",func.rua);
                            printf("\nBairro = %s",func.bairro);
                            printf("\nNúmero = %d",func.numero);
                            printf("\nComplemento = %s",func.complemento);
                            printf("\nCidade = %s",func.cidade);
                            printf("\nUF = %s",func.uf);
                            printf("\nCEP = %s",func.cep);
                            printf("\nEmail = %s",func.email);
                        }
                    }
                }
                else{
                    printf("\nNenhum departamento com esse ID!!!");
                }
                printf("\n\nDeseja sair da listagem de gerente por departamento?\n1- Sim 2- Não ");
                scanf("%d",&sair);
            }while(sair != 1);
        }
        else{
            printf("\nNenhum funcionário cadastrado!!!");
            printf("\n\nAperte ENTER para continuar...");
            setbuf(stdin,NULL);
            getchar();
            setbuf(stdin,NULL);
        }
    }
    else{
        printf("\nNenhum departamento cadastrado!!!");
        printf("\n\nAperte ENTER para continuar...");
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}