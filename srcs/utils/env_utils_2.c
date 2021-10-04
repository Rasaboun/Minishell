/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:58:33 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/04 17:03:54 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_cell(t_env *env, int how)
{
	if (how == 1 || how == 2)
		free(env);
	if (how == 2)
		free(env->str);
}

char	**ft_sort_env(char **envp)
{
	char	*tmp;
	int		i;
	int		j;
	int		env_len;

	tmp = NULL;
	i = 0;
	j = 0;
	env_len = ft_array_len(envp);
	while (i < env_len)
	{
		j = 0;
		while (j < env_len - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

int		ft_env_len(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	*ft_env_value(char *str, t_env *env)
{
	int		len;
	t_env	*cur;
	int		i;
	int		j;
	char	*ret;

	len = ft_strlen(str);
	cur = ft_find_env(str, env);
	if (cur == NULL)
		return (NULL);
	i = ft_strlen(cur->str) - (len + 1);
	ret = malloc(sizeof(char*) * (i + 1));
	if (ret == NULL)
		return (NULL);
	i = len + 1;
	j = 0;
	while (cur->str[i])
	{
		ret[j] = cur->str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_strjoin_env(char *s1, char *s2)
{
	int		i;
	int		j;
	int		mallen;
	char	*out;

	if (!s1)
		return (NULL);
	mallen = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(out = (char *)malloc(sizeof(char) * mallen + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		out[i++] = s1[j++];
	out[i++] = '=';
	j = 0;
	if (s2)
		while (s2[j])
			out[i++] = s2[j++];
	out[i] = '\0';
	return (out);
}