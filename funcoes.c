#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include "historicos.h"

int verificaVazio(char *s){
    if(isspace(s[0])!= 0){
        return 1;
    }
    return -1;
}

void retiraEnter(char *s){
   if(s[strlen(s)-1]=='\n')
      s[strlen(s)-1]='\0';
}

int apenasNumero(char *s){
    for(int i = 0; s[i] != '\0';i++){
        if (!isdigit(s[i])){
            return 1;
        }
    }

    return -1;
}

int verificaData(char *data){
    int i;
    long int datas[3];
    const char delimitador[2] = "/";
    const char substring[3] = "//";

    for (i = 0; data[i] != '\0'; i++){
        if (data[i] != '/' && !isdigit(data[i])){
            return 1;
        }
    }
    if (strstr(data, substring) != NULL){
        return 0;
    }
    i = 0;
    char *token = strtok(data, delimitador);

    while (token != NULL){
        datas[i++] = strtol(token, NULL, 10);
        token = strtok(NULL, delimitador);
    }
    if(datas[1] < 1 || datas[1] > 12 || datas[0] < 1 || datas[0] > 31 || datas[2] < 1960 || datas[2] > 2021){
            return 1;   //caso o mes n estiver entre 1 e 12 ou se o dia n estiver entre 1 e 31 ou se a data for menor que 20/06/1960 e maior que 2021,retorna erro
    }
    else if((datas[2] == 1960 && datas[1] < 6) || (datas[2] == 1960 && datas[0] < 20)){
        return 1;
    }
    switch(datas[1]){
        case 4:;
        case 6:;
        case 9:;
        case 11:
            if(datas[0] < 1 || datas[0] > 30) //se o dia n estiver entre 0 ou 30 nos meses 4,6,9,11,volta erro
                return 1;
        break;
        case 2:
            if(((datas[2]%4 == 0)&&(datas[2]% 100 != 0)) || (datas[2]% 400 == 0)){ //verificando se é ano bissexto e se o dia entrado é valido
                if(datas[0] < 1 || datas[0] > 29)                                     //caso seja ou não ano bissexto
                    return 1;
            }
            else{
                if(datas[0] < 1 || datas[0] > 28)
                    return 1;
            }
        break;
    }

    return -1;
}

int verificarNumerosIguais(int *cpf,int numero){//função para verificar se todos os números do vetor CPF são iguais, e caso for, retorna erro
    int igual;

    igual = 0;
    for(int i = 0;i<11;i++){
        if(cpf[i] == numero)
            igual++;
    }
    if(igual == 11)
        return 1;

    return -1;
}

int validaCPF(char *cpf){
    int i = 0,cpfint[11],somador=0,resultado1,resultado2,digito1,digito2;

    for(i = 0;i<11;i++){    //convertendo cpf para inteiro
        cpfint[i] = cpf[i]-48;
    }

    //verificando se todos os números são iguais, pois estes casos passam na verificação de CPF, mas são invalidos
    for(int k = 0; k < 10; k++){
        if(verificarNumerosIguais(cpfint,k)==1){
            return 1;
        }
    }


    for(i=0;i<9;i++){
        somador+=cpfint[i]*(10-i); //somando o produto dos 9 primeiros numeros entre 10 a 2(1 digito * 10, 2 digito * 9...)
    }

    resultado1 = somador%11; //calculando o resto da soma por 11

    if(resultado1 == 0 || resultado1 == 1){//caso resultado seja 0 ou 1, o 1 digito verificador sera 0
        digito1 = 0;
    }
    else{
        digito1 = 11-resultado1; //caso não seja, o primeiro digito validador é o resultado - 11
    }

    somador = 0; //zerando o somador para calcular o 2 digito

    for(i=0;i<10;i++){
        somador+=cpfint[i]*(11-i); //somando o produto dos 9 primeiros numeros entre 11 a 3
    }

    resultado2=somador%11;   //calculando resto da soma por 11

    if(resultado2==0 || resultado2==1){ //caso o resto seja 0 ou 1, o 2 digito verificador sera 0
        digito2=0;
    }
    else{
        digito2=11-resultado2;  //caso nao seja, sera 11 - resultado
    }

    if((digito1==cpfint[9]) && (digito2==cpfint[10])){
        return -1;  //
    }

    return 1;

}

void retiraBarra(char *s){
    for(int i = 0;i < 11;i++){
        if(s[i] == '\0'){
            if(i == 10){
                ;
            }
            else{
                s[i] = '/';
            }

        }
    }
    return;
}

void mesAno(char *data,short unsigned int *mes,short unsigned int *ano){
    int i=0;
    int datas[3];
    const char delimitador[2] = "/";
    char *token = strtok(data, delimitador);

    while (token != NULL){
        datas[i++] = strtol(token, NULL, 10);
        token = strtok(NULL, delimitador);
    }
    *mes = datas[1];
    *ano = datas[2];
}

