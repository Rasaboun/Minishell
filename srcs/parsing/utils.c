#include "minishell.h"

int	ft_istrchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (c == '\0')
		return (0);
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return (i);
}

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

int ft_lcharlen(t_lchar *lst)
{
	t_lchar	*lst2;
    int i;

    i = 0;
	lst2 = lst;
	if (!lst)
		return (0);
	while (lst2->next)
    {
        lst2 = lst2->next;
        i++;
    }
	return (i);
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

t_lchar    *ft_lcharadd(t_lchar *alst, t_lchar *rnew)
{
    t_lchar *tmp;
    t_lchar *lst;

    lst = alst;
    if (!rnew)
    {
        tmp = lst;
        if (!lst->previous)
        {
            lst = lst->next;
            lst->previous = NULL;
        }
        else
        {
            lst = lst->next;
            lst->previous = tmp->previous;
        }
        return (lst);
    }
    if (lst->previous == NULL)
    {
        tmp = ft_lcharlast(rnew);
        if (lst->c == '\0')
        {
            lst->previous = tmp;
            tmp->next = lst;
            lst = rnew;
        }
        else
        {
        tmp->next = lst->next;
        lst->next->previous = tmp;
        lst = rnew;
        }
    }
    else
    {
        
        tmp = ft_lcharlast(rnew);
        tmp->next = lst->next;
        if (lst->next)
            lst->next->previous = tmp;
        rnew->previous = lst->previous;
        lst->previous->next = rnew;
        lst = rnew;
    }

   return (lst);
    
}

char    *get_dollar(t_lchar **lst)
{
    t_lchar *tmp;
    t_lchar *lchar;
    int i;
    char *line;

    line = NULL;
    i = 0;
    lchar = *lst;
    tmp = *lst;
    
    while (lchar->next && ft_isalnum(lchar->c) && lchar->c != '\"')
    {
        i++;
        lchar = lchar->next;
    }
    line = (char *)malloc(sizeof(char) * (i + 1));
    lchar = *lst;
    i = 0;
    while (lchar->next && ft_isalnum(lchar->c) && lchar->c != '\"')
    {
        line[i] = lchar->c;
        lchar = lchar->next;
        i++;
    }
    line[i] = '\0';
    lchar = lchar->previous;
    tmp->previous = tmp->previous->previous;
    if (tmp->previous)
    {
        tmp->previous->next = lchar;
        lchar->previous = tmp->previous;
    }
    else
        tmp->previous = NULL;
    
    lchar->previous = tmp->previous;
    *lst = lchar;
    return (line);
}

t_lchar    *ft_tabtolchar(char *line)
{
    int i;
    t_lchar *tmp;
    t_lchar *c;

    c = NULL;
    tmp = NULL;
    i = 0;
    if (!line)
        return (NULL);
    while (line[i])
    {
        tmp = ft_lcharnew(line[i]);
        ft_lcharadd_back(&c,tmp);
        i++;
    }
    return (c);
}

char    *delquotes(char *line, t_env *env)
{
    int  i;
    t_lchar *q;
    t_lchar *tmp;
    char    *final;
    t_lchar *first;
    char *str;

    str = NULL;
    i = 0;
    q = NULL;
    tmp = NULL;
    if (!line)
        return (NULL);
    while (line[i])
    {
        tmp = ft_lcharnew(line[i]);
        ft_lcharadd_back(&q,tmp);
        i++;
    }
    tmp = ft_lcharnew(line[i]);
    ft_lcharadd_back(&q,tmp);
    i = 0;
    free(line);

    while (q && q->next)
    {
        while (q && q->c == '\'')
        {
            if (!q->previous && q->next && q->c == '\'')
            {
                q->next->previous = NULL;
                q = q->next;
            }
            while (q->next && q->c != '\'' && q->c != '\0')
                q = q->next;
            if (q && q->previous && q->c == '\'')
            {
                q->previous->next = q->next;
                q->next->previous = q->previous;
            }
            if (q->c == '\'' && q->next->c == '\0' && !q->previous)
            {
                q->next->previous = NULL;
                q = q->next;
            }
            if (q->next)
                q = q->next;
        }
        if (q->c == '$')
        {
            q = q->next;
            if (q->next && q->c != ' ')
            {
                final = get_dollar(&q);
                str = ft_env_value(final,env);
                first = ft_tabtolchar(str);
                if (!first)
                    return (NULL);
                else
                    q = ft_lcharadd(q,first);
            }
        }
        while (q && q->c == '\"')
        {
            if (!q->previous && q->next && q->c == '\"')
            {
                q->next->previous = NULL;
                q = q->next;
            }
            while (q->next && q->c != '\"' && q->c != '\0')
            {
                if (q->c == '$')
                {
                    q = q->next;
                    if (q->next && q->c != ' ')
                    {
                        final = get_dollar(&q);
                        str = ft_env_value(final,env);
                        first = ft_tabtolchar(str);
                        q = ft_lcharadd(q,first);
                    }
                }
                if (q->c != '\"')    
                    q = q->next;
            }
            if (q && q->previous && q->c == '\"')
            {
                q->previous->next = q->next;
                q->next->previous = q->previous;
            }
            if (q->c == '\"' && q->next->c == '\0' && !q->previous)
            {
                q->next->previous = NULL;
                q = q->next;
            }
            if (q && q->next)
                q = q->next;
        }
       if (q && q->next && q->c != '\'' && q->c != '\"')
            q = q->next; 
    }
    if (!q)
        fprintf(stderr,"error");
    
    while (q->previous)
        q = q->previous;
        
    i = ft_lcharlen(q);

    final = (char *)malloc(sizeof(char) * (i+1));
    i = 0;
    while (q)
    {
        final[i] = q->c;
        q = q->next;
        i++;
    }
    return (final);
}

int    ft_delquotes(char **line, t_env *env)
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
    if (!line)
        return (0) ;
    while (line[i])
    {
        if (line[i] && (line[i][0] == '|' || line[i][0] == ';'))
        {
            if (i == 0)
            {
                ft_write_error("erreur de syntaxe près du symbole inattendu\n");
                return (0);
            }
        }
        line[i] = delquotes(line[i], env);
        i++;
    }
    return (1);
}