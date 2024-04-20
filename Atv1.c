#include<stdio.h>

int main(){

    float nota;
    char nome[60] = "";

    printf("Insira seu primeiro nome:\n");
    scanf("%s", &nome);

    printf("Insira sua nota:\n");
    scanf("%f", &nota);

    if(nota >= 7.0){
        printf("Aprovado(a)\n");
    } else{
        printf("Reprovado(a)\n");
    }

}