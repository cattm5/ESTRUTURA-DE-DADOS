#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ProximoIdCliente "cliente_id.txt"

//criação de uma estrutura de dados para os veículos, clientes e gestores e aluguer;

//veículos
typedef struct veiculo {
    int CustoDeAluguer;
    char TipoDeModelo[50];
    int CargaBateria;
    char localizacaoVeiculo[50];
    int codigoVeiculo;
    struct veiculo* prox;
    //serve para representar uma lista encadeada de veículos o ponteiro prox aponta sempre para o próximo veículo na lista
    //facilita a criação e retirada de veículos.
} veiculo;

typedef struct cliente {
    char Nome[50];
    int IdCliente;
    int NIF;
    float saldo;
    char Morada[50];

    struct cliente* esq;
    struct cliente* dir;
} cliente;

typedef struct gestor {
    char nome[50]; // corrigido: nome deve ser uma string
    int senha;
} gestor;

int proximoIdCliente() {
    int proximo_id = 1;
    FILE* id_historico = fopen(ProximoIdCliente, "r");
    if (id_historico != NULL) {
        fscanf(id_historico, "%d", &proximo_id);
        fclose(id_historico);
    }
    id_historico = fopen(ProximoIdCliente, "w");
    if (id_historico != NULL) {
        fprintf(id_historico, "%d", proximo_id + 1);
        fclose(id_historico);
    }
    return proximo_id;
}

void guardarCliente(cliente c) {
    FILE* arquivo = fopen("historico.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    fprintf(arquivo, "Id Cliente: %d\n", c.IdCliente);
    fprintf(arquivo, "\n");
    fprintf(arquivo, "Nome: %s\n", c.Nome);
    fprintf(arquivo, "Morada: %s\n", c.Morada);
    fprintf(arquivo, "NIF: %d\n", c.NIF);
    fprintf(arquivo, "---------------------------------------");
    fprintf(arquivo, "\n");

    fclose(arquivo);
}

void consultarHistorico() {
    FILE* arquivo = fopen("historico.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("ID | Nome | Morada | NIF\n");
    printf("-------------------------\n");

    int id, nif;
    char nome[50], morada[50];
    while (fscanf(arquivo, "%d|%[^,]|%[^,]|%d\n", &id, nome, morada, &nif) != EOF) {
        printf("%d | %s | %s | %d\n", id, nome, morada, nif);
    }

    fclose(arquivo);
}

int main() {
    int opcoes;
    int opcao;
    cliente c;

    printf("1-ALUGAR\n");
    printf("2-GESTOR\n");
    printf("3-SAIR\n");
    scanf("%d", &opcoes);
    getchar();
    system("cls");
    switch (opcoes) {
    case 1:

        printf("Ja alugou connosco anteriormente? \n");
        printf("1 - Sim.\n");
        printf("2 - Nao.\n");
        scanf("%d", &opcao);
        getchar();


        if (opcao == 1) {
            system("cls");
            printf("Insira o seu ID de cliente: ");
            scanf("%d", &c.IdCliente);
        }

        else {
            system("cls");
            printf("Vamos criar um registo\n");
            printf("Insira o seu nome: ");
            fgets(c.Nome, 50, stdin);
            getchar();

            printf("Insira a sua morada: ");
            fgets(c.Morada, 50, stdin);
            getchar();

            printf("Insira o seu NIF: ");
            scanf("%d", &c.NIF);

            c.IdCliente = proximoIdCliente();
            printf("O seu ID de cliente e: %d\n", c.IdCliente);

            guardarCliente(c);

            system("cls");
        }
        break;
    case 2:

        char SenhaCorreta[] = "217736";
        char SenhaInserida[50];
        printf("LOGIN\n");
        printf("Insira a sua senha: ");
        scanf("%d", &SenhaInserida);
        if (strcmp(SenhaInserida, SenhaCorreta) == 1) {
            printf("Acesso permitido.\n");
        }
        else {
            printf("Senha Incorreta.\n");
        }
        break;
}
return 0;
        }
