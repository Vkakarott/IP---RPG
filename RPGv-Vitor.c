#include <stdio.h> //Biblioteca de input e output
#include <stdbool.h> //Valores booleanos
#include <stdlib.h> //Função rand
#include <time.h> //Tempo
#include <unistd.h> //Sleep no linux
#include <string.h>//Biblioteca de strings (para uso de strcmp, que compara strings)

//Cores
void red() {
    printf("\033[0;31m");
}
void green() {
    printf("\033[0;32m");
}
void yellow() {
    printf("\033[0;33m");
}
void blue() {
    printf("\033[0;34m");
}
void purple() {
    printf("\033[0;35m");
}
void cyan() {
    printf("\033[0;36m");
}
void white() {
    printf("\033[0;37m");
}

void loading(){ //Função que mostra os 3 pontinhos
    white();
    for(int i = 0; i < 3; i++){
        printf(".");
        fflush(stdout); // Força o print a sair imediatamente
        sleep(1);
    }
    printf("\n");
}

void abertura() {
    const char *lines[] = {
        "         _____                  _____     _____    _______",
        "|   /   |     |   |\\      /|   |     |   |     |      |  ",
        "|  /    |     |   | \\    / |   |     |   |     |      |  ",
        "| /     |     |   |  \\  /  |   |_____|   |     |      |  ",
        "|/      |     |   |   \\/   |   |_____    |_____|      |  ",
        "|\\      |     |   |        |   |     |   |     |      |  ",
        "| \\     |     |   |        |   |     |   |     |      |  ",
        "|  \\    |     |   |        |   |     |   |     |      |  ",
        "|   \\   |_____|   |        |   |_____|   |     |      |  ",
        "                                                          ",
        " _____     _____     _____                                ",
        "|     |   |     |   |                                     ",
        "|     |   |     |   |                                     ",
        "|_____|   |     |   |                                     ",
        "| \\       |_____|   |   ___                              ",
        "|  \\      |         |     |                              ",
        "|   \\     |         |     |                              ",
        "|    \\    |         |     |                              ",
        "|     \\   |         |_____|                              "
    };

    int numLinhas = 19;
    int numCol = 59;
    int lin;
    int col;
    
    getchar();

    for (lin = 0; lin < numLinhas; lin++) {
        for (col = 0; col < numCol; col++) {
            if (lines[lin][col] != '\0') {
                printf("\033[0;34m%c", lines[lin][col]);
            } else {
                printf(" ");
            }
            fflush(stdout);
            usleep(1000); // 0.001 segundos
        }
        printf("\n");
    }
    printf("\n");
    printf("\033[0;32mPRESSIONE ENTER PARA JOGAR\n");
    getchar();
}

void input(const char *arg, void *var){ //Função que recebe entrada, com um estilo
    white();
    printf("> ");
    if (arg[0] == '%') {
        if (arg[1] == 'i') {
            scanf("%d", (int *)var);
        } else if (arg[1] == 'f') {
            scanf("%lf", (double *)var);
        }
    }
}

void divisor(){ //Função que mostra uma linha divisoria entre blocos
    white();
    printf("-----------------------------------------\n");
}

//Barra de status atual
void status(int HPAtual, int HPMaxima, int manaMax, int manaAtual, int playerLvl, int pontos, int class, int pocaoHP, int pocaoMP) {
    int bar = 10; // Tamanho total da barra de HP

    // Barra de Vida
    int preenchidaHP = (int)((double)HPAtual / HPMaxima * bar);
    red();
    printf("VIDA: [");
    for (int i = 0; i < bar; i++) {
        if (i < preenchidaHP) {
            printf("#"); // Caractere para representar a HP
        } else {
            printf(" "); // Espaço em branco para representar a parte vazia da barra
        }
    }
    printf("] %d/%d    ", HPAtual, HPMaxima);
    yellow();
    printf("PONTOS: %d\n", pontos);

    // Barra de mana
    int barM = 10;
    int preenchidaMana = (int)((double)manaAtual / manaMax * barM);
    blue();
    printf("MANA: [");
    for (int i = 0; i < barM; i++) {
        if (i < preenchidaMana) {
            printf("#"); // Caractere para representar a Mana
        } else {
            printf(" "); // Espaço em branco para representar a parte vazia da barra
        }
    }
    printf("] %d/%d     ", manaAtual, manaMax);
    yellow();
    printf("LEVEL: %d\n", playerLvl);
    if (class == 4) {
        green();
        printf("POCOES DE CURA: %d   POCOES DE MANA: %d\n", pocaoHP, pocaoMP);
    }
}

