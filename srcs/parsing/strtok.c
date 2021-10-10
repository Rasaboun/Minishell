#include "minishell.h"

int ft_is(int c)
{
	if (c != '\'' && c != '\"' && c != ' ')
		return (1);
	return (0);
}

char *ft_substrs(const char *s, int min, int max)
{
	int i;
	char *s2;

	if (!(s2 = malloc(sizeof(char) * (max - min + 1))))
		return (NULL);
	i = 0;
	while (min < max)
	{
		s2[i] = s[min];
		i++;
		min++;
	}
	s2[i] = '\0';
	return (s2);
}

static int whilequote_count(const char *line, t_count *ct, char c)
{
	if (line[ct->i] == c)
	{
		while (line[ct->i] == c)
		{
			ct->i++;
			while (line[ct->i] && line[ct->i] != c)
				ct->i++;
			if (line[ct->i] && line[ct->i] == c)
				ct->i++;
			else
			{
				write(2, "Not closed quote\n", 17);
				g_minishell.ret = 1;
				return (0);
			}
		}
		ct->num++;
	}
	return (1);
}

static int whilequotealpha(const char *line, t_count *ct, char c)
{
	if (line[ct->i] == c)
	{
		ct->i++;
		while (line[ct->i] && line[ct->i] != c)
			ct->i++;
		if (line[ct->i] && line[ct->i] == c)
		{
			ct->i++;
			while (line[ct->i] && ft_is(line[ct->i]))
				ct->i++;
			ct->num++;
		}
		else
		{
			write(2, "Not closed quote\n", 17);
			g_minishell.ret = 1;
			return (0);
		}
	}
	return (1);
}

static int whilealpha_count(const char *line, char *strset, t_count *ct)
{
	if (line[ct->i] && ft_is(line[ct->i]) && !ft_strchr(strset, line[ct->i])) //ALPHANUM
	{
		while (line[ct->i] && ft_is(line[ct->i]) && !ft_strchr(strset, line[ct->i]))
			ct->i++;
		if (line[ct->i] == '\"')
		{
			if (whilequotealpha(line, ct, '\"') == 0)
				return (0);
		}
		if (line[ct->i] == '\'')
		{
			if (whilequotealpha(line, ct, '\'') == 0)
				return (0);
		}
		else if (ct->min < ct->i)
			ct->num++;
	}
	return (1);
}

static	int	whilecount(const char *line, char *strset, t_count *ct)
{
	if (whilequote_count(line, ct, '\'') == 0)
			return (0);
	if (whilequote_count(line, ct, '\"') == 0)
		return (0);
	if (whilealpha_count(line, strset, ct) == 0)
		return (0);
	return (1);
}

static int ft_countt(const char *line, char *strset)
{
	t_count ct;

	ct.m = 0;
	ct.n = 0;
	ct.min = 0;
	ct.num = 0;
	ct.i = 0;
	while (line[ct.i] != '\0')
	{
		while (line[ct.i] && line[ct.i] == ' ')
			ct.i++;
		if (whilecount(line, strset, &ct) == 0)
			return (0);
		if (ft_strchr(strset, line[ct.i]))
		{
			while (line[ct.i] && ft_strchr(strset, line[ct.i]))
				ct.i++;
			ct.num++;
		}
	}
	return (ct.num);
}

static void ft_freee(int n, char **s)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
}

int init_strok(const char *line, char *strset, t_tok *t)
{
	t->num = ft_countt(line, strset);
	if (t->num < 1)
		return (1);
	t->str = malloc(sizeof(char *) * (t->num + 1));
	if (t->str == NULL)
	{
		ft_write_error("Error");
		g_minishell.ret = 1;
		return (1);
	}
	t->str[t->num] = NULL;
	t->i = 0;
	t->min = 0;
	t->num = 0;
	return (0);
}

void while_quotes(const char *line, t_tok *t, char c, int w)
{
	if (line[t->i] == c)
	{
		if (w == 0)
			t->min = t->i;
		while (line[t->i] == c)
		{
			t->i++;
			while (line[t->i] && line[t->i] != c)
				t->i++;
			if (line[t->i] && line[t->i] == c)
			{
				t->i++;
				if (line[t->i] != c && line[t->i] != ' ')
					while (line[t->i] && line[t->i] != c)
						t->i++;
			}
		}
		t->str[t->num] = ft_substrs(line, t->min, t->i);
		if (!t->str[t->num])
			ft_freee(t->num, t->str);
		t->num++;
	}
}

void alphanum_strtok(t_tok *t, char *line, char *strset)
{
	if (line[t->i] && ft_is(line[t->i]) && !ft_strchr(strset, line[t->i]))
	{
		t->min = t->i;
		while (line[t->i] && ft_is(line[t->i]) && !ft_strchr(strset, line[t->i]))
			t->i++;
		if (line[t->i] == '\'')
			while_quotes(line, t, '\'', 1);
		else if (line[t->i] == '\"')
			while_quotes(line, t, '\"', 1);
		else if (t->min < t->i)
		{
			t->str[t->num] = ft_substrs(line, t->min, t->i);
			if (!t->str[t->num])
				ft_freee(t->num, t->str);
			t->num++;
		}
	}
}

void strset_strtok(t_tok *t, char *line, char *strset)
{
	if (line[t->i] && ft_strchr(strset, line[t->i]))
	{
		t->min = t->i;
		while (line[t->i] && ft_strchr(strset, line[t->i]))
			t->i++;
		t->str[t->num] = ft_substrs(line, t->min, t->i);
		if (!t->str[t->num])
			ft_freee(t->num, t->str);
		t->num++;
	}
}

char **ft_strtok(char *line, char *strset)
{
	t_tok t;

	if (!line)
		return (NULL);
	if (init_strok(line, strset, &t) == 1)
		return (NULL);
	while (line[t.i] != '\0')
	{
		while (line[t.i] && line[t.i] == ' ')
			t.i++;
		while_quotes(line, &t, '\'', 0);
		while_quotes(line, &t, '\"', 0);
		alphanum_strtok(&t, line, strset);
		strset_strtok(&t, line, strset);
		if (line[t.i] == ' ')
			t.i++;
	}
	return (t.str);
}