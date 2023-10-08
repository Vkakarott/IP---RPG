#include <stdio.h>
#include <stdbool.h> //biblioteca de valores booleanos
#include <stdlib.h> //biblioteca de gerar aleatorios
#include <time.h>
#include <unistd.h>

//FUNCOES
    //estilo
void loading(){
    printf(".");
    sleep(1000);
    printf(".");
    sleep(1000);
    printf(".\n");
    sleep(1000);
}

void input(const char *arg, void *var){
    printf("> ");
    if (arg[0] == '%') {
        if (arg[1] == 'i') {
            scanf("%d", (int *)var);
        } else if (arg[1] == 'f') {
            scanf("%lf", (double *)var);
        }
    }
}

void divisor(){
    printf("-----------------------------------------\n");
}

void linha(){
    printf(" \n");
}

//Barra de status atual
void status(int HPAtual, int HPMaxima, int manMax, int manaAtual) {
    int bar = 10; // Tamanho total da barra de HP

    // Barra de Vida
    int preenchidaHP = (int)((double)HPAtual / HPMaxima * bar);
    printf("VIDA: [");
    for (int i = 0; i < bar; i++) {
        if (i < preenchidaHP) {
            printf("#"); // Caractere para representar a HP
        } else {
            printf(" "); // Espaço em branco para representar a parte vazia da barra
        }
    }
    printf("] %d/%d\n", HPAtual, HPMaxima);

    // Barra de mana
    int barM = 5;
    printf("MANA: [");
    for (int i = 0; i < barM; i++) {
        if (i < manaAtual) {
            printf("#"); // Caractere para representar a Mana
        } else {
            printf(" "); // Espaço em branco para representar a parte vazia da barra
        }
    }
    printf("] %d/%d\n", manaAtual, manMax);
}

hpEnemy(int enemyHP, int enemyHPMax){
    int bar = 10;
    int barEny = (int)((double)enemyHP / enemyHPMax * bar);
    printf("HP INIMIGA: [");
    for(int i = 0; i < bar; i++){
        if(i < bar){
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("} %d/%d\n", enemyHP, enemyHPMax);
}

//CODIGO PRINCIPAL
int main(){
    srand(time(NULL)); //tempo atual

    int jogar;
    int class;
    bool repeat = true;
    bool jogando = false;
    int HPMaxima = 50;
    int HPAtual = 50;
    int manaMax = 5;
    int manaAtual;
    double res;
    double atk;
    int esq;
    int acao;
    int dano;
    int atkBase = 10;
    int atkEsp = 20;
    int enemyHP;
    int enemyHPMax = 50;
    int danoEnemy = 10;
    double playerHPmax; //transformei essas variáveis em double pra ficar mais facil de escalar os valores dependendo da classe usando divisão

    //array de strings
    char *arr[] = {
        "TROLL",
        "BRUXA",
        "GOLLEN",
        "DRAGAO"
    };

    //INICIO
    divisor();
    printf("Precione [1] para JOGAR ou [0] para SAIR\n");
    input("%i", &jogar);
    if(jogar == 0){
        divisor();
        printf("          OBRIGADO! ATE A PROXIMA.\n");
        divisor();
    }

    //ESCOLHA DE CLASSES
    do {
        printf("Escolha sua Classe:\n");
        printf("[1]Herói\n");
        printf("[2]Paladino\n");
        printf("[3]Bruxo\n");
        printf("[4]Ranger\n");
        printf("[5]Ninja\n");
        input("%i", &class);

        switch (class){
            case 1:
                res = 0.5;
                atk = 1.7;
                manaAtual = 1;
                esq = 20;
                printf("Voce escolheu o Heroi!\n");
                repeat = false;
                break;
            case 2:
                res = 0.1;
                atk = 1.5;
                manaAtual = 1;
                int esq = 10;
                printf("Voce escolheu o Paladino!\n");
                repeat = false;
                break;
            case 3:
                res = 0.9;
                atk = 1.7;
                manaAtual = 4;
                esq = 30;
                printf("Voce escolheu o Bruxo!\n");
                repeat = false;
                break;
            case 4:
                res = 0.9;
                atk = 1.5;
                manaAtual = 1;
                esq = 30;
                printf("Voce escolheu o Ranger!\n");
                repeat = false;
                break;
            case 5:
                res = 0.9;
                atk = 1.9;
                manaAtual = 1;
                esq = 50;
                printf("Voce escolheu o Ninja!\n");
                repeat = false;
                break;
            default:
                printf("Classe invalida! Tente novamente.\n");
                break;
        }
    } while (repeat); //Caso o usuario insira o numero errado o loop continua

    if(jogar == 1 && class >= 1 || class <= 3){
        jogando = true;
        divisor();
        status(HPAtual, HPMaxima, manaMax, manaAtual);
        divisor();
        int min = 0;
        int max = 3;
        int randomInRange = (rand() % (max - min + 1)) + min;
        printf("VOCE ENCONTROU %s\n", arr[randomInRange]);
        hpEnemy(enemyHP, enemyHPMax);
    }
    // do while para rodar o codigo e depois testar a condicao
    do {
        linha();
        if(class == 1 || class == 2){
            printf("SELECIONE A AÇÃO\n");
            printf("[1] ATAQUE NORMAL\n");
            printf("[2] MAGIA\n");
            printf("[3] DEFENDER\n");
            printf("[4] FUGIR\n" );
            input("%i", &acao);
            sleep(1000);
        }
        if(acao == 1){
            dano = atkBase * atk;
            enemyHP -= dano;
            manaAtual += 1;
            printf("VOCE USOU ATAQUE NORMAL:\nCAUSOU %d DE DANO\nRECEBEU %d DE DANO\nRECEBEU + 1 DE MANA", dano, danoEnemy);
            status(HPAtual, HPMaxima, manaMax, manaAtual);
            divisor();
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
                sleep(1000);
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
                sleep(1000);
                break;
                } else {
                    printf("Sem mana suficiente\n");
                    sleep(1000);
                    continue;
                }
            case 3: //buffar
                if (playerMPcurr >= playerMPmax*1/2){
                playerMPcurr -= playerMPmax*1/2; 
                playerAtk += playerMPmax*1/5;
                printf("VOCÊ RECEBEU +4 Atk E GASTOU %.1lf MANA\n", playerMPmax/2);
                sleep(1000);
                break;
                } else {
                    printf("Sem mana suficiente\n");
                    sleep(1000);
                    continue; 
                }
            case 4: //meditar (defender para magos)
                playerMPcurr += playerMPmax*3/4;
                defesa += playerMPmax*1/4; //essa defesa escala com mana ao invés de hp
                printf("VOCÊ SE DEFENDEU DE NO MÁXIMO %.1lf DE DANO E RECUPEROU +%.1lf MANA\n", defesa, playerMPmax*3/4);
                sleep(1000);
                break;
            default: 
                continue; //voltar
            }
        }
    }
    
    return 0;
}
