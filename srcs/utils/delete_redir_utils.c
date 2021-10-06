/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:13:34 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/06 15:28:53 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*list_rewind(t_args *args)
{
	while (args && args->previous)
	{
		args = args->previous;
	}
	return (args);
}

char	**delete_redir_in_args(char **args)
{
	char	**args_without_redir;
	t_args	*list_args;
	t_args	*tmp;

	list_args = ft_init_args(args);
	list_args = ft_delete_cell_args(list_args);
	list_args = list_rewind(list_args);
	ft_free_array(args);
	args_without_redir = ft_list_to_array_args(list_args);
	while (list_args)
	{
		tmp = list_args;
		list_args = list_args->next;
		free(tmp->str);
		free(tmp);
	}
	return (args_without_redir);
}

t_args	*ft_delete_cell_args(t_args *args)
{
	t_args	*cur;
	t_args	*prev;

	cur = args;
	if (ft_is_redir(args->str) == SUCCESS)
	{
		if (args->next->next)
		{
			args = args->next->next;
			args->previous = NULL;
		}
		else
			args = NULL;
		ft_free_cell_args_next(cur);
	}
	ft_delete_cell_args_next(args, cur, prev);
	return (args);
}

void	ft_delete_cell_args_next(t_args *args, t_args *cur, t_args *prev)
{
	while (args && args->next != NULL)
	{
		if (args->previous)
			prev = args->previous;
		cur = args;
		if (ft_is_redir(args->str) == SUCCESS)
		{
			if (args->next->next)
			{
				args->next->next->previous = prev;
				prev->next = args->next->next;
				args = args->next->next;
				ft_free_cell_args_next(cur);
			}
			else
			{
				prev->next = NULL;
				ft_free_cell_args_next(cur);
				args = prev;
			}
		}
		else
			args = args->next;
	}
}

void	ft_free_cell_args_next(t_args *cur)
{
	free(cur->next->str);
	free(cur->next);
	free(cur->str);
	free(cur);
}
