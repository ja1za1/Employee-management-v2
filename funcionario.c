#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "departamento.h"
#include "funcionario.h"
#include "funcoes.h"
#include "historicos.h"

void listarFunc(FILE *arqFunc){
    TFuncionario LF;
    fseek(arqFunc,0,SEEK_END);
    if(ftell(arqFunc)>0){
        printf("\n-------- Funcionários Existentes --------\n");
        fseek(arqFunc,0,SEEK_SET);
        while(fread(&LF,sizeof(TFuncionario),1,arqFunc)==1){
            printf("\n\nID = %ld",LF.id);
            printf("\nMatrícula = %s",LF.matricula);
            printf("\nNome = %s",LF.nome);
            printf("\nData Nascimento = %s",LF.dataNascimento);
            printf("\nCPF = %s",LF.CPF);
            printf("\nID departamento = %ld",LF.id_departamento);
            printf("\nSalário = R$%.2f",LF.salario);
            printf("\nRua = %s",LF.rua);
            printf("\nBairro = %s",LF.bairro);
            printf("\nNúmero = %d",LF.numero);
            printf("\nComplemento = %s",LF.complemento);
            printf("\nCidade = %s",LF.cidade);
            printf("\nUF = %s",LF.uf);
            printf("\nCEP = %s",LF.cep);
            printf("\nEmail = %s",LF.email);
        }   
    }
    else{
        printf("\nNenhum funcionário cadastrado!!!");
    }
    printf("\n\nAperte ENTER para continuar...");
    setbuf(stdin,NULL);
    getchar();
    setbuf(stdin,NULL);
}

int pesquisaIdFunc(FILE *arqFunc,int id){
    int posicao = 0;
    TFuncionario reg;
    fseek(arqFunc,0,SEEK_SET);
    while(fread(&reg,sizeof(TFuncionario),1,arqFunc)==1){
        if(reg.id == id){
            return posicao;
        }
        else{
            posicao++;
        }
    }
    return -1;
}

int pesquisaFunc(FILE *arqFunc,char *s){
    int posicao = 0;
    TFuncionario reg;
    fseek(arqFunc,0,SEEK_SET);
    while(fread(&reg,sizeof(TFuncionario),1,arqFunc)==1){
        if(strcmp(reg.matricula,s)==0){
            return posicao;
        }
        else{
            posicao++;
        }
    }
    return -1;
}

