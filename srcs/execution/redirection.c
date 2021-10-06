/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:59 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/06 15:11:43 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_output_trunc(char **args, int i)
{
	int		fd_out;

	fd_out = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd_out == -1)
	{
		ft_write_error("minishell: ");
		ft_write_error(args[i + 1]);
		ft_write_error(": No such file or directory");
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
		ft_write_error(": No such file or directory");
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
		ft_write_error(": No such file or directory");
		return (2);
	}
	dup2(fd_in, STDIN_FILENO);
	ft_close(fd_in);
	return (SUCCESS);
}

int	ft_redir_input_eof(char **args, int i)
{
	int		fd_in;
	int		fd_out;
	char	*line;

	line = NULL;
	fd_out = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, args[i + 1]) == 0)
		{
			free(line);
			break ;
		}
		else
		{
			ft_putstr_eol_fd(line, fd_out);
			free(line);
		}
	}
	ft_close(fd_out);
	fd_in = open(".heredoc", O_RDONLY, S_IRUSR);
	dup2(fd_in, STDIN_FILENO);
	ft_close(fd_in);
	return (SUCCESS);
}

int	ft_check_redir(char **args)
{
	int		i;
	int		ret;

	ret = FAILURE;
	i = 0;
	while (args[i])
	{
		if (strcmp(args[i], ">") == 0)
			ret = ft_redir_output_trunc(args, i);
		else if (strcmp(args[i], ">>") == 0)
			ret = ft_redir_output_append(args, i);
		else if (strcmp(args[i], "<") == 0)
			ret = ft_redir_input(args, i);
		else if (strcmp(args[i], "<<") == 0)
			ret = ft_redir_input_eof(args, i);
		i++;
	}
	return (ret);
}
