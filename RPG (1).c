#include <stdio.h>
#include <stdbool.h> //biblioteca de valores booleanos(verdadeiro ou falso)
#include <stdlib.h> //biblioteca que gera valores aleatorios
#include <time.h>
#include <windows.h>

int main() {
    srand(time(NULL)); // tempo atual

    int jogar = 0;
    bool jogando = false;
    double playerHPmax; //transformei essas variáveis em double pra ficar mais facil de escalar os valores dependendo da classe usando divisão
    double playerHPcurr; //coloquei muitas equações nos prints para ficar mais facil de quando esses variaveis não forem fixas (quando adicionarmos classes)
    double playerMPmax;
    double playerMPcurr;
    double defesa = 0;
    double enemyHP = 50;
    int danoInimigo, danoPlayer;
    int acao; //menu de combate
    int playerAtk = 0; //usado como modificador adicional de dano
    bool repeat = true;
    int class; 
    
    //array de strings para tipos de inimigos
    char *arr[] = {
        "TROLL",
        "BRUXA",
        "GOLEM",
        "DRAGAO"
    };
    
    printf("Pressione [1] para JOGAR ou [0] para SAIR\n");
    scanf("%i", &jogar);
    if (jogar != 1){
        printf("OBRIGADO POR JOGAR!");
        return 0;
    }

     //Sistema de classes
     do {
    printf("Escolha sua classe:\n");
    printf("[1]Herói");
    printf("[2]Paladino");
    printf("[3]Bruxo\n");
    scanf("%i", &class);
     
        switch (class) {
            case 1: //A classe do herói é basicamente a classe com os status padrão de antes mesmo, se vocês quiserem alterar isso, fiquem a vontade.
                playerHPmax = 30; 
                playerHPcurr = playerHPmax;
                playerMPmax = 20;
                playerMPcurr = playerMPmax;
                repeat = false;  // classe válida, sair do loop
                break;

            case 2: //Classe do Paladino, +HP -MP
                playerHPmax = 30 * 1.35; //Fiz dessa forma para aumentar o HP ou diminuir, mas se acharem uma forma melhor, fiquem a vontade. 
                playerHPcurr = playerHPmax;
                playerMPmax = 20 * 0.75;
                playerMPcurr = playerMPmax;
                repeat = false;  // classe válida, sair do loop
                break;

            case 3: //Classe do Bruxo, -HP +MP 
                playerHPmax = 30 * 0.75;
                playerHPcurr = playerHPmax;
                playerMPmax = 20 * 1.45;
                playerMPcurr = playerMPmax;
                repeat = false;  // classe válida, sair do loop
                break;

            default:
                printf("Classe inválida! Por favor, escolha novamente.\n");
                break;
        }
    } while (repeat); // Caso o usuário insira um número errado, volta pro início para escolher uma classe 

     if (jogar == 1 && class >= 1 || class <= 3){
        jogando = true;
        printf("SUA VIDA = %.1lf/%.1lf SUA MANA = %.1lf/%.1lf\nVIDA DO INIMIGO = %.1lf\n", playerHPcurr, playerHPmax, playerMPcurr, playerMPmax, enemyHP);
        int min = 0;
        int max = 3;
        int randomInRange = (rand() % (max - min + 1)) + min;
        printf("VOCE ENCONTROU %s\n", arr[randomInRange]);
    } else {
        printf("Obrigado por jogar!\n");
        return 0;
    }
    // do while para rodar o codigo e depois testar a condicao
    do {
        printf("SELECIONE A AÇÃO\n");
        printf("[1] ATAQUE NORMAL ");
        printf("[2] MAGIA ");
        printf("[3] DEFENDER ");
        printf("[4] FUGIR\n" );
        scanf("%i", &acao);
        Sleep(1000);

        if (acao < 1 || acao > 4) {
            printf("Ação inválida. Escolha uma ação válida (1, 2, 3 ou 4).\n");
            continue;
        }
        if (acao == 1) {
            int dMin = 5+playerAtk;
            int dMax = 15+playerAtk;
            int randomDano = (rand() % (dMax - dMin + 1)) + dMin;
            danoPlayer = randomDano;
            enemyHP -= danoPlayer;
            playerMPcurr += playerMPmax/5;
            printf("VOCÊ USOU ATAQUE NORMAL E RECEBEU +%.1lf MANA\n", playerMPmax/5);
            Sleep(1000);
            printf("DANO: %i\n", danoPlayer);
        } else if (acao == 2) {
            printf("Escolha uma magia: [1] Ataque Especial(%.1lf) [2] Cura(%.1lf) [3] Atk Buff(%.1lf) [4] Meditar(+%.1lf) [Outro Número] Voltar\n", playerMPmax*3/4, playerMPmax*2/5, playerMPmax*1/2,playerMPmax*3/4);
            scanf("%i", &acao);
            switch (acao) //começa os efeitos de cada magia
            {
            case 1: //ataque especial
                if (playerMPcurr >= playerMPmax*3/4){ //verificar a mana do player 
                playerMPcurr -= playerMPmax*3/4;
                int dMin = 16+2*playerAtk;
                int dMax = 25+2*playerAtk;
                int randomDano = (rand() % (dMax - dMin + 1)) + dMin;
                danoPlayer = randomDano;
                enemyHP -= danoPlayer;
                printf("VOCÊ USOU ATAQUE ESPECIAL E GASTOU %.1lf MANA!\n", playerMPmax*3/4);
                Sleep(1000);
                printf("DANO: %i\n", danoPlayer);
                break;
                } else { //caso o player não tenha mana
                    printf("Sem mana suficiente\n");
                    continue;
                }
            case 2: //cura
                if (playerMPcurr >= playerMPmax*2/5){
                playerMPcurr -= playerMPmax*2/5;
                playerHPcurr += playerMPmax*1/2;
                printf("VOCÊ RECUPEROU +%.1lf HP E GASTOU %.1lf MANA\n", playerMPmax/2, playerMPmax*2/5);
                Sleep(1000);
                break;
                } else {
                    printf("Sem mana suficiente\n");
                    Sleep(1000);
                    continue;
                }
            case 3: //buffar
                if (playerMPcurr >= playerMPmax*1/2){
                playerMPcurr -= playerMPmax*1/2; 
                playerAtk += playerMPmax*1/5;
                printf("VOCÊ RECEBEU +4 Atk E GASTOU %.1lf MANA\n", playerMPmax/2);
                Sleep(1000);
                break;
                } else {
                    printf("Sem mana suficiente\n");
                    Sleep(1000);
                    continue; 
                }
            case 4: //meditar (defender para magos)
                playerMPcurr += playerMPmax*3/4;
                defesa += playerMPmax*1/4; //essa defesa escala com mana ao invés de hp
                printf("VOCÊ SE DEFENDEU DE NO MÁXIMO %.1lf DE DANO E RECUPEROU +%.1lf MANA\n", defesa, playerMPmax*3/4);
                Sleep(1000);
                break;
            default: 
                continue; //voltar
            }

        } else if (acao ==3) { //defender
            defesa += playerHPmax/2; //usada na formula de dano recebido, escala com hp maxímo
            playerMPcurr += playerMPmax/2.5;
            printf("VOCÊ SE DEFENDEU DE NO MÁXIMO %.1lf DE DANO E RECEBEU +%.1lf MANA\n", defesa, playerMPmax*2/5);
            Sleep(1000);
        } else if (acao == 4) { //fugir
            int min = 0;
            int max = 3;
            int randomInRange = (rand() % (max - min + 1)) + min;
            printf("VOCE FUGIU E ENCONTROU %s\n", arr[randomInRange]);
            Sleep(1000);
        }

        printf(".");
        Sleep(1000);
        printf(".");
        Sleep(1000);
        printf(".\n");
        Sleep(1000);
        
        // Inimigo ataca
        printf("SEU INIMIGO USOU (placeholder)!\n");
        Sleep(1000);
        
        danoInimigo = 6-defesa;
        
        if (playerHPcurr > playerHPmax) playerHPcurr = playerHPmax; // impedir de HP e mp de passar do limite, dano negativo e HP negativo
        if (playerMPcurr > playerMPmax) playerMPcurr = playerMPmax; //
        if (enemyHP < 0) enemyHP = 0;                               // 
        if (danoInimigo < 0) danoInimigo = 0;                       // dano do inimigo não ficar negativo por causa da formula de defesa
        
        playerHPcurr -= danoInimigo;
        printf("DANO: %i\n", danoInimigo);

        printf(".");
        Sleep(1000);
        printf(".");
        Sleep(1000);
        printf(".\n");
        Sleep(1000);

        printf("SUA VIDA = %.1lf/%.1lf SUA MANA = %.1lf/%.1lf\nVIDA DO INIMIGO = %.1lf\n", playerHPcurr, playerHPmax, playerMPcurr, playerMPmax, enemyHP);
        
        defesa = 0; //resetar a defesa no final do turno

        if (playerHPcurr <= 0 && enemyHP <= 0){
            printf("Você morreu, mas com honrra! Fim de jogo.\n");
        } else if (playerHPcurr <= 0) {
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