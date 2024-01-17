#include <stdio.h> //Biblioteca de input e output
#include <stdbool.h> //Valores booleanos
#include <stdlib.h> //Função rand
#include <time.h> //Tempo
#include <unistd.h> //Sleep no linux
#include <string.h>//Biblioteca de strings (para uso de strcmp, que compara strings)
#include <termios.h>// Para função kbhit
#include <fcntl.h>// Para função kbhit

//Cores
void red() { printf("\033[0;31m"); }
void green() { printf("\033[0;32m"); }
void yellow() { printf("\033[0;33m"); }
void blue() { printf("\033[0;34m"); }
void purple() { printf("\033[0;35m"); }
void cyan() { printf("\033[0;36m"); }
void white() { printf("\033[0;37m"); }

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
        "                                                                                                    ",
        "     __                      __            __                                                       ",
        "    / /__ ____   ____ ___   / /_   ____ _ / /_ ___                                                  ",
        "   / //_// __ \\ / __ `__ \\ / __ \\ / __ `// __// _ \\                                             ",
        "  / ,<  / /_/ // / / / / // /_/ // /_/ // /_ /  __/                                                 ",
        " /_/|_| \\____//_/ /_/ /_//_.___/ \\__,_/ \\__/ \\___/                                              ",
        "                                                                                                    ",
        "                                                                                                    ",
        "                                                                                                    ",
        "                                  ██▀███   ██▓███    ▄████                                          ",
        "                                 ▓██ ▒ ██▒▓██░  ██▒ ██▒ ▀█                                          ",
        "                                 ▓██ ░▄█ ▒▓██░ ██▓▒▒██░▄▄                                           ",
        "                                 ▒██▀▀█▄  ▒██▄█▓▒ ▒░▓█  ██                                          ",
        "                                 ░██▓ ▒██▒▒██▒ ░  ░░▒▓███▀▒                                         ",
        "                                 ░ ▒▓ ░▒▓░▒▓▒░ ░  ░ ░▒   ▒                                          ",
        "                                   ░▒ ░ ▒░░▒ ░       ░   ░                                          ",
        "                                   ░░   ░ ░░       ░ ░   ░                                          ",
        "                                    ░                    ░                                          ",
        "                                                                                                    "
    };

    int numLinhas = 19;
    int numCol = 100;
    int lin;
    int col;

    for (lin = 0; lin < numLinhas; lin++) {
        for (col = 0; col < numCol; col++) {
            if (lines[lin][col] != '\0') {
                printf("%c", lines[lin][col]);
            } else {
                printf(" ");
            }
            fflush(stdout);
            usleep(1000); // 0.001 seconds
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
            scanf("%d%*c", (int *)var);
        } else if (arg[1] == 'f') {
            scanf("%lf%*c", (double *)var);
        }
    }
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


void divisor(){ //Função que mostra uma linha divisoria entre blocos
    white();
    printf("------------------------------------------------------------------\n");
}

double golpe() {
    const char* men[52] = {
        " "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","P","R","E","S","S","I","O","N","E"," ","E","N","T","E","R"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "
    };
    const char* curAtk[50] = {
        " "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "
    };
    const char* brAtk[50] = {
        "▭","▭","▭","▭","■","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▣","▣","▣","□","▣","▣","▣","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","■","▭","▭","▭","▭"
    };
    int atk = 0;
    int i, j;
    system("clear");
    while (1) {
        printf("┏");
        for(i = 0; i < 49; i++) printf("━");
        printf("┓\n┃");
        for (i = 0; i < 49; i++) {
            if (i == atk) {
                printf("\033[0;34m▼\033[0;37m");
            } else {
                printf("%s", curAtk[i]);
            }
            fflush(stdout);
        }
        printf("┃\n┃");

        for (j = 0; j < 49; j++) {
            if (j == 4 || j == 44) red();
            else if (j > 20 && j < 28) green();
            else if (j > 17 && j < 31) yellow();
            else white();
            
            printf("%s", brAtk[j]);
            fflush(stdout);
        }
        printf("┃\n┗");
        for(i = 0; i < 49; i++) printf("━");
        printf("┛\n");
        for (i = 0; i < 51; i++) {
            printf("%s", men[i]);
            fflush(stdout);
        }

        usleep(30000);
        atk++;
        if(atk == 49) {
            atk = 0;
        }
        system("clear");
        if (kbhit()) {
            break;  // Sai do loop se uma tecla for pressionada
        }
    }
    double crit = 0;
    yellow();
    if (atk == 25) {
        printf("GOLPE CRITICO! ");
        crit = 2;
    }
    else if (atk > 20 && atk < 28) {
        printf("MUITO BOM! ");
        crit = 1.5;
    }
    else if (atk > 17 && atk < 31) {
        printf("BOM ");
        crit = 1.2;
    }
    else if (atk > 3 && atk < 45) {
        printf("ACERTOU ");
        crit = 1;
    }
    else {
        printf("ERROU! ");
        crit = 0;
    }
    return crit;    
}

//Barra de status atual
void status(int HPAtual, int HPMaxima, int manaMax, int manaAtual, int playerLvl, int moedas, int class, int atkBase, int res, int forca, int pocaoHP, int pocaoMP, int contraataque) {
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
    printf("] %d/%d\n", manaAtual, manaMax);
    if (class == 4) {
        green();
        printf("POCOES DE CURA: %d   POCOES MAGICAS: %d\n", pocaoHP, pocaoMP);
    }
    yellow();
    if (contraataque == 0) {
        printf("LEVEL: %d  MOEDAS: %d    ATK: %d   RES: %d   FOR: %d\n", playerLvl+1, moedas,atkBase, res, forca);
    } else {
        printf("LEVEL: %d  MOEDAS: %d    ATK: %d   RES: %d   FOR: %d    CTATK: %d\n", playerLvl+1, moedas, atkBase, res, forca, contraataque);
    }
}

//Status do inimigo
void hpEnemy(int enemyHP, int enemyHPMax, int enemyLvl, const char *mobs[], int enemyIndex, bool bossFinal, int burnMago){
    int bar = 10;
    int barEny = (int)((double)enemyHP / enemyHPMax * bar);
    red();
    if (bossFinal == false) {
    printf("HP %s: [", mobs[enemyIndex]);
    } else {
        printf("HP HEBERT: [");
    }
    for(int i = 0; i < bar; i++){
        if(i < barEny){
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("] %d/%d ", enemyHP, enemyHPMax);
    yellow();
    if (bossFinal == false) {
        if (burnMago == 0) {
            printf("  LVL: %d\n", enemyLvl+1);
        } else {
            printf("  LVL: %d    FURIA: %d\n", enemyLvl+1, burnMago);
        }
    } else {
        if (burnMago == 0) {
            printf("  LVL: 99\n");
        } else {
            printf("  LVL: 99    FURIA: %d\n", burnMago);
        }
    }

}

void menu(int class, bool* jogando, int inventario[]) {
    while (1) {
        int acao = 0;
        system("clear");
        const char* dica1[] = {"É recomendado usar Furia no inicio da batalha!", "Quanto mais vida máxima, mais FOR é ganha ao usar Furia!", "O Sifao cura mais dependendo do quanto dano você da!",};
        const char* dica2[] = {"A postura divina reduz a cada turno que o inimigo te ataca!", "A postura divina é mais efetiva com mais RES", "Ambas FOR e RES aumentam o seu dano!",};
        const char* dica3[] = {"É recomendado usar Sobrecarga no inicio da batalha!", "Furia dos espiritos cura e da dano, porem reduz a cada turno", "O seu dano nao e aumentado com FOR, mas sim com MPMAX!",};
        const char* dica4[] = {"Acertar golpe critico com o Tiro Potente atordoa seu inimigo!", "Sua classe nao consegue ganhar FOR a nao ser por meio de itens!", "A flecha enfraquecedora reduz o dano que o inimigo da!"};
        if(class==1) red();
        if(class==2) cyan();
        if(class==3) purple();
        if(class==4) green();
        printf("========= MENU =========\n");
        printf("SELECIONE UMA OPCAO:\n");
        printf("[1] VOLTAR\n");
        printf("[2] DICA\n");
        printf("[3] INVENTARIO\n");
        printf("[4] SAIR DO JOGO\n");

        input("%i", &acao);

        if (acao == 1){
            system("clear");
            break;
        } else if (acao == 2){
            if(class==1) red();
            if(class==2) cyan();
            if(class==3) purple();
            if(class==4) green();
            if(class == 1){
                system("clear");
                printf("%s\nPressione Enter para voltar!\n", dica1[rand() % 3]);
            }
            if(class == 2){
                system("clear"); 
                printf("%s\nPressione Enter para voltar!\n", dica2[rand() % 3]);
                loading();
            }
            if(class == 3){
                system("clear");
                printf("%s\nPressione Enter para voltar!\n", dica3[rand() % 3]);
            }
            if(class == 4){
                system("clear");
                printf("%s\nPressione Enter para voltar!\n", dica4[rand() % 3]);
            }
            getchar();
            continue;
        } else if (acao == 3){
            system("clear");
            if(class==1) red();
            if(class==2) cyan();
            if(class==3) purple();
            if(class==4) green();
            if (inventario[0] != 0) printf("+%d FOR, Luvas de Forca\n", inventario[0] * 4);
            if (inventario[1] != 0) printf("+%d RES, Anel de Defesa\n", inventario[1] * 3);
            if (inventario[2] != 0) printf("+%d MPMAX, Colar Magico\n", inventario[2] * 30);
            if (inventario[3] != 0) printf("+%d HPMAX, Brincos Vitais\n", inventario[3] * 30);
            printf("Pressione enter para retornar.\n");
            getchar();
            continue;
        } else if(acao == 4){
            *jogando = false;
            break;
        } else continue;
        sleep(1);
    }
}

void result(int danoT, int danoR, int exp){
    divisor();
    printf("|                       RESUMO DA PARTIDA                        |\n");
    divisor();
    sleep(1);
    printf(" Dano causado: %d\n", danoT);
    sleep(1);
    printf(" Dano Recebido: %d\n", danoR);
    sleep(1);
    printf(" EXP: %d\n", exp);
    divisor();
}

//Menu de magias
void magia(int class, int* HPMaxima, int* HPAtual, int* manaMax, int* manaAtual, int* manaTemp, int manaTempMax, int* defesa, int* res, int* forca, int* acao, int dano, int* atkBase, int* enemyHP, int* contraataque, int* burnMago, bool* stun, int* pocaoHP, int* pocaoMP, int* danoT){
        switch(class) {
            case 1: //HABILIDADES DO GUERREIRO
            red();
            printf("Escolha uma magia:\n[1] Golpe Ciclone (-%iMP)\n[2] Sifao (-%iMP)\n[3] Furia (-%iHP)\n[4] Descansar (+%iMP +%iHP)\n[Outro] Voltar\n", *manaMax*3/4, *manaMax/2, *HPMaxima/3, *manaMax, *HPMaxima/3);   
            input("%i",&*acao);
            system("clear");
            sleep(1);
            switch (*acao){
            case 1:
                if (*manaAtual >= *manaMax*3/4) {
                    *manaAtual -= *manaMax*3/4;
                    double crit = golpe();
                    dano = 0.4 * *atkBase * (1+0.2 * *forca) * crit;
                    *enemyHP -= dano * 4;
                    *danoT += dano * 4;
                    red();
                    printf("VOCE USOU GOLPE CICLONE E GASTOU %d MANA!\n", *manaMax*3/4);
                    sleep(1);
                    for (int i = 0; i < 4; i ++) {
                    printf("DANO: %i\n", dano);
                    usleep(100000);
                    }
                    break;
                } else {
                    blue();
                    printf("Sem mana suficiente\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
            case 2:
                if (*manaAtual >= *manaMax/2) {
                    *manaAtual -= *manaMax/2;
                    double crit = golpe();
                    dano = 1.3 * *atkBase * (1+0.1 * *forca) * crit;
                    *enemyHP -= dano;
                    *danoT += dano;
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
                    sleep(1);
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
                    blue();
                    printf("Sem HP suficiente\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
            case 4:
                    *manaAtual = *manaMax;
                    *HPAtual += *HPMaxima/3;
                    red();
                    printf("VOCE DESCANSOU, RECUPEROU TODA SUA MANA E CUROU %d DE HP\n", *HPMaxima/3);
                    sleep(1);
                    break;
            default:
                break;
            }
        break;
            case 2: //HABILIDADES DE PALADINO
            cyan();
            printf("Escolha uma magia:\n[1] Investida de Escudo (-%iMP)\n[2] Rezar (-%iMP +%iHP)\n[3] Defesa de Ferro (-%iMP)\n[4] Postura Divina (-%iMP)\n[Outro] Voltar\n", *manaMax*7/10, *manaMax/2, *HPMaxima/2, *manaMax*3/5, *manaMax/3);
            input("%i",&*acao);
            system("clear");
            sleep(1);
            switch (*acao){
                case 1:
                if (*manaAtual >= *manaMax*7/10) {
                    *manaAtual -= *manaMax*7/10;
                    double crit = golpe();
                    dano = 1.5 * *atkBase * (1+0.2 * *res) * (1+0.2 * *forca) * crit;
                    *danoT += dano;
                    *enemyHP -= dano;
                    cyan();
                    printf("VOCE USOU INVESTIDA DE ESCUDO E GASTOU %d MANA!\n", *manaMax*7/10);
                    sleep(1);
                    printf("DANO: %i\n", dano);
                    sleep(1);
                    break;
                } else {
                    blue();
                    printf("Sem mana suficiente\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
                case 2:
                if (*manaAtual >= *manaMax/2) {
                    *manaAtual -= *manaMax/2;
                    *HPAtual += *HPMaxima/2;
                    cyan();
                    printf("VOCE REZOU, GASTOU %d DE MANA E RECEBEU %d DE HP\n", *manaMax/2, *HPMaxima*2/3);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
                case 3:
                if (*manaAtual >= *manaMax*3/5) {
                    *manaAtual -= *manaMax*3/5;
                    *res += *manaMax/9;
                    cyan();
                    printf("VOCE USOU DEFESA DE FERRO, GASTOU %d DE MANA E RECEBEU %d DE RESISTENCIA\n", *manaMax*3/5, *manaMax/9);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
                case 4:
                if(*manaAtual >= *manaMax/3) {
                    *manaAtual -= *manaMax/3;
                    *contraataque += *HPMaxima/10;
                    *defesa += *HPMaxima/8;
                    cyan();
                    printf("VOCE USOU POSTURA DIVINA, GASTOU %d DE MANA, BLOQUEOU %d DE DANO, E CONTRAATACA POR %d DE DANO\n", *manaMax/3, *defesa, *contraataque);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
                default: 
                    break;
            }
            break;
            case 3:
            purple();
            printf("Escolha uma magia:\n[1] Explosao De Mana (-%iMP)\n[2] Furia dos Espiritos (-%iMP +%iHP)\n[3] Sobrecarregar (+%iMPMAX)\n[4] Meditar (+%iMP)\n[Outro] Voltar\n", *manaMax-*manaTemp, (*manaMax-*manaTemp)/2, *HPMaxima/5, manaTempMax, *manaMax*3/4);
            input("%i",&*acao);
            system("clear");
            sleep(1);
            switch (*acao){
                case 1:
                if(*manaAtual >= *manaMax-*manaTemp) {
                    *manaAtual -= *manaMax-*manaTemp;
                    double crit = golpe();
                    dano = *atkBase * (0.04 * *manaMax) * crit;
                    *danoT += dano;
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
                    sleep(1);
                    *acao = 5;
                    break;
                }
                case 2:
                if(*manaAtual >= (*manaMax-*manaTemp)/2) {
                    *manaAtual -= (*manaMax-*manaTemp)/2;
                    *burnMago += *manaMax/5;
                    *HPAtual += *HPMaxima/5;
                    purple();
                    printf("VOCE USOU FURIA DOS ESPIRITOS, SUGANDO A ALMA DO INIMIGO, RESTAUROU %d HP E GASTOU %d MANA\n", *HPMaxima/5, (*manaMax-*manaTemp)/2);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
                case 3:
                if (*manaTemp == 0) {
                    *manaTemp += *manaMax*6/5;
                    *manaMax += *manaTemp;
                    *manaAtual = *manaMax;
                    purple();
                    printf("VOCE SOBRECARREGOU, GANHANDO +%d DE MANA MAXIMA TEMPORARIA\n", manaTempMax);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Voce ja esta sobrecarregado!\n");
                    sleep(1);
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
            printf("Escolha uma magia:\n[1] Tiro potente (-%iMP)\n[2] Usar pocao de cura (+%iHP)\n[3] Tiro enfraquecedor (-%iMP)\n[4] Usar pocao magica (+%iMP)\n[Outro] Voltar\n", *manaMax, *HPMaxima, *manaMax/2, *manaMax);
            input("%i",&*acao);
            system("clear");
            sleep(1);
            switch (*acao){
                case 1:
                if (*manaAtual >= *manaMax) {
                    *manaAtual -= *manaMax;
                    double crit = golpe();
                    dano = 2 * *atkBase * (1+0.1 * *forca) * crit;
                    *enemyHP -= dano;
                    *danoT += dano;
                    green();
                    if (crit == 2) {
                        *stun = true;
                        printf("VOCE USOU TIRO POTENTE, ATORDOANDO O INIMIGO E GASTANDO %d MANA!\n", *manaMax);
                    } else  printf("VOCE USOU TIRO POTENTE, GASTANDO %d MANA!\n", *manaMax);
                    sleep(1);
                    printf("DANO: %i\n", dano);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Sem mana suficiente\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
                case 2:
                if (*pocaoHP > 0) {
                    *pocaoHP -= 1;
                    *HPAtual += *HPMaxima;
                    green();
                    printf("VOCE USOU UMA POCAO DE CURA E CUROU %d DE HP\n", *HPMaxima);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Voce nao tem uma pocao\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
                case 3:
                if (*manaAtual >= *manaMax/2) {
                    *manaAtual -= *manaMax/2;
                    double crit = golpe();
                    *res += *manaMax/4;
                    dano = 1.3 * *atkBase * (1+0.1 * *forca) * crit;
                    *danoT += dano;
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
                    sleep(1);
                    *acao = 5;
                    break;
                }
                case 4:
                if (*pocaoMP > 0) {
                    *pocaoMP -= 1;
                    *manaAtual += *manaMax;
                    *defesa += *HPMaxima/5;
                    green();
                    printf("VOCE USOU UMA POCAO MAGICA, BLOQUEOU %d DE DANO, RECEBEU %d MANA\n", *defesa,*manaMax);
                    sleep(1);
                    break;
                }  else {
                    blue();
                    printf("Voce nao tem uma pocao\n");
                    sleep(1);
                    *acao = 5;
                    break;
                }
                default:
                    break;
            }
            break;
        }
    
}

//Verificar se a batalha acabou e o resultado
void checkWin(int HPAtual, int enemyHP, bool *jogando, bool *levelUp, int*playerLvl, int *enemyLvl, int* exp, int* moedas,int *contraataque, int *burnMago, int *enemyIndex, int *nMobs, const char *mobs[], bool *bossFinal) {
    sleep(1);
    if (HPAtual <= 0) {
        system("clear");
        white();
        printf("Voce morreu. Fim de jogo.\n");
        *jogando = false;
    } else if ((enemyHP <= 0)&&(HPAtual <= 0)) {
        system("clear");
        white();
        printf("Voce morreu, mas com Honra! Fim de jogo.\n");
        *jogando = false;
    } else if ((enemyHP <= 0)&&(*bossFinal == false)) {
        system("clear");
        white();
        int Xp = 10 * (*enemyLvl + 1);
        int Dindin = (10 + rand() % 6) * (double)(1 + *enemyLvl * 0.4);
        *exp += Xp;
        *moedas += Dindin;
        printf("Voce derrotou o inimigo! \033[0;33m(+%d XP) (+%d $)\n", Xp, Dindin);

        int mobsCount = *nMobs;
        for (int i = *enemyIndex; i < mobsCount - 1; i++) {
            mobs[i] = mobs[i + 1];
        }
        mobs[mobsCount - 1] = NULL;
        (*nMobs)--;
        if (*nMobs < 1) { 
            *bossFinal = true;
        }
        *playerLvl += 1;
        *enemyLvl += *playerLvl;
        *contraataque = 0;
        *burnMago = 0;
        *levelUp = true;
        sleep(1);
    } else if ((enemyHP <= 0)&&(*bossFinal == true)) {
        system("clear");
        white();
        printf("VOCE DERROTOU O SER MAIS FORTE DE TODOS, O PROFESSOR\n");
        sleep(1);
        printf("AGORA VAI TER FERIADO!\nPOREM, AINDA NAO ACABOU, DESEJA EXTENDER O FERIADO?\n0 - NAO\n1 - SIM\n");
        int acao;
        input("%i", &acao);
        if (acao == 0) {
            *jogando = false;
        } else {
            system("clear");
            int Xp = 10 * (*enemyLvl + 1);
            int Dindin = (10 + rand() % 6) * (double)(1 + *enemyLvl * 0.4);
            *nMobs = 4;
            *exp += Xp;
            *moedas += Dindin;
            mobs[0] = "TROLL";
            mobs[1] = "BRUXA";
            mobs[2] = "GOLEM";
            mobs[3] = "DRAGAO";
            printf("Voce derrotou o inimigo! \033[0;33m(+%d XP) (+%d $)\n", Xp, Dindin);
            int mobsCount = *nMobs;
            for (int i = *enemyIndex; i < mobsCount - 1; i++) {
                mobs[i] = mobs[i + 1];
            }
            mobs[mobsCount - 1] = NULL;
            (*nMobs)--;
            *playerLvl += 1;
            *enemyLvl += *playerLvl;
            *contraataque = 0;
            *burnMago = 0;
            *bossFinal = false;
            *levelUp = true;
        }
    }
}

void loja(int inventario[], int* moedas, int* forca, int* res, int* manaMax, int *manaAtual, int* HPMaxima, int *HPAtual) {
    int acao = 0;
    const char *items[] = {"Luvas da Forca", "Anel de defesa", "Colar Magico", "Brincos Vitais",};
    sleep(1);
    printf("Voce encontrou uma loja!\n");
    sleep(1);
    while (1) {
        system("clear");
        yellow();
        printf("|                                  -LOJA-                                |\n");
        printf("|    1- Luvas da Forca (+4 FOR)  70$ || 3- Colar Magico  (+30 MPMAX) 50$ |\n");
        printf("|    2- Anel de Defesa (+3 RES)  50$ || 4- Brincos Vitais(+30 HPMAX) 60$ |\n");
        printf("|                               OUTRO- SAIR                              |\n");
        printf("Moedas: %d\n", *moedas);
        input("%i", &acao);
        if (acao == 1 && *moedas >= 70) {
            inventario[0]+= 1;
            *forca += 4;
            *moedas -= 70;
        } else if (acao == 2 && *moedas >= 50) {
            inventario[1]+= 1;
            *res += 3;
            *moedas -= 50;
        } else if (acao == 3 && *moedas >= 50) {
            inventario[2]+= 1;
            *manaMax += 30;
            *manaAtual = *manaMax;
            *moedas -= 50;
        } else if (acao == 4 && *moedas >= 60) {
            inventario[3]+= 1;
            *HPMaxima += 30;
            *HPAtual = *HPMaxima;
            *moedas -= 60;
        } else if (acao > 4 || acao < 1)break;
        else {
            printf("Sem dinheiro suficiente");
            continue;
        }
        printf("Voce comprou %s!\n", items[acao-1]);
        sleep(2);
    }
    printf("Voce decidiu sair da loja\n ");
    system("clear");
}

//Proxima rodada
void escalamento(int class, int *atkBase, int *res, int* forca, int* HPMaxima, int* HPAtual, int* manaMax, int* manaAtual, int* manaTempMax, int* manaTemp, int playerLvl, int enemyLvl, int* enemyHPMax, int* enemyHP, int* enemyBaseAtk, int* pocaoHP, int* pocaoMP, const char *mobs[], bool bossFinal, int nMobs, int *enemyIndex, int inventario[], int* moedas){
divisor();
switch (class){
            case 1:
                *atkBase = 10+3*playerLvl;
                *res = 1 + 3 * inventario[1];
                *forca = 2 + 1*playerLvl + 4 * inventario[0];
                *HPMaxima = 50 + 10*playerLvl + 30 * inventario[3];
                *HPAtual = *HPMaxima;
                *manaMax = 20 + 4*playerLvl + 30 * inventario[2];
                *manaAtual = *manaMax;
                yellow();
                printf("LEVEL UP! Voce recebeu:\n+3 ATK\n+1 FORCA\n+10 HP\n+4 MANA\n");
                break;
            case 2:
                *atkBase = 10 + 2*playerLvl;
                *res = 2 + 1 * playerLvl + 3 * inventario[1];
                *forca = 0 + 4 * inventario[0];
                *HPMaxima = 60 + 15*playerLvl + 30 * inventario[3];
                *HPAtual = *HPMaxima;
                *manaMax = 30 + 6*playerLvl + 30 * inventario[2];
                *manaAtual = *manaMax;
                yellow();
                printf("LEVEL UP! Voce recebeu:\n+2 ATK\n+1 RES\n+15 HP\n+6 MANA\n");
                break;
            case 3:
                *atkBase = 8 + 2*playerLvl;
                *res = 0 + 3 * inventario[1];
                *forca = 0 + 4 * inventario[0];
                *HPMaxima = 45 + 9 * playerLvl + 30 * inventario[3];
                *HPAtual = *HPMaxima;
                *manaMax = 50 + 10 * playerLvl + 30 * inventario[2];
                *manaAtual = *manaMax;
                *manaTemp = 0;
                *manaTempMax = *manaMax;
                yellow();
                printf("LEVEL UP! Voce recebeu:\n+2 ATK\n+9 HP\n+10 MANA\n");
                break;
            case 4:
                *atkBase = 12 + 4*playerLvl;
                *res = 0 + 3 * inventario[1];
                *forca = 0 + 4 * inventario[0];
                *HPMaxima = 40 + 10*playerLvl + 30 * inventario[3];
                *HPAtual = *HPMaxima;
                *manaMax = 20 + 2*playerLvl + 30 * inventario[2];
                *manaAtual = *manaMax;
                *pocaoHP = 2;
                *pocaoMP = 2;
                yellow();
                printf("LEVEL UP! Voce recebeu:\n+4 ATK\n+10 HP\n+2 MANA\n");
                break;
        }
        divisor();
        sleep(3);
        system("clear");
        if(bossFinal == true){
            loja(inventario, moedas, forca, res, manaMax, manaAtual, HPMaxima, HPAtual);
            printf("Voce chegou no boss final, O PROFESSOR!!!\n");
            loading();
        } else {
            *enemyIndex = rand() % nMobs;
            sleep(1);
            white();
            printf("VOCE ENCONTROU %s\n", mobs[*enemyIndex]);
            sleep(1);
            loading();
        }
        *enemyHPMax = 75 + 15 * enemyLvl;
        *enemyHP = *enemyHPMax;
        *enemyBaseAtk = 10 + 2 * enemyLvl;
}



//Função para os ataques específicos de inimigos
void inimigoAtacar(bool* inimigoAtacou, int* lastEnemyAtk, int* danoR, bool bossFinal, int enemyIndex, const char* mobs[], const char* atksTroll[], const char* atksBruxa[], const char* atksGolem[], const char* atksDragao[], const char* atksProf[], int *inimigoBaseAtk, int* inimigoAtk, int *enemyHPMax, int *enemyHP, int *res, int *enemyLvl,int enemyAtkIndex, int defesa, int* HPAtual) {
    if (bossFinal == false) {
        if (*lastEnemyAtk == 2|| *res < -7){
            enemyAtkIndex = rand() % 2;
        } else {
            enemyAtkIndex = rand() % 3;
        }
        *lastEnemyAtk = enemyAtkIndex;
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
                    *enemyHPMax += (50 + 10 * *enemyLvl) * 1/3;
                    *enemyHP += (50 + 10 * *enemyLvl) * 1/3;
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
        } else {
            if (*lastEnemyAtk == 3|| *res < -8){
                enemyAtkIndex = rand() % 3;
            } else {
                enemyAtkIndex = rand() % 4;
            }   
            yellow();
            printf("O PROFESSOR USOU %s\n", atksProf[enemyAtkIndex]);
            sleep(1);
            *lastEnemyAtk = enemyAtkIndex;
            
            if (enemyAtkIndex == 0) {   //Erro no Sharif
                *inimigoAtk = *inimigoBaseAtk * 4/3;
                int danoInimigo = (*inimigoAtk - defesa)/(1+*res*0.1);
                if (danoInimigo < 0) danoInimigo = 0;
                *danoR += danoInimigo;
                *HPAtual -= danoInimigo;
                sleep(1);
                printf("TEST 1: WRONG\n");
                usleep(100000);
                printf("DANO: %d\n", danoInimigo/4);
                sleep(1);
                printf("RUNTIME ERROR\n");
                usleep(100000);
                printf("DANO: %d\n", danoInimigo/4);
                sleep(1);
                printf("OUTPUT SIZE LIMIT EXCEEDED\n");
                usleep(100000);
                printf("DANO: %d\n", danoInimigo/4);
                sleep(1);
                printf("ERRO DE COMPILACAO\n");
                usleep(100000);
                printf("DANO: %d\n", danoInimigo/4);
                sleep(1);
                }
                
            if (enemyAtkIndex == 1)  {  //Prova Surpresa
                *inimigoAtk = *inimigoBaseAtk * 5/3;
                *inimigoAtacou = true;
            }
            if (enemyAtkIndex == 2) {   //Reajuste Salarial
                *inimigoBaseAtk += 20 * 2/5;
                yellow();
                printf("O SALARIO DO PROFESSOR AUMENTOU, SEU ATK CRESCEU EM %d\n", 20 * 2/5);
            }
            if (enemyAtkIndex == 3) {   //Aula no Feriado
               *res -= 4;
               yellow();
               printf("O PROFESSOR NAO VAI EMENDAR O FERIADO, REDUZIU SUA MORAL EM 4\n"); 
            }  
        }
}


//Função principal
int main(){
    srand(time(NULL)); //Tempo atual

    //Variaveis
    int class;
    int atkBase;
    int enemyAtkIndex = 0;
    int playerLvl = 0;
    int nMobs = 4;
    int enemyLvl = 0;
    int manaTemp = 0;
    int defesa = 0;
    int contraataque = 0;
    int burnMago = 0;
    int exp = 0;
    int moedas = 0;
    int danoT;
    int danoR;
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
    int enemyHPMax;
    int enemyHP;
    int lastEnemyAtk = 0;
    int inimigoAtk;
    int inimigoBaseAtk;
    int inventario[4] = {0, 0, 0, 0};
    bool levelUp = false;
    bool inimigoAtacou = false;
    bool stun = false;
    bool jogando = true;
    bool bossFinal = false;

    //Array de strings
    const char *mobs[] = {"TROLL", "BRUXA", "GOLEM", "DRAGAO", NULL};
    const char *atksTroll[] = {"Paulada","Garras Afiadas","Grito Bestial",};
    const char *atksBruxa[] = {"Raio Sombrio","Gas Toxico","Atolar",};
    const char *atksGolem[] = {"Impacto Meteoro","Terremoto","Fortalecer",};
    const char *atksDragao[] = {"Chamas Infernais","Furacao","Rugido Draconico",};
    const char *atksProf[] = {"Erro no Sharif", "Prova Surpresa", "Reajuste Salarial" ,"Aula no Feriado",};
    const char *atksBasicos[] = {NULL, "CORTE COM ESPADA", "GOLPE COM ESCUDO", "MISSIL MAGICO", "TIRO FRACO"};

    //Start
    abertura();
    system("clear");
    //Escolha de classes
    do{
        white();
        printf("Escolha sua Classe:\n\033[0;31m[1] Guerreiro\n\033[0;36m[2] Paladino\n\033[0;35m[3] Mago\n\033[0;32m[4] Arqueiro\n");
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
                break;
            case 3:
                atkBase = 8;
                res = 0;
                forca = 0;
                HPMaxima = 45;
                HPAtual = HPMaxima;
                manaMax = 50;
                manaAtual = manaMax;
                manaTempMax = manaMax;
                purple();
                printf("Voce escolheu o Mago!\n");
                break;
            case 4:
                atkBase = 12;
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
                break;
            default:
                printf("Classe invalida! Tente novamente.\n");
                break;
        }
    } while (class < 1|| class > 4);


        enemyIndex = rand() % nMobs;
        sleep(1);
        system("clear");
        if(nMobs > 0){
            white();
            printf("VOCE ENCONTROU %s\n", mobs[enemyIndex]);
            sleep(1);
            loading();
            enemyHPMax = 75;
            enemyHP = 75;
            inimigoBaseAtk = 10;
        }
        
        do {
            system("clear");
            divisor();
            status(HPAtual, HPMaxima, manaMax, manaAtual, playerLvl, moedas, class, atkBase, res, forca, pocaoHP, pocaoMP, contraataque);
            divisor();
            hpEnemy(enemyHP, enemyHPMax, enemyLvl, mobs, enemyIndex, bossFinal, burnMago);
            if(class==1) red();
            if(class==2) cyan();
            if(class==3) purple();
            if(class==4) green();
            printf("SELECIONE A ACAO\n[1] ATAQUE BASICO\n[2] MAGIA\n[3] DEFENDER\n[4] MENU\n");     
            input("%i", &acao);
            sleep(1);
            if(class==1) red();
            if(class==2) cyan();
            if(class==3) purple();
            if(class==4) green();

            if(acao == 1){
                double crit = golpe();
                if (class==1) dano = atkBase * (1+0.1*forca) * crit;
                if (class==2) dano = atkBase * (1+0.05*res) * (1+0.2*forca) * crit;
                if (class==3) dano = atkBase * (1+0.015*manaMax) * crit;
                if (class==4) dano = atkBase * 1.2 * (1+0.1*forca) * crit;
                enemyHP -= dano;
                danoT += dano;
                manaAtual += manaMax/10;
                system("clear");
                if(class==1) red();
                if(class==2) cyan();
                if(class==3) purple();
                if(class==4) green();
                printf("VOCE USOU %s, CAUSOU %d DE DANO E RECEBEU %d DE MANA\n", atksBasicos[class], dano, manaMax/10);
                sleep(1);
            } else if (acao == 2) {
                system("clear");
                divisor();
                status(HPAtual, HPMaxima, manaMax, manaAtual, playerLvl, moedas, class, atkBase, res, forca, pocaoHP, pocaoMP, contraataque);
                divisor();
                hpEnemy(enemyHP, enemyHPMax, enemyLvl, mobs, enemyIndex, bossFinal, burnMago);
                magia(class, &HPMaxima, &HPAtual, &manaMax, &manaAtual, &manaTemp, manaTempMax, &defesa, &res, &forca, &acao, dano, &atkBase, &enemyHP, &contraataque, &burnMago, &stun, &pocaoHP, &pocaoMP, &danoT);
                if (acao > 4 || acao <1) {
                continue;
                }   
            } else if (acao ==3) { //defender
                defesa += HPMaxima/2; //usada na formula de dano recebido, escala com hp maxímo
                manaAtual += manaMax*2/5;
                system("clear");
                printf("VOCÊ SE DEFENDEU DE %d DE DANO E RECEBEU +%d MANA\n", defesa, manaMax*2/5);
                sleep(1);
            }  else if (acao == 4) { 
                menu(class, &jogando, inventario);
                sleep(1);
                if (!jogando) break;
                continue;
            } else continue;
            loading();
            if (jogando == false) break;
            if (HPAtual > HPMaxima) HPAtual = HPMaxima;    // impedir de HP e mp de passar do limite, dano negativo e HP negativo
            if (manaAtual > manaMax) manaAtual = manaMax;  
            if (enemyHP < 0) enemyHP = 0; 

            // Inimigo ataca
            if(enemyHP > 0){
                if (stun == false) {  //Verifica se o inimigo esta atordoado
                inimigoAtacar(&inimigoAtacou, &lastEnemyAtk, &danoR, bossFinal, enemyIndex, mobs, atksTroll, atksBruxa, atksGolem, atksDragao, atksProf, &inimigoBaseAtk, &inimigoAtk, &enemyHPMax, &enemyHP, &res, &enemyLvl, enemyAtkIndex, defesa, &HPAtual);
                if (inimigoAtacou == true) {  // verificar se o inimigo atacou
                    int danoInimigo = (inimigoAtk - defesa)/(1+res*0.1);
                    if (danoInimigo < 0) danoInimigo = 0;   // dano do inimigo não ficar negativo por causa da formula de defesa
                    danoR += danoInimigo;
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
                    sleep(1);
                    purple();
                    printf("VOCE SUGOU A ALMA DO SEU INIMIGO, CAUSANDO %d DE DANO E CURANDO %d DE VIDA\n", burnMago, burnMago);
                    sleep(1);
                    burnMago -= burnMago/4;                 //burn reduz em 25%/turno
                }
            }
            }
            if (HPAtual > HPMaxima) HPAtual = HPMaxima;    // impedir de HP e mp de passar do limite, dano negativo e HP negativo
            if (manaAtual > manaMax) manaAtual = manaMax;  
            if (enemyHP < 0) enemyHP = 0;                  //
            defesa = 0;  //resetar a defesa no final do turno
            checkWin(HPAtual, enemyHP, &jogando, &levelUp, &playerLvl, &enemyLvl, &exp, &moedas, &contraataque, &burnMago, &enemyIndex, &nMobs, mobs, &bossFinal);
            loading();
            if (levelUp) {
                escalamento(class, &atkBase, &res, &forca, &HPMaxima, &HPAtual, &manaMax, &manaAtual, &manaTempMax, &manaTemp, playerLvl, enemyLvl, &enemyHPMax, &enemyHP, &inimigoBaseAtk, &pocaoHP, &pocaoMP, mobs, bossFinal, nMobs, &enemyIndex, inventario, &moedas);
                stun = false;
                levelUp = false;
            }
    
    } while (jogando);
        
    result(danoT, danoR, exp);
    
}
