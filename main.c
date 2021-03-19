#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct termios origin;

void rawmode()
{

struct termios raw;
tcgetattr(STDIN_FILENO,&origin);

raw = origin;
raw.c_lflag &= ~(ECHO | ICANON | ISIG);
tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);


}


int main()
{
    rawmode();
    int c;
    
    while (1){
        write(STDOUT_FILENO,"\x1b[32m()\x1b[30m==[\x1b[36m:::::::::::::>  \x1b[37m : ",46);
        if (read(STDIN_FILENO,&c,1) == 1) {
        if (c == 'q') break;
        if (c == 'v'){
            write(STDOUT_FILENO,"\x1b[2J",4);
            write(STDOUT_FILENO,"\x1b[H",3);
                     } 
        if (iscntrl(c)){
            printf("%d\n", c);
                       }
        else{
            printf("%d ('%c')\n", c, c);
            }
                                           }
            }
    return 0;
}