/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:10:16 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 23:09:59 by dkoriaki         ###   ########.fr       */
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
		return (ft_write_error(" cd: HOME not set\n"));
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
		ft_write_error("minishell: cd: ");
		ft_write_error(&str[i]);
		ft_write_error(": No such file or directory\n");
	}
	return (FAILURE);
}

int	ft_save_pwd(t_env *env)
{
	char	path[PATH_MAX];
	t_env	*cur;

	getcwd(path, sizeof(path));
	cur = ft_find_env("PWD", env);
	if (cur == NULL)
		return (FAILURE);
	cur->str = ft_change_env(cur, "PWD", path);
	return (SUCCESS);
}

int	ft_save_oldpwd(t_env *env)
{
	char	oldpath[PATH_MAX];
	t_env	*cur;

	getcwd(oldpath, sizeof(oldpath));
	cur = ft_find_env("OLDPWD", env);
	if (cur == NULL)
		return (FAILURE);
	cur->str = ft_change_env(cur, "OLDPWD", oldpath);
	return (SUCCESS);
}

int	ft_cd(t_cmd *ccmd, t_env *env)
{
	char	*directory;

	if (ccmd->args[1] && ccmd->args[2])
		return (ft_write_error("minishell: cd: too many arguments\n"));
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
		ft_write_error("minishell: cd: ");
		ft_write_error(directory);
		ft_write_error(": No such file or directory\n");
	}
	return (FAILURE);
}
