#include "minishell.h"

static char	*ft_substrs(const char *s, int min, int max)
{
	int		i;
	char	*s2;

	if (!(s2 = malloc(sizeof(char*) * (max - min + 1))))
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

	min = 0;
	num = 0;
	i = 0;
	while(line[i] != '\0')
	{
		while(line[i] && line[i] == ' ')
			i++;
		if (line[i] == '\'')//QUOTE
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i])
			{
				i++;
				
				num++;
			}
			else
			{
				write(1,"Not closed quote\n",17);
				exit(0);
			}
		}

		if (ft_isalnum(line[i]) && !ft_strchr(strset,line[i]))//ALPHANUM
		{
			while (line[i] && ft_isalnum(line[i]) && !ft_strchr(strset,line[i]))
				i++;
			if (line[i] == '\'')
			{
				i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i])
			{
				i++;
				while(line[i] && ft_isalnum(line[i]))
					i++;
				
				num++;
			}
			else
			{
				write(1,"Not closed quote\n",17);
				exit(0);
			}	//QUOTE

			}
			else if (min < i)
			{
				
				num++;
			}
				
		}
		
		if (ft_strchr(strset,line[i]))//STRSET
		{
			while (line[i] && ft_strchr(strset,line[i]))
				i++;
			
			num++;
		}
	}
	return (num);
}

static void	ft_freee(int n, char **s)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
}

void	init_strok(const char *line, char *strset, t_tok *t)
{
	t->num = ft_countt(line, strset);
	if (t->num < 1)
	{
		perror("Error size");
		exit(EXIT_FAILURE);
	}
		
	t->str = malloc(sizeof(char *) * (t->num + 1));
	if (t->str == NULL)
	{
		perror("Error Malloc");
		exit(EXIT_FAILURE);
	}
	t->str[ft_countt(line, strset)] = NULL;
	t->i = 0;
	t->min = 0;
	t->num = 0;
}

void	while_quotes(const char *line, char *strset, t_tok *t, char c, int w)
{
		if (line[t->i] == c)//QUOTE
		{
			if (w == 0)
				t->min = t->i;
			t->i++;
			while (line[t->i] && line[t->i] != c)
				t->i++;
			if (line[t->i])
			{
				t->i++;
				while(line[t->i] && ft_isalnum(line[t->i]))
					t->i++;
				t->str[t->num] = ft_substrs(line, t->min, t->i);
				if (!t->str[t->num])
					ft_freee(t->num, t->str);
				t->num++;
			}
			else
			{
				fprintf(stderr, "line i : %c",line[t->i]);
				exit(0);
			}	//QUOTE


		}
}

char	**ft_strtok(const char *line, char	*strset)
{
	t_tok t;

	if (!line)
		return (NULL);
	init_strok(line, strset, &t);
	while(line[t.i] != '\0')
	{
		while(line[t.i] && line[t.i] == ' ')
			t.i++;
			
		//QUOTES
		while_quotes(line, strset, &t, '\'', 0);
		if (ft_isalnum(line[t.i]) && !ft_strchr(strset,line[t.i]))//ALPHANUM
		{
			t.min = t.i;
			while (line[t.i] && ft_isalnum(line[t.i]) && !ft_strchr(strset,line[t.i]))
				t.i++;
			if (line[t.i] == '\'')
			{

				while_quotes(line, strset, &t, '\'',1);
			}
				
			else if (t.min < t.i)
			{
				t.str[t.num] = ft_substrs(line, t.min, t.i);
				if (!t.str[t.num])
					ft_freee(t.num, t.str);
				t.num++;
			}
		}//ALPHANUM
		
		if (ft_strchr(strset,line[t.i]))//STRSET
		{
			t.min = t.i;
			while (line[t.i] && ft_strchr(strset,line[t.i]))
				t.i++;
			t.str[t.num] = ft_substrs(line, t.min, t.i);
			if (!t.str[t.num])
					ft_freee(t.num, t.str);
			t.num++;
		}//STRSET
		t.i++;
	}
	return (t.str);
}