//Status do inimigo
void hpEnemy(int enemyHP, int enemyHPMax, int enemyLvl, const char *enemyName){
    int bar = 10;
    int barEny = (int)((double)enemyHP / enemyHPMax * bar);
    red();
    printf("HP %s: [", enemyName);
    for(int i = 0; i < bar; i++){
        if(i < barEny){
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("] %d/%d ", enemyHP, enemyHPMax);
    yellow();
    printf("LVL: %d\n", enemyLvl);
}

//Menu de magias
void magia(int class, bool magiaMenu, int* HPMaxima, int* HPAtual, int* manaMax, int* manaAtual, int* manaTemp, int manaTempMax, int* defesa, int* res, int* forca, int* acao, int dano, int* atkBase, int* enemyHP, int* contraataque, int* burnMago, bool* stun, int* pocaoHP, int* pocaoMP){
    if (magiaMenu){
        switch(class) {
            case 1: //HABILIDADES DO GUERREIRO
            red();
            printf("Escolha uma magia:\n[1] Golpe Ciclone (-%iMP)\n[2] Sifao (-%iMP)\n[3] Furia (-%iHP)\n[4] Descansar (+%iMP)\n[Outro] Voltar\n", *manaMax*3/4, *manaMax/2, *HPMaxima/3, *manaMax);   
            input("%i",&*acao);
            sleep(1);
            switch (*acao){
            case 1:
                if (*manaAtual >= *manaMax*3/4) {
                    *manaAtual -= *manaMax*3/4;
                    dano = 0.4 * *atkBase * (1+0.2 * *forca);
                    *enemyHP -= dano * 4;
                    red();
                    printf("VOCÊ USOU GOLPE CICLONE E GASTOU %d MANA!\n", *manaMax*3/4);
                    sleep(1);
                    for (int i = 0; i < 4; i ++) {
                    printf("DANO: %i\n", dano);
                    usleep(10000);
                    }
                    break;
                } else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                }
            case 2:
                if (*manaAtual >= *manaMax/2) {
                    *manaAtual -= *manaMax/2;
                    dano = 1.3 * *atkBase * (1+0.1 * *forca);
                    *enemyHP -= dano;
                    *HPAtual += dano/2;
                    red();
                    printf("VOCE USOU SIFAO, CUROU %d DE HP E GASTOU %d MANA\n", dano/2, *manaMax/2);
                    sleep(1);
                    printf("DANO: %i\n", dano);
                    sleep(1);
                    break;
                } else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                break;
                }
            case 3:
                if (*HPAtual >= *HPMaxima/3) {
                    *HPAtual -= *HPMaxima/3;
                    *forca += *HPMaxima/8;
                    red();
                    printf("VOCE USOU FURIA, RECEBEU %d DE FORCA E GASTOU %d DE HP\n", *HPMaxima/8, *HPMaxima/3);
                    sleep(1);
                    break;
                } else {
                    blue();
                    printf("Sem HP suficiente\n");
                    *acao = 5;
                    break;
                }
            case 4:
                    *manaAtual = *manaMax;
                    red();
                    printf("VOCE DESCANSOU E RECUPEROU TODA SUA MANA\n");
                    sleep(1);
                    break;
            default:
                break;
            }
        break;
            case 2: //HABILIDADES DE PALADINO
            cyan();
            printf("Escolha uma magia:\n[1] Investida de Escudo (-%iMP)\n[2] Rezar (-%iMP+%iHP)\n[3] Parede Inquebravel (-%iMP)\n[4] Protecao Divina(-%iMP)\n[Outro] Voltar\n", *manaMax*3/4, *manaMax/2, *HPMaxima*2/3, *manaMax*2/3, *manaMax/3);
            input("%i",&*acao);
            sleep(1);
            switch (*acao){
                case 1:
                if (*manaAtual >= 3/4 * *manaMax) {
                    *manaAtual -= 3 * *manaMax/4;
                    dano = 1.3 * *atkBase * (1+0.1 * *res);
                    *enemyHP -= dano;
                    printf("VOCE USOU INVESTIDA DE ESCUDO E GASTOU %d MANA!\n", *manaMax*3/4);
                    sleep(1);
                    printf("DANO: %i\n", dano);
                    sleep(1);
                    break;
                } else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                }
                case 2:
                if (*manaAtual >= *manaMax/2) {
                    *manaAtual -= *manaMax/2;
                    *HPAtual += *HPMaxima*2/3;
                    cyan();
                    printf("VOCE REZOU, GASTOU %d DE MANA E RECEBEU %d DE HP\n", *manaMax/2, *HPMaxima*2/3);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                }
                case 3:
                if (*manaAtual >= *manaMax*2/3) {
                    *manaAtual -= *manaMax*2/3;
                    *res += *manaMax/6;
                    cyan();
                    printf("VOCE USOU PAREDE INQUEBRAVEL, GASTOU %d DE MANA E RECEBEU %d DE RESISTENCIA\n", *manaMax*2/3, *manaMax/6);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                }
                case 4:
                if(*manaAtual >= *manaMax/3) {
                    *manaAtual -= *manaMax/3;
                    *contraataque += *res;
                    *defesa += *HPMaxima/10;
                    cyan();
                    printf("VOCE USOU PROTECAO DIVINA, GASTOU %d DE MANA, BLOQUEOU %d DE DANO, E CONTRAATACA TODA VEZ QUE TOMA DANO POR %d DE DANO\n", *manaMax/3, *defesa, *contraataque);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                }
                default: 
                    break;
            }
            break;
            case 3:
            purple();
            printf("Escolha uma magia:\n[1] Explosao De Mana (-%iMP)\n[2] Furia dos Espiritos (-%iMP+%iHP)\n[3] Sobrecarregar (+%iMPMAX)\n[4] Meditar (+%iMP)\n[Outro] Voltar\n", *manaMax-*manaTemp, (*manaMax-*manaTemp)/2, *HPMaxima/4, manaTempMax, *manaMax*3/4);
            input("%i",&*acao);
            sleep(1);
            switch (*acao){
                case 1:
                if(*manaAtual >= *manaMax-*manaTemp) {
                    *manaAtual -= *manaMax-*manaTemp;
                    dano = *atkBase * (0.05 * *manaMax);
                    *enemyHP -= dano;
                    printf("VOCE USOU EXPLOSAO DE MANA E GASTOU %d MANA!\n", *manaMax-*manaTemp);
                    sleep(1);
                    printf("DANO: %i\n", dano);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                }
                case 2:
                if(*manaAtual >= (*manaMax-*manaTemp)/2) {
                    *manaAtual -= (*manaMax-*manaTemp)/2;
                    *burnMago += *manaMax/8;
                    *HPAtual += *HPMaxima/4;
                    printf("VOCE USOU FURIA DOS ESPIRITOS, SUGANDO A ALMA DO INIMIGO, RESTAUROU %d HP E GASTOU %d MANA", *HPMaxima/4, (*manaMax-*manaTemp)/2);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                }
                case 3:
                if (*manaTemp == 0) {
                    *manaTemp += *manaMax*6/5;
                    *manaMax += *manaTemp;
                    printf("VOCE SOBRECARREGOU, GANHANDO +%d DE MANA MAXIMA TEMPORARIA\n", manaTempMax);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Voce ja esta sobrecarregado!\n");
                    *acao = 5;
                    break;
                }
                case 4:
                    *manaAtual += *manaMax*3/4;
                    *defesa += *manaMax/6;
                    printf("VOCE MEDITOU, GANHANDO +%d DE MANA E BLOQUEANDO %d DE DANO\n", *manaMax*3/4, *manaMax/6);
                    sleep(1);
                    break;
                default:
                    break;
            }
            break;
            case 4:
            green();
            printf("Escolha uma magia:\n[1] Tiro potente (-%iMP)\n[2] Usar pocao de cura (+%iHP)\n[3] Tiro enfraquecedor (-%iMP)\n[4] Usar pocao de mana(+%iMP)\n[Outro] Voltar\n", *manaMax, *HPMaxima, *manaMax/2, *manaMax);
            input("%i",&*acao);
            sleep(1);
            switch (*acao){
                case 1:
                if (*manaAtual >= *manaMax) {
                    *manaAtual -= *manaMax;
                    dano = 2 * *atkBase * (1+0.1 * *forca);
                    *enemyHP -= dano;
                    *stun = true;
                    printf("VOCE USOU TIRO POTENTE, ATORDOANDO O INIMIGO E GASTANDO %d MANA!\n", *manaMax);
                    sleep(1);
                    printf("DANO: %i\n", dano);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                }
                case 2:
                if (*pocaoHP > 0) {
                    *pocaoHP -= 1;
                    *HPAtual += *HPMaxima;
                    printf("VOCE USOU UMA POCAO DE CURA E CUROU %d DE HP\n", *HPMaxima);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Voce nao tem uma pocao\n");
                    *acao = 5;
                    break;
                }
                case 3:
                if (*manaAtual >= *manaMax/2) {
                    *manaAtual -= *manaMax/2;
                    *res += *manaMax/4;
                    dano = 1.3 * *atkBase * (1+0.1 * *forca);
                    *enemyHP -= dano;
                    printf("VOCE USOU TIRO ENFRAQUECEDOR, ENFRAQUECENDO O INIMIGO E GASTANDO %d MANA\n", *manaMax/2);
                    sleep(1);
                    printf("DANO: %i\n", dano);
                    sleep(1);
                    break;
                } else {
                    blue();
                    printf("Sem mana suficiente\n");
                    *acao = 5;
                    break;
                }
                case 4:
                if (*pocaoMP > 0) {
                    *pocaoMP -= 1;
                    *manaAtual += *manaMax;
                    printf("VOCE USOU UMA POCAO DE MANA E RECEBEU %d MANA\n", *manaMax);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Voce nao tem uma pocao\n");
                    *acao = 5;
                    break;
                }
                default:
                    break;
            }
            break;
        }
    }
}

