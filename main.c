#include "Libft/libft.h"
#include <stdio.h>

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
		if (line[i] == '*')//QUOTE
		{
			i++;
			while (line[i] && line[i] != '*')
				i++;
			if (line[i])
				num++;
			else
			{
				write(1,"Not closed quote\n",17);
				exit(0);
			}
		}

		if (ft_isalnum(line[i]) && !ft_strchr(strset,line[i]))//ALPHANUM
		{
			min = i;
			while (line[i] && ft_isalnum(line[i]) && !ft_strchr(strset,line[i]))
				i++;
			if (min < i)
				num++;
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

char	**ft_strtok(const char *line, char	*strset)
{
	int	i;
	int min;
	char **str;
	int num;



	if (!line)
		return (NULL);
	num = ft_countt(line, strset);
	str = malloc(sizeof(char *) * (num + 1));
	/*fprintf(stderr,"Num : %d",num);
	exit(0);*/
	str[ft_countt(line, strset)] = NULL;
	i = 0;
	min = 0;
	num = 0;
	while(line[i] != '\0')
	{
		while(line[i] && line[i] == ' ')
		{
			
			i++;
		}
			

		if (line[i] == '*')//QUOTE
		{
			min = i;
			i++;
			while (line[i] && line[i] != '*')
				i++;
			if (line[i])
			{
				i++;
				while(line[i] && ft_isalnum(line[i]))
					i++;
				str[num] = ft_substrs(line, min, i);
				if (!str[num])
					ft_freee(num, str);
				num++;
			}
			else
			{
				write(1,"Not closed quote\n",17);
				exit(0);
			}	//QUOTE


		}
		if (ft_isalnum(line[i]) && !ft_strchr(strset,line[i]))//ALPHANUM
		{
			min = i;
			while (line[i] && ft_isalnum(line[i]) && !ft_strchr(strset,line[i]))
				i++;
			if (min < i)
			{
				str[num] = ft_substrs(line, min, i);
				if (!str[num])
					ft_freee(num, str);
				num++;
			}
		}//ALPHANUM
		
		if (ft_strchr(strset,line[i]))//STRSET
		{
			min = i;
			while (line[i] && ft_strchr(strset,line[i]))
				i++;
			str[num] = ft_substrs(line, min, i);
			if (!str[num])
					ft_freee(num, str);
			num++;
		}//STRSET

	}
	return (str);
}

int main(int ac, char **av)
{
    char **line;
    if (ac > 1)
        line = ft_strtok(av[1], "|;");

	if (line)
		for (int i = 0;line[i];i++)
    		printf("%s\n",line[i]);
}