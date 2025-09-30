// TEMA 1 - NIVEL AVENTUREIRO

// incluindo bibliotecas padrão
#include <stdio.h>   // Biblioteca padrão para entrada e saída (printf, scanf)
#include <stdlib.h>  // Biblioteca para alocação de memória e funções utilitárias (malloc, free, srand, rand)
#include <string.h>  // Biblioteca para manipulação de strings (strcpy, strlen, strcmp)
#include <time.h>    // Biblioteca para tempo, usada para inicializar a semente rand com time(NULL)

// criando uma struct com os dados dos territórios
struct Territorio{
  char nome[30];  // campo para armazenar o nome do território (até 29 caracteres + '\0')
  char cor[10];   // campo para armazenar a cor/dono do território (ex: "vermelho", "azul")
  int tropas;     // campo para armazenar a quantidade de tropas naquele território
};

// função limparBuffer criada para contornar erro do scanf que lê o '\n' deixado pelo Enter
void limparBuffer() {
    int c; // declara a variável que receberá caracteres do buffer
    // while que percorre a variável c, que recebe o getchar() que puxa o que está no buffer,
    // e vai rodando o while descartando até encontrar o '\n'
    // o 'EOF' é para garantir que rode até o fim para não ocorrer erro
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// função criada especificamente para criar um sistema de pressionar a tecla 'ENTER' para continuar
void enter(){
    // mensagem de instrução para o usuário
    printf("||PRESSIONE 'ENTER' PARA CONTINUAR||\n");
    // declaração de variável temporária para capturar a entrada do usuário
    char enter;
    // scanf que lê tudo até a quebra de linha (evita precisar pressionar duas vezes)
    scanf("%[^\n]", &enter);
    // limpa o buffer após a leitura para evitar problemas nos próximos scanf
    limparBuffer();
}

// função responsável por cadastrar todos os territórios do jogo
// recebe como parâmetro um ponteiro para o vetor de territórios (mapa) e a quantidade total
void cadastrarTerritorios(struct Territorio* mapa, int total) {
    // for para percorrer cada posição do vetor e cadastrar os dados
    for (int i = 0; i < total; i++) {
        // pede ao usuário o nome do território número i+1 (mais estético)
        printf("ESCREVA O NOME DO %d° TERRITÓRIO: ", i + 1);
        // scanf %[^\n] lê todo o texto até a quebra de linha e armazena em mapa[i].nome
        scanf("%[^\n]", mapa[i].nome);
        // limpa o \n que ficou no buffer para evitar que o próximo scanf seja pulado
        limparBuffer();

        // pede a cor/dono do território
        printf("ESCREVA A COR DO %d° TERRITÓRIO: ", i + 1);
        // lê a cor até a quebra de linha e armazena em mapa[i].cor
        scanf("%[^\n]", mapa[i].cor);
        limparBuffer(); // limpa o buffer após a leitura

        // pede a quantidade de tropas do território
        printf("ESCREVA A QUANTIDADE DE TROPAS DO %d° TERRITÓRIO: ", i + 1);
        // scanf que lê números inteiros e armazena em mapa[i].tropas
        scanf("%d", &mapa[i].tropas);
        limparBuffer(); // limpa o \n que ficou no buffer

        // mensagem de confirmação do cadastro com feedback ao usuário
        printf("\n %d° TERRITÓRIO CADASTRADO COM SUCESSO!\n\n", i + 1);
        // pausa para o usuário ver a mensagem antes de continuar
        enter();
    }
}

// função que exibe todos os territórios cadastrados (nome, cor e tropas)
// recebe ponteiro para o mapa e o total de territórios
void exibirTerritorios(struct Territorio* mapa, int total) {
    printf("\n LISTA DE TERRITÓRIOS:\n\n"); // título da lista
    // percorre o vetor e exibe os dados de cada território
    for (int i = 0; i < total; i++) {
        printf("[%d] Nome: %s\n", i + 1, mapa[i].nome);    // exibe índice e nome
        printf("    Cor: %s\n", mapa[i].cor);              // exibe a cor/dono
        printf("    Tropas: %d\n\n", mapa[i].tropas);     // exibe a quantidade de tropas
    }
}

// função que simula uma batalha entre dois territórios
// recebe ponteiros para os territórios atacante e defensor
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // impede que um território com apenas 1 tropa ataque (não faz sentido atacar com 0/1)
    if (atacante->tropas <= 1) {
        printf("\n O território atacante precisa de mais de 1 tropa para atacar!\n");
        return; // sai da função se não houver tropas suficientes
    }

    // mensagem inicial do combate informando quais territórios participam
    printf("\n️  BATALHA ENTRE %s (atacante) e %s (defensor)\n", atacante->nome, defensor->nome);

    // gera valores aleatórios de 1 a 6 simulando a rolagem de dados para atacante e defensor
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    // exibe os valores dos dados sorteados
    printf("\n Dado do atacante: %d\n", dadoAtacante);
    printf(" Dado do defensor: %d\n", dadoDefensor);

    // compara as rolagens para decidir o resultado da batalha
    if (dadoAtacante > dadoDefensor) {
        // quando o atacante vence
        printf("\n %s venceu a batalha!\n", atacante->nome);

        // o defensor muda de dono: copiamos a cor do atacante para o defensor
        strcpy(defensor->cor, atacante->cor);
        // defensor recebe metade das tropas do atacante (regra do jogo definida)
        defensor->tropas = atacante->tropas / 2;
        // atacante perde metade das suas tropas ao conquistar (movimentação/saída de tropas)
        atacante->tropas = atacante->tropas / 2;

        // mensagem informando a conquista
        printf("\n %s conquistou %s!\n", atacante->nome, defensor->nome);
    } else {
        // quando o defensor vence ou empata (empate favorece o defensor aqui)
        printf("\n️  %s defendeu com sucesso!\n", defensor->nome);
        // atacante perde 1 tropa como penalidade por falhar no ataque
        atacante->tropas -= 1;
    }

    // mostra a situação atualizada dos dois territórios após o combate
    printf("\n SITUAÇÃO APÓS O COMBATE:\n");
    printf("️ Atacante: %s | Tropas: %d | Cor: %s\n", atacante->nome, atacante->tropas, atacante->cor);
    printf("️ Defensor: %s | Tropas: %d | Cor: %s\n", defensor->nome, defensor->tropas, defensor->cor);
}