//Verificar se a batalha acabou e o resultado
void checkWin(int HPAtual, int enemyHP, int *jogando, int *levelUp, int *playerLvl, int *enemyLvl, int *pontos, int *contraataque, int *burnMago, int *enemyIndex, int *nMobs, const char *mobs[], int bossFinal) {
    sleep(1);

    if (HPAtual <= 0) {
        white();
        printf("Voce morreu. Fim de jogo.\n");
        *jogando = false;
    } else if (enemyHP <= 0) {
        white();
        printf("Voce derrotou o inimigo!\n");

        int mobsCount = *nMobs;
        for (int i = *enemyIndex; i < mobsCount - 1; i++) {
            mobs[i] = mobs[i + 1];
        }
        mobs[mobsCount - 1] = NULL;
        (*nMobs)--;
        if (*nMobs < 1) { 
            bossFinal = true;
        }
        *playerLvl += 1;
        *enemyLvl += *playerLvl;
        *pontos += *enemyLvl;
        *contraataque = 0;
        *burnMago = 0;
        *levelUp = true;
        loading();
        yellow();
        printf("Voce ganhou +%d pontos!\n", *enemyLvl);
        divisor();
    }
}

//Proxima rodada
void escalamento(int class, int *atkBase, int *res, int* forca, int* HPMaxima, int* HPAtual, int* manaMax, int* manaAtual, int* manaTempMax, int* manaTemp, int playerLvl, int enemyLvl, int* enemyHPMax, int* enemyHP, int* enemyBaseAtk, int* pocaoHP, int* pocaoMP, const char *mobs[], bool bossFinal, int nMobs, int enemyIndex){

switch (class){
            case 1:
                *atkBase = 10+3*playerLvl;
                *res = 1;
                *forca = 2 + 1*playerLvl;
                *HPMaxima = 50 + 10*playerLvl;
                *HPAtual = *HPMaxima;
                *manaMax = 20 + 4*playerLvl;
                *manaAtual = *manaMax;
                yellow();
                printf("LEVEL UP! Voce recebeu:\n+3 ATK\n+1 FORCA\n+10 HP\n+4 MANA\n");
                break;
            case 2:
                *atkBase = 10 + 2*playerLvl;
                *res = 2 + 1*playerLvl;
                *forca = 0;
                *HPMaxima = 60 + 15*playerLvl;
                *HPAtual = *HPMaxima;
                *manaMax = 30 + 6*playerLvl;
                *manaAtual = *manaMax;
                yellow();
                printf("LEVEL UP! Voce recebeu:\n+2 ATK\n+1 RES\n+15 HP\n+6 MANA\n");
                break;
            case 3:
                *atkBase = 8 + 2*playerLvl;
                *res = 0;
                *forca = 0;
                *HPMaxima = 40 + 10 * playerLvl;
                *HPAtual = *HPMaxima;
                *manaMax = 50 + 10 * playerLvl;
                *manaAtual = *manaMax;
                *manaTemp = 0;
                *manaTempMax = *manaMax;
                yellow();
                printf("LEVEL UP! Voce recebeu:\n+2 ATK\n+10 HP\n+10 MANA\n");
                break;
            case 4:
                *atkBase = 14 + 4*playerLvl;
                *res = 0;
                *forca = 0;
                *HPMaxima = 40 + 8*playerLvl;
                *HPAtual = *HPMaxima;
                *manaMax = 20 + 2*playerLvl;
                *manaAtual = *manaMax;
                *pocaoHP = 2;
                *pocaoMP = 2;
                yellow();
                printf("LEVEL UP! Voce recebeu:\n+4 ATK\n+8 HP\n+2 MANA\n");
                break;
            default:
                red();
                printf("Meu deus eu devo ter feito muita merda\n");
                break;
        }
        divisor();

        if(bossFinal){
            printf("Voce chegou no boss final O PROFESSOR!!!");
            //Criar boss final
        } else {
            enemyIndex = rand() % nMobs;
            int enemyIndex2 = enemyIndex;
            sleep(1);
            white();
            printf("VOCE ENCONTROU %s\n", mobs[enemyIndex2]);
            sleep(1);
            *enemyHPMax += 10 * enemyLvl;
            *enemyHP = *enemyHPMax;
            *enemyBaseAtk += 2 * enemyLvl;
        }
}