void cadastroFunc(FILE *arqFunc,FILE *arqDep){
    FILE *historicoSal;
    FILE *historicoFunc;
    int sair,achou;
    char matricula[10];
    TFuncionario ID,regFunc;
    TDepartamento cursos;
    HistoricoFuncionario hfunc;
    HistoricoSalario hsal;
    fseek(arqDep,0,SEEK_END);
    if(ftell(arqDep)>0){
        do{
            printf("\n------------ Cadastro de Funcionário ------------\n");
            printf("\nMatrícula: ");
            setbuf(stdin,NULL);
            fgets(matricula,10,stdin);
            setbuf(stdin,NULL);

            if(pesquisaFunc(arqFunc,matricula)==-1){
                fseek(arqFunc,0,SEEK_END);
                if(ftell(arqFunc)>0){
                    fseek(arqFunc,0,SEEK_SET);
                    while(fread(&ID,sizeof(TFuncionario),1,arqFunc)==1){
                        ;
                    }
                }
                else{
                    ID.id = 0;
                }
                regFunc.id = ++(ID.id);
                retiraEnter(matricula);
                strcpy(regFunc.matricula,matricula);
                printf("\nDigite o nome: ");
                setbuf(stdin,NULL);
                fgets(regFunc.nome,100,stdin);
                setbuf(stdin,NULL);
                while(verificaVazio(regFunc.nome)==1){
                    printf("\nNão é permitido nome vazio ou com espaço no início!!\n\nDigite um nome válido: ");
                    setbuf(stdin,NULL);
                    fgets(regFunc.nome,100,stdin);
                    setbuf(stdin,NULL);
                }
                retiraEnter(regFunc.nome);
                printf("\nDigite a data de nascimento(dd/mm/aaaa): ");
                setbuf(stdin,NULL);
                fgets(regFunc.dataNascimento,12,stdin);
                setbuf(stdin,NULL);
                retiraEnter(regFunc.dataNascimento);
                while(verificaData(regFunc.dataNascimento)==1){
                    printf("\nData inválida!!!\n\nDigite uma data válida(dd/mm/aaaa): ");
                    setbuf(stdin,NULL);
                    fgets(regFunc.dataNascimento,12,stdin);
                    retiraEnter(regFunc.dataNascimento);
                    setbuf(stdin,NULL);
                }
                retiraBarra(regFunc.dataNascimento);
                printf("\nDigite o CPF: ");
                setbuf(stdin,NULL);
                fgets(regFunc.CPF,13,stdin);
                retiraEnter(regFunc.CPF);
                setbuf(stdin,NULL);                       
                while(validaCPF(regFunc.CPF)==1){
                    printf("\nCPF inválido!!!\n\nDigite um CPF válido: ");
                    setbuf(stdin,NULL);
                    fgets(regFunc.CPF,13,stdin);
                    retiraEnter(regFunc.CPF);
                    setbuf(stdin,NULL);
                }
                do{
                    rewind(arqDep);
                    printf("\nID\t\tNome\n");

                    while(fread(&cursos,sizeof(TDepartamento),1,arqDep)==1)
                        printf("\n%lu\t\t%s\n",cursos.id,cursos.nome);
               
                    printf("\n\nForneça o ID do departamento: ");
                    scanf("%ld",&regFunc.id_departamento);

                    achou = pesquisaIdDep(arqDep,regFunc.id_departamento);
                    if(achou==-1)
                        printf("\nID de departamento inexistente!!!\n\n");

                }while(achou==-1);

                printf("\nSalário: ");
                scanf("%f",&regFunc.salario);

                printf("\nRua: ");
                setbuf(stdin,NULL);
                fgets(regFunc.rua,40,stdin);
                retiraEnter(regFunc.rua);
                setbuf(stdin,NULL);

                printf("\nBairro: ");
                setbuf(stdin,NULL);
                fgets(regFunc.bairro,30,stdin);
                retiraEnter(regFunc.bairro);
                setbuf(stdin,NULL);

                printf("\nNúmero: ");
                scanf("%d",&regFunc.numero);

                printf("\nComplemento: ");
                setbuf(stdin,NULL);
                fgets(regFunc.complemento,30,stdin);
                retiraEnter(regFunc.complemento);
                setbuf(stdin,NULL);

                printf("\nCidade: ");
                setbuf(stdin,NULL);
                fgets(regFunc.cidade,40,stdin);
                retiraEnter(regFunc.cidade);
                setbuf(stdin,NULL);

                printf("\nUF: ");
                setbuf(stdin,NULL);
                fgets(regFunc.uf,4,stdin);
                retiraEnter(regFunc.uf);
                setbuf(stdin,NULL);

                printf("\nCEP: ");
                setbuf(stdin,NULL);
                fgets(regFunc.cep,10,stdin);
                retiraEnter(regFunc.cep);
                setbuf(stdin,NULL);

                printf("\nEmail: ");
                setbuf(stdin,NULL);
                fgets(regFunc.email,40,stdin);
                retiraEnter(regFunc.email);
                setbuf(stdin,NULL);

                fseek(arqFunc,0,SEEK_END);
                fwrite(&regFunc,sizeof(TFuncionario),1,arqFunc);

                historicoFunc=fopen("historicoFuncionario.dat","rb+");
                    if(!historicoFunc)
                        historicoFunc=fopen("historicoFuncionario.dat","wb+");
                    hfunc.id_funcionario = regFunc.id;
                    hfunc.id_departamento = regFunc.id_departamento;
                    printf("\nDigite a data desse registro(dd/mm/aaaa): ");
                    setbuf(stdin,NULL);
                    fgets(hfunc.data,12,stdin);
                    setbuf(stdin,NULL);
                    retiraEnter(hfunc.data);
                    while(verificaData(hfunc.data)==1){
                        printf("\nData inválida!!!\n\nDigite uma data válida(dd/mm/aaaa): ");
                        setbuf(stdin,NULL);
                        fgets(hfunc.data,12,stdin);
                        retiraEnter(hfunc.data);
                        setbuf(stdin,NULL);
                    }
                    retiraBarra(hfunc.data);
                    fseek(historicoFunc,0,SEEK_END);
                    fwrite(&hfunc,sizeof(HistoricoDepartamento),1,historicoFunc);
                    fclose(historicoFunc);

                    historicoSal=fopen("historicoSalario.dat","rb+");
                    if(!historicoSal)
                        historicoSal=fopen("historicoSalario.dat","wb+");
                    hsal.id_funcionario = regFunc.id;
                    hsal.salario = regFunc.salario;
                    mesAno(hfunc.data,&hsal.mes,&hsal.ano);
                    fseek(historicoSal,0,SEEK_END);
                    fwrite(&hsal,sizeof(HistoricoSalario),1,historicoSal);
                    fclose(historicoSal);
            }
            else{
                printf("\nMatrícula repetida!!!");
            }
            printf("\n\nDeseja sair do cadastro de funcionário?\n1- Sim 2- Não ");
            scanf("%d",&sair);
        }while(sair != 1);
    }
    else{
        printf("\nNenhum departamento cadastrado!!!");
        printf("\n\nDigite ENTER para continuar...");
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}

void alteraFunc(FILE *arqFunc,FILE *arqDep){
    FILE *historicoFuncionario;
    char mat[10];
    int achou,sair,posicao;
    TFuncionario funcOrig,funcAlter;
    TDepartamento cursos;
    HistoricoFuncionario histFunc;

    fseek(arqFunc,0,SEEK_END);
    if(ftell(arqFunc)>0){
        do{
            printf("\nDigite a matrícula do funcionário para realizar alteração: ");
            setbuf(stdin,NULL);
            fgets(mat,10,stdin);
            setbuf(stdin,NULL);
            retiraEnter(mat);
            posicao = pesquisaFunc(arqFunc,mat);
            if(posicao != -1){
                fseek(arqFunc,posicao*sizeof(TFuncionario),SEEK_SET);
                fread(&funcOrig,sizeof(TFuncionario),1,arqFunc);
        
                funcAlter.id = funcOrig.id;
                strcpy(funcAlter.matricula,funcOrig.matricula);
                printf("\nDigite o nome: ");
                setbuf(stdin,NULL);
                fgets(funcAlter.nome,100,stdin);
                setbuf(stdin,NULL);
                while(verificaVazio(funcAlter.nome)==1){
                    printf("\nNão é permitido nome vazio ou com espaço no início!!\n\nDigite um nome válido: ");
                    setbuf(stdin,NULL);
                    fgets(funcAlter.nome,100,stdin);
                    setbuf(stdin,NULL);
                }
                retiraEnter(funcAlter.nome);
                printf("\nDigite a data de nascimento(dd/mm/aaaa): ");
                setbuf(stdin,NULL);
                fgets(funcAlter.dataNascimento,12,stdin);
                setbuf(stdin,NULL);
                retiraEnter(funcAlter.dataNascimento);
                while(verificaData(funcAlter.dataNascimento)==1){
                    printf("\nData inválida!!!\n\nDigite uma data válida(dd/mm/aaaa): ");
                    setbuf(stdin,NULL);
                    fgets(funcAlter.dataNascimento,12,stdin);
                    retiraEnter(funcAlter.dataNascimento);
                    setbuf(stdin,NULL);
                }
                retiraBarra(funcAlter.dataNascimento);
                printf("\nDigite o CPF: ");
                setbuf(stdin,NULL);
                fgets(funcAlter.CPF,13,stdin);
                retiraEnter(funcAlter.CPF);
                setbuf(stdin,NULL);                       
                while(validaCPF(funcAlter.CPF)==1){
                    printf("\nCPF inválido!!!\n\nDigite um CPF válido: ");
                    setbuf(stdin,NULL);
                    fgets(funcAlter.CPF,13,stdin);
                    retiraEnter(funcAlter.CPF);
                    setbuf(stdin,NULL);
                }
                do{
                    rewind(arqDep);
                    printf("\nID\tNome\n");

                    while(fread(&cursos,sizeof(TDepartamento),1,arqDep)==1)
                        printf("\n%lu\t%s\n",cursos.id,cursos.nome);
               
                    printf("\n\nForneça o ID do departamento: ");
                    scanf("%ld",&funcAlter.id_departamento);

                    achou = pesquisaIdDep(arqDep,funcAlter.id_departamento);
                    if(achou==-1)
                        printf("\nID de departamento inexistente!!!\n\n");

                }while(achou==-1);

                printf("\nSalário: ");
                scanf("%f",&funcAlter.salario);

                printf("\nRua: ");
                setbuf(stdin,NULL);
                fgets(funcAlter.rua,40,stdin);
                retiraEnter(funcAlter.rua);
                setbuf(stdin,NULL);

                printf("\nBairro: ");
                setbuf(stdin,NULL);
                fgets(funcAlter.bairro,30,stdin);
                retiraEnter(funcAlter.bairro);
                setbuf(stdin,NULL);

                printf("\nNúmero: ");
                scanf("%d",&funcAlter.numero);

                printf("\nComplemento: ");
                setbuf(stdin,NULL);
                fgets(funcAlter.complemento,30,stdin);
                retiraEnter(funcAlter.complemento);
                setbuf(stdin,NULL);

                printf("\nCidade: ");
                setbuf(stdin,NULL);
                fgets(funcAlter.cidade,40,stdin);
                retiraEnter(funcAlter.cidade);
                setbuf(stdin,NULL);

                printf("\nUF: ");
                setbuf(stdin,NULL);
                fgets(funcAlter.uf,4,stdin);
                retiraEnter(funcAlter.uf);
                setbuf(stdin,NULL);

                printf("\nCEP: ");
                setbuf(stdin,NULL);
                fgets(funcAlter.cep,10,stdin);
                retiraEnter(funcAlter.cep);
                setbuf(stdin,NULL);

                printf("\nEmail: ");
                setbuf(stdin,NULL);
                fgets(funcAlter.email,40,stdin);
                retiraEnter(funcAlter.email);
                setbuf(stdin,NULL);

                fseek(arqFunc,posicao*sizeof(TFuncionario),SEEK_SET);
                fwrite(&funcAlter,sizeof(TFuncionario),1,arqFunc);

                if(funcOrig.id_departamento != funcAlter.id_departamento){
                    historicoFuncionario=fopen("historicoFuncionario.dat","rb+");
                    if(!historicoFuncionario)
                        historicoFuncionario=fopen("historicoFuncionario.dat","wb+");
                    histFunc.id_funcionario = funcAlter.id;
                    histFunc.id_departamento = funcAlter.id_departamento;
                    printf("\nDigite a data dessa alteração(dd/mm/aaaa): ");
                    setbuf(stdin,NULL);
                    fgets(histFunc.data,12,stdin);
                    setbuf(stdin,NULL);
                    retiraEnter(histFunc.data);
                    while(verificaData(histFunc.data)==1){
                        printf("\nData inválida!!!\n\nDigite uma data válida(dd/mm/aaaa): ");
                        setbuf(stdin,NULL);
                        fgets(histFunc.data,12,stdin);
                        retiraEnter(histFunc.data);
                        setbuf(stdin,NULL);
                    }
                    retiraBarra(histFunc.data);
                    fseek(historicoFuncionario,0,SEEK_END);
                    fwrite(&histFunc,sizeof(HistoricoDepartamento),1,historicoFuncionario);
                    fclose(historicoFuncionario);
                }
            }
            else{
                printf("\nNão existe funcionário com essa matrícula!!!\n");
            }
            
            printf("\nDeseja sair da alteração de funcionário?\n1- Sim 2- Não ");
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

void alteraDepFunc(FILE *arqFunc,FILE *arqDep){
    FILE *historicoFunc;
    int ID,sair,posicao,achou;
    TFuncionario func;
    TDepartamento cursos;
    HistoricoFuncionario hfunc;

    fseek(arqFunc,0,SEEK_END);
    if(ftell(arqFunc)> 0){
        do{
            printf("\nDigite o ID do funcionário para alterar o departamento: ");
            scanf("%d",&ID);
            posicao = pesquisaIdFunc(arqFunc,ID);
            if(posicao != -1){
                fseek(arqFunc,posicao*sizeof(TFuncionario),SEEK_SET);
                fread(&func,sizeof(TFuncionario),1,arqFunc);
                do{
                    rewind(arqDep);
                    printf("\nID\tNome\n");

                    while(fread(&cursos,sizeof(TDepartamento),1,arqDep)==1)
                        printf("\n%lu\t%s\n",cursos.id,cursos.nome);
               
                    printf("\n\nForneça o ID do departamento: ");
                    scanf("%ld",&func.id_departamento);

                    achou = pesquisaIdDep(arqDep,func.id_departamento);
                    if(achou==-1)
                        printf("\nID de departamento inexistente!!!\n\n");

                }while(achou==-1);
                fseek(arqFunc,posicao*sizeof(TFuncionario),SEEK_SET);
                fwrite(&func,sizeof(TFuncionario),1,arqFunc);

                historicoFunc=fopen("historicoFuncionario.dat","rb+");
                    if(!historicoFunc)
                        historicoFunc=fopen("historicoFuncionario.dat","wb+");
                    hfunc.id_funcionario = func.id;
                    hfunc.id_departamento = func.id_departamento;
                    printf("\nDigite a data dessa alteração(dd/mm/aaaa): ");
                    setbuf(stdin,NULL);
                    fgets(hfunc.data,12,stdin);
                    setbuf(stdin,NULL);
                    retiraEnter(hfunc.data);
                    while(verificaData(hfunc.data)==1){
                        printf("\nData inválida!!!\n\nDigite uma data válida(dd/mm/aaaa): ");
                        setbuf(stdin,NULL);
                        fgets(hfunc.data,12,stdin);
                        retiraEnter(hfunc.data);
                        setbuf(stdin,NULL);
                    }
                    retiraBarra(hfunc.data);
                    fseek(historicoFunc,0,SEEK_END);
                    fwrite(&hfunc,sizeof(HistoricoDepartamento),1,historicoFunc);
                    fclose(historicoFunc);

            }
            else{
                printf("\nNão existe funcionário com esse ID!!!");
            }

            printf("\n\nDeseja sair da alteração de departamento de funcionário?\n1- Sim 2- Não ");
            scanf("%d",&sair);

        }while(sair != 1);
    }
    else{
        printf("\nNenhum funcionário cadastrado!!!");
        printf("\n\nAperte ENTER para continuar...");
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);;
    }

}

void consultaFunc(FILE *arqFunc,FILE *arqDep){
    int sair,posicao,posdep;
    char mat[10];
    TFuncionario func;
    TDepartamento dep;

    fseek(arqFunc,0,SEEK_END);
    if(ftell(arqFunc)>0){
        do{
            printf("\nDigite a matrícula para realizar a consulta: ");
            setbuf(stdin,NULL);
            fgets(mat,10,stdin);
            setbuf(stdin,NULL);
            retiraEnter(mat);
            posicao = pesquisaFunc(arqFunc,mat);
            if(posicao != -1){
                fseek(arqFunc,posicao*sizeof(TFuncionario),SEEK_SET);
                fread(&func,sizeof(TFuncionario),1,arqFunc);
                posdep = pesquisaIdDep(arqDep,func.id_departamento);
                fseek(arqDep,posdep*sizeof(TDepartamento),SEEK_SET);
                fread(&dep,sizeof(TDepartamento),1,arqDep);

                printf("\nDados do funcionário %s",func.nome);
                printf("\n\nID = %ld",func.id);
                printf("\nMatrícula = %s",func.matricula);
                printf("\nNome = %s",func.nome);
                printf("\nData Nascimento = %s",func.dataNascimento);
                printf("\nCPF = %s",func.CPF);
                printf("\nID departamento = %ld",func.id_departamento);
                printf("\nNome Departamento = %s",dep.nome);
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
            else{
                printf("\nNenhum funcionário com essa matrícula!!!");
            }
            printf("\n\nDeseja sair da consulta por matrícula?\n1- Sim 2- Não ");
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

void gerarFolhaPagamento(FILE *arqFunc){
    int sair,posicao;
    char mat[10];
    TFuncionario func;
    fseek(arqFunc,0,SEEK_END);
    if(ftell(arqFunc)>0){
        do{
            printf("\nDigite a matrícula para gerar a folha de pagamento: ");
            setbuf(stdin,NULL);
            fgets(mat,10,stdin);
            setbuf(stdin,NULL);
            retiraEnter(mat);
            posicao = pesquisaFunc(arqFunc,mat);
            if(posicao != -1){
                fseek(arqFunc,posicao*sizeof(TFuncionario),SEEK_SET);
                fread(&func,sizeof(TFuncionario),1,arqFunc);
                printf("\n-------- FOLHA DE PAGAMENTO --------");
                printf("\nMatrícula = %s",func.matricula);
                printf("\nNome = %s",func.nome);
                printf("\nSalário = R$%.2f",func.salario);
            }
            else{
                printf("\nNenhum funcionário com essa matrícula!!!");
            }
            printf("\n\nDeseja sair de gerar folha de pagamento?\n1- Sim 2- Não ");
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

void alteraSalario(FILE *arqFunc){
    FILE *historicoSal;
    int sair,posicao,id;
    HistoricoSalario hSal;
    TFuncionario func;

    fseek(arqFunc,0,SEEK_END);
    if(ftell(arqFunc)>0){
        do{
            historicoSal=fopen("historicoSalario.dat","rb+");
            if(!historicoSal)
                historicoSal=fopen("historicoSalario.dat","wb+");
            printf("\nDigite o ID do funcionário para alterar o salário: ");
            scanf("%d",&id);
            posicao = pesquisaIdFunc(arqFunc,id);
            if(posicao != -1){
                hSal.id_funcionario = id;
                printf("\nDigite o salário novo: ");
                scanf("%f",&hSal.salario);
                printf("\nDigite o mês dessa mudança: ");
                scanf("%hu",&hSal.mes);
                while(hSal.mes < 0 || hSal.mes > 12){
                    printf("\nMês inválido!!!\nDigite um mês válido: ");
                    scanf("%hu",&hSal.mes);
                }
                printf("\nDigite o ano dessa mudança: ");
                scanf("%hu",&hSal.ano);
                while(hSal.ano < 1960 || hSal.ano > 2021){
                    printf("\nAno inválido!!!\nDigite um ano válido: ");
                    scanf("%hu",&hSal.ano);
                }
                fseek(historicoSal,0,SEEK_END);
                fwrite(&hSal,sizeof(HistoricoSalario),1,historicoSal);
                
                fseek(arqFunc,posicao*sizeof(TFuncionario),SEEK_SET);
                fread(&func,sizeof(TFuncionario),1,arqFunc);
                func.salario = hSal.salario;
                
                fseek(arqFunc,posicao*sizeof(TFuncionario),SEEK_SET);
                fwrite(&func,sizeof(TFuncionario),1,arqFunc);

                fclose(historicoSal);
            }
            else{
                printf("\nNenhum funcionário com esse ID!!!");
            }


            printf("\n\nDeseja sair de altera salário?\n1- Sim 2- Não ");
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

void histSalario(FILE *arqFunc){
    FILE *histSal;
    int sair,id,posicao;
    int mes[2],ano[2];
    HistoricoSalario hSal;

    fseek(arqFunc,0,SEEK_END);
    if(ftell(arqFunc)>0){
        printf("\nDigite o ID do funcionário para consultar o histórico de salário: ");
        scanf("%d",&id);
        posicao = pesquisaIdFunc(arqFunc,id);
        do{
            if(posicao != -1){
                printf("\nDigite o período que deseja consultar o histórico desse funcionário\n");
                printf("\nMês inicial: ");
                scanf("%d",&mes[0]);
                while(mes[0] < 1 || mes[0] > 12){
                    printf("\nMês inválido!!!\nDigite um mês válido: ");
                    scanf("%d",&mes[0]);
                }
                printf("\nAno inicial: ");
                scanf("%d",&ano[0]);
                while(ano[0] < 1960 || ano[0] > 2021){
                    printf("\nAno inválido!!!\nDigite um ano válido: ");
                    scanf("%d",&ano[0]);
                }
                printf("\nMês final: ");
                scanf("%d",&mes[1]);
                while(mes[1] < 1 || mes[1] > 12){
                    printf("\nMês inválido!!!\nDigite um mês válido: ");
                    scanf("%d",&mes[1]);
                }
                printf("\nAno final: ");
                scanf("%d",&ano[1]);
                while(ano[1] < 1960 || ano[1] > 2021){
                    printf("\nAno inválido!!!\nDigite um ano válido: ");
                    scanf("%d",&ano[1]);
                }
                histSal=fopen("historicoSalario.dat","rb+");
                    if(!histSal)
                        histSal=fopen("historicoSalario.dat","wb+");
                fseek(histSal,0,SEEK_SET);
                while(fread(&hSal,sizeof(HistoricoSalario),1,histSal)==1){
                    if(hSal.id_funcionario == id){
                        if(hSal.mes >= mes[0]  && hSal.ano >= ano[0]){
                            if(hSal.ano < ano[1] || (hSal.ano == ano[1] && hSal.mes <= mes[1])){
                                printf("\nMes/Ano\tSalário");
                                printf("\n%d/%d\tR$%.2f\n",hSal.mes,hSal.ano,hSal.salario);
                            }
                        }
                    }
                }
            }
            else{
                printf("\nNenhum funcionário com esse ID!!!");
            }

            printf("\nDeseja sair da consulta de histórico de salário?\n1- Sim 2- Não ");
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