/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:47:10 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/04 15:43:53 by dkoriaki         ###   ########.fr       */
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

void	print_env_array(char **array)
{
	int		y;
	int		x;
	int		equal;

	
	y = 0;
	while (array[y])
	{
		x = 0;
		equal = 0;
		write(STDOUT_FILENO, "declare -x ", 11);
		while(array[y][x])
		{
			write(STDOUT_FILENO, &array[y][x], 1);
			if (array[y][x] == '=')
			{
				write(STDOUT_FILENO, "\"", 1);
				equal = 1;
			}
			x++;
		}
		if (equal == 1)
			write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
		y++;
	}
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

char	**ft_list_to_array(t_env *env)
{
	int		nb_lines;
	int		i;
	char	**array;

	i = 0;
	nb_lines = ft_env_len(env);
	array = (char **)malloc(sizeof(char *) * (nb_lines + 1));
	if (!array)
		return (NULL);
	while (env && i < nb_lines)
	{
		array[i] = ft_strdup(env->str);
		env = env->next;
		i++;
	}
	array[i] = NULL;
	
	return (array);
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

	if (!s1/* || !s2*/)
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

char	*ft_change_env(t_env *env, char *str, char *value)
{
	char	*out;

	env->str = NULL;
	free(env->str);
	out = ft_strjoin_env(str, value);
	env->new = 1;
	return(out);
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

t_env  *lst_add_back(t_env *env, char *str, int new_var)
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

void    print_lst(t_env *env)
{
    while (env)
    {
        printf("%s\n", env->str);
        env = env->next;
    }
    printf("\n");
}