//Função para os ataques específicos de inimigos
void inimigoAtacar(bool* inimigoAtacou, int enemyIndex, const char* mobs[], const char* atksTroll[], const char* atksBruxa[], const char* atksGolem[], const char* atksDragao[], int *inimigoBaseAtk, int* inimigoAtk, int *enemyHPMax, int *enemyHP, int *res, int *enemyLvl,int enemyAtkIndex, int lastEnemyAtk) {
    bool carregar = false;   //usar ataques carregados
    if (lastEnemyAtk == 2){
        enemyAtkIndex = rand() % 2;
    } else {
        enemyAtkIndex = rand() % 3;
    }
    int lastEnemyAtkk = enemyAtkIndex;
    if (strcmp(mobs[enemyIndex], "TROLL") == 0){        //Troll
        green();
        printf("%s USOU %s!\n", mobs[enemyIndex], atksTroll[enemyAtkIndex]);
        sleep(1);
        if (enemyAtkIndex == 0) {   //Paulada
            *inimigoAtk = *inimigoBaseAtk;
            *inimigoAtacou = true;
        }

        if (enemyAtkIndex == 1) {   //Garras Afiadas
            *inimigoAtk = *inimigoBaseAtk * 3/2;
            *inimigoAtacou = true;
        }

        if (enemyAtkIndex == 2) {   //Grito Bestial
            *inimigoBaseAtk += (10 + 2 **enemyLvl) * 1/3;
            green();
            printf("O INIMIGO AUMENTOU SEU ATK EM %d\n", (10 + 2 **enemyLvl) * 1/3);
        }
    }
    if (strcmp(mobs[enemyIndex], "BRUXA") == 0){   //Bruxa
        purple();
        printf("%s USOU %s!\n", mobs[enemyIndex], atksBruxa[enemyAtkIndex]);
        sleep(1);
        if (enemyAtkIndex == 0) {   //Raio Sombrio
            *inimigoAtk = *inimigoBaseAtk;
            *inimigoAtacou = true;
        }

        if (enemyAtkIndex == 1) {    // Gas toxico
            *inimigoAtk = *inimigoBaseAtk * 3/2;
            *inimigoAtacou = true;
        }

        if (enemyAtkIndex == 2) {    // Atolar
            *res -= 3;
            purple();
            printf("O INIMIGO REDUZIU SUA RESISTENCIA EM 3\n");
        }
    }
    if (strcmp(mobs[enemyIndex], "GOLEM") == 0){   //Golem
        cyan();
        printf("%s USOU %s!\n", mobs[enemyIndex], atksGolem[enemyAtkIndex]);
        sleep(1);
        if (enemyAtkIndex == 0)  {   //Impacto Meteoro
            *inimigoAtk = *inimigoBaseAtk * 5/3;
            *inimigoAtacou = true;
        }
        if (enemyAtkIndex == 1) {  // Terremoto
            *inimigoAtk = *inimigoBaseAtk * 3/2;
            *inimigoAtacou = true;
        }
        if (enemyAtkIndex == 2) {   //Fortalecer
            *enemyHPMax += (50 + 7 * *enemyLvl) * 1/3;
            *enemyHP += (50 + 7 * *enemyLvl) * 1/3;
            cyan();
            printf("O INIMIGO AUMENTOU SEU HP EM %d\n", (50 + 10 * *enemyLvl) * 1/3);
        }

    }
    if (strcmp(mobs[enemyIndex], "DRAGAO") == 0) {   //Dragao
        red();
        printf("%s USOU %s!\n", mobs[enemyIndex], atksDragao[enemyAtkIndex]);
        sleep(1);

        if (enemyAtkIndex == 0) {   //Furacao
            *inimigoAtk = *inimigoBaseAtk;
            *inimigoAtacou = true;
        }
        if (enemyAtkIndex == 1)  {  //Chamas Infernais
            *inimigoAtk = *inimigoBaseAtk * 5/3;
            *inimigoAtacou = true;
        }
        if (enemyAtkIndex == 2) {   //Rugido Draconico
            *inimigoBaseAtk += (10 + 2 * *enemyLvl) * 1/3;
            red();
            printf("O INIMIGO AUMENTOU SEU ATK EM %d\n", (10 + 2 **enemyLvl) * 1/3);
        }
    }
}

