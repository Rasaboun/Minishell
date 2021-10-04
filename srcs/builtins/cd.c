/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:10:16 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/04 14:21:05 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_to_home(t_env *env)
{
	t_env	*cur;
	char	*str;
	int		i;

	cur = ft_find_env("HOME", env);
	if (cur == NULL)
	{
		ft_write_error(" cd: HOME not set");
		return (FAILURE);
	}
	str = cur->str;
	i = 1;
	while (str[i - 1] != '=')
		i++;
	if (chdir(&str[i]) == 0)
	{
		ft_save_pwd(env);
		return (SUCCESS);
	}
	else
	{
		ft_write_error(" cd: ");
		ft_write_error(&str[i]);
		ft_write_error(": No such file or directory\n");
	}
	return (FAILURE);
}

int	ft_save_pwd(t_env *env)
{
	char	path[PATH_MAX];
	char	*tmp;
	t_env	*cur;

	getcwd(path, sizeof(path));
	tmp = NULL;
	cur = ft_find_env("PWD", env);
	if (cur == NULL)
		return (FAILURE);
	printf("cur->new = %d\n", cur->new);
	if (cur->new == 1)
		tmp = cur->str;
	cur->str = ft_change_env(cur, "PWD", path);
	if (tmp)
		free(tmp);
	return (SUCCESS);
}

int	ft_save_oldpwd(t_env *env)
{
	char	oldpath[PATH_MAX];
	char	*tmp;
	t_env	*cur;

	getcwd(oldpath, sizeof(oldpath));
	tmp = NULL;
	cur = ft_find_env("OLDPWD", env);
	if (cur == NULL)
		return (FAILURE);
	if (cur->new == 1)
		tmp = cur->str;
	cur->str = ft_change_env(cur, "OLDPWD", oldpath);
	if (tmp)
		free(tmp);
	return (SUCCESS);
}

int	ft_cd(t_cmd *ccmd, t_env *env)
{
	char	*directory;

	directory = ccmd->args[1];
	ft_save_oldpwd(env);
	if (!directory)
		return (go_to_home(env));
	else if (chdir(directory) == 0)
	{
		ft_save_pwd(env);
		return (SUCCESS);
	}
	else
	{
		ft_write_error(" cd: ");
		ft_write_error(directory);
		ft_write_error(": No such file or directory\n");
	}
	return (FAILURE);
}
