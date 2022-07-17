#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "departamento.h"
#include "funcionario.h"


int main(){
    FILE *arqFunc,*arqDep;
   int opcao,abriu=1;
   setlocale(LC_ALL,"Portuguese");

   arqFunc=fopen("funcionario.dat","rb+");
   if(!arqFunc)//if(arqA==NULL
      arqFunc=fopen("funcionario.dat","wb+");

   if(arqFunc){
      arqDep=fopen("departamento.dat","rb+");
      if(!arqDep)
         arqDep=fopen("departamento.dat","wb+");
      if(!arqDep)
         abriu=0;
   }
   else
      abriu = 0;

   if(abriu){
      do{
         printf("\n1- Cadastro de Departamento\n2- Cadastro de Funcionário\n3- Alterar dados de funcionário");
         printf("\n4- Alterar departamento funcionário\n5- Alterar gerente de departamento\n6- Consulta de funcionário por matrícula\n7- Gerar folha de pagamento");
         printf("\n8- Alterar salário de um funcionário\n9- Relatório de funcionário por departamento\n10- Histórico Salário em um período\n11- Gerentes de um departamento\n12- Listar Departamentos\n13- Listar Funcionários\n0- Sair\n\nForneça sua opção: ");
         scanf("%d",&opcao);
         system("cls || clear");

         switch(opcao){
            case 1:
               cadastroDep(arqDep,arqFunc);
            break;
            
            case 2:
               cadastroFunc(arqFunc,arqDep);
            break;
            
            case 3:
               alteraFunc(arqFunc,arqDep);
            break;
            
            case 4:
               alteraDepFunc(arqFunc,arqDep);
            break;

            case 5:
               alteraGerente(arqDep,arqFunc);
            break;

            case 6:
               consultaFunc(arqFunc,arqDep);
            break;

            case 7:
               gerarFolhaPagamento(arqFunc);
            break;

            case 8:
               alteraSalario(arqFunc);
            break;

            case 9:
               relatorioFunc(arqFunc,arqDep);
            break;

            case 10:
               histSalario(arqFunc);
            break;

            case 11:
               gerentesDep(arqFunc,arqDep);
            break;

            case 12:
               listarDep(arqDep);   
            break;

            case 13:
               listarFunc(arqFunc);
            break;

            case 0:
                printf("\nSaindo do programa...");
                printf("\n\nAperte ENTER para continuar...");
                setbuf(stdin,NULL);
                getchar();
                setbuf(stdin,NULL);
            break;

         }
         system("cls || clear");   
      }while(opcao!=0);
      fclose(arqFunc);
      fclose(arqDep);
   }
   else
      printf("\nErro na Abertura dos Arquivos!!!!\n");
   
   return 0;
}
