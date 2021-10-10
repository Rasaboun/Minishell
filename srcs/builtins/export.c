/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:38:59 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 15:06:54 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exp_free(t_exp *exp)
{
	if (exp->var)
		free(exp->var);
	if (exp->value)
		free(exp->value);
}

int	ft_print_export(t_env *env)
{
	char	**array;

	array = ft_list_to_array(env);
	array = ft_sort_env(array);
	print_env_array(array);
	ft_free_array(array);
	return (SUCCESS);
}

void	ft_exec_export(t_exp *exp, t_env *env)
{
	t_env	*cur;
	char	*tmp;

	cur = ft_find_env(exp->var, env);
	if (cur != NULL)
	{
		if (!exp->value)
			return ;
		cur->str = ft_change_env(cur, exp->var, exp->value);
		return ;
	}
	else if (exp->value || exp->equal == 1)
	{
		tmp = ft_strjoin_env(exp->var, exp->value);
		env = lst_add_back(env, tmp, 1);
	}
	else
		env = lst_add_back(env, ft_strdup(exp->var), 1);
	return ;
}

int	ft_export(t_cmd *ccmd, t_env *env)
{
	int		i;
	t_exp	exp;
	int		ret;
	int		ret2;

	i = 1;
	ret = 0;
	ret2 = 0;
	if (ft_array_len(ccmd->args) == 1)
		return (ft_print_export(env));
	while (ccmd->args[i])
	{
		ret = parse_export(ccmd->args[i]);
		if (ccmd->args[i][0] != '\0' && ret == 0)
		{
			exp = ft_export_split(ccmd->args[i]);
			ft_exec_export(&exp, env);
			ft_exp_free(&exp);
		}
		else if (ret != 0)
			ret2 = 1;
		i++;
	}
	return (ret2);
}
