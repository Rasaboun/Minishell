/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:59 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 01:24:44 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_output_trunc(char **args, int i)
{
	int		fd_out;

	if (args[i + 1][0] == '\0')
	{
		ft_write_error("minishell: ambiguous redirect\n");
		return (2);
	}
	fd_out = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd_out == -1)
	{
		ft_write_error("minishell: ");
		ft_write_error(args[i + 1]);
		ft_write_error(": No such file or directory\n");
		return (FAILURE);
	}
	dup2(fd_out, STDOUT_FILENO);
	ft_close(fd_out);
	return (SUCCESS);
}

int	ft_redir_output_append(char **args, int i)
{
	int		fd_out;

	fd_out = open(args[i + 1], O_WRONLY
			| O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd_out == -1)
	{
		ft_write_error("minishell: ");
		ft_write_error(args[i + 1]);
		ft_write_error(": No such file or directory\n");
		return (FAILURE);
	}
	dup2(fd_out, STDOUT_FILENO);
	ft_close(fd_out);
	return (SUCCESS);
}

int	ft_redir_input(char **args, int i)
{
	int		fd_in;

	fd_in = open(args[i + 1], O_RDONLY, S_IRUSR);
	if (fd_in == -1)
	{
		ft_write_error("minishell: ");
		ft_write_error(args[i + 1]);
		ft_write_error(": No such file or directory\n");
		return (2);
	}
	dup2(fd_in, STDIN_FILENO);
	ft_close(fd_in);
	return (SUCCESS);
}

int	ft_redir_input_eof(char **args, int i, t_minishell *minishell)
{
	int		fd_in;
	int		fd_out;
	int		fd_out_copy;

	if (minishell->stdin != STDIN_FILENO)
		dup2(minishell->stdin, STDIN_FILENO);
	if (minishell->stdout != STDOUT_FILENO)
	{
		fd_out_copy = dup(STDOUT_FILENO);
		dup2(minishell->stdout, STDOUT_FILENO);
	}
	fd_out = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_rl_input_eof(args[i + 1], fd_out);
	ft_close(fd_out);
	fd_in = open(".heredoc", O_RDONLY, S_IRUSR);
	dup2(fd_in, STDIN_FILENO);
	ft_close(fd_in);
	dup2(fd_out_copy, STDOUT_FILENO);
	close(fd_out_copy);
	return (SUCCESS);
}

int	ft_check_redir(char **args, t_minishell *minishell)
{
	int		i;
	int		ret;

	ret = FAILURE;
	i = 0;
	while (args[i])
	{
		if (strcmp(args[i], "'>'") == 0)
			ret = ft_redir_output_trunc(args, i);
		else if (strcmp(args[i], "'>>'") == 0)
			ret = ft_redir_output_append(args, i);
		else if (strcmp(args[i], "'<'") == 0)
			ret = ft_redir_input(args, i);
		else if (strcmp(args[i], "'<<'") == 0)
			ret = ft_redir_input_eof(args, i, minishell);
		i++;
	}
	return (ret);
}
