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

void menu() {
    const char* menu[50][10] = {
        {"========== MENU =========", " "},
        {"SELECIONE UMA OPCAO:     ", " "},
        {" ", "   VOLTAR                "},
        {" ", "   DICA                  "},
        {" ", "   INVENTARIO            "},
        {" ", "   SAIR DO JOGO          "},
        {"=========================", " "}
    };

    int s = 2;
    char input;

    while (1) {
        system("clear");
        for (int i = 0; i < 7; i++) {
            if (i == s) printf("▶ %s", menu[i][1]);
            else printf("%s%s", menu[i][0], menu[i][1]);
            printf("\n");
        }

        while (!kbhit()) {
            usleep(100000);  // Aguarda 100 milissegundos (0.1 segundo)
        }

        input = getchar();

        if (input == 'w') {
            if (s == 2) s = 5;
            else s--;
        } else if (input == 's') {
            if (s == 5) s = 2;
            else s++;
        } else if (input == '\n') {
            break;
        }
    }

    printf("%s\n", menu[s][1]);
}

int main() {
    menu();
    return 0;
}