// função responsável por liberar a memória alocada dinamicamente para o mapa
void liberarMemoria(struct Territorio* mapa) {
    free(mapa); // libera o bloco de memória apontado por mapa
    printf("\n Memória liberada com sucesso!\n"); // informa que a memória foi liberada
}

// função principal do programa onde a execução começa
int main() {
    srand(time(NULL)); // inicializando a semente dos números aleatórios para gerar valores diferentes a cada execução

    // mensagem de boas-vindas
    printf(" BEM-VINDO AO JOGO DE TERRITÓRIOS!\n\n");
    enter(); // pausa inicial para o usuário pressionar Enter

    int total; // variável que vai armazenar a quantidade de territórios que o usuário deseja criar
    printf("Digite o número total de territórios que deseja cadastrar: ");
    // lê um número inteiro com a quantidade desejada
    scanf("%d", &total);
    limparBuffer(); // limpa o buffer após o scanf para evitar problemas com próximos scanf/gets

    // alocação dinâmica de memória para armazenar 'total' territórios
    struct Territorio* mapa = (struct Territorio*) malloc(total * sizeof(struct Territorio));
    // verifica se a alocação foi bem-sucedida; se não, informa e encerra com erro
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1; // retorno não-zero indica erro
    }

    // chama a função de cadastro passando o ponteiro para o mapa e o total de territórios
    cadastrarTerritorios(mapa, total);
    // exibe os territórios cadastrados
    exibirTerritorios(mapa, total);

    // variáveis que irão armazenar as escolhas do usuário para atacante e defensor
    int escolhaAtacante, escolhaDefensor;

    // instrução para iniciar a escolha de ataque
    printf("\n️ ESCOLHA UM TERRITÓRIO PARA ATACAR:\n");
    // mostra todos os territórios novamente para facilitar a escolha
    exibirTerritorios(mapa, total);

    // usuário escolhe qual território será o atacante (número mostrado na lista)
    printf("Digite o número do território atacante: ");
    scanf("%d", &escolhaAtacante);
    limparBuffer(); // limpa o buffer após o scanf

    // usuário escolhe qual território será o defensor
    printf("Digite o número do território defensor: ");
    scanf("%d", &escolhaDefensor);
    limparBuffer(); // limpa o buffer após a leitura

    // verifica se as escolhas são válidas: dentro do intervalo e não sendo o mesmo território
    if (escolhaAtacante < 1 || escolhaAtacante > total || escolhaDefensor < 1 || escolhaDefensor > total || escolhaAtacante == escolhaDefensor) {
        // caso inválido, informa o usuário
        printf("\n Escolha inválida!\n");
    } else {
        // se válido, chama a função de ataque passando os endereços dos territórios escolhidos
        // subtrai 1 porque a lista mostrada ao usuário começa em 1, mas o array começa em 0
        atacar(&mapa[escolhaAtacante - 1], &mapa[escolhaDefensor - 1]);
    }

    // após o ataque, exibe o estado final dos territórios
    printf("\n ESTADO FINAL DOS TERRITÓRIOS:\n");
    exibirTerritorios(mapa, total);

    // libera a memória alocada dinamicamente para o mapa antes de terminar o programa
    liberarMemoria(mapa);
    return 0; // finaliza o programa com sucesso
}
