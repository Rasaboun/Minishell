/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redir_in_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:43:50 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/06 11:44:54 by dkoriaki         ###   ########.fr       */
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

int		ft_is_redir(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (SUCCESS);
	if (ft_strcmp(str, ">>") == 0)
		return (SUCCESS);
	if (ft_strcmp(str, "<") == 0)
		return (SUCCESS);
	if (ft_strcmp(str, "<<") == 0)
		return (SUCCESS);
	return (FAILURE);
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
		free(cur->next->str);
		free(cur->next);
		free(cur->str);
		free(cur);
	}
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
				free(cur->next->str);
				free(cur->next);
				free(cur->str);
				free(cur);
			}
			else
			{
				prev->next = NULL;
				free(cur->next->str);
				free(cur->next);
				free(cur->str);
				free(cur);
				args = prev;
			}
		}
		else
			args = args->next;
	}
	return (args);
}

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
/*
void	ft_freecmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}*/
