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
void magia(int class, bool magiaMenu, int HPMaxima, int HPAtual, int manaMax, int manaAtual, int defesa, int res, int forca, int esq, int acaomagia, int dano, int atkBase, int enemyHP){
if (magiaMenu = true)
{
    switch(class) {
    case 1: //HABILIDADES DO GUERREIRO
        printf("Escolha uma magia: [1] Golpe Ciclone(-%iMP) [2] Sifao (-%iMP) [3] Furia(-%iHP) [4] Descansar(+%iMP) [Outro Número] Voltar\n", manaMax*3/4, manaMax/2, HPMaxima/4, manaMax);
        input("%i",&acaomagia);
        switch (acaomagia)
    {
        case 1:
            if (manaAtual >= manaMax*3/4) {
                manaAtual -= manaMax*3/4;
                dano = 0.5 * atkBase * (1+0.1 * forca);
                enemyHP -= 4 * dano;
                printf("VOCÊ USOU GOLPE CICLONE E GASTOU %d MANA!\n", manaMax*3/4);
                Sleep(1000);
                for (int i = 0; i < 4; i ++) {
                printf("DANO: %i\n", dano);
                Sleep(1000);
                }
                break;
            } else {
                printf("Sem mana suficiente\n");
                break;
        }
        case 2:
            if (manaAtual >= manaMax/2) {
                manaAtual -= manaMax/2;
                dano = 1.3 * atkBase * (1+0.1 * forca);
                HPAtual += dano/2;
                printf("VOCE USOU SIFAO, CUROU %d DE HP E GASTOU %d MANA\n", dano/2, manaMax/2);
                Sleep(1000);
                printf("DANO: %i\n", dano);
                Sleep(1000);
                break;
            } else {
                printf("Sem mana suficiente\n");
                break;
            break;
            }
        case 3:
            if (HPAtual >= HPMaxima/4) {
                HPAtual -= HPMaxima/4;
                forca += HPMaxima/10;
                printf("VOCE USOU FURIA, RECEBEU %d DE FORCA E GASTOU %d DE HP\n", HPMaxima/10, HPMaxima/4);
                Sleep(1000);
            } else {
                printf("Sem HP suficiente\n");
                break;
            }
        case 4:
                manaAtual = manaMax;
                printf("VOCE DESCANSOU E RECUPEROU TODA SUA MANA\n");
                Sleep(1000);
        default:
            magiaMenu = false;
            break;
        }
        
    case 2:
        
    }
}
}


//CODIGO PRINCIPAL
int main(){
    srand(time(NULL)); //tempo atual

    int jogar;
    int class;
    bool repeat = true;
    bool jogando = false;
    bool magiaMenu = false;
    int HPMaxima = 50;
    int HPAtual = 50;
    int manaMax = 5;
    int manaAtual = 5;
    int defesa = 0;
    int res;
    int forca;
    int esq;
    int acao;
    int acaomagia;
    int dano;
    int atkBase;
    int enemyHPMax = 50;
    int enemyHP = enemyHPMax;
    int danoEnemy = 10; 

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
        divisor();
        printf("          OBRIGADO! ATE A PROXIMA.\n");
        divisor();
    }

    //ESCOLHA DE CLASSES
    do {
        printf("Escolha sua Classe:\n[1]Guerreiro\n[2]Paladino\n[3]Bruxo\n[4]Ranger\n[5]Ninja\n");
        input("%i", &class);

        switch (class){
            case 1:
                atkBase = 10;
                res = 1;
                forca = 4;
                manaMax = 20;
                manaAtual = manaMax;
                esq = 20;
                printf("Voce escolheu o Guerreiro!\n");
                repeat = false;
                break;
            case 2:
                atkBase = 12;
                res = 3;
                forca = 2;
                HPMaxima = 60;
                HPAtual = HPMaxima;
                manaMax = 15;
                manaAtual = manaMax;
                esq = 10;
                printf("Voce escolheu o Paladino!\n");
                repeat = false;
                break;
            case 3:
                atkBase = 8;
                res = 0;
                forca = 0;
                HPMaxima = 36;
                HPAtual = HPMaxima;
                manaMax = 40;
                manaAtual = manaMax;
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
                res = -2;
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
        loading();
        divisor();
        status(HPAtual, HPMaxima, manaMax, manaAtual);
        divisor();
        int min = 0;
        int max = 3;
        int randomInRange = (rand() % (max - min + 1)) + min;
        Sleep(1000);
        printf("VOCE ENCONTROU %s\n", arr[randomInRange]);
        hpEnemy(enemyHP, enemyHPMax);
        Sleep(1000);
    }
    // do while para rodar o codigo e depois testar a condicao
    do {
        linha();
            printf("SELECIONE A AÇÃO\n[1] ATAQUE NORMAL\n[2] MAGIA\n[3] DEFENDER\n[4] FUGIR\n");
            input("%i", &acao);
            Sleep(1000);

        if(acao == 1){
            dano = atkBase * (1+0.1*forca);
            enemyHP -= dano;
            manaAtual += manaMax/10;
            printf("VOCE USOU ATAQUE NORMAL:\nCAUSOU %d DE DANO\nRECEBEU %d DE DANO\nRECEBEU + %d DE MANA", dano, danoEnemy, manaAtual/10);
            Sleep(1000);
        } else if (acao == 2) {
            magiaMenu = true;
            magia(class, magiaMenu, HPMaxima, HPAtual, manaMax, manaAtual, defesa, res, forca, esq, acaomagia, dano, atkBase, enemyHP);
            if (acaomagia > 4 || acaomagia <1) {
                magiaMenu = false;
                Sleep(1000);
                continue;
            }
            
        } else if (acao ==3) { //defender
            defesa += HPMaxima/2; //usada na formula de dano recebido, escala com hp maxímo
            manaAtual += manaMax/2.5;
            printf("VOCÊ SE DEFENDEU DE NO MÁXIMO %d DE DANO E RECEBEU +%d MANA\n", defesa, manaMax*2/5);
            Sleep(1000);
        } else if (acao == 4) { //fugir
            int min = 0;
            int max = 3;
            int randomInRange = (rand() % (max - min + 1)) + min;
            printf("VOCE FUGIU E ENCONTROU %s\n", arr[randomInRange]);
            Sleep(1000);
        }

        loading();
        
        // Inimigo ataca
        printf("SEU INIMIGO USOU (placeholder)!\n");
        Sleep(1000);
        
        danoEnemy = (6-defesa)/(1+0.1*res);
        
        if (HPAtual > HPMaxima) HPAtual = HPMaxima; // impedir de HP e mp de passar do limite, dano negativo e HP negativo
        if (manaAtual > manaMax) manaAtual = manaMax; //
        if (enemyHP < 0) enemyHP = 0;                               // 
        if (danoEnemy < 0) danoEnemy = 0;                       // dano do inimigo não ficar negativo por causa da formula de defesa
        
        HPAtual -= danoEnemy;
        printf("DANO: %d\n", danoEnemy);
        
        defesa = 0; //resetar a defesa no final do turno

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
        divisor();
        status(HPAtual, HPMaxima, manaMax, manaAtual);
        divisor();
        hpEnemy(enemyHP, enemyHPMax);
    } while (jogando);

    printf("Fim de jogo!\n");

    return 0;
    }
}

