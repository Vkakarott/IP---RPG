#include <stdio.h>
#include <unistd.h> //Sleep no linux


void input(const char *arg, void *var){ //Função que recebe entrada, com um estilo
    printf("> ");
    if (arg[0] == '%') {
        if (arg[1] == 'i') {
            scanf("%d%*c", (int *)var);
        } else if (arg[1] == 'f') {
            scanf("%lf%*c", (double *)var);
        }
    }
}
void divisor(){ //Função que mostra uma linha divisoria entre blocos
    printf("------------------------------------------------------------------\n");
}


void loja(int inventario[4]) {
    int moedas = 100;
    int acao = 0;
    const char *items[] = {"Luvas da Forca", "Anel de defesa", "Colar Magico", "Brincos Vitais",};
    while (1) {
        printf("|                                  -LOJA-                                |\n");
        printf("|    1- Luvas da Forca (+4 FOR)  50$ || 3- Colar Magico  (+30 MPMAX) 50$ |\n");
        printf("|    2- Anel de defesa (+3 RES)  50$ || 4- Brincos Vitais(+30 HPMAX) 50$ |\n");
        printf("|                               OUTRO- SAIR                              |\n");
        input("%i", &acao);
        if (acao == 1) {
            inventario[0]+= 1;
            moedas -= 50;
        } else if (acao == 2) {
            inventario[1]+= 1;
            moedas -= 50;
        } else if (acao == 3) {
            inventario[2]+= 1;
            moedas -= 50;
        } else if (acao == 4) {
            inventario[3]+= 1;
            moedas -= 50;
        } else break;
        printf("Voce comprou %s!\n", items[acao-1]);
        sleep(2);
        system("clear");
    }
    printf("Voce decidiu sair da loja\n ");
}
int main() {
    int inventario[4];
    int i;
    for (i = 0; i < 4; i++) inventario[i] = 0;
    loja(inventario);
    for (i = 0; i < 4; i++) {
        printf("%d", inventario[i]);
    }

}