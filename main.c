#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
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

typedef struct s_cmdlist
{
	char *str;
	struct s_cmdlist *next;
} t_cmdlist;

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
	while (lst2->next != NULL)
		lst2 = lst2->next;
	return (lst2);
}

t_charlist *ft_charlstfirst(t_charlist *lst)
{
	t_charlist *lst2;

	lst2 = lst;
	if (!lst)
		return ((void *)0);
	while (lst2->previous)
		lst2 = lst2->previous;
	return (lst2);
}

t_cmdarlist *ft_cmdlstlast(t_cmdarlist *lst)
{
	t_cmdarlist *lst2;

	lst2 = lst;
	if (!lst)
		return ((void *)0);
	while (lst2->next != NULL)
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
	else
	{
		free(alst);
		alst = NULL;
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

int ft_charlstlen(t_charlist *alst)
{
	t_charlist *lst2;
	int y;

	y = 0;
	lst2 = alst;

	if (!lst2)
		return (0);
	while (lst2->next != NULL && lst2->c != '\0')
	{
		lst2 = lst2->next;
		y++;
	}
	return (y);
}

void ft_charlstadd_back2(t_charlist **alst, t_charlist *new)
{
	t_charlist *lst2;

	if (*alst == NULL)
		*alst = new;
	else
	{
		lst2 = ft_charlstlast(*alst);
		new->previous = lst2->previous;
		if (lst2->previous != NULL)
			lst2->previous->next = new;
		new->next = lst2;
		lst2->previous = new;
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

int ft_putchar(int tc)
{
	write(1, &tc, 1);
	return (0);
}

struct termios origin;


t_cmdlist *ft_cmdstrnew(t_charlist *cmd,int i)
{
	t_cmdlist *cmdstr;
	int n;

	n  = 0;
	cmdstr = malloc(sizeof(t_cmdlist));
	cmdstr->str = malloc((sizeof(char) * i) + 1);
	while(cmd != NULL && n < i)
	{
		cmdstr->str[n] = cmd->c;
		cmd = cmd->next;
		n++;
	}
	cmdstr->str[i] = '\0';
	return (cmdstr);
}

void skipwhitespace(t_charlist *cmd)
{
	while(cmd != NULL && ((cmd->c >= 9 && cmd->c <= 13) || (cmd->c == 32)))
		cmd = cmd->next;
}


char *cmdtochar(t_charlist *cmd)
{
	t_charlist *cmmd;
	t_cmdlist *cmdstr;
	int i;
	int n;

	n = 0;
	i = 0;
	i = ft_charlstlen(cmd);
	cmdstr = malloc(sizeof(t_cmdlist));
	cmdstr->str = malloc((sizeof(char) * i)+1);
	while (cmd != NULL && cmd->c != '\0')
	{
		cmdstr->str[n] = cmd->c;
		n++;
		cmd = cmd->next;
	}
	cmdstr->str[i] = '\0';
	return (cmdstr->str);
}

int ft_passint(char *str)
{
	int		i;

	i = 0;
	while (str[i] <= '9' && str[i] >= '0')
		i++;
	return (i);
}

void cursor_pos(int *line, int *col)
{
	char buf[254];
	unsigned int rett;
	int i;
	int start;

	start = 0;
	i = 0;
	write(1, "\033[6n", 4);
	rett = read(0, buf, 254);
	buf[rett] = '\0';
	while (buf[i] != '\0')
	{
		while(!ft_isdigit(buf[i]) && buf[i] != '\0')
			i++;
		if (buf[i] <= '9' && buf[i] >= '0' && start == 0)
		{
			*line = ft_atoi(&buf[i]);
			while (buf[i] <= '9' && buf[i] >= '0')
				i++;
			start++;
		}
		if (buf[i] <= '9' && buf[i] >= '0')
			*col = ft_atoi(&buf[i]);
		while (buf[i] <= '9' && buf[i] >= '0')
			i++;
		i++;
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

void clears(int c, t_charlist *lst)
{
	while (c > 0)
	{
		if (lst != NULL)
		{
			ft_charlstclear(lst);
			if (lst)
				lst = lst->previous;
		}
		//write(STDOUT_FILENO, "\b \b", 4);
		c--;
	}
}

void clearcharlst(t_charlist **lst, int c)
{
	t_charlist *next;

	next = NULL;
	while (c > 0)
	{
		write(STDOUT_FILENO, "\b \b", 3);
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

void ft_regroup(long *s, t_cmdarlist **cmdhist, char *tc, char *backs, int lim, int colm)
{
	long c;
	t_charlist *charlst;
	t_charlist *tmp;
	t_charlist *last;
	t_cmdarlist *cmd;
	t_cmdarlist *history;
	t_cmdarlist *historyF;
	t_charlist *history_tmp;
	int y;
	int start;
	int li;
	int col;
	int lin;
	int cole;
	charlst = NULL;
	tmp = NULL;
	cmd = NULL;
	history = NULL;
	history_tmp = NULL;
	c = 0;
	start = 0;
	history = ft_cmdlstlast(*cmdhist);
	y = 0;
	last = ft_charlstnew('\0');
	charlst = last;
	int o;
	o = 0;
	cursor_pos(&li,&col);
	li = li-1;
	lin = li;


	//Prompt
	write(STDOUT_FILENO, "\x1b[32m()\x1b[30m==[\x1b[36m:::::::> MINISHELL \x1b[35m✗ \x1b[37m : ", 57);

	while (1)
	{
		if (read(STDIN_FILENO, &c, sizeof(c)) > 0)
		{
			//Check if printable && count Y char print && add char to CHARLST
			if (ft_isprint(c) == 1 && c != '\n' && c != '\0')
			{
				y++;
				write(STDIN_FILENO, &c, sizeof(c));
				tmp = ft_charlstnew(c);
				ft_charlstadd_back2(&charlst, tmp);
				o++;
				if (o%(colm) == (colm-29))
				{
					lin++;
		
				}
				if (lin == li)
					{
					tputs(tgoto(tc, o + 29, lin), 1, ft_putchar);
					tputs(tgoto(backs, o + 29, lin), 1, ft_putchar);
					}
					else
					{
					tputs(tgoto(tc, (o-55)%(lim), lin), 1, ft_putchar);
					tputs(tgoto(backs,(o-55)%(lim), lin), 1, ft_putchar);
					}
			}
			/*
			//Check UP arrow
			if (c == 4283163)
			{
				if (history != NULL)
				{
					if (history->previous != NULL && start != 0)
						history = history->previous;
					y = ft_charlstlen(history->lststr);
					start = 1;
					clearcharlst(&charlst, y);
					history_tmp = history->lststr;
					y = 0;
					while (history_tmp != NULL && history_tmp->c != '\0')
					{
						y++;
						write(STDOUT_FILENO, &history_tmp->c, sizeof(history_tmp->c));
						tmp = ft_charlstnew(history_tmp->c);
						ft_charlstadd_back(&charlst, tmp);
						history_tmp = history_tmp->next;
					}
				}
			}

			
			//gauche
			if (c == 4479771)
			{
				
				if (o > 0)
				{
					o--;
					tputs(tgoto(tc, o+29, 1), 1, ft_putchar);
				}
			}
			//droite
			if (c == 4414235)
			{
				if (o < y)
				{
				o++;
				tputs(tgoto(tc, o+29, 1), 1, ft_putchar);
				}
			}
			

			// DOWN ARROW
			if (c == 4348699)
			{
				if (history != NULL)
				{
					if (history->next != NULL)
						history = history->next;
					y = ft_charlstlen(history->lststr);
					clearcharlst(&charlst, y);
					history_tmp = history->lststr;
					y = 0;
					while (history_tmp != NULL && history_tmp->c != '\0')
					{
						y++;
						write(STDOUT_FILENO, &history_tmp->c, sizeof(history_tmp->c));
						tmp = ft_charlstnew(history_tmp->c);
						ft_charlstadd_back(&charlst, tmp);
						history_tmp = history_tmp->next;
					}
				}
			}*/
			if (c == 127 && y > 0)
			{
				//cursor_pos(&li,&col);
				if (o > 0)
				{

				
					if (o%(colm) == (colm-29))
					{
						lin--;
					}
					
					o--;
					if (lin == li)
					{
					tputs(tgoto(tc, o + 29, lin), 1, ft_putchar);
					tputs(tgoto(backs, o + 29, lin), 1, ft_putchar);
					}
					else
					{
					tputs(tgoto(tc, (o-55)%(lim), lin), 1, ft_putchar);
					tputs(tgoto(backs,(o-55)%(lim), lin), 1, ft_putchar);
					}
					
					
				}
				tmp = ft_charlstlast(charlst);
				if (tmp->previous != NULL)
					tmp = tmp->previous;
				clears(1, tmp);
				y--;
			}

			if (c == '\n')
			{
				//Revers
				if (charlst != NULL)
				{
					while (charlst->previous != NULL)
						charlst = charlst->previous;
					cmd = ft_cmdlstnew(charlst);
					if (cmd != NULL)
						ft_cmdlstadd_back(cmdhist, cmd);
				}
				break;
			}
			if (c == 'q')
				exit(EXIT_FAILURE);
			s = &c;
			c = 0;
		}
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
	char *str;
	commande = NULL;
	int ret;
	char *term_type = getenv("TERM");

	if (term_type == NULL)
	{
		fprintf(stderr, "TERM must be set (see 'env').\n");
		return -1;
	}

	ret = tgetent(NULL, term_type);

	if (ret == -1)
	{
		fprintf(stderr, "Could not access to the termcap database..\n");
		return -1;
	}
	else if (ret == 0)
	{
		fprintf(stderr, "Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
		return -1;
	}

	int column_count = tgetnum("co");
	int line_count = tgetnum("li");
	/*
	char *cl_cap = tgetstr("cl", NULL);
	tputs (cl_cap, 1, ft_putchar);*/
	char *tc_pos = tgetstr("cm", NULL);
	char *tc_back = tgetstr("ce", NULL);
	
	while (1)
	{
		ft_regroup(&c, &commande, tc_pos, tc_back, line_count, column_count);
		tmp = ft_cmdlstlast(commande);
		if (tmp)
		{
			if (tmp->lststr->c != '\0')
			{
				write(STDOUT_FILENO, "\n", 2);
				if (tmp->lststr)
				{
					//C'est Ici que l'on recup la commande en char*
					str = cmdtochar(tmp->lststr);
					printf("%s",str);
					fflush(NULL);
				}
					
				write(STDOUT_FILENO, "\n", 2);
			}
			else
			{
				write(STDOUT_FILENO, "\n", 2);
			}
		}
		else
		{
			write(STDOUT_FILENO, "ERROR", 7);
		}

		//PRINTF
		if (c == 'q')
		{
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}