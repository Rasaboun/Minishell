#include "minishell.h"

t_redir	*ft_redirlast(t_redir *lst)
{
	t_redir	*lst2;

	lst2 = lst;
	if (!lst)
		return (NULL);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}

void	ft_rediradd_back(t_redir **alst, t_redir *rnew)
{
	t_redir	*lst2;

	if (*alst == NULL)
		*alst = rnew;
	else
	{
		lst2 = ft_redirlast(*alst);
		lst2->next = rnew;
		rnew->next = NULL;
        rnew->previous = lst2;
	}
}

t_redir	*ft_redirnew(char *st)
{
	t_redir *s;

	if (!(s = (t_redir *)malloc(sizeof(t_redir))))
		return (NULL);
	s->str = st;
	s->next = NULL;
    s->previous = NULL;
	return (s);
}

char **rediredit(char **tabs)
{
    int i;
    char **final;
    int n;
    t_redir *lst;
    t_redir *tmp;
    t_redir *lnew;
    int redir;

    redir = 0;
    n = 0;
    final = NULL;
    i = 0;
    lst = NULL;
    while (tabs[i])
    {
       lnew = ft_redirnew(tabs[i]);
       ft_rediradd_back(&lst, lnew);
       i++;
    }
    tmp = lst;
    while (lst->next)
    {
        if (strcmp(lst->str,"-") == 0)
        {
            if (lst && lst->previous && strcmp(lst->previous->str,"-"))
            {
                if (lst->next)
                {
                    lst->previous->next = lst->next->next;
                   if (lst->next->next)
                        lst->next->next->previous = lst->previous;
                    /*tmp = lst;
                    lst = lst->previous;
                    free(tmp);
                    free(tmp->next);*/
                    
                }
                else
                {
                    write(1, "Error END REDIR",15);
                    exit(0);
                }
            }
            else
            {
                write(1, "Error END REDIR",15);
                exit(0);
            }
        }
        lst = lst->next;
    }
    while (lst->previous)
    {
        lst = lst->previous;
    }
    while(lst)
    {
        printf("c = %s\n",lst->str);
        lst = lst->next;
    }
    exit(0);
}

int main(int ac, char **av)
{
    rediredit(av);
}