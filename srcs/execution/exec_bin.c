/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 12:59:27 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/09 01:43:07 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_bin_error(char *path)
{
	int		fd;
	DIR		*dir;
	int		ret;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	ft_write_error("minishell: ");
	ft_write_error(path);
	if (ft_strchr(path, '/') == NULL)
		ft_write_error(": command not found\n");
	else if (fd == -1 && dir != NULL)
		ft_write_error(": is a directory\n");
	else if (access(path, R_OK) == 0 && access(path, X_OK) != 0 && dir == NULL)
		ft_write_error(": Permission denied\n");
	else if (fd == -1 && dir == NULL)
		ft_write_error(": No such file or directory\n");
	if (ft_strchr(path, '/') == NULL || (fd == -1 && dir == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = CANNOT_EXECUTE;
	ft_close(fd);
	if (dir)
		closedir(dir);
	return (ret);
}

void	ft_write_error_bin(int ret)
{
	if (ret == 139)
		ft_write_error("Segmentation fault: 11\n");
	else if (ret == 138)
		ft_write_error("Bus error: 10\n");
	else if (ret == 134)
		ft_write_error("Abort trap: 6\n");
}

int	bin_fonction(char **argv, t_env *env)
{
	char	**array;
	char	**env_cpy;
	int		found;
	int		i;
	int		ret;

	i = 0;
	found = 0;
	array = split_path(env);
	env_cpy = ft_list_to_array(env);
	while (array && array[i])
	{
		ret = bin_is_exist(array[i], argv, env_cpy);
		if (ret != -1)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found == 0)
		ret = exec_bin(argv[0], argv, env_cpy);
	ft_free_array(env_cpy);
	ft_free_array(array);
	return (ret);
}

int	bin_is_exist(char *path, char **cmd, char **env_cpy)
{
	struct stat	sb;
	char		*tmp;
	int			ret;

	ret = -1;
	tmp = ft_strjoin(path, "/");
	path = ft_strjoin(tmp, cmd[0]);
	free(tmp);
	if (stat(path, &sb) == 0)
		ret = exec_bin(path, cmd, env_cpy);
	free(path);
	return (ret);
}

int	exec_bin(char *path, char **cmd, char **env_cpy)
{
	pid_t	pid;
	int		ret;
	int		status;

	ret = FAILURE;
	if (strchr(path, '/') == NULL || access(path, R_OK) != 0)
		return (ft_check_bin_error(path));
	pid = fork();
	signal(SIGINT, stop_bin_process);
	signal(SIGQUIT, quit_bin_process);
	if (pid == 0)
	{
		if (strchr(path, '/') != NULL)
			execve(path, cmd, env_cpy);
		ret = ft_check_bin_error(path);
		exit(ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		ret = ft_ret_fork_status(status);
		ft_write_error_bin(ret);
	}
	return (ret);
}
