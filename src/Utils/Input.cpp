#include "Input.h"

#if defined(_WIN32)
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#endif

char getCharInput() {
#if defined(_WIN32)
    return _getch();  // Windows: from <conio.h>
#else
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);         // save terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);       // disable line buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();                         // read one character
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore settings
    return ch;
#endif
}
