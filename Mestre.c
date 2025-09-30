// TEMA 1 - NIVEL MESTRE
// NESSE NIVEL TIVE VONTADE DE ME APROFUNDAR NA VISÃO DE SER UM JOGO MESMO E NÃO DE CRIAÇÃO DE DIVERSOS TERRITORIOS, INCREMENTANDO CRIAÇÃO DE TERRITÓRIOS ALEATÓRIOS E AUTOMÁTICAMENTE
#include <stdio.h>      // Biblioteca padrão para entrada e saída
#include <stdlib.h>     // Biblioteca para malloc, free, rand, srand
#include <string.h>     // Biblioteca para manipulação de strings (strcpy, strlen, strstr)
#include <time.h>       // Biblioteca para trabalhar com tempo, usada para srand

#define MAX_TERRITORIOS 5  // Número máximo de territórios no jogo
#define MAX_MISSAO 200     // Tamanho máximo da string de missão

// ==================== Estrutura de Território ====================
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército dono do território
    int tropas;      // Quantidade de tropas no território
} Territorio;

// ==================== Estrutura de Jogador ====================
typedef struct {
    char nome[30];   // Nome do jogador
    char cor[10];    // Cor do jogador
    int tropasTotais;// Total de tropas do jogador
    char *missao;    // Missão atribuída, armazenada dinamicamente
    int missaoAceita;// Flag: 0 = não aceitou, 1 = aceitou
} Jogador;

// ==================== Funções de Missões ====================

// Função que sorteia uma missão e atribui ao jogador
void atribuirMissao(char **destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;  // Sorteia índice aleatório
    *destino = (char*) malloc((strlen(missoes[sorteio]) + 1) * sizeof(char)); // Aloca memória
    if (*destino == NULL) {  // Verifica se malloc funcionou
        printf("Erro ao alocar memória para missão.\n");
        exit(1);  // Sai do programa em caso de erro
    }
    strcpy(*destino, missoes[sorteio]); // Copia missão sorteada para a memória alocada
}

// Função que exibe a missão do jogador
void exibirMissao(char *missao) {
    printf("\n>>> Sua missão: %s\n\n", missao); // Mostra a missão no terminal
}

// ==================== Criar mapa aleatório ====================

// Função que gera territórios com nomes, cores e tropas aleatórias
void gerarMapaAleatorio(Territorio *mapa, int tamanho) {
    char *cores[] = {"vermelho", "azul", "verde", "amarelo", "roxo"}; // Cores possíveis
    for (int i = 0; i < tamanho; i++) {
        sprintf(mapa[i].nome, "Territorio %c", 'A' + i);  // Nome automático: Territorio A, B, C...
        strcpy(mapa[i].cor, cores[rand() % 5]);           // Cor aleatória
        mapa[i].tropas = (rand() % 10) + 1;              // Tropas entre 1 e 10
    }
}

// ==================== Ataque automático ====================

// Função que simula ataque do jogador a um território aleatório
void atacar(Jogador *jogador, Territorio *mapa, int tamanho) {
    int indiceAtacante = rand() % tamanho;    // Território aleatório do jogador (simulado)
    int indiceDefensor = rand() % tamanho;    // Território inimigo aleatório

    // Garante que o jogador não ataque seu próprio território
    while (strcmp(mapa[indiceDefensor].cor, jogador->cor) == 0) {
        indiceDefensor = rand() % tamanho;
    }

    printf("\n%s ataca %s!\n", jogador->nome, mapa[indiceDefensor].nome); // Mostra ação

    // Simula rolagem de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    // Verifica quem venceu a batalha
    if (dadoAtacante > dadoDefensor) {
        printf("Vitória do atacante! Conquistou o território!\n");
        strcpy(mapa[indiceDefensor].cor, jogador->cor);           // Defensor muda de cor
        mapa[indiceDefensor].tropas = mapa[indiceAtacante].tropas / 2; // Metade das tropas do atacante vai pro defensor
        mapa[indiceAtacante].tropas /= 2;                         // Reduz tropas do atacante
    } else {
        printf("Defensor resistiu! Atacante perdeu 1 tropa.\n");
        jogador->tropasTotais -= 1;                               // Perda de tropa total do jogador
        if (jogador->tropasTotais < 0) jogador->tropasTotais = 0; // Garante que não seja negativo
    }
}

// ==================== Exibir mapa ====================

