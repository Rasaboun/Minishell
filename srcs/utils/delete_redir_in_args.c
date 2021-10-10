/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redir_in_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:43:50 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 13:33:19 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_is_empty_list(t_args *args)
{
	if (args == NULL)
		return (1);
	return (0);
}

t_args	*args_create_cell(char *str)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->str = ft_strdup(str);
	args->next = NULL;
	args->previous = NULL;
	return (args);
}

t_args	*args_add_back(t_args *args, char *str)
{
	t_args	*new;
	t_args	*cur;

	new = args_create_cell(str);
	cur = args;
	if (args_is_empty_list(args))
		return (new);
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
	new->previous = cur;
	return (args);
}

t_args	*ft_init_args(char **args)
{
	int		i;
	t_args	*list_args;

	i = 0;
	list_args = NULL;
	while (args[i] != NULL)
	{
		list_args = args_add_back(list_args, args[i]);
		i++;
	}
	return (list_args);
}

int	ft_is_redir(char *str)
{
	if (ft_strcmp(str, "{'>'}") == 0)
		return (SUCCESS);
	if (ft_strcmp(str, "{'>>'}") == 0)
		return (SUCCESS);
	if (ft_strcmp(str, "{'<'}") == 0)
		return (SUCCESS);
	if (ft_strcmp(str, "{'<<'}") == 0)
		return (SUCCESS);
	return (FAILURE);
}
