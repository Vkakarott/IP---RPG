#include <stdio.h>
#include <string.h>

void red() {
    printf("\x1b[31m");  // ANSI escape code for red text
}

void green() {
    printf("\x1b[32m");  // ANSI escape code for green text
}

void white() {
    printf("\x1b[0m");   // ANSI escape code for resetting text color to default
}

void att() {
    char brAtk[51] = "▭▭▭▭■▭▭▭▭▭▭▭▭▭▭▭▭▭▭▭▣▣▣□□▣▣▣▭▭▭▭▭▭▭▭▭▭▭▭▭▭■▭▭▭▭";
    char formattedString[51 * 7 + 1];  // 51 characters with color codes, plus null terminator
    int i;
    int offset = 0;

    for (i = 0; i < 50; i++) {
        if (i == 4 || i == 45) {
            red();
            offset += sprintf(formattedString + offset, "\x1b[31m%c", brAtk[i]);
        } else if (i > 19 && i < 27) {
            green();
            offset += sprintf(formattedString + offset, "\x1b[32m%c", brAtk[i]);
        } else {
            white();
            offset += sprintf(formattedString + offset, "\x1b[0m%c", brAtk[i]);
        }
    }

    white();  // Reset text color after printing the bar
    printf("%s\n", formattedString);
}

int main(){
    printf("APERTE ENTER PARA ATACAR\n");
    while (getchar() != '\n');
    att();
    return 0;
}