/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:54:51 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/09/30 17:21:38 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int		env_variable_len(char *str)
{
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
	{
		len++;
	}
	return (len);
}

int		parse_unset(char *str)
{
	int		i;

	i = 0;
	if (str[i] && ft_isalpha(str[i]) != 1 && str[i] != '_')
	{
		ft_write_error(" unset: `");
		ft_write_error(str);
		ft_write_error("': not a valid identifier\n");
		return (1);
	}
	return (0);
}

void	ft_exec_unset(char *str, t_env *env)
{
	t_env	*cur;
	t_env	*prec;

	cur = env;
	prec = env;
	if (ft_find_env(str, env) == NULL)
		return;
	if (!env)
		return;
	if (ft_strncmp(str, env->str, env_variable_len(env->str)) == 0)
	{
		env = env->next;
		free(cur);
	}
	while (cur)
	{
		prec = cur;
		cur = cur->next;
		if (ft_strncmp(str, cur->str, env_variable_len(cur->str)) == 0)
		{
			prec->next = cur->next;
			free(cur);
			return;
		}
	}
}

int		ft_unset(t_cmd *ccmd, t_env *env)
{
	int		i;
	int		ret;
	int		ret2;

	i = 0;
	ret = 0;
	ret2 = 0;
	while(ccmd->args[i])
	{
		ret = parse_unset(ccmd->args[i]);
		if (ret == 0)
			ft_exec_unset(ccmd->args[i], env);
		else
			ret2 = 1;
		i++;
	}
	return (ret2);
}

/*
int		*ftt_exec_unset(char *str, t_env *env)
{
	t_env	*cur;
	t_env	*prec;

	cur = env;
	prec = env;
	if (ft_find_env(str, env) == NULL)
		return (0);
	if (!env)
		return (0);
	if (ft_strncmp(str, env->str, env_variable_len(env->str)) == 0)
	{
		env = env->next;
		free(cur);
		return (0);
	}
	while (cur)
	{
		prec = cur;
		cur = cur->next;
		if (ft_strncmp(str, cur->str, env_variable_len(cur->str)) == 0)
		{
			prec->next = cur->next;
			free(cur);
			return (0);
		}
	}
	return (0);
}*/