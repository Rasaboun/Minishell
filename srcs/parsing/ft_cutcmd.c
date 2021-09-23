#include "minishell.h"

char	*ft_cutequotes(char *line)
{
	int n;
	char *l;

	l = NULL;

	n = ft_strlen(line);
	if ((n - 2) > 0)
	{
		l = ft_substr(line, 1, n-1);
		return (l);
	}
	return (NULL);
}


void	ft_cutcmd(t_cmd **cmd, char *line)
{
	int	i;
	char *l;
	int n;
	t_cmd *tmp;
	char **str;

	i = 0;
	str = ft_strtok(line, "|;");
	while (str[i])
	{
		printf("%s\n",str[i]);
		i++;

	}

}