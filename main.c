#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"

struct termios origin;

static int ft_while(char *s3, const char *s1, int i)
{
    int p;
    int y;

    p = 0;
    y = 0;
    while (p < i)
    {
        s3[p] = s1[y];
        p++;
        y++;
    }
    return (p);
}

char *ft_charjoin(char *s1, char s2)
{
    int p;
    char *s3;
    int y;
    int i;

    if (!s1 || !s2)
        return (NULL);
    y = 0;
    p = 0;
    i = (int)ft_strlen(s1);
    if (!(s3 = (char *)malloc(sizeof(char) * (i + 1 + 1))))
        return (0);
    p = ft_while(s3, s1, i);
    y = 0;
    s3[p] = s2;
    p++;
    s3[p] = '\0';
    free(s1);
    return (s3);
}

void rawmode()
{

    struct termios raw;
    tcgetattr(STDIN_FILENO, &origin);

    raw = origin;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void clear(int c)
{
    while (c > 0)
    {
        write(STDOUT_FILENO,"\b \b",4);
        c--;
    }
}

char *ft_regroup(char *s)
{
    char *line;
    line = NULL;
    line = ft_calloc(1, sizeof(char));
    char c;
    c = '\0';
    char seq[3];
    //Prompt
    write(STDOUT_FILENO, "\x1b[32m()\x1b[30m==[\x1b[36m:::::::> MINISHELL \x1b[35m✗ \x1b[37m : ", 57);
    while (1)
    {
        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            if ((isalnum(c) || c == '\n' || c == ' ' )&& c != 'b')
                write(STDIN_FILENO,&c,1);
                
            if (c == 'b')
            {
                clear(4);
            }
            //Check arrow
            if (c == '\x1b')
            {
                read(STDIN_FILENO, &seq[0], 1);
                read(STDIN_FILENO, &seq[1], 1);
                if (seq[0] == '[')
                    if(seq[1] == 'B')
                    {
                       // printf("ok");
                        printf("k");
                      
                        }

            }
            line = ft_charjoin(line, c);
        }
        if (c == '\n')
            break;
        if (c == 'q')
            exit(EXIT_FAILURE);
        if (c == 'v')
        {
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
        }
        s = &c;
    }
    return (line);
}

int main()
{
    rawmode();
    char c;
    c = '\0';
    char *line;
    line = NULL;
    while (1)
    {
        line = ft_regroup(&c);
        printf(" \x1b[37m %s", line);
        if (c == 'q')
        {
            free(line);
            exit(EXIT_FAILURE);
        }
        if (c == 'v')
        {
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
        }
    }
    return 0;
}