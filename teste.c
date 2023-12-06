#include <stdio.h>
#include <unistd.h>


void newOpen() {
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

int main() {
    newOpen();
    return 0;
}