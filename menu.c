#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

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

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int menu(char *titulo, int numOpcoes, char *opcoes[]) {
    int s = 0;
    int f = numOpcoes - 1;
    char input;

    while (1) {
        system("clear");
        printf("%s\n", titulo);
        for (int i = 0; i < numOpcoes; i++) {
            if (i == s) printf("▶  %s", opcoes[i]);
            else printf("  %s", opcoes[i]);
            printf("\n");
        }

        while (!kbhit()) {
            usleep(100000);  // Aguarda 100 milissegundos (0.1 segundo)
        }

        input = getchar();

        switch (input) {
            case 'w':
            case 65: // Código ASCII para a seta para cima
                if (s == 0) s = f;
                else s--;
                break;
            case 's':
            case 66: // Código ASCII para a seta para baixo
                if (s == f) s = 0;
                else s++;
                break;
            case '\n':
                return s;
        }
    }
    return s;
}

int main() {
    char *opcoes[4] = {
        "Jogar",
        "Instruções",
        "Créditos",
        "Sair"
    };

    menu("MENU PRINCIPAL", 4, opcoes);
    return 0;
}