/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:47:10 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/04 18:11:55 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_change_env(t_env *env, char *str, char *value)
{
	char	*out;

	env->str = NULL;
	free(env->str);
	out = ft_strjoin_env(str, value);
	env->new = 1;
	return (out);
}

t_env	*ft_find_env(char *str, t_env *env)
{
	int		len;

	len = ft_strlen(str);
	while (env)
	{
		if (ft_strncmp(str, env->str, len) == 0 && (env->str[len] == '='
				|| env->str[len] == '\0'))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	print_lst(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->str);
		env = env->next;
	}
	printf("\n");
}

t_env	*create_cell(char *str)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
		return NULL;
	env->str = str;
	env->next = NULL;
	return (env);
}

t_env	*lst_add_back(t_env *env, char *str, int new_var)
{
	t_env	*new;
	t_env	*cur;

	new = create_cell(str);
	new->new = new_var;
	cur = env;
	if (is_empty_list(env))
		return (new);
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
	return (env);
}
