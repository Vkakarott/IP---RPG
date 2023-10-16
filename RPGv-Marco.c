#include <stdio.h>
#include <stdbool.h> //biblioteca de valores booleanos
#include <stdlib.h> //biblioteca de gerar aleatorios
#include <time.h>
#include <windows.h> //#include <unistd.h>

//FUNCOES
    //estilo
void loading(){
    printf(".");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf(".\n");
    Sleep(1000);
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
//Verificar se o inimigo ou o player morreu, e upar de level
void checkWin(int HPAtual, int enemyHP, bool* jogando, bool* levelup, int* playerLvl, int* enemyLvl, int* pontos, int* contraataque, int* burnMago){
Sleep(1000);
if (HPAtual <= 0 && enemyHP <= 0){
        printf("Voce morreu, mas com honra! Fim de jogo.\n");
        *jogando = false;
    } else if (HPAtual <= 0) {
        printf("Voce morreu. Fim de jogo.\n");
        *jogando = false;
    } else if (enemyHP <= 0) {
        printf("Voce derrotou o inimigo!\n");
        *playerLvl += 1;
        *enemyLvl += *playerLvl;
        *pontos += *enemyLvl;
        *contraataque = 0;
        *burnMago = 0;
        *levelup = true;
        loading();
        printf("Voce ganhou +%d pontos!\n", *enemyLvl);
        loading();
    }
}
// Prosseguir com o Jogo
void escalamento(int class, int *atkBase, int *res, int* forca, int* HPMaxima, int* HPAtual, int* manaMax, int* manaAtual, int* manaTempMax, int* manaTemp, int* esq, int playerLvl, int enemyLvl, int* enemyHPMax, int* enemyHP, int* enemyBaseAtk){

switch (class){
            case 1:
                *atkBase = 10+3*playerLvl;
                *res = 1;
                *forca = 4 + 1*playerLvl;
                *HPMaxima = 50 + 10*playerLvl;
                *HPAtual = *HPMaxima;
                *manaMax = 20 + 4*playerLvl;
                *manaAtual = *manaMax;
                *esq = 20;
                printf("LEVEL UP! Voce recebeu:\n+3 ATK\n+1 FORCA\n+10 HP\n+4 MANA\n");
                break;
            case 2:
                *atkBase = 10 + 2*playerLvl;
                *res = 3 + 1*playerLvl;
                *forca = 0;
                *HPMaxima = 60 + 18*playerLvl;
                *HPAtual = *HPMaxima;
                *manaMax = 30 + 6*playerLvl;
                *manaAtual = *manaMax;
                *esq = 10;
                printf("LEVEL UP! Voce recebeu:\n+2 ATK\n+1 RES\n+18 HP\n+6 MANA\n");
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
                *esq = 30;
                printf("LEVEL UP! Voce recebeu:\n+4 ATK\n+8 HP\n+2 MANA\n");
                break;
            case 5:
                *atkBase = 12 + 3*playerLvl;
                *res = 0;
                *forca = 0;
                *HPMaxima = 30 + 3*playerLvl;
                *HPAtual = *HPMaxima;
                *manaMax = 30 + 6*playerLvl;
                *manaAtual = *manaMax;
                *esq = 50;
                printf("LEVEL UP! Voce recebeu:\n+3 ATK\n+3 HP\n+6 MANA\n");
                break;
            default:
                printf("Meu deus eu devo ter feito muita merda\n");
                break;
        }
        char *arr[] = {"TROLL","BRUXA","GOLEM","DRAGAO"};

        int min = 0;
        int max = 3;
        int randomInRange = (rand() % (max - min + 1)) + min;
        Sleep(1000);
        printf("VOCE ENCONTROU %s\n", arr[randomInRange]);
        Sleep(1000);
        *enemyHPMax += 10 * enemyLvl;
        *enemyHP = *enemyHPMax;
        *enemyBaseAtk += 2 * enemyLvl;

}

//Barra de status atual
void status(int HPAtual, int HPMaxima, int manaMax, int manaAtual, int playerLvl, int pontos) {
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
    printf("] %d/%d    PONTOS: %d\n", HPAtual, HPMaxima, pontos);

    // Barra de mana
    int barM = 10;
    int preenchidaMana = (int)((double)manaAtual / manaMax * barM);
    printf("MANA: [");
    for (int i = 0; i < barM; i++) {
        if (i < preenchidaMana) {
            printf("#"); // Caractere para representar a Mana
        } else {
            printf(" "); // Espaço em branco para representar a parte vazia da barra
        }
    }
    printf("] %d/%d     LEVEL: %d\n", manaAtual, manaMax, playerLvl);
}

void hpEnemy(int enemyHP, int enemyHPMax, int enemyLvl, const char *enemyName){
    int bar = 10;
    int barEny = (int)((double)enemyHP / enemyHPMax * bar);
    printf("HP INIMIGA: [");
    for(int i = 0; i < bar; i++){
        if(i < barEny){
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("] %d/%d LVL: %d\n", enemyHP, enemyHPMax, enemyLvl);
}
//HORA DO MEGAZORD
void magia(int class, bool magiaMenu, int* HPMaxima, int* HPAtual, int* manaMax, int* manaAtual, int* manaTemp, int manaTempMax, int* defesa, int* res, int* forca, int* esq, int* acao, int dano, int* atkBase, int* enemyHP, int* contraataque, int* burnMago){
if (magiaMenu = true)
{
    switch(class) {
    case 1: //HABILIDADES DO GUERREIRO
         printf("Escolha uma magia:\n[1] Golpe Ciclone (-%iMP)\n[2] Sifao (-%iMP)\n[3] Furia (-%iHP)\n[4] Descansar (+%iMP)\n[Outro] Voltar\n", *manaMax*3/4, *manaMax/2, *HPMaxima/3, *manaMax);   
        input("%i",&*acao);
        Sleep(1000);
        switch (*acao)
    {
        case 1:
            if (*manaAtual >= *manaMax*3/4) {
                *manaAtual -= *manaMax*3/4;
                dano = 0.4 * *atkBase * (1+0.2 * *forca);
                *enemyHP -= dano * 4;
                printf("VOCÊ USOU GOLPE CICLONE E GASTOU %d MANA!\n", *manaMax*3/4);
                Sleep(1000);
                for (int i = 0; i < 4; i ++) {
                printf("DANO: %i\n", dano);
                Sleep(1000);
                }
                break;
            } else {
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
                printf("VOCE USOU SIFAO, CUROU %d DE HP E GASTOU %d MANA\n", dano/2, *manaMax/2);
                Sleep(1000);
                printf("DANO: %i\n", dano);
                Sleep(1000);
                break;
            } else {
                printf("Sem mana suficiente\n");
                *acao = 5;
                break;
            break;
            }
        case 3:
            if (*HPAtual >= *HPMaxima/3) {
                *HPAtual -= *HPMaxima/3;
                *forca += *HPMaxima/10;
                printf("VOCE USOU FURIA, RECEBEU %d DE FORCA E GASTOU %d DE HP\n", *HPMaxima/10, *HPMaxima/3);
                Sleep(1000);
                break;
            } else {
                printf("Sem HP suficiente\n");
                *acao = 5;
                break;
            }
        case 4:
                *manaAtual = *manaMax;
                printf("VOCE DESCANSOU E RECUPEROU TODA SUA MANA\n");
                Sleep(1000);
                break;
        default:
            break;
        }
    break;
    case 2: //HABILIDADES DE PALADINO
        printf("Escolha uma magia:\n[1] Investida de Escudo (-%iMP)\n[2] Rezar (-%iMP+%iHP)\n[3] Parede Inquebravel (-%iMP)\n[4] Protecao Divina(-%iMP)\n[Outro] Voltar\n", *manaMax*3/4, *manaMax/2, *HPMaxima*2/3, *manaMax/2, *manaMax/3);
        input("%i",&*acao);
        Sleep(1000);
        switch (*acao)
    {
        case 1:
            if (*manaAtual >= 3/4**manaMax) {
                *manaAtual -= 3/4**manaMax;
                dano = 1.3 * *atkBase * (1+0.1 * *res);
                *enemyHP -= dano;
                printf("VOCE USOU INVESTIDA DE ESCUDO E GASTOU %d MANA!\n", *manaMax*3/4);
                Sleep(1000);
                printf("DANO: %i\n", dano);
                Sleep(1000);
                break;
            } else {
                printf("Sem mana suficiente\n");
                *acao = 5;
                break;
            }
        case 2:
            if (*manaAtual >= *manaMax/2) {
                *manaAtual -= *manaMax/2;
                *HPAtual += *HPMaxima*2/3;
                printf("VOCE REZOU, GASTOU %d DE MANA E RECEBEU %d DE HP\n", *manaMax/2, *HPMaxima*2/3);
                Sleep(1000);
                break;
            }  else {
                printf("Sem mana suficiente\n");
                *acao = 5;
                break;
            }
        case 3:
            if (*manaAtual >= *manaMax/2) {
                *manaAtual -= *manaMax/2;
                *res += *manaMax/6;
                printf("VOCE USOU PAREDE INQUEBRAVEL, GASTOU %d DE MANA E RECEBEU %d DE RESISTENCIA\n", *manaMax/2, *manaMax/6);
                Sleep(1000);
                break;
            }  else {
                printf("Sem mana suficiente\n");
                *acao = 5;
                break;
            }
        case 4:
            if(*manaAtual >= *manaMax/3) {
                *manaAtual -= *manaMax/3;
                *contraataque += *res;
                *defesa += *HPMaxima/10;
                printf("VOCE USOU PROTECAO DIVINA, GASTOU %d DE MANA, BLOQUEOU %d DE DANO, E CONTRAATACA TODA VEZ QUE TOMA DANO POR %d DE DANO\n", *manaMax/3, *defesa, *contraataque);
                Sleep(1000);
                break;
            }  else {
                printf("Sem mana suficiente\n");
                *acao = 5;
                break;
            }
        default: 
            break;
        }
    break;
    case 3:
        printf("Escolha uma magia:\n[1] Explosao De Mana (-%iMP)\n[2] Furia dos Espiritos (-%iMP+%iHP)\n[3] Sobrecarregar (+%iMPMAX)\n[4] Meditar (+%iMP)\n[Outro] Voltar\n", *manaMax-*manaTemp, (*manaMax-*manaTemp)/2, *HPMaxima/4, manaTempMax, *manaMax*3/4);
        input("%i",&*acao);
        Sleep(1000);
        switch (*acao)
    {
        case 1:
            if(*manaAtual >= *manaMax-*manaTemp) {
                *manaAtual -= *manaMax-*manaTemp;
                dano = *atkBase * (0.05 * *manaMax);
                *enemyHP -= dano;
                printf("VOCE USOU EXPLOSAO DE MANA E GASTOU %d MANA!\n", *manaMax-*manaTemp);
                Sleep(1000);
                printf("DANO: %i\n", dano);
                Sleep(1000);
                break;
            }  else {
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
                Sleep(1000);
                break;
            }  else {
                printf("Sem mana suficiente\n");
                *acao = 5;
                break;
            }
        case 3:
            if (*manaTemp == 0) {
                *manaTemp += *manaMax*6/5;
                *manaMax += *manaTemp;
                printf("VOCE SOBRECARREGOU, GANHANDO +%d DE MANA MAXIMA TEMPORARIA\n", manaTempMax);
                Sleep(1000);
                break;
            }  else {
                printf("Voce ja esta sobrecarregado!\n");
                *acao = 5;
                break;
            }
        case 4:
                *manaAtual += *manaMax*3/4;
                *defesa += *manaMax/6;
                printf("VOCE MEDITOU, GANHANDO +%d DE MANA E BLOQUEANDO %d DE DANO\n", *manaMax*3/4, *manaMax/6);
                Sleep(1000);
                break;
        default:
            break;
    }
    break;
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
    int HPMaxima, HPAtual;
    int playerLvl = 0, enemyLvl = 0, pontos = 0;
    int manaTemp = 0, manaTempMax, burnMago = 0;  //apenas usado pelo mago
    int manaMax;
    int manaAtual;
    int defesa = 0;
    int res, forca;
    int contraataque = 0;               //apenas usado pelo paladino
    int esq;
    int acao;
    int dano;
    int atkBase;
    int enemyHPMax;
    int enemyHP;
    int enemyBaseAtk = 10;
    int danoEnemy;
    int enemyIndex = 0; // Variável que resgata qual é o inimigo atual 

    //array de strings
    char *arr[] = {"TROLL","BRUXA","GOLEM","DRAGAO"};

    char *atksTroll[] = {"Paulada","Garras Afiadas","Grito Bestial",};

    char *atksBruxa[] = {"Raio Sombrio","Gas Toxico","Atolar",};
    
    char *atksGolem[] = {"Desmoronar","Impacto Meteoro","Terremoto",};
    
    char *atksDragao[] = {"Rugido Draconico","Chamas Infernais","Furacao",};

    //INICIO
    divisor(); {
    printf("Pressione [1] para JOGAR ou [0] para SAIR\n");
    input("%i", &jogar);
    Sleep(1000);
    if(jogar == 0){
        divisor();
        printf("          OBRIGADO! ATE A PROXIMA.\n");
        divisor();
        return 0;
    }

    //ESCOLHA DE CLASSES
    do {
        printf("Escolha sua Classe:\n[1]Guerreiro\n[2]Paladino\n[3]Bruxo\n[4]Ranger\n[5]Ninja\n");
        input("%i", &class);
        Sleep(1000);
        switch (class){
            case 1:
                atkBase = 10;
                res = 1;
                forca = 4;
                HPMaxima = 50;
                HPAtual = HPMaxima;
                manaMax = 20;
                manaAtual = manaMax;
                esq = 20;
                printf("Voce escolheu o Guerreiro!\n");
                repeat = false;
                break;
            case 2:
                atkBase = 10;
                res = 3;
                forca = 0;
                HPMaxima = 60;
                HPAtual = HPMaxima;
                manaMax = 30;
                manaAtual = manaMax;
                esq = 10;
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
                esq = 30;
                printf("Voce escolheu o Ranger!\n");
                repeat = false;
                break;
            case 5:
                atkBase = 12;
                res = 0;
                forca = 0;
                HPMaxima = 30;
                HPAtual = HPMaxima;
                manaMax = 30;
                manaAtual = manaMax;
                esq = 50;
                printf("Voce escolheu o Ninja!\n");
                repeat = false;
                break;
            default:
                printf("Classe invalida! Tente novamente.\n");
                break;
        }
    } while (repeat); //Caso o usuario insira o numero errado o loop continua

    if(jogar == 1 && class >= 1 || class <= 5){
        jogando = true;
        int min = 0;
        int max = 3;
        int randomInRange = (rand() % (max - min + 1)) + min;
        enemyIndex = randomInRange;
        Sleep(1000);
        printf("VOCE ENCONTROU %s\n", arr[randomInRange]);
        Sleep(1000);
        enemyHPMax = 50;
        enemyHP = 50;
    }
    // do while para rodar o codigo e depois testar a condicao
    do {
        linha();
        loading();
        divisor();
        status(HPAtual, HPMaxima, manaMax, manaAtual, playerLvl, pontos);
        divisor();
        hpEnemy(enemyHP, enemyHPMax, enemyLvl, arr[enemyIndex]);
        printf("SELECIONE A ACAO\n[1] ATAQUE NORMAL\n[2] MAGIA\n[3] DEFENDER\n[4] SAIR\n");
        input("%i", &acao);
        Sleep(1000);

        if(acao == 1){
            dano = atkBase * (1+0.1*forca);
            enemyHP -= dano;
            manaAtual += manaMax/10;
            printf("VOCE USOU ATAQUE NORMAL, CAUSOU %d DE DANO E RECEBEU %d DE MANA\n", dano, manaMax/10);
            Sleep(1000);
        } else if (acao == 2) {
            magiaMenu = true;
            magia(class, &magiaMenu, &HPMaxima, &HPAtual, &manaMax, &manaAtual, &manaTemp, manaTempMax, &defesa, &res, &forca, &esq, &acao, dano, &atkBase, &enemyHP, &contraataque, &burnMago);
            if (acao > 4 || acao <1) {
                magiaMenu = false;
                Sleep(1000);
                continue;
            }   
            
        } else if (acao ==3) { //defender
            defesa += HPMaxima/2; //usada na formula de dano recebido, escala com hp maxímo
            manaAtual += manaMax/2.5;
            printf("VOCÊ SE DEFENDEU DE NO MÁXIMO %d DE DANO E RECEBEU +%d MANA\n", defesa, manaMax*2/5);
            Sleep(1000);
        }  else if (acao == 4) { 
            jogando = false;
            Sleep(1000);
        }

        loading();
        if (jogando == false) break;
        // Inimigo ataca
        if (arr[enemyIndex] == "TROLL"){
        printf("%s USOU %s!\n", arr[enemyIndex], atksTroll[rand() % (sizeof(atksTroll) / sizeof(atksTroll[0]))]);
        Sleep(1000);
        }
        if(arr[enemyIndex] == "BRUXA"){
        printf("%s USOU %s!\n", arr[enemyIndex], atksBruxa[rand() % (sizeof(atksBruxa) / sizeof(atksBruxa[0]))]);
        Sleep(1000);
        }
        if(arr[enemyIndex] == "GOLEM"){
        printf("%s USOU %s!\n", arr[enemyIndex], atksGolem[rand() % (sizeof(atksGolem) / sizeof(atksGolem[0]))]);
        Sleep(1000);
        }
        if(arr[enemyIndex] == "DRAGAO"){
        printf("%s USOU %s!\n", arr[enemyIndex], atksDragao[rand() % (sizeof(atksDragao) / sizeof(atksDragao[0]))]);
        Sleep(1000);
        }
        
        danoEnemy = (enemyBaseAtk-defesa)/(1+0.1*res);
            
        if (danoEnemy < 0) danoEnemy = 0;              // dano do inimigo não ficar negativo por causa da formula de defesa
        defesa = 0;  //resetar a defesa no final do turno
            
        HPAtual -= danoEnemy;
        printf("DANO: %d\n", danoEnemy);
        if (contraataque != 0) {                       // contraataque do paladino
            enemyHP -= contraataque;
            contraataque -= contraataque/4;            // contraataque reduz em 25% por turno
            Sleep(1000);
            printf("VOCE REVIDOU O ATAQUE, CAUSANDO %d DE DANO\n", contraataque*4/3);
            Sleep(1000);
        }

        if (class == 3) { // coisas exclusivas do mago
            if (manaTemp != 0) {
                manaTemp -= manaTempMax/5;
                manaMax -= manaTempMax/5;
            }
            
            if (burnMago != 0) {
                enemyHP -= burnMago;
                HPAtual += burnMago;
                burnMago -= burnMago/4;
                Sleep(1000);
                printf("VOCE SUGOU A ALMA DO SEU INIMIGO, CAUSANDO %d DE DANO E CURANDO %d DE VIDA\n", burnMago*4/3, burnMago*4/3);
                Sleep(1000);
            }
        }
        if (HPAtual > HPMaxima) HPAtual = HPMaxima;    // impedir de HP e mp de passar do limite, dano negativo e HP negativo
        if (manaAtual > manaMax) manaAtual = manaMax;  
        if (enemyHP < 0) enemyHP = 0;                  //

        checkWin(HPAtual, enemyHP, &jogando, &levelup, &playerLvl, &enemyLvl, &pontos, &contraataque, &burnMago);
        if (levelup == true) {
            escalamento(class, &atkBase, &res, &forca, &HPMaxima, &HPAtual, &manaMax, &manaAtual, &manaTempMax, &manaTemp, &esq, playerLvl, enemyLvl, &enemyHPMax, &enemyHP, &enemyBaseAtk);
            levelup = false;
        }


    } while (jogando == true);

    printf("Fim de jogo!\n");

    return 0;
    }
    
}