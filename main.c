#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"

typedef	struct	s_charlist
{
	char            c;
	struct s_charlist	*next;
}				t_charlist;

typedef	struct	s_cmdarlist
{
	struct s_charlist	*lststr;
	struct s_cmdarlist	*next; 
    struct s_cmdarlist	*previous;
}				t_cmdarlist;

t_charlist	*ft_charlstlast(t_charlist *lst)
{
	t_charlist	*lst2;

	lst2 = lst;
	if (!lst)
		return ((void *)0);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}

void	ft_charlstadd_back(t_charlist **alst, t_charlist *new)
{
	t_charlist	*lst2;

	if (*alst == NULL)
		*alst = new;
	else
	{
		lst2 = ft_charlstlast(*alst);
		lst2->next = new;
		new->next = NULL;
	}
}

t_charlist	*ft_charlstnew(char content)
{
	t_charlist *s;

	if (!(s = malloc(sizeof(t_charlist))))
		return (NULL);
	s->c = content;
	s->next = NULL;
	return (s);
}

struct termios origin;

void    printlst(t_charlist *cmd)
{
    while (cmd != NULL)
    {
        write(STDOUT_FILENO,&cmd->c,1);
        cmd = cmd->next;
    }
}

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

void ft_regroup(char *s, t_charlist **cmd)
{
    char c;
    c = '\0';
    char seq[3];
    int i;
    char *tmp;
    i = 0;
    t_charlist *cmmd;
    //Prompt
    write(STDOUT_FILENO, "\x1b[32m()\x1b[30m==[\x1b[36m:::::::> MINISHELL \x1b[35m✗ \x1b[37m : ", 57);
    while (1)
    {
        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            if ((isalnum(c) || c == '\n' || c == ' ' )&& c != 'b')
            {
                i++;
                write(STDIN_FILENO,&c,1);
            }
                
            if (c == 127 && i != 0)
            {
                clear(1);
                i--;
            }
            //Check DOWN arrow
            if (c == '\x1b')
            {
                read(STDIN_FILENO, &seq[0], 1);
                read(STDIN_FILENO, &seq[1], 1);
                if (seq[0] == '[')
                    if(seq[1] == 'B')
                    {
                        write(STDOUT_FILENO,"SALUT",6);                    
                    }

            }
            cmmd = ft_charlstnew(c);
            ft_charlstadd_back(cmd,cmmd);
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
}

int main()
{
    rawmode();
    char c;
    c = '\0';
    char *line;
    line = NULL;
    t_charlist  *command;
    command = NULL;

    while (1)
    {
        ft_regroup(&c,&command);
        printlst(command);
        //PRINTF

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