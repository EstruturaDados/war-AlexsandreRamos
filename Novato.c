// TEMA 1 - NIVEL NOVATO
// incluindo bibliotecas padrão
#include <stdio.h>  // Biblioteca padrão para entrada e saída (printf, scanf)
#include <string.h> // Biblioteca para manipulação de strings (strcpy, strlen, etc)

// criando uma constante para o máximo de territórios, neste caso equivale a 5
#define MAX_TERRITORIOS 5 // Constante que define quantos territórios o programa vai cadastrar

// criando uma struct com os dados dos territórios
struct Territorio{
  char nome[30];  // Campo para armazenar o nome do território
  char cor[10];   // Campo para armazenar a cor do território
  int tropas;     // Campo para armazenar a quantidade de tropas do território
};

// função limparBuffer criada para contornar erro do scanf que lê o \n deixado pelo Enter
void limparBuffer() {
    int c; // declara a variável que receberá os caracteres do buffer
    // while que percorre a variável c, que recebe o getchar() que puxa o que está no buffer,
    // e vai rodando o while descartando até encontrar o \n
    // o 'EOF' é para garantir que rode até o fim para não ocorrer erro
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// função criada especificamente para criar um sistema de pressionar a tecla 'ENTER' para continuar
void enter(){
    // mensagem de instrução
    printf("||PRESSIONE 'ENTER' PARA CONTINUAR||\n");
    // declaração de variável para capturar o Enter
    char enter;
    // scanf da variável enter, onde ele lê tudo até ter uma quebra de linha (evitando problemas de ter que pressionar o ENTER duas vezes)
    scanf("%[^\n]", &enter);
    // função de limpeza de buffer para não ocorrer problemas nos próximos scanf
    limparBuffer();
}

// onde vai rodar o programa
int main() {
 
    printf("BEM-VINDO AO PROGRAMA DE CRIAÇÃO DE TERRITÓRIOS!\n\n"); // Mensagem de boas-vindas
    // função enter para continuar
    enter();
   
    // declarando a struct Territorios e usando a constante de máximo de territórios que está setada como 5
    struct Territorio Territorios[MAX_TERRITORIOS]; // Array de structs que armazenará os territórios
   
    // for que enquanto i for menor que 5 incrementa 1
    for(int i = 0; i < 5; i++){
        // printf escrito o que é para fazer; %d equivale ao i criado no for + 1 para dar mais estética
        printf("ESCREVA O NOME DO %d° TERRITÓRIO: ", i + 1);
        // scanf %[^\n] lê todos os caracteres até encontrar uma quebra de linha \n e armazena em Territorios[i].nome
        // o [i] equivale à posição do array, controlada pelo for
        scanf("%[^\n]", Territorios[i].nome);
        limparBuffer(); // limpa o \n que ficou no buffer para evitar que o próximo scanf seja pulado
        
        printf("ESCREVA A COR DO %d° TERRITÓRIO: ", i + 1);
        // scanf %[^\n] lê todos os caracteres até encontrar uma quebra de linha \n e armazena em Territorios[i].cor
        scanf("%[^\n]", Territorios[i].cor);
        limparBuffer(); // limpa o \n que ficou no buffer

        printf("ESCREVA A QUANTIDADE DE TROPAS DO %d° TERRITÓRIO: ", i + 1);
        // scanf que lê números inteiros e armazena em Territorios[i].tropas
        scanf("%d", &Territorios[i].tropas);
        limparBuffer(); // limpa o \n que ficou no buffer
        
        // if enquanto i (i declarado no for) for menor que 4 entra nele
        if(i < 4){
            // i + 1 por estética, para mostrar qual foi cadastrado
            printf("\n\nPARABÉNS! %d° TERRITÓRIO CADASTRADO.\n", i + 1);
            // i + 2 por estética, para indicar qual é o próximo a ser cadastrado
            printf("AGORA VAMOS CADASTRAR O %d° TERRITÓRIO!\n\n", i + 2);  
        } else {
            // quando i for 4 (última percorrida do for) entra no else
            printf("\n\nTODOS OS TERRITÓRIOS FORAM CADASTRADOS COM SUCESSO!\n\n");
        }
       // função enter para continuar
        enter();
    }
  
    // printf fora do for e antes para funcionar como um 'título'
    printf("\n\nOS TERRITÓRIOS CADASTRADOS SÃO:\n\n");
    enter(); // Espera o usuário pressionar Enter antes de mostrar os territórios

    // Loop para exibir todos os territórios cadastrados
    for(int i = 0; i < 5; i++){
        printf("%d° TERRITÓRIO CADASTRADO:\n\n", i + 1);
        // todos os printf puxando do array com posição definida pela contagem do for
        printf("NOME DO TERRITÓRIO: %s\n", Territorios[i].nome);
        printf("COR DO TERRITÓRIO: %s\n", Territorios[i].cor);
        printf("QUANTIDADE DE TROPAS DO TERRITÓRIO: %d\n\n\n", Territorios[i].tropas);

        // função enter para continuar
        enter();
    }
  
    return 0; // Finaliza o programa
}
