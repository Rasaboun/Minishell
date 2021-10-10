/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:32:31 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 13:29:36 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_export(char *str)
{
	int		i;

	i = 0;
	if ((str[i] && ft_isalpha(str[i]) != 1 && str[i] != '_') || str[i] == '\0'
		|| space_in_env_name(str) == SUCCESS)
	{
		ft_write_error("minishell: export: `");
		ft_write_error(str);
		ft_write_error("': not a valid identifier\n");
		return (1);
	}
	return (0);
}

void	ft_len_variable_and_value(char *str, t_exp *exp)
{
	int		i;

	i = 0;
	exp->len_value = 0;
	exp->len_var = 0;
	exp->equal = 0;
	while (str[i] && str[i] != '=')
	{
		exp->len_var++;
		i++;
	}
	if (str[i] && str[i] == '=')
	{
		exp->equal = 1;
		i++;
	}
	if (str[i])
	{
		while (str[i])
		{
			exp->len_value++;
			i++;
		}
	}
}

char	*ft_set_value_export(int i, char *str, int value_len)
{
	int		j;
	char	*value;

	j = 0;
	i++;
	value = malloc(sizeof(char) * (value_len + 1));
	if (!value)
		return (NULL);
	while (str[i])
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

void	ft_set_variable_and_value(char *str, t_exp *exp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	exp->var = NULL;
	exp->value = NULL;
	if (exp->len_var > 0)
	{
		exp->var = malloc(sizeof(char) * (exp->len_var + 1));
		while (str[i] && str[i] != '=')
		{
			exp->var[i] = str[i];
			i++;
		}
		exp->var[i] = '\0';
	}
	if (exp->len_value > 0)
		exp->value = ft_set_value_export(i, str, exp->len_value);
}

t_exp	ft_export_split(char *str)
{
	t_exp	exp;
	int		i;

	i = 0;
	ft_len_variable_and_value(str, &exp);
	ft_set_variable_and_value(str, &exp);
	return (exp);
}
