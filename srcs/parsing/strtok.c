#include "minishell.h"

int	ft_is(int c)
{
	if (c != '\'' && c != '\"' && c != ' ')
		return (1);
	return (0);
}

char	*ft_substrs(const char *s, int min, int max)
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

static	int	ft_countt(const char *line, char *strset)
{
	int i;
	int num;
	int min;
	int n;
	char m;
	char mm;

	m = 0;
	n = 0;
	min = 0;
	num = 0;
	i = 0;
	while (line[i] != '\0')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '\'')
		{
			while (line[i] == '\'') //QUOTE
			{

				i++;
				while (line[i] && line[i] != '\'')
					i++;
				if (line[i] && line[i] == '\'')
				{
					i++;
				}
				else
				{
					write(2, "Not closed quote\n", 17);
					return (0);
				}
			}
			num++;
		}
		if (line[i] == '\"')
		{
			while (line[i] == '\"') //QUOTE
			{

				i++;
				while (line[i] && line[i] != '\"')
					i++;
				if (line[i] && line[i] == '\"')
				{
					i++;
				}
				else
				{
					write(2, "Not closed quote\n", 17);
					return (0);
				}
			}
			num++;
		}

		if (line[i] && ft_is(line[i]) && !ft_strchr(strset, line[i])) //ALPHANUM
		{
			while (line[i] && ft_is(line[i]) && !ft_strchr(strset, line[i]))
				i++;
			if (line[i] == '\'')
			{
				i++;
				while (line[i] && line[i] != '\'')
					i++;
				if (line[i] && line[i] == '\'')
				{
					i++;
					while (line[i] && ft_is(line[i]))
						i++;

					num++;
				}
				else
				{
					write(2, "Not closed quote\n", 17);
					return (0);
				}
			}
			if (line[i] == '\"')
			{
				i++;
				while (line[i] && line[i] != '\"')
					i++;
				if (line[i] && line[i] == '\"')
				{
					i++;
					while (line[i] && ft_is(line[i]))
						i++;

					num++;
				}
				else
				{
					write(2, "Not closed quote\n", 17);
					return (0);
				}
			}
			else if (min < i)
			{

				num++;
			}
		}

		if (ft_strchr(strset, line[i]))
		{
			m = line[i];
			while (line[i] && (ft_strchr(strset, line[i]) || line[i] == ' '))
			{
				if (ft_strchr(strset, line[i]))
					n++;
				mm = line[i];
				i++;
			}
			fprintf(stderr,"n : %d",n);
			if (!line[i] && (m != ';' || m != mm))
			{
				ft_write_error("Error 2");
				return (0);
			}
			if (n > 2 && i > 0 && (line[i - 2] != '>' || line[i - 2] != '<'))
			{
				ft_write_error("Error");
				return (0);
			}
			else
				n = 0;
			num++;
		}
	}
	return (num);
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
	int i;

	i = 0;
	t->num = ft_countt(line, strset);
	if (t->num < 1)
		return (EXIT_FAILURE);
	t->str = malloc(sizeof(char *) * (t->num + 1));
	while (i < t->num + 1)
	{
		t->str[i] = NULL;
		i++;
	}
	if (t->str == NULL)
	{
		ft_write_error("Error");
		return (EXIT_FAILURE);
	}
	t->i = 0;
	t->min = 0;
	t->num = 0;
	return (0);
}

void while_quotes(const char *line, char *strset, t_tok *t, char c, int w)
{
	if (line[t->i] == c) //QUOTE
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
				if (line[t->i] == c)
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
			while_quotes(line, strset, t, '\'', 1);
		else if (line[t->i] == '\"')
			while_quotes(line, strset, t, '\"', 1);
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
	if (init_strok(line, strset, &t))
		return (NULL);
	while (line[t.i] != '\0')
	{
		while (line[t.i] && line[t.i] == ' ')
			t.i++;
		while_quotes(line, strset, &t, '\'', 0);
		while_quotes(line, strset, &t, '\"', 0);
		alphanum_strtok(&t, line, strset);
		strset_strtok(&t, line, strset);
		if (line[t.i] == ' ')
			t.i++;
	}
	return (t.str);
}