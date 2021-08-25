/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:47:10 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/08/25 18:48:17 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_empty_list(t_env *env)
{
    if (env == NULL)
        return (1);
    return (0);
}

t_env	*create_cell(char *str)
{
	t_env	*env;

	if (!(env = malloc(sizeof(t_env))))
		return NULL;
	env->str = str;
	env->next = NULL;
	return (env);
}

t_env  *lst_add_back(t_env *env, char *str)
{
	t_env	*new;
	t_env	*cur;

	new = create_cell(str);
	cur = env;
	if (is_empty_list(env))
		return (new);
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
	return (env);
}

void    print_lst(t_env *env)
{
    while (env)
    {
        printf("%s\n", env->str);
        env = env->next;
    }
    printf("\n");
}

void	ft_env(t_env *env)
{
	while (env)
	{
		if(ft_charchr(env->str, '=') == SUCCESS)
			printf("%s\n", env->str);
		env = env->next;
	}
	write(1, "\n", 1);
}