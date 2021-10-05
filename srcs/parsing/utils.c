#include "minishell.h"



t_lchar	*ft_lcharlast(t_lchar *lst)
{
	t_lchar	*lst2;

	lst2 = lst;
	if (!lst)
		return (NULL);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}

void	ft_lcharadd_back(t_lchar **alst, t_lchar *rnew)
{
	t_lchar	*lst2;

	if (*alst == NULL)
		*alst = rnew;
	else
	{
		lst2 = ft_lcharlast(*alst);
		lst2->next = rnew;
		rnew->next = NULL;
        rnew->previous = lst2;
	}
}

t_lchar	*ft_lcharnew(char st)
{
	t_lchar *s;

	if (!(s = (t_lchar *)malloc(sizeof(t_lchar))))
		return (NULL);
	s->c = st;
	s->next = NULL;
    s->previous = NULL;
	return (s);
}









t_cm	*ft_cmlast(t_cm *lst)
{
	t_cm	*lst2;

	lst2 = lst;
	if (!lst)
		return (NULL);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}

void	ft_cmadd_back(t_cm **alst, t_cm *rnew)
{
	t_cm	*lst2;

	if (*alst == NULL)
		*alst = rnew;
	else
	{
		lst2 = ft_cmlast(*alst);
		lst2->next = rnew;
		rnew->next = NULL;
        rnew->previous = lst2;
	}
}

t_cm	*ft_cmnew(char **st)
{
	t_cm *s;

	if (!(s = (t_cm *)malloc(sizeof(t_cm))))
		return (NULL);
	s->str = st;
	s->next = NULL;
    s->previous = NULL;
	return (s);
}

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

void    delquotes(char *line)
{
    int  i;
    t_lchar *q;
    t_lchar *tmp;

    i = 0;
    q = NULL;
    tmp = NULL;
    while (line[i])
    {
        tmp = ft_lcharnew(line[i]);
        ft_lcharadd_back(&q,tmp);
        i++;
    }
    tmp = ft_lcharnew(line[i]);
    ft_lcharadd_back(&q,tmp);
    free(line);
    while (q->next)
    {
        while (q->next && q->c == '\'')
        {
            if (!q->previous && q->next && q->c == '\'')
            {
                q->next->previous = NULL;
                q = q->next;
            }
            /*if (q->next && q->previous && q->c == '\'')
            {
                q->next->previous = q->previous;
                q->previous->next = q->next;
                q = q->next;
            }*/
            //while (q->next && q->c != '\'')
                q = q->next;
        }
        /*if (q && q->c == '\"')
        {
            if (!q->previous && q->next)
            {
                q->next->previous = NULL;
            }
            if (q->next && q->previous)
            {
                q->next->previous = q->previous;
                q->previous->next = q->next;
            }
        }*/
        if (q->next)
            q = q->next;
    }
    while (q->previous)
        q = q->previous;
    while (q->next)
    {
        printf("%c",q->c);
        q = q->next;
    }
    exit(0);

}

void    ft_delquotes(char **line)
{
    char **sp;
    char *final;
    int i;
    int n;
    int ii;

    ii = 0;
    n = 0;
    sp = NULL;
    final = NULL;
    i = 0;

    while (line[i])
    {
        /*ii = 0;
        while (line[i][ii])
        {
            if (line[i][ii] == '\'')
            {
                ii++;
                n = ii;
                while (line[i][ii] && line[i][ii] != '\'')
                    ii++;
                if (line[i][ii] && n == ii)
                {
                    line[i][0] = '\0'; 
                    ii++;
                    break;
                }
                final = ft_substrs(line[i],n,ii-1);
                line[i] = final;
                i++;
                ii = 0;
                
            }
            else
                ii++;
        }*/
        delquotes(line[i]);
        i++;
       /* if (ft_strchr(line[i],'\''))
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
        if (ft_strchr(line[i],'\"'))
        {
            sp = ft_split(line[i],'\"');
            
            n = 0;
            while (sp[n])
            {
                final = ft_strfjoin(final, sp[n]);
                n++;
            }
            line[i] = final;
        }
        i++;*/
    }
    for (i = 0;line[i];i++)
        printf("line = %s\n",line[i]);
}