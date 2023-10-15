#include <stdio.h>
#include <stdbool.h> //biblioteca de valores booleanos
#include <stdlib.h> //biblioteca de gerar aleatorios
#include <time.h>
#include <unistd.h>

//FUNCOES
    //estilo
void loading(){
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".\n");
    sleep(1);
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
void status(int HPAtual, int HPMaxima, int manaMax, int manaAtual) {
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
    printf("] %d/%d\n", manaAtual, manaMax);
}

void hpEnemy(int enemyHP, int enemyHPMax){
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
    printf("} %d/%d\n", enemyHP, enemyHPMax);
}
//HORA DO MEGAZORD
void magia(int class, bool magiaMenu, int* HPMaxima, int* HPAtual, int* manaMax, int* manaAtual, int* manaTemp, int manaTempMax, int* defesa, int* res, int* forca, int* esq, int* acao, int dano, int* atkBase, int* enemyHP, int* contraataque, int* burnMago){
if (magiaMenu = true)
{
    switch(class) {
    case 1: //HABILIDADES DO GUERREIRO
        printf("Escolha uma magia:\n[1] Golpe Ciclone(-%iMP)\n[2] Suga-Vidas (-%iMP)\n[3] Furia(-%iHP)\n[4] Descansar(+%iMP)\n[Outro] Voltar\n", *manaMax*3/4, *manaMax/2, *HPMaxima/4, *manaMax);
        input("%i",&*acao);
        switch (*acao)
    {
        case 1:
            if (*manaAtual >= *manaMax*3/4) {
                *manaAtual -= *manaMax*3/4;
                dano = 0.5 * *atkBase * (1+0.1 * *forca);
                *enemyHP -= dano * 4;
                printf("VOCÊ USOU GOLPE CICLONE E GASTOU %d MANA!\n", *manaMax*3/4);
                sleep(1);
                for (int i = 0; i < 4; i ++) {
                printf("DANO: %i\n", dano);
                sleep(1);
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
                sleep(1);
                printf("DANO: %i\n", dano);
                sleep(1);
                break;
            } else {
                printf("Sem mana suficiente\n");
                *acao = 5;
                break;
            break;
            }
        case 3:
            if (*HPAtual >= *HPMaxima/4) {
                *HPAtual -= *HPMaxima/4;
                *forca += *HPMaxima/10;
                printf("VOCE USOU FURIA, RECEBEU %d DE FORCA E GASTOU %d DE HP\n", *HPMaxima/10, *HPMaxima/4);
                sleep(1);
            } else {
                printf("Sem HP suficiente\n");
                *acao = 5;
                break;
            }
        case 4:
                *manaAtual = *manaMax;
                printf("VOCE DESCANSOU E RECUPEROU TODA SUA MANA\n");
                sleep(1);
        default:
            break;
        }
    break;
    case 2: //HABILIDADES DE PALADINO
        printf("Escolha uma magia:\n[1] Investida de Escudo (-%iMP)\n[2] Rezar (-%iMP+%iHP)\n[3] Parede Inquebravel (-%iMP)\n[4] Protecao Divina(-%iMP)\n[Outro] Voltar\n", *manaMax*3/4, *manaMax/2, *HPMaxima*2/3, *manaMax/2, *manaMax/3);
        input("%i",&*acao);
        switch (*acao)
    {
        case 1:
            if (*manaAtual >= 3/4**manaMax) {
                *manaAtual -= 3/4**manaMax;
                dano = 1.3 * *atkBase * (1+0.1 * *res);
                *enemyHP -= dano;
                printf("VOCE USOU INVESTIDA DE ESCUDO E GASTOU %d MANA!\n", *manaMax*3/4);
                sleep(1);
                printf("DANO: %i\n", dano);
                sleep(1);
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
                sleep(1);
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
                sleep(1);
                break;
            }  else {
                printf("Sem mana suficiente\n");
                *acao = 5;
                break;
            }
        case 4:
            if(*manaAtual >= *manaMax/3) {
                *manaAtual -= *manaMax/3;
                *contraataque += *manaMax/5;
                *defesa += *HPMaxima/10;
                printf("VOCE USOU PROTECAO DIVINA, GASTOU %d DE MANA, BLOQUEOU %d DE DANO, E CONTRAATACA TODA VEZ QUE TOMA DANO POR %d DE DANO\n", *manaMax/3, *defesa, *manaMax/5);
                sleep(1);
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
        printf("Escolha uma magia:\n[1] Explosao De Mana (-%iMP)\n[2] Furia dos Espiritos (-%iMP)\n[3] Sobrecarregar (+%iMPMAX)\n[4] Meditar (+%iMP)\n[Outro] Voltar\n", *manaMax-*manaTemp, (*manaMax-*manaTemp)/2, manaTempMax, *manaMax*3/4);
        input("%i",&*acao);
        switch (*acao)
    {
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
                printf("Sem mana suficiente\n");
                *acao = 5;
                break;
            }
        case 2:
            if(*manaAtual >= *manaMax/2) {
                *manaAtual -= *manaMax/2;
                *burnMago += *manaMax/6;
                printf("VOCE USOU FURIA DOS ESPIRITOS, ROUBANDO A ALMA DO INIMIGO, DANDO E CURANDO %d HP E GASTANDO %d DE MANA\n", *burnMago, *manaMax/6);
                sleep(1);
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
                sleep(1);
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
                sleep(1);
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
    int HPMaxima, HPAtual;
    int manaTemp = 0;                   //
    int manaTempMax = 0;                //apenas usado pelo mago
    int burnMago = 0;                   //
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
    int danoBaseEnemy = 10;
    int danoEnemy; 

    //array de strings
    char *arr[] = {
        "TROLL",
        "BRUXA",
        "GOLLEN",
        "DRAGAO"
    };

    //INICIO
    divisor(); {
    printf("Pressione [1] para JOGAR ou [0] para SAIR\n");
    input("%i", &jogar);
    if(jogar == 0){
        linha();
        divisor();
        printf("          OBRIGADO! ATE A PROXIMA.\n");
        divisor();
        return 0;
    }

    //ESCOLHA DE CLASSES
    do {
        linha();
        printf("Escolha sua Classe:\n[1]Guerreiro\n[2]Paladino\n[3]Bruxo\n[4]Ranger\n[5]Ninja\n");
        input("%i", &class);

        switch (class){
            case 1:
                atkBase = 10;
                res = 1;
                forca = 4;
                HPMaxima = 50;
                HPAtual = 50;
                manaMax = 20;
                manaAtual = 20;
                esq = 20;
                printf("Voce escolheu o Guerreiro!\n");
                repeat = false;
                break;
            case 2:
                atkBase = 10;
                res = 3;
                forca = 0;
                HPMaxima = 60;
                HPAtual = 60;
                manaMax = 30;
                manaAtual = 30;
                esq = 10;
                printf("Voce escolheu o Paladino!\n");
                repeat = false;
                break;
            case 3:
                atkBase = 8;
                res = 0;
                forca = 0;
                HPMaxima = 36;
                HPAtual = 36;
                manaMax = 50;
                manaAtual = 50;
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
                HPAtual = 40;
                manaMax = 20;
                manaAtual = 20;
                esq = 30;
                printf("Voce escolheu o Ranger!\n");
                repeat = false;
                break;
            case 5:
                atkBase = 12;
                res = -2;
                forca = 0;
                HPMaxima = 30;
                HPAtual = 30;
                manaMax = 30;
                manaAtual = 30;
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
        sleep(1);
        printf("VOCE ENCONTROU %s\n", arr[randomInRange]);
        sleep(1);
        enemyHPMax = 50;
        enemyHP = 50;
    }
    // do while para rodar o codigo e depois testar a condicao
    do {
        linha();
            loading();
            divisor();
            status(HPAtual, HPMaxima, manaMax, manaAtual);
            divisor();
            hpEnemy(enemyHP, enemyHPMax);
            printf("SELECIONE A ACAO\n[1] ATAQUE NORMAL\n[2] MAGIA\n[3] DEFENDER\n[4] FUGIR\n");
            input("%i", &acao);
            sleep(1);

        if(acao == 1){
            dano = atkBase * (1+0.1*forca);
            enemyHP -= dano;
            manaAtual += manaMax/10;
            printf("VOCE USOU ATAQUE NORMAL, CAUSOU %d DE DANO E RECEBEU %d DE MANA", dano, manaMax/10);
            sleep(1);
        } else if (acao == 2) {
            magiaMenu = true;
            magia(class, &magiaMenu, &HPMaxima, &HPAtual, &manaMax, &manaAtual, &manaTemp, manaTempMax, &defesa, &res, &forca, &esq, &acao, dano, &atkBase, &enemyHP, &contraataque, &burnMago);
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
        } else if (acao == 4) { //fugir
            int min = 0;
            int max = 3;
            int randomInRange = (rand() % (max - min + 1)) + min;
            printf("VOCE FUGIU E ENCONTROU %s\n", arr[randomInRange]);
            sleep(1);
        }

        loading();
        
        // Inimigo ataca
        printf("SEU INIMIGO USOU (placeholder)!\n");
        sleep(1);
        
        danoEnemy = (danoBaseEnemy-defesa)/(1+0.1*res);
        
        HPAtual -= danoEnemy;
        printf("DANO: %d\n", danoEnemy);
        if (contraataque != 0) {                       // contraataque do paladino
            enemyHP -= contraataque;
            contraataque -= contraataque/4;            // contraataque reduz em 25% por turno
            sleep(1);
            printf("VOCE REVIDOU O ATAQUE, CAUSANDO %d DE DANO\n", contraataque*4/3);
            sleep(1);
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
                sleep(1);
                printf("VOCE SUGOU A ALMA DO SEU INIMIGO, CAUSANDO %d DE DANO E CURANDO %d DE VIDA\n", burnMago*4/3, burnMago*4/3);
                sleep(1);
        }    
        }

        
        if (HPAtual > HPMaxima) HPAtual = HPMaxima;    // impedir de HP e mp de passar do limite, dano negativo e HP negativo
        if (manaAtual > manaMax) manaAtual = manaMax;  //
        if (enemyHP < 0) enemyHP = 0;                  //
        if (danoEnemy < 0) danoEnemy = 0;              // dano do inimigo não ficar negativo por causa da formula de defesa
        defesa = 0;  //resetar a defesa no final do turno

        if (HPAtual <= 0 && enemyHP <= 0){
            printf("Você morreu, mas com honrra! Fim de jogo.\n");
            break;
        } else if (HPAtual <= 0) {
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
}

