/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:44:58 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/04 18:12:52 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_init_env(char **envp)
{
	int		i;
	t_env	*env;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		env = lst_add_back(env, envp[i], 0);
		i++;
	}
	return (env);
}

void	ft_increment_shlvl(t_env *env)
{
	t_env	*cur;
	char	*tmp;
	char	*env_value;
	int		value;

	cur = ft_find_env("SHLVL", env);
	env_value = ft_env_value("SHLVL", env);
	if (!cur)
		lst_add_back(env, "SHLVL=1", 0);
	else if (!ft_isnum(env_value))
	{
		cur->str = ft_change_env(cur, "SHLVL", "1");
	}
	else
	{
		value = ft_atoi(env_value);
		cur->str = NULL;
		free(cur->str);
		tmp = ft_itoa(value + 1);
		cur->str = ft_change_env(cur, "SHLVL", tmp);
		free(tmp);
		free(env_value);
	}
}

void	ft_init_minishell(t_minishell *minishell, char **envp)
{
	minishell->env = ft_init_env(envp);
	ft_increment_shlvl(minishell->env);
	minishell->exit = 0;
	minishell->ret = 0;
	minishell->stdout = dup(STDOUT_FILENO);
	minishell->stdin = dup(STDIN_FILENO);
}

int	is_empty_list(t_env *env)
{
	if (env == NULL)
		return (1);
	return (0);
}
