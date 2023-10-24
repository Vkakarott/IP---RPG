#include <stdio.h>
#include <stdbool.h> //biblioteca de valores booleanos
#include <stdlib.h> //biblioteca de gerar aleatorios
#include <time.h>
#include <unistd.h>
#include <string.h> //biblioteca para uso de strcmp, possibilitando comparar duas strings sem dar erros (na parte dos inimigos)

//FUNCOES
    
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
    
    //estilo
void loading(){
    white();
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".\n");
    sleep(1);
}

void input(const char *arg, void *var){
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

void divisor(){
    white();
    printf("-----------------------------------------\n");
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
    printf("\033[0;32mPRESSIONE ENTER PARA CONTINUAR\n");
    getchar();
}

void linha(){
    printf(" \n");
}

//Verificar se o inimigo ou o player morreu, e upar de level
void checkWin(int HPAtual, int enemyHP, bool* jogando, bool* levelup, int* playerLvl, int* enemyLvl, int* pontos, int* contraataque, int* burnMago){
sleep(1);
if (HPAtual <= 0 && enemyHP <= 0){
        white();
        printf("Voce morreu, mas com honra! Fim de jogo.\n");
        *jogando = false;
    } else if (HPAtual <= 0) {
        white();
        printf("Voce morreu. Fim de jogo.\n");
        *jogando = false;
    } else if (enemyHP <= 0) {
        white();
        printf("Voce derrotou o inimigo!\n");
        *playerLvl += 1;
        *enemyLvl += *playerLvl;
        *pontos += *enemyLvl;
        *contraataque = 0;
        *burnMago = 0;
        *levelup = true;
        loading();
        yellow();
        printf("Voce ganhou +%d pontos!\n", *enemyLvl);
        loading();
    }
}
// Prosseguir com o Jogo
void escalamento(int class, int *atkBase, int *res, int* forca, int* HPMaxima, int* HPAtual, int* manaMax, int* manaAtual, int* manaTempMax, int* manaTemp, int* esq, int playerLvl, int enemyLvl, int* enemyHPMax, int* enemyHP, int* inimigoBaseAtk, int* pocaoHP, int* pocaoMP, int* enemyIndex){

switch (class){
            case 1:
                *atkBase = 10+3*playerLvl;
                *res = 1;
                *forca = 2 + 1*playerLvl;
                *HPMaxima = 50 + 10*playerLvl;
                *HPAtual = *HPMaxima;
                *manaMax = 20 + 4*playerLvl;
                *manaAtual = *manaMax;
                *esq = 20;
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
                *esq = 10;
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
                *esq = 30;
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
                *esq = 30;
                yellow();
                printf("LEVEL UP! Voce recebeu:\n+4 ATK\n+8 HP\n+2 MANA\n");
                break;
            default:
                printf("Meu deus eu devo ter feito muita merda\n");
                break;
        }

        char *arr[] = {"TROLL","BRUXA","GOLEM","DRAGAO"};

        *enemyIndex = rand() % 3;
        sleep(1);
        white();
        printf("VOCE ENCONTROU %s\n", arr[*enemyIndex]);
        sleep(1);
        *enemyHPMax = 50 + 10 * enemyLvl;
        *enemyHP = *enemyHPMax;
        *inimigoBaseAtk = 10 + 2 * enemyLvl; 

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
    printf("] %d/%d    PONTOS: %d\n", HPAtual, HPMaxima, pontos);

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
    yellow();
    printf("] %d/%d     LEVEL: %d\n", manaAtual, manaMax, playerLvl+1);
    if (class == 4) {
        green();
        printf("POCOES DE CURA: %d   POCOES DE MANA: %d\n", pocaoHP, pocaoMP);
    }
}

void hpEnemy(int enemyHP, int enemyHPMax, int enemyLvl, const char* enemyName){
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
    yellow();
    printf("] %d/%d LVL: %d\n", enemyHP, enemyHPMax, enemyLvl+1);
}
//HORA DO MEGAZORD
void magia(int class, bool magiaMenu, int* HPMaxima, int* HPAtual, int* manaMax, int* manaAtual, int* manaTemp, int manaTempMax, int* defesa, int* res, int* forca, int* esq, int* acao, int dano, int* atkBase, int* enemyHP, int* contraataque, int* burnMago, bool* stun, int* pocaoHP, int* pocaoMP){
if (magiaMenu == true) //tinha um erro aqui, ja corrigi (Vitor)
{
    switch(class) {
    case 1: //HABILIDADES DO GUERREIRO
         red();
         printf("Escolha uma magia:\n[1] Golpe Ciclone (-%iMP)\n[2] Sifao (-%iMP)\n[3] Furia (-%iHP)\n[4] Descansar (+%iMP)\n[Outro] Voltar\n", *manaMax*3/4, *manaMax/2, *HPMaxima/3, *manaMax);   
        input("%i",&*acao);
        sleep(1);
        switch (*acao)
    {
        case 1:
            if (*manaAtual >= *manaMax*3/4) {
                *manaAtual -= *manaMax*3/4;
                dano = 0.4 * *atkBase * (1+0.2 * *forca);
                *enemyHP -= dano * 4;
                red();
                printf("VOCE USOU GOLPE CICLONE E GASTOU %d MANA!\n", *manaMax*3/4);
                sleep(1);
                for (int i = 0; i < 4; i ++) {
                red();
                printf("DANO: %i\n", dano);
                sleep(1);
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
                *forca += *HPMaxima/10;
                red();
                printf("VOCE USOU FURIA, RECEBEU %d DE FORCA E GASTOU %d DE HP\n", *HPMaxima/10, *HPMaxima/3);
                sleep(1);
                break;
            } else {
                red();
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
        printf("Escolha uma magia:\n[1] Investida de Escudo (-%iMP)\n[2] Rezar (-%iMP +%iHP)\n[3] Parede Inquebravel (-%iMP)\n[4] Protecao Divina(-%iMP)\n[Outro] Voltar\n", *manaMax*3/4, *manaMax/2, *HPMaxima*2/3, *manaMax*2/3, *manaMax/3);
        input("%i",&*acao);
        sleep(1);
        switch (*acao)
    {
        case 1:
            if (*manaAtual >= 3/4**manaMax) {
                *manaAtual -= 3**manaMax/4;
                dano = 1.3 * *atkBase * (1+0.1 * *res);
                *enemyHP -= dano;
                cyan();
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
                printf("VOCE USOU PAREDE INQUEBRAVEL, GASTOU %d DE MANA E RECEBEU %d DE RESISTENCIA\n", *manaMax/2, *manaMax/6);
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
        switch (*acao)
    {
        case 1:
            if(*manaAtual >= *manaMax-*manaTemp) {
                *manaAtual -= *manaMax-*manaTemp;
                dano = *atkBase * (0.05 * *manaMax);
                *enemyHP -= dano;
                purple();
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
                purple();
                printf("VOCE USOU FURIA DOS ESPIRITOS, SUGANDO A ALMA DO INIMIGO, RESTAUROU %d HP E GASTOU %d MANA\n", *HPMaxima/4, (*manaMax-*manaTemp)/2);
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
                purple();
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
                purple();
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
        switch (*acao)
    {
        case 1:
            if (*manaAtual >= *manaMax) {
                *manaAtual -= *manaMax;
                dano = 2 * *atkBase * (1+0.1 * *forca);
                *enemyHP -= dano;
                *stun = true;
                green();
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
                red();
                printf("VOCE USOU UMA POCAO DE CURA E CUROU %d DE HP\n", *HPMaxima);
                sleep(1);
                break;
            }  else {
                green();
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
                green();
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
                blue();
                printf("VOCE USOU UMA POCAO DE MANA E RECEBEU %d MANA\n", *manaMax);
                sleep(1);
                break;
            }  else {
                green();
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

//Função para os ataques específicos de inimigos
void inimigoAtacar(bool* inimigoAtacou, int enemyIndex, const char* arr[], const char* atksTroll[], const char* atksBruxa[], const char* atksGolem[], const char* atksDragao[], int *inimigoBaseAtk, int* inimigoAtk, int *enemyHPMax, int *enemyHP, int *res) {
    bool carregar = false;   //usar ataques carregados
    if (enemyIndex == 0){        //Troll
        int enemyAtkIndex = rand() % 2;
        green();
        printf("%s USOU %s!\n", arr[enemyIndex], atksTroll[enemyAtkIndex]);
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
            *inimigoBaseAtk += *inimigoBaseAtk * 1/3;
            green();
            printf("O INIMIGO AUMENTOU SEU ATK EM %d", *inimigoBaseAtk*1/3);
        }
    }
    if (enemyIndex == 1){   //Bruxa
        int enemyAtkIndex = rand() % 2;
        purple();
        printf("%s USOU %s!\n", arr[enemyIndex], atksBruxa[enemyAtkIndex]);
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
            printf("O INIMIGO REDUZIU SUA RESISTENCIA EM 3");
        }
    }
    if (enemyIndex == 2){   //Golem
        int enemyAtkIndex = rand() % 2;
        cyan();
        printf("%s USOU %s!\n", arr[enemyIndex], atksGolem[enemyAtkIndex]);
        sleep(1);
        if (enemyAtkIndex == 0) {   //Fortalecer
            *enemyHP += *enemyHPMax * 1/3;
            *enemyHPMax += *enemyHPMax * 1/3;
            red();
            printf("O INIMIGO AUMENTOU SEU HP EM %d\n", *enemyHPMax * 1/3);
        }
        if (enemyAtkIndex == 1)  {   //Impacto Meteoro
            *inimigoAtk = *inimigoBaseAtk * 5/3;
            *inimigoAtacou = true;
        }
        if (enemyAtkIndex == 2) {  // Terremoto
            *inimigoAtk = *inimigoBaseAtk * 3/2;
            *inimigoAtacou = true;
        }

    }
    if (enemyIndex == 3) {   //Dragao
        int enemyAtkIndex = rand() % 2;
        red();
        printf("%s USOU %s!\n", arr[enemyIndex], atksDragao[enemyAtkIndex]);
        sleep(1);
        if (enemyAtkIndex == 0) {   //Rugido Draconico
            *inimigoBaseAtk += *inimigoBaseAtk * 1/3;
            red();
            printf("O INIMIGO AUMENTOU SEU ATK EM %d", *inimigoBaseAtk * 1/3);
        }

        if (enemyAtkIndex == 1) {   //Furacao
            *inimigoAtk = *inimigoBaseAtk;
            *inimigoAtacou = true;
        }

        if (enemyAtkIndex == 2)  {  //Chamas Infernais
            *inimigoAtk = *inimigoBaseAtk * 5/3;
            *inimigoAtacou = true;
        }
        

    }



}

//CODIGO PRINCIPAL
int main(){
    srand(time(NULL)); //tempo atual

    int jogar, class;
    bool repeat = true;
    bool jogando = false;
    bool magiaMenu = false;
    bool levelup = false; 
    bool inimigoAtacou = false;  // verificar se o inimigo atacou (para paladino)
    bool stun = false;          //stunar o inimigo
    int HPMaxima, HPAtual;
    int playerLvl = 0, enemyLvl = 0, pontos = 0;
    int manaTemp = 0, manaTempMax, burnMago = 0;  //apenas usado pelo mago
    int manaMax;
    int manaAtual;
    int pocaoHP, pocaoMP;                          //apenas usado pelo arqueiro
    int defesa = 0;
    int res, forca;
    int contraataque = 0;               //apenas usado pelo paladino
    int esq;
    int acao;
    int dano;
    int atkBase;
    int enemyHPMax;
    int enemyHP;
    int inimigoBaseAtk;
    int inimigoAtk;
    int danoInimigo = 0;
    int enemyIndex = 0; // Variável que resgata qual é o inimigo atual 
    int enemyAtkIndex = 0; // Variável que resgata qual o golpe foi escolhido no turno atual

    //array de strings
    const char *arr[] = {"TROLL","BRUXA","GOLEM","DRAGAO"};

    const char *atksTroll[] = {"Paulada","Garras Afiadas","Grito Bestial",};

    const char *atksBruxa[] = {"Raio Sombrio","Gas Toxico","Atolar",};
    
    const char *atksGolem[] = {"Fortalecer","Impacto Meteoro","Terremoto",};
    
    const char *atksDragao[] = {"Rugido Draconico","Chamas Infernais","Furacao",};

    //INICIO
    abertura();
    divisor(); {
    white();
    printf("Pressione [1] para JOGAR ou [0] para SAIR\n");
    input("%i", &jogar);
    sleep(1);
    if(jogar == 0){
        divisor();
        white();
        printf("          OBRIGADO! ATE A PROXIMA.\n");
        divisor();
        return 0;
    }

    //ESCOLHA DE CLASSES
    do {
        white();
        printf("Escolha sua Classe:\n[1]Guerreiro\n[2]Paladino\n[3]Bruxo\n[4]Arqueiro\n");
        input("%i", &class);
        sleep(1);
        switch (class){
            case 1:
                atkBase = 10;
                res = 1;
                forca = 2;
                HPMaxima = 50;
                HPAtual = HPMaxima;
                manaMax = 20;
                manaAtual = manaMax;
                esq = 20;
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
                esq = 10;
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
                esq = 30;
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
                esq = 30;
                green();
                printf("Voce escolheu o Arqueiro!\n");
                repeat = false;
                break;
            default:
                printf("Classe invalida! Tente novamente.\n");
                break;
        }
    } while (repeat); //Caso o usuario insira o numero errado o loop continua

    if((jogar == 1 && class >= 1) || class <= 4){
        jogando = true;
        enemyIndex = rand() % 3;
        sleep(1);
        white();
        printf("VOCE ENCONTROU %s\n", arr[enemyIndex]);
        sleep(1);
        enemyHPMax = 50;
        enemyHP = 50;
        inimigoBaseAtk = 10;
    }
    // do while para rodar o codigo e depois testar a condicao
    do {
        linha();
        loading();
        divisor();
        status(HPAtual, HPMaxima, manaMax, manaAtual, playerLvl, pontos, class, pocaoHP, pocaoMP);
        divisor();
        hpEnemy(enemyHP, enemyHPMax, enemyLvl, arr[enemyIndex]);
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
            magia(class, &magiaMenu, &HPMaxima, &HPAtual, &manaMax, &manaAtual, &manaTemp, manaTempMax, &defesa, &res, &forca, &esq, &acao, dano, &atkBase, &enemyHP, &contraataque, &burnMago, &stun, &pocaoHP, &pocaoMP);
            if (acao > 4 || acao < 1) {
                magiaMenu = false;
                sleep(1);
                continue;
            }   
            
        } else if (acao ==3) { //defender
            defesa += HPMaxima/2; //usada na formula de dano recebido, escala com hp maxímo
            manaAtual += manaMax/2.5;
            printf("VOCE SE DEFENDEU DE NO MAXIMO %d DE DANO E RECEBEU +%d MANA\n", defesa, manaMax*2/5);
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
        if (enemyHP > 0) {
            
            if (stun == false) {  
            
                inimigoAtacar(&inimigoAtacou, enemyIndex, arr, atksTroll, atksBruxa, atksGolem, atksDragao, &inimigoBaseAtk, &inimigoAtk, &enemyHPMax, &enemyHP, &res);
                if (inimigoAtacou == true) {            // verificar se o inimigo atacou
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

        checkWin(HPAtual, enemyHP, &jogando, &levelup, &playerLvl, &enemyLvl, &pontos, &contraataque, &burnMago);
        if (levelup == true) {
            escalamento(class, &atkBase, &res, &forca, &HPMaxima, &HPAtual, &manaMax, &manaAtual, &manaTempMax, &manaTemp, &esq, playerLvl, enemyLvl, &enemyHPMax, &enemyHP, &inimigoBaseAtk, &pocaoHP, &pocaoMP, &enemyIndex);
            levelup = false;
        }


    } while (jogando == true);
    
    white();
    printf("Fim de jogo!\n");

    return 0;
    }

}
