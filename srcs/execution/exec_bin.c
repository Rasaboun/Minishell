/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 12:59:27 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/02 15:32:35 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bin_fonction(char **argv, t_env *env)
{
	char	**array;
	char	**env_cpy;
	char	*path;
	int		found;
	int		i;

	i = 0;
	found = 0;
	path = ft_env_value("PATH", env);
	array = ft_split(path, ':');
	env_cpy = ft_list_to_array(env);
	while (array[i])
	{
		if (bin_is_exist(array[i], argv, env_cpy) == 0)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found == 0)
		exec_bin(argv[0], argv, NULL);
	ft_free_array(env_cpy);
	ft_free_array(array);
	free(path);
	return (0);
}

int		bin_is_exist(char *path, char **cmd, char **env_cpy)
{
	struct stat sb;
	char	*tmp;
	int		ret;

	ret = 1;
	tmp = ft_strjoin(path, "/");
	path = ft_strjoin(tmp, cmd[0]);
	free(tmp);
	//printf("path = %s\n", path);
	if (stat(path, &sb) == 0)
	{
		ret = exec_bin(path, cmd, env_cpy);
		//printf("tchoin tchoin tchoin\n");
		//Il faut free le tableau env_cpy;
		free(path);
		ft_free_array(env_cpy);
	}
	//printf("tchip\n");
	return (ret);
}

int		exec_bin(char *path, char **cmd, char **env_cpy)
{
	pid_t	pid;
	int		status;
	(void)path;

	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd, env_cpy);
		//execve("./a.out", cmd, env_cpy);
	}
	else
		waitpid(pid, &status, 0);
		//wait(NULL);
	return (0);
}