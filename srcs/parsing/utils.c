#include "minishell.h"



static int	ft_whil(char *s3, const char *s1, int i)
{
	int		p;
	int		y;

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

char		*ft_strfjoin(char const *s1, char *s2)
{
	int		p;
	char	*s3;
	int		y;
	int		i;

	if (!s2)
		return (NULL);
    if (!s1)
        return (s2);
	y = 0;
	p = 0;
	i = (int)ft_strlen(s1);
	if (!(s3 = (char *)malloc(sizeof(char) * (i + ft_strlen(s2) + 1))))
		return (0);
	p = ft_whil(s3, s1, i);
	y = 0;
	while (p <= (int)(i + ft_strlen(s2) - 1))
	{
		s3[p] = s2[y];
		p++;
		y++;
	}
	s3[p] = '\0';
	return (s3);
}



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
    tmp = NULL;
    lnew = NULL;
    while (tabs[i])
    {
       lnew = ft_redirnew(tabs[i]);
       ft_rediradd_back(&lst, lnew);
       i++;
    }
    tmp = lst;
    while (lst->next)
    {
        if (strcmp(lst->str,">") == 0)
        {
            if (lst && lst->previous && strcmp(lst->previous->str,">"))
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
    tmp = lst;
    i = 0;
    while(tmp->next)
    {
        i++;
        tmp = tmp->next;
    }
    
    final = (char**)malloc(sizeof(char *) * (i));
    i = 0;
    while (lst->next)
    {
        final[i] = lst->str;
        lst = lst->next;
        i++;
    }
    return (final);
}


void    ft_delquotes(char **line)
{
    char **sp;
    char *final;
    int i;
    int n;

    n = 0;
    sp = NULL;
    final = NULL;
    i = 0;

    while (line[i])
    {
        if (ft_strchr(line[i],'\''))
        {
            sp = ft_split(line[i],'\'');
            
            n = 0;
            while (sp[n])
            {
                final = ft_strfjoin(final, sp[n]);
                n++;
            }
            line[i] = final;
        }
        i++;
    }
}