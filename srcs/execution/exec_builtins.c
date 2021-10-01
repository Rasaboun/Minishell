/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:38:30 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/01 13:32:48 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		exec_builtins(t_cmd *ccmd, t_minishell *minishell)
{
	int		ret;
	t_env	*env;

	env = minishell->env;
	if (ft_strcmp(ccmd->args[0], "echo") == 0)
		ret = ft_echo(ccmd);
	else if (ft_strcmp(ccmd->args[0], "cd") == 0)
		ret = ft_cd(ccmd, env);
	else if (ft_strcmp(ccmd->args[0], "pwd") == 0)
		ret = ft_pwd();
	if (ft_strcmp(ccmd->args[0], "export") == 0)
		ret = (ft_export(ccmd, env));
	if (ft_strcmp(ccmd->args[0], "unset") == 0)
		ret = ft_unset(ccmd, env);
	if (ft_strcmp(ccmd->args[0], "env") == 0)
		ret = ft_env(env);
	else if (ft_strcmp(ccmd->args[0], "exit") == 0)
		ret = ft_exit(ccmd, minishell);
	printf("\n\necho $? = %d\n", ret);
	return (ret);
}