// Mostra todos os territórios, cores e tropas
void exibirMapa(Territorio *mapa, int tamanho) {
    printf("\n===== MAPA =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s | Cor: %s | Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("================\n");
}

// ==================== Verificar missão ====================

// Função que verifica se o jogador cumpriu sua missão
int verificarMissao(Jogador *jogador, Territorio *mapa, int tamanho) {
    char *missao = jogador->missao;

    // Missão: controlar 3 territórios
    if (strstr(missao, "Controlar 3 territorios")) {
        int total = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, jogador->cor) == 0) total++;
        }
        return (total >= 3); // Retorna 1 se controlar 3 ou mais
    }

    // Missão: eliminar tropas vermelhas
    else if (strstr(missao, "Eliminar tropas vermelhas")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0)
                return 0; // Ainda existem tropas vermelhas
        }
        return 1; // Missão concluída
    }

    // Missão: ter um território com mais de 10 tropas
    else if (strstr(missao, "Ter um territorio com mais de 10 tropas")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, jogador->cor) == 0 && mapa[i].tropas > 10)
                return 1;
        }
        return 0;
    }

    return 0; // Missão não reconhecida ou não cumprida
}

// ==================== Recompensa ====================

// Função que adiciona tropas ao jogador ao concluir missão
void recompensarJogador(Jogador *jogador) {
    int bonus = (rand() % 5) + 5; // Tropas extras entre 5 e 9
    jogador->tropasTotais += bonus;
    printf("\n🎉 MISSÃO CONCLUÍDA! Você ganhou %d tropas extras!\n", bonus);
    printf("Tropas totais agora: %d\n", jogador->tropasTotais);
}

// ==================== Menu ====================

void exibirMenu() {
    printf("\n===== MENU =====\n");
    printf("1 - Ver Status do Jogador\n");
    printf("2 - Atacar\n");
    printf("3 - Missão (sorteio ou consultar)\n");
    printf("4 - Sair do jogo\n");
    printf("================\n");
    printf("Escolha: ");
}

// ==================== Ver status do jogador ====================

void verStatus(Jogador *jogador) {
    printf("\n===== STATUS =====\n");
    printf("Nome: %s\n", jogador->nome);
    printf("Cor: %s\n", jogador->cor);
    printf("Tropas: %d\n", jogador->tropasTotais);
    printf("=================\n");
}

// ==================== Liberar memória ====================

void liberarMemoria(Jogador *jogador, Territorio *mapa) {
    free(jogador->missao); // Libera memória da missão
    free(mapa);             // Libera memória dos territórios
}

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    srand(time(NULL)); // Inicializa números aleatórios

    // ===== Criar jogador =====
    Jogador jogador;

    printf("Digite seu nome: ");
    scanf(" %[^\n]", jogador.nome); // ✅ Lê o nome completo com espaços

    printf("Escolha sua cor: ");
    scanf(" %[^\n]", jogador.cor);  // ✅ Lê a cor completa com espaços

    jogador.tropasTotais = 20; // Tropas iniciais
    jogador.missaoAceita = 0;  // Missão ainda não aceita

    // ===== Missoes possíveis =====
    char *missoes[] = {
        "Controlar 3 territorios",
        "Eliminar tropas vermelhas",
        "Ter um territorio com mais de 10 tropas"
    };
    int totalMissoes = 3;

    // ===== Criar mapa automaticamente =====
    Territorio *mapa = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));
    gerarMapaAleatorio(mapa, MAX_TERRITORIOS);

    int opcao = 0;
    int venceu = 0; // Flag para missão concluída

    // ===== Loop principal do jogo =====
    while (1) {
        // Se missão não aceita, sorteia e pergunta
        if (!jogador.missaoAceita) {
            atribuirMissao(&jogador.missao, missoes, totalMissoes);
            exibirMissao(jogador.missao);
            printf("Deseja aceitar esta missão? (1 - Sim / 2 - Não): ");
            int aceitar;
            scanf("%d", &aceitar);
            if (aceitar == 1) {
                jogador.missaoAceita = 1;
            } else {
                printf("Missão recusada. Você pode sortear outra no menu.\n");
            }
        }

        // Exibe menu
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                verStatus(&jogador); // Mostra status do jogador
                break;
            case 2:
                atacar(&jogador, mapa, MAX_TERRITORIOS); // Ataque automático
                // Verifica missão após ataque
                if (jogador.missaoAceita && verificarMissao(&jogador, mapa, MAX_TERRITORIOS)) {
                    recompensarJogador(&jogador); // Dá recompensa
                    venceu = 1; // Flag de vitória
                }
                break;
            case 3:
                if (!jogador.missaoAceita) {
                    printf("Sorteando nova missão...\n");
                } else {
                    exibirMissao(jogador.missao); // Mostra missão atual
                }
                break;
            case 4:
                printf("\nJogo encerrado. Obrigado por jogar!\n");
                liberarMemoria(&jogador, mapa);
                return 0; // Sai do programa
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

        // Verifica se missão foi concluída
        if (venceu) {
            printf("\n=== PARABÉNS %s! Você completou sua missão! ===\n", jogador.nome);
            liberarMemoria(&jogador, mapa);
            return 0; // Finaliza jogo
        }
    }

    return 0;
}