//Função principal
int main(){
    srand(time(NULL)); //Tempo atual

    //Variaveis
    int jogar;
    int class;
    int atkBase;
    int enemyAtkIndex = 0;
    int playerLvl = 1;
    int nMobs = 4;
    int pontos = 0;
    int enemyLvl = 1;
    int manaTemp = 0;
    int defesa = 0;
    int contraataque = 0;
    int burnMago = 0;
    int acao;
    int dano;
    int res;
    int forca;
    int HPMaxima;
    int HPAtual;
    int manaMax;
    int manaAtual;
    int manaTempMax;
    int pocaoHP;
    int pocaoMP;
    int enemyIndex;
    int enemyIndex2;
    int enemyHPMax;
    int enemyHP;
    int danoEnemy;
    int lastEnemyAtk;
    int inimigoAtk;
    int danoInimigo = 0;
    int enemyBaseAtk = 10;
    int inimigoBaseAtk;
    bool levelUp = false;
    bool inimigoAtacou = false;
    bool stun = false;
    bool magiaMenu = false;
    bool repeat = true;
    bool jogando = true;
    bool bossFinal = false;

    //Array de strings
    const char *mobs[] = {"TROLL", "BRUXA", "GOLEM", "DRAGAO", NULL};
    const char *atksTroll[] = {"Paulada","Garras Afiadas","Grito Bestial",};
    const char *atksBruxa[] = {"Raio Sombrio","Gas Toxico","Atolar",};
    const char *atksGolem[] = {"Impacto Meteoro","Terremoto","Fortalecer",};
    const char *atksDragao[] = {"Chamas Infernais","Furacao","Rugido Draconico",};

    //Start
    abertura();

    //Escolha de classes
    do{
        white();
        printf("Escolha sua Classe:\n[1]Guerreiro\n[2]Paladino\n[3]Bruxo\n[4]Arqueiro\n");
        input("%i", &class);
        sleep(1);
        switch (class){ //Cada classe ganha atributos diferentes
            case 1:
                atkBase = 10;
                res = 1;
                forca = 2;
                HPMaxima = 50;
                HPAtual = HPMaxima;
                manaMax = 20;
                manaAtual = manaMax;
                red();
                printf("Voce escolheu o Guerreiro!\n");
                repeat = false;
                break;
            case 2:
                atkBase = 10;
                res = 2;
                forca = 0;
                HPMaxima = 60;
                HPAtual = HPMaxima;
                manaMax = 30;
                manaAtual = manaMax;
                cyan();
                printf("Voce escolheu o Paladino!\n");
                repeat = false;
                break;
            case 3:
                atkBase = 8;
                res = 0;
                forca = 0;
                HPMaxima = 40;
                HPAtual = HPMaxima;
                manaMax = 50;
                manaAtual = manaMax;
                manaTempMax = manaMax;
                purple();
                printf("Voce escolheu o Bruxo!\n");
                repeat = false;
                break;
            case 4:
                atkBase = 14;
                res = 0;
                forca = 0;
                HPMaxima = 40;
                HPAtual = HPMaxima;
                manaMax = 20;
                manaAtual = manaMax;
                pocaoHP = 2;
                pocaoMP = 2;
                green();
                printf("Voce escolheu o Arqueiro!\n");
                repeat = false;
                break;
            default:
                printf("Classe invalida! Tente novamente.\n");
                break;
        }
    } while (repeat);

    
    do {
        enemyIndex = rand() % nMobs;
        sleep(1);
        if(nMobs > 0){
            white();
            printf("VOCE ENCONTROU %s\n", mobs[enemyIndex]);
            sleep(1);
            enemyHPMax = 50;
            enemyHP = 50;
            inimigoBaseAtk = 10;
        }
        
        do {
            loading();
            divisor();
            status(HPAtual, HPMaxima, manaMax, manaAtual, playerLvl, pontos, class, pocaoHP, pocaoMP);
            divisor();
            hpEnemy(enemyHP, enemyHPMax, enemyLvl, mobs[enemyIndex]);
            if(class==1) red();
            if(class==2) cyan();
            if(class==3) purple();
            if(class==4) green();
            printf("SELECIONE A ACAO\n[1] ATAQUE NORMAL\n[2] MAGIA\n[3] DEFENDER\n[4] SAIR\n");
            input("%i", &acao);
            sleep(1);

            if(acao == 1){
                dano = atkBase * (1+0.1*forca);
                enemyHP -= dano;
                manaAtual += manaMax/10;
                printf("VOCE USOU ATAQUE NORMAL, CAUSOU %d DE DANO E RECEBEU %d DE MANA\n", dano, manaMax/10);
                sleep(1);
            } else if (acao == 2) {
                magiaMenu = true;
                magia(class, &magiaMenu, &HPMaxima, &HPAtual, &manaMax, &manaAtual, &manaTemp, manaTempMax, &defesa, &res, &forca, &acao, dano, &atkBase, &enemyHP, &contraataque, &burnMago, &stun, &pocaoHP, &pocaoMP);
                if (acao > 4 || acao <1) {
                    magiaMenu = false;
                    sleep(1);
                continue;
                }   
            } else if (acao ==3) { //defender
                defesa += HPMaxima/2; //usada na formula de dano recebido, escala com hp maxímo
                manaAtual += manaMax/2.5;
                printf("VOCÊ SE DEFENDEU DE NO MÁXIMO %d DE DANO E RECEBEU +%d MANA\n", defesa, manaMax*2/5);
                sleep(1);
            }  else if (acao == 4) { 
                jogando = false;
                sleep(1);
            } else continue;

            loading();
            if (jogando == false) break;
            if (HPAtual > HPMaxima) HPAtual = HPMaxima;    // impedir de HP e mp de passar do limite, dano negativo e HP negativo
            if (manaAtual > manaMax) manaAtual = manaMax;  
            if (enemyHP < 0) enemyHP = 0; 

            // Inimigo ataca
            if(enemyHP > 0){
                if (stun == false) {  //Verifica se o inimigo esta atordoado
                inimigoAtacar(&inimigoAtacou, enemyIndex, mobs, atksTroll, atksBruxa, atksGolem, atksDragao, &inimigoBaseAtk, &inimigoAtk, &enemyHPMax, &enemyHP, &res, &enemyLvl, enemyAtkIndex, lastEnemyAtk);
                if (inimigoAtacou == true) {  // verificar se o inimigo atacou
                    danoInimigo = (inimigoAtk - defesa) / (1 + 0.1 * res);                   
                    if (danoInimigo < 0) danoInimigo = 0;   // dano do inimigo não ficar negativo por causa da formula de defesa
                    defesa = 0;  //resetar a defesa no final do turno
                    HPAtual -= danoInimigo;
                    printf("DANO: %d\n", danoInimigo);
                
                    if (contraataque != 0) {                       // contraataque do paladino
                        enemyHP -= contraataque;
                        contraataque -= contraataque/4;            // contraataque reduz em 25%/turno
                        sleep(1);
                        cyan();
                        printf("VOCE REVIDOU O ATAQUE, CAUSANDO %d DE DANO\n", contraataque*4/3);
                        sleep(1);
                    }
                    inimigoAtacou = false;
                }

            } else {
                printf("O INIMIGO FOI ATORDOADO, MAS SE RECUPEROU\n");
                stun = false;
            }
            if (class == 3) { // coisas exclusivas do mago
                
                if (manaTemp != 0) {
                    manaTemp -= manaTempMax/5;              //mana temporaria reduz em 25%/turno
                    manaMax -= manaTempMax/5;
                }
                
                if (burnMago != 0) {
                    enemyHP -= burnMago;
                    HPAtual += burnMago;
                    burnMago -= burnMago/4;                 //burn reduz em 25%/turno
                    sleep(1);
                    purple();
                    printf("VOCE SUGOU A ALMA DO SEU INIMIGO, CAUSANDO %d DE DANO E CURANDO %d DE VIDA\n", burnMago*4/3, burnMago*4/3);
                    sleep(1);
                }
            }
            }
            if (HPAtual > HPMaxima) HPAtual = HPMaxima;    // impedir de HP e mp de passar do limite, dano negativo e HP negativo
            if (manaAtual > manaMax) manaAtual = manaMax;  
            if (enemyHP < 0) enemyHP = 0;                  //

            checkWin(HPAtual, enemyHP, &jogando, &levelUp, &playerLvl, &enemyLvl, &pontos, &contraataque, &burnMago, &enemyIndex, &nMobs, mobs, bossFinal);
            if (levelUp) {
                escalamento(class, &atkBase, &res, &forca, &HPMaxima, &HPAtual, &manaMax, &manaAtual, &manaTempMax, &manaTemp, playerLvl, enemyLvl, &enemyHPMax, &enemyHP, &inimigoBaseAtk, &pocaoHP, &pocaoMP, mobs, bossFinal, nMobs, &enemyIndex);
                levelUp = false;
            }
        } while (jogando);
        
    } while (jogando);
    
}