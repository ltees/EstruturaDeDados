#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_TELEFONE 15
#define MAX_CURSO 50
#define MAX_NOTAS 5
#define MAX_ALUNOS 100

typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
    char curso[MAX_CURSO];
    float notas[MAX_NOTAS];
    float media;
    char situacao[10];
} Aluno;

// funcao para ler os dados dos alunos a partir de um arquivo CSV
int lerDados(Aluno alunos[]) {
    FILE *entrada;
    char nome_arquivo_entrada[] = "DadosEntrada.csv";
    int num_alunos = 0;

    entrada = fopen(nome_arquivo_entrada, "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return -1;
    }

    while (fscanf(entrada, "%[^,],%[^,],%[^,],%f,%f\n", alunos[num_alunos].nome,
                  alunos[num_alunos].telefone, alunos[num_alunos].curso,
                  &alunos[num_alunos].notas[0], &alunos[num_alunos].notas[1]) != EOF) {
        num_alunos++;
    }

    fclose(entrada);
    return num_alunos;
}

// funcao para calcular a situacao (aprovado/reprovado) dos alunos com base nas notas
void calcularSituacao(Aluno alunos[], int num_alunos) {
    for (int i = 0; i < num_alunos; i++) {
        alunos[i].media = (alunos[i].notas[0] + alunos[i].notas[1]) / 2;
        if (alunos[i].media >= 7.0)
            strcpy(alunos[i].situacao, "APROVADO");
        else
            strcpy(alunos[i].situacao, "REPROVADO");
    }
}

// funcao para escrever a situacao final dos alunos em um arquivo CSV
void escreverSituacao(Aluno alunos[], int num_alunos) {
    FILE *saida;
    char nome_arquivo_saida[] = "SituacaoFinal.csv";

    saida = fopen(nome_arquivo_saida, "w");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo de saida.\n");
        return;
    }

    for (int i = 0; i < num_alunos; i++) {
        fprintf(saida, "%s, %.2f, %s\n", alunos[i].nome, alunos[i].media, alunos[i].situacao);
    }

    fclose(saida);
    printf("Arquivo %s gerado com sucesso.\n", nome_arquivo_saida);
}

int main() {
    Aluno alunos[MAX_ALUNOS];
    int num_alunos;

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Processar dados dos alunos\n");
        printf("2. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                num_alunos = lerDados(alunos);
                if (num_alunos <= 0) {
                    printf("Nenhum aluno encontrado.\n");
                    break;
                }
                calcularSituacao(alunos, num_alunos);
                escreverSituacao(alunos, num_alunos);
                break;
            case 2:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 2);

    return 0;
}
