#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

void red() {
    printf("\033[0;31m");
}
void green() {
    printf("\033[0;32m");
}
void white() {
    printf("\033[0;37m");
}
void yellow() {
    printf("\033[0;33m");
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

int att() {
    const char* men[52] = {
        " "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","P","R","E","S","S","I","O","N","E"," ","E","N","T","E","R"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "
    };
    const char* curAtk[50] = {
        " "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "
    };
    const char* brAtk[50] = {
        "▭","▭","▭","▭","■","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▣","▣","▣","□","□","□","▣","▣","▣","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","▭","■","▭","▭","▭","▭"
    };
    int atk = 25;
    int i, j;
    
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
            else if (j > 19 && j < 29) green();
            else if (j > 16 && j < 32) yellow();
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

        usleep(50000);
        atk++;
        if(atk == 49) {
            atk = 0;
        }
        if (kbhit()) {
            break;  // Sai do loop se uma tecla for pressionada
        }
        system("clear");
    }
    return atk;
}

int main(){
    printf("atk: %d\n", att());
    return 0;
}