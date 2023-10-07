#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    int jogar = 0;
    bool jogando = false;
    int playerHP = 30;
    int enemyHP = 50;
    int danoInimigo;
    int danoPlayer;
    int acao;
    char *arr[] = {
        "TROLL",
        "BRUXA",
        "GOLLEM",
        "DRAGAO"
    };

    printf("Pressione [1] para JOGAR ou [0] para SAIR\n");
    scanf("%i", &jogar);

    if (jogar == 1) {
        jogando = true;
        printf("SUA VIDA = %i\nVIDA DO INIMIGO = %i\n", playerHP, enemyHP);
        int min = 0;
        int max = 3;
        int randomInRange = (rand() % (max - min + 1)) + min;
        printf("VOCE ENCONTOU %s\n", arr[randomInRange]);
    } else {
        printf("Obrigado por jogar!\n");
        return 0;
    }

    do {
        printf("SELECIONE A AÇÃO\n");
        printf("[1] ATAQUE NORMAL\n");
        printf("[2] ATAQUE ESPECIAL\n");
        printf("[3] FUGIR\n");
        scanf("%i", &acao);

        if (acao < 1 || acao > 3) {
            printf("Ação inválida. Escolha uma ação válida (1, 2 ou 3).\n");
            continue;
        }

        if (acao == 1) {
            int dMin = 5;
            int dMax = 15;
            int randomDano = (rand() % (dMax - dMin + 1)) + dMin;
            danoPlayer = randomDano;
            enemyHP -= danoPlayer;
            printf("VOCÊ USOU ATAQUE NORMAL\n");
            printf("DANO: %i\n", danoPlayer);
        } else if (acao == 2) {
            int dMin = 16;
            int dMax = 25;
            int randomDano = (rand() % (dMax - dMin + 1)) + dMin;
            danoPlayer = randomDano;
            enemyHP -= danoPlayer;
            printf("VOCÊ USOU ATAQUE ESPECIAL!\n");
            printf("DANO: %i\n", danoPlayer);
        } else if (acao == 3) {
            int min = 0;
            int max = 3;
            int randomInRange = (rand() % (max - min + 1)) + min;
            printf("VOCE FUGIU E ENCONTOU %s\n", arr[randomInRange]);
        }

        // Inimigo ataca
        printf("SEU INIMIGO USOU (placeholder)!\n");
        danoInimigo = 6;
        playerHP -= danoInimigo;
        printf("DANO: %i\n", danoInimigo);

        printf("SUA VIDA: %i\n", playerHP);
        printf("VIDA DO INIMIGO: %i\n", enemyHP);
        if (playerHP <= 0 && enemyHP <= 0){
            printf("Você morreu, mas com honrra! Fim de jogo.");
        } else if (playerHP <= 0) {
            printf("Você morreu. Fim de jogo.\n");
            break;
        } else if (enemyHP <= 0) {
            printf("Você venceu! Fim de jogo.\n");
            break;
        }
    } while (jogando);

    printf("Fim de jogo!\n");

    return 0;
}