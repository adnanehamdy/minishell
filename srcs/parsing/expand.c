/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:25:34 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/30 19:00:13 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_len(char *var)
{
	int i;

	i = 0;
	while (var[i] || ft_isdigit(var[i]) || ft_isalpha(var[i]) || var[i] == '_')
		i++;
	return (i);
}
char *get_var_name(char *prompt_cmd, int *index)
{
	char *var_name;
	int	i;

	i = 0;
	var_name = malloc(var_len(&prompt_cmd[*index]));
	while (prompt_cmd[*index] && (ft_isdigit(prompt_cmd[*index])
		|| ft_isalpha(prompt_cmd[*index]) || prompt_cmd[*index] == '_'))
	{
		var_name[i] = prompt_cmd[*index];
		(*index)++;
		i++;
	}
	return (var_name);
}
 
char *search_in_env(char *var_name)
{
	char **env;
	int	i;
	char	*tmp;

	i = 0;
	env = NULL;
	env = envp_handler(GETENV, env);
	while (env[i])
	{
		if (!env_var_cmp(env[i], var_name))
		{
			tmp = &env[i][ft_strlen(var_name) + 1];
			return (tmp);
		}
		i++;
	}
	return (NULL);	
}

char	*check_env(char *prompt_cmd, int *index)
{
	char *tmp;
	char *var_content;
	int	i;
	char *tmp01;

	i = 0;
	*index = *index + 1;
	if(ft_isalpha(prompt_cmd[*index]) || prompt_cmd[*index] == '_')
	{
		i = *index - 1;
		tmp = get_var_name(prompt_cmd, index);
		var_content = search_in_env(tmp);
		free(tmp);
		if (!var_content)
		{
			tmp = prompt_cmd;
			prompt_cmd[i] = 0;
			prompt_cmd = ft_strjoin(prompt_cmd, prompt_cmd + *index);
			free(tmp);
			*index = 0;
			if (!(prompt_cmd[0]))
				return (prompt_cmd);
		}
		else
		{
			tmp = prompt_cmd;
			prompt_cmd[i] = 0;
			prompt_cmd = ft_strjoin(prompt_cmd, var_content);
			i = ft_strlen(tmp);
			tmp01 = prompt_cmd;
			prompt_cmd = ft_strjoin(prompt_cmd, &tmp[*index]);
			free(tmp);
			free(tmp01);
			*index = i;
			return (prompt_cmd);
		}
	}
	else if (ft_isdigit(prompt_cmd[*index]))
	{
		tmp = prompt_cmd;
		prompt_cmd[*index - 1] = 0;
		i = ft_strlen(tmp);
		prompt_cmd = ft_strjoin(prompt_cmd, prompt_cmd + (*index) + 1);
		free(tmp);
		*index = i;
		return (prompt_cmd);
	}
	else if (prompt_cmd[*index] == '?')
	{
		tmp = prompt_cmd;
		prompt_cmd[*index - 1] = 0;
		var_content = ft_itoa(exit_code_handler(GETEXIT, 0));
		prompt_cmd = ft_strjoin(prompt_cmd, var_content);
		i = ft_strlen(tmp);
		tmp01 = prompt_cmd;
		prompt_cmd = ft_strjoin(prompt_cmd, tmp + *index + 1);
		free(tmp);
		free(tmp01);
		*index = i;
		return (prompt_cmd);
	}
	else if (prompt_cmd[*index] == '\'' || prompt_cmd[*index] == '"')
	{
		tmp = prompt_cmd;
		prompt_cmd[*index - 1] = 0;
		i = ft_strlen(&prompt_cmd[*index - 1]);
		prompt_cmd = ft_strjoin(prompt_cmd, prompt_cmd + *index);
		free(tmp);
		*index = i;
		return (prompt_cmd);
	}
	else
		*index = *index + 1;
	return (prompt_cmd);
}

void	expand_handler(char **prompt_cmd)
{
	int index;
	char	last_char;

	index = 0;
	while ((*prompt_cmd)[index])
	{
		if ((*prompt_cmd)[index] == '<' && (*prompt_cmd)[index] == (*prompt_cmd)[index + 1])
		{
			index += 2;
			index = index + skip_io_redirection(*prompt_cmd + index);
		}
		else if (((*prompt_cmd)[index]) == '$' && ((*prompt_cmd)[index + 1]))
		{
			if ((last_char == '\'' || last_char == '"') && (*prompt_cmd)[index + 1] == last_char)
			{
				index++;
				continue;
			}
			*prompt_cmd = check_env(*prompt_cmd, &index);
			if (!(*prompt_cmd[0]))
				return ;
		}
		last_char = (*prompt_cmd)[index];
		index++;
	}
}