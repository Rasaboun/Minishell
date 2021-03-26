#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"

typedef struct s_charlist
{
	long c;
	struct s_charlist *next;
	struct s_charlist *previous;
} t_charlist;

typedef struct s_cmdarlist
{
	struct s_charlist *lststr;
	struct s_cmdarlist *next;
	struct s_cmdarlist *previous;
} t_cmdarlist;

t_charlist *ft_charlstnew(long content)
{
	t_charlist *s;

	if (!(s = malloc(sizeof(t_charlist))))
		return (NULL);
	s->c = content;
	s->next = NULL;
	s->previous = NULL;
	return (s);
}

t_cmdarlist *ft_cmdlstnew(t_charlist *content)
{
	t_cmdarlist *s;

	if (!(s = malloc(sizeof(t_cmdarlist))))
		return (NULL);
	s->lststr = content;
	s->next = NULL;
	s->previous = NULL;
	return (s);
}

t_charlist *ft_charlstlast(t_charlist *lst)
{
	t_charlist *lst2;

	lst2 = lst;
	if (!lst)
		return ((void *)0);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}

t_cmdarlist *ft_cmdlstlast(t_cmdarlist *lst)
{
	t_cmdarlist *lst2;

	lst2 = lst;
	if (!lst)
		return ((void *)0);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}

void ft_charlstclear(t_charlist *alst)
{
	t_charlist *tmp;
	t_charlist *next;
	if (alst->next != NULL)
	{
		next = alst->next;
		if (alst->previous != NULL)
		{
			alst->previous->next = alst->next;
			alst->next->previous = alst->previous;
			free(alst);
			alst = next;
		}
		else
		{
			tmp = alst;
			alst = alst->next;
			alst->previous = NULL;
			free(tmp);
			tmp = NULL;
		}
	}
	else if (alst->previous != NULL)
	{
		next = alst->previous;
		alst->previous->next = NULL;
		free(alst);
		alst = next;
	}
}
void ft_charlstadd_back(t_charlist **alst, t_charlist *new)
{
	t_charlist *lst2;

	if (*alst == NULL)
		*alst = new;
	else
	{
		lst2 = ft_charlstlast(*alst);
		lst2->next = new;
		new->next = NULL;
		new->previous = lst2;
	}
}

void ft_cmdlstadd_back(t_cmdarlist **alst, t_cmdarlist *new)
{
	t_cmdarlist *lst2;

	if (*alst == NULL)
		*alst = new;
	else
	{
		lst2 = ft_cmdlstlast(*alst);
		lst2->next = new;
		new->next = NULL;
		new->previous = lst2;
	}
}

struct termios origin;

void printlst(t_charlist *cmd)
{
	while (cmd != NULL)
	{
		write(STDOUT_FILENO, &cmd->c, 1);
		cmd = cmd->next;
	}
}

void rawmode()
{

	struct termios raw;
	tcgetattr(STDIN_FILENO, &origin);

	raw = origin;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void clear(int c, t_charlist *lst)
{
	while (c > 0)
	{
		if (lst != NULL)
		{
			ft_charlstclear(lst);
			lst = lst->previous;
		}
		write(STDOUT_FILENO, "\b \b", 4);
		c--;
	}
}

void clearcharlst(t_charlist **lst, int c)
{
	t_charlist *next;

	next = NULL;

	while (c > 0)
	{
		write(STDOUT_FILENO, "\b \b", 4);
		c--;
	}
	while (*lst)
	{
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	lst = NULL;
}

void ft_regroup(long *s, t_cmdarlist **cmdhist)
{
	long c;
	t_charlist *charlst;
	t_charlist *tmp;
	t_cmdarlist *cmd;
	t_cmdarlist *history;
	t_cmdarlist *historyF;
	t_charlist *history_tmp;
	int y;
	int start;
	charlst = NULL;
	tmp = NULL;
	cmd = NULL;
	history = NULL;
	history_tmp = NULL;
	c = 0;
	start = 0;
	history = ft_cmdlstlast(*cmdhist);
	y = 0;

	//Prompt
	write(STDOUT_FILENO, "\x1b[32m()\x1b[30m==[\x1b[36m:::::::> MINISHELL \x1b[35m✗ \x1b[37m : ", 57);

	while (1)
	{
		if (read(STDIN_FILENO, &c, sizeof(c)) > 0)
		{
			//Check if printable && count Y char print && add char to CHARLST
			if (ft_isprint(c) == 1 && c != '\n')
			{
				y++;
				write(STDIN_FILENO, &c, sizeof(c));
				tmp = ft_charlstnew(c);
				ft_charlstadd_back(&charlst, tmp);
			}

			//Check UP arrow
			if (c == 4283163)
			{
				if (history != NULL)
				{
					if (history->previous != NULL && start != 0)
						history = history->previous;
					//if (history != historyF)
						start = 1;
					clearcharlst(&charlst,y);
					history_tmp = history->lststr;
					y = 0;
					while (history_tmp != NULL)
					{
						y++;
						write(STDOUT_FILENO, &history_tmp->c, sizeof(history_tmp->c));
						tmp = ft_charlstnew(history_tmp->c);
						ft_charlstadd_back(&charlst, tmp);
						history_tmp = history_tmp->next;
					}
				}
			}

			// DOWN ARROW
			if (c == 4348699)
			{
				if (history != NULL)
				{
					if (history->next != NULL)
						history = history->next;
					clearcharlst(&charlst,y);
					history_tmp = history->lststr;
					y = 0;
					while (history_tmp != NULL)
					{
						y++;
						write(STDOUT_FILENO, &history_tmp->c, sizeof(history_tmp->c));
						tmp = ft_charlstnew(history_tmp->c);
						ft_charlstadd_back(&charlst, tmp);
						history_tmp = history_tmp->next;
					}
				}
			}

			if (c == 127 && y > 0)
			{
				tmp = ft_charlstlast(charlst);
				clear(1, tmp);
				y--;
			}
		}
		if (c == '\n')
		{
			cmd = ft_cmdlstnew(charlst);
			if (cmd != NULL)
				ft_cmdlstadd_back(cmdhist, cmd);
			break;
		}
		if (c == 'q')
			exit(EXIT_FAILURE);
		if (c == 'v')
		{
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
		}
		s = &c;
		c = 0;
	}
}

int main()
{
	rawmode();
	long c;
	c = '\0';
	char *line;
	line = NULL;
	t_charlist *command;
	t_cmdarlist *commande;
	t_cmdarlist *tmp;
	commande = NULL;

	while (1)
	{
		ft_regroup(&c, &commande);
		tmp = ft_cmdlstlast(commande);
		if (tmp)
		{
			write(STDOUT_FILENO, "\n", 2);

			printlst(tmp->lststr);
			write(STDOUT_FILENO, "\n", 2);
		}
		else
		{
			write(STDOUT_FILENO,"ERROR",7);
		}
		
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