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

 void hpEnemy(int enemyHP, int enemyHPMax, const char *enemyName){
    int bar = 10;
    int barEny = (int)((double)enemyHP / enemyHPMax * bar);
    printf("HP %s: [", enemyName);
    for(int i = 0; i < bar; i++){
        if(i < barEny){
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
    int manaAtual = 5;
    int defesa = 0;
    int res;
    int forca;
    int esq;
    int acao;
    int dano;
    int atkBase;
    int enemyHPMax = 50;
    int enemyHP = enemyHPMax;
    int danoEnemy = 10; 
    int enemyIndex = 0; // Variável que resgata qual é o inimigo atual  

    //array de strings
    char *arr[] = {"TROLL","BRUXA","GOLEM","DRAGAO"};
    
    char *atksTroll[] = {"Paulada","Garras Afiadas","Grito Bestial",};

    char *atksBruxa[] = {"Raio Sombrio","Gas Toxico","Atolar",};
    
    char *atksGolem[] = {"Desmoronar","Impacto Meteoro","Terremoto",};
    
    char *atksDragao[] = {"Rugido Draconico","Chamas Infernais","Furacao",};
    
    //INICIO
    divisor(); {
    printf("Precione [1] para JOGAR ou [0] para SAIR\n");
    input("%i", &jogar);
    if(jogar == 0){
        divisor();
        printf("          OBRIGADO! ATE A PROXIMA.\n");
        divisor();
    }

    //ESCOLHA DE CLASSES
    do {
        printf("Escolha sua Classe:\n[1]Herói\n[2]Paladino\n[3]Bruxo\n[4]Ranger\n[5]Ninja\n");
        input("%i", &class);

        switch (class){
            case 1:
                atkBase = 10;
                res = 1;
                forca = 4;
                manaMax = 20;
                manaAtual = manaMax;
                esq = 20;
                printf("Voce escolheu o Heroi!\n");
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
        divisor();
        status(HPAtual, HPMaxima, manaMax, manaAtual);
        divisor();
        int min = 0;
        int max = 3;
        int randomInRange = (rand() % (max - min + 1)) + min;
        enemyIndex = randomInRange;
        printf("VOCE ENCONTROU %s\n", arr[randomInRange]);
        hpEnemy(enemyHP, enemyHPMax, arr[enemyIndex]);
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
            manaAtual += 1;
            printf("VOCE USOU ATAQUE NORMAL:\nCAUSOU %d DE DANO\nRECEBEU %d DE DANO\nRECEBEU + 1 DE MANA\n", dano, danoEnemy);
        } else if (acao == 2) {
            printf("Escolha uma magia: [1] Ataque Especial(%d) [2] Cura(%d) [3] Atk Buff(%d) [4] Meditar(+%d) [Outro Número] Voltar\n", manaMax*3/4, manaMax*2/5, manaMax*1/2,manaMax*3/4);
            input("%i", &acao);
            switch (acao) //começa os efeitos de cada magia
            {
            case 1: //ataque especial
                if (manaAtual >= manaMax*3/4){ //verificar a mana do player 
                manaAtual -= manaMax*3/4;
                dano = 2 * atkBase * (1+0.1 * forca);
                enemyHP -= dano;
                printf("VOCÊ USOU ATAQUE ESPECIAL E GASTOU %d MANA!\n", manaMax*3/4);
                Sleep(1000);
                printf("DANO: %i\n", dano);
                break;
                } else { //caso o player não tenha mana
                    printf("Sem mana suficiente\n");
                    continue;
                }
            case 2: //cura
                if (manaAtual >= manaMax*2/5){
                manaAtual -= manaMax*2/5;
                HPAtual += manaMax*1/2;
                printf("VOCÊ RECUPEROU +%d HP E GASTOU %d MANA\n", manaMax/2, manaMax*2/5);
                Sleep(1000);
                break;
                } else {
                    printf("Sem mana suficiente\n");
                    
                    continue;
                }
            case 3: //buffar
                if (manaAtual >= manaMax*1/2){
                manaAtual -= manaMax*1/2; 
                forca += manaMax*1/5;
                printf("VOCÊ RECEBEU %d DE FORÇA E GASTOU %d MANA\n", manaMax*1/5,manaMax/2);
                Sleep(1000);
                break;
                } else {
                    printf("Sem mana suficiente\n");
                    
                    continue; 
                }
            case 4: //meditar (defender para magos)
                manaAtual += manaMax*3/4;
                defesa += manaMax*1/4; //essa defesa escala com mana ao invés de hp
                printf("VOCÊ SE DEFENDEU DE NO MÁXIMO %d DE DANO E RECUPEROU +%d MANA\n", defesa, manaMax*3/4);
                Sleep(1000);
                break;
            default: 
                continue; //voltar
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
            enemyIndex = randomInRange;
            printf("VOCE FUGIU E ENCONTROU %s\n", arr[randomInRange]);
            Sleep(1000);
        }
       
        loading();
       
        // Inimigo usa um ataque aleatório
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
        Sleep(1000)
        }
        if(arr[enemyIndex] == "DRAGAO"){
        printf("%s USOU %s!\n", arr[enemyIndex], atksDragao[rand() % (sizeof(atksDragao) / sizeof(atksDragao[0]))]);
        Sleep(1000)
        }
        danoEnemy = (6-defesa)/(1+0.1*res);
        
        if (HPAtual > HPMaxima) HPAtual = HPMaxima; // impedir de HP e mp de passar do limite, dano negativo e HP negativo
        if (manaAtual > manaMax) manaAtual = manaMax; //
        if (enemyHP < 0) enemyHP = 0;                            
        if (danoEnemy < 0) danoEnemy = 0;                       // dano do inimigo não ficar negativo por causa da formula de defesa
        
        HPAtual -= danoEnemy;
        printf("DANO: %d\n", danoEnemy);
        
        defesa = 0; //resetar a defesa no final do turno

        if (HPAtual <= 0 && enemyHP <= 0){
            printf("Você morreu, mas com honra! Fim de jogo.\n");
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
        hpEnemy(enemyHP, enemyHPMax, arr[enemyIndex]);
    } while (jogando);

    printf("Fim de jogo!\n");

    return 0;
    }
}
