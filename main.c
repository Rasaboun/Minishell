#include "Libft/libft.h"
#include <stdio.h>

char	**ft_strtok(char *line, char	*strset)
{
	int	i;
	int n;
	char **str;
	int num;

	num = 0;
	str = malloc(sizeof(char *) * 10);
	str[10] = 0;
	i = 0;
	n = 0;
	while(line[i] != '\0')
	{
		if (line[i] && line[i] == '*')
		{
			n = i;
            i++;
			while (line[i] && line[i] != '*')
				i++;
			if (line[i] != '\0')
			{
				str[num] = ft_substr(line, n, i-n);
				num++;
                n = i;
                i++;
			}
			else
			{
				return (NULL);
				//free
			}
		}
		if (line[i] && line[i] == '\"')
		{
			n = i;
			while (line[i] && line[i] != '\"')
				i++;
			if (line[i] != '\0')
			{

				str[num] = ft_substr(line, n, i-n);
				num++;
                n = i;
			}
			else
			{
				return (NULL);
				//free
			}
		}
		if (line[i] && ft_strchr(strset, line[i]))
		{
			if (n < i)
			{
				str[num] = ft_substr(line, n, i-n);
				num++;
                n = i;
			}
            
		}
		i++;
	}
	return (str);
}

int main(int ac, char **av)
{
    char **line;
    if (ac > 1)
        line = ft_strtok(av[1], " |");

    for (int i = 0; line[i];i++)
        printf("%s\n",line[i]);
}