/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 12:59:27 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/02 14:12:17 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bin_fonction(char **argv, t_env *env)
{
	char	**tab;
	char	*path;
	int		i;

	i = 0;
	path = ft_env_value("PATH", env);
	tab = ft_split(path, ':');
	while (tab[i])
	{
		if (bin_is_exist(tab[i], argv, env) == 0)
			break ;
		i++;
	}
	//printf("ta mere la tchoin\n");
	return (0);
}

int		bin_is_exist(char *path, char **cmd, t_env *env)
{
	struct stat sb;
	char	*tmp;
	int		ret;
	char	**env_cpy;

	ret = 1;
	tmp = ft_strjoin(path, "/");
	path = ft_strjoin(tmp, cmd[0]);
	free(tmp);
	if (stat(path, &sb) == 0)
	{
		env_cpy = ft_list_to_array(env);
		ret = exec_bin(path, cmd, env_cpy);
		//printf("tchoin tchoin tchoin\n");
		//Il faut free le tableau env_cpy;
		free(env_cpy);
	}
	//printf("tchip\n");
	return (ret);
}

int		exec_bin(char *path, char **cmd, char **env_cpy)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd, env_cpy);
	}
	else
		waitpid(pid, &status, 0);
		//ait(NULL);
	return (0);
}