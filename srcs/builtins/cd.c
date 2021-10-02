/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:10:16 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/09/10 18:04:07 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		go_to_home(t_env *env)
{
	t_env	*cur;
	char	*str;

	cur = ft_find_env("HOME", env);
	if (cur == NULL)
	{
		ft_write_error(" cd: HOME not set");
		return (FAILURE);
	}
	str = cur->str;
	int i = 1;
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
	t_env	*cur;

	getcwd(path, sizeof(path));
	cur = ft_find_env("PWD", env);
	if (cur == NULL)
		return (FAILURE);
	cur->str = ft_change_env("PWD", path);
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
	cur->str = ft_change_env("OLDPWD", oldpath);
	return (SUCCESS);
}

int		ft_cd(t_cmd *ccmd, t_env *env)
{
	char	*directory;

	directory = ccmd->args[1];
	ft_save_oldpwd(env);
	if (!directory)
		return (go_to_home(env));
	else if (chdir(directory) == 0)
	{
		ft_save_pwd(env);
		return(SUCCESS);
	}
	else
	{
		ft_write_error(" cd: ");
		ft_write_error(directory);
		ft_write_error(": No such file or directory\n");
	}
	return (FAILURE);
}