/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:31:46 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/20 18:27:36 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <stdlib.h>
# include "../Libft/libft.h"

# define PIPED 1
# define BREAK 2
# define END 3

typedef	struct	s_cmd
{
	char **args;
	int pipe[2];
	int type;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}				t_cmd;

void	ft_tcmdadd_back(t_cmd **alst, t_cmd *new);
t_cmd	*ft_tcmdlast(t_cmd *lst);
int	ft_tcmdsize(t_cmd *lst);
t_cmd	*ft_tcmdnew(char **args);


#endif
