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
         printf("\n1- Cadastro de Departamento\n2- Cadastro de Funcion�rio\n3- Alterar dados de funcion�rio");
         printf("\n4- Alterar departamento funcion�rio\n5- Alterar gerente de departamento\n6- Consulta de funcion�rio por matr�cula\n7- Gerar folha de pagamento");
         printf("\n8- Alterar sal�rio de um funcion�rio\n9- Relat�rio de funcion�rio por departamento\n10- Hist�rico Sal�rio em um per�odo\n11- Gerentes de um departamento\n12- Listar Departamentos\n13- Listar Funcion�rios\n0- Sair\n\nForne�a sua op��o: ");
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
