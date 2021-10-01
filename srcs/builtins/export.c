/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:38:59 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/01 14:07:08 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"





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
	//print_lst(env);
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

int		ft_print_export(t_env *env)
{
	char	**array;

	array = ft_list_to_array(env);
	array = ft_sort_env(array);
	print_env_array(array);
	ft_free_array(array);
	return (SUCCESS);
}

int		parse_export(char *str)
{
	int		i;

	i = 0;
	if (str[i] && ft_isalpha(str[i]) != 1 && str[i] != '_')
	{
		ft_write_error(" export: `");
		ft_write_error(str);
		ft_write_error("': not a valid identifier\n");
		return (1);
	}
	return (0);
}

void	ft_len_variable_and_value(char *str, t_exp *exp)
{
	int		i;

	i = 0;
	exp->len_value = 0;
	exp->len_var = 0;
	exp->equal = 0;
	while(str[i] && str[i] != '=')
	{
		exp->len_var++;
		i++;
	}
	if (str[i] && str[i] == '=')
	{
		exp->equal = 1;
		i++;
	}
	if (str[i])
	{
		while (str[i])
		{
			exp->len_value++;
			i++;
		}
	}
}

void	ft_set_variable_and_value(char *str, t_exp *exp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	exp->var = NULL;
	exp->value = NULL;
	if (exp->len_var > 0)
	{
		exp->var = malloc(sizeof(char) * (exp->len_var + 1));
		while(str[i] && str[i] != '=')
		{
			exp->var[i] = str[i];
			i++;
		}
		exp->var[i] = '\0';
	}
	if (exp->len_value > 0)
	{
		exp->value = malloc(sizeof(char) * (exp->len_value + 1));
		i++;
		while(str[i])
		{
			exp->value[j] = str[i];
			i++;
			j++;
		}
		exp->value[j] = '\0';
	}
}

t_exp	ft_export_split(char *str)
{
	t_exp	exp;
	int		i;

	i = 0;
	ft_len_variable_and_value(str, &exp);
	ft_set_variable_and_value(str, &exp);
	//printf("%s\n", str);
	//printf("var = %s\nlen_var = %d\nequal = %d\nvalue = %s\nlen_value = %d\n",exp.var, exp.len_var, exp.equal, exp.value, exp.len_value);
	return (exp);
}

void	ft_exec_export(char *str, t_exp *exp, t_env *env)
{
	t_env	*cur;
	char	*tmp;


	//IF str existe deja =
	cur = ft_find_env(exp->var, env);
	if (cur != NULL)
	{
		if (!exp->value)
			return;
		cur->str = ft_change_env(cur, exp->var, exp->value);
		return;
	}
	//cas : export -> "str=value" && "str="
	else if (exp->value || exp->equal == 1)
	{
		tmp = ft_strjoin_env(exp->var, exp->value);
		env = lst_add_back(env, tmp, 1);
	}
	else // cas : "export str"
		env = lst_add_back(env, ft_strdup(exp->var), 1);
	return;
}

int		ft_export(t_cmd *ccmd, t_env *env)
{
	int		i;
	t_exp	exp;
	int		ret;
	int		ret2;

	i = 1;
	ret = 0;
	ret2 = 0;
	if (ft_array_len(ccmd->args) == 1)
		return(ft_print_export(env));
	while (ccmd->args[i])
	{
		ret = parse_export(ccmd->args[i]);
		if (ret == 0)
		{
			exp = ft_export_split(ccmd->args[i]);
			ft_exec_export(ccmd->args[i] ,&exp, env);
			//printf("var = %s | value = %s", exp.var, exp.value);
			if (exp.var)
				free(exp.var);
			if (exp.value)
				free(exp.value);
		}
		else
			ret2 = 1;
		//printf("var = %s | value = %s", exp.var, exp.value);
		/*if (exp.var)
			free(exp.var);
		if (exp.value)
			free(exp.value);*/
		i++;
	}
	return (ret2);
}
/*
int		ft_export(char *str, char *value, t_env *env)
{
	char	**array;
	t_env	*cur;
	char	*tmp;
	//If 0 arguments, 
	if(!str && !value)
		return (ft_print_export(env));
	//IF str existe deja =
	cur = ft_find_env(str, env);
	if (cur != NULL)
	{
		if (!value)
			return (SUCCESS);
		cur->str = ft_change_env(cur, str, value);
		return (SUCCESS);
	}
	//cas : export -> "str=value" && "str="
	if (value)
	{
		tmp = ft_strjoin_env(str, value);
		env = lst_add_back(env, tmp);
	}
	else // cas : "export str"
		env = lst_add_back(env, str);
	return (SUCCESS);
}*/



//char	**delet_redir_args(char **args)
//{
//	char	**ret;

	//exemple "echo > test.txt hello world"
	//args = [echo, >, test.txt, hello, world];
	//ret = malloc(sizeof(char*) * ("nombre d'args sans la redir et le fichier, ici c'est echo, hello, world. Donc 3"));
	//a la fin ret = [echo, hello, world]
	//Il faut free l'ancien args pour le remplacer par le nouveau.
	// return (ret);
//}
/*
int		main(void)
{
	char	**args = [echo, >, test.txt, hello, world];

	args = delet_redir_args(args);
	mtn args = [echo, hello, world];
}*/


/*

Il faut faire une fonction qui va lire les entrées de l'utilisateur jusqu'a qu'il ecrive l'END OF FILE
je pense qu'il faut creer un fichier temporaire, a chaque fois qu'il ecrit une nouvelle ligne on l'ajoute au fichier
et quand il a fini, on execute la fonction avec le fichier et on le supprime.

void	redir_eof(char *eof)
{
	fd_redir = open(tab[i + 1], O_WRONLY|O_CREAT|O_APPEND, 0666); Ca c'est pour rajouter 
}
*/