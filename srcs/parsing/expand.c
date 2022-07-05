/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:25:34 by ahamdy            #+#    #+#             */
/*   Updated: 2022/07/04 17:59:46 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_var_name(char *prompt_cmd, int *index)
{
	char *var_name;
	int	i;

	i = 0;
	var_name = malloc(var_len(&prompt_cmd[*index]) + 1);
	while (prompt_cmd[*index] && (ft_isdigit(prompt_cmd[*index])
		|| ft_isalpha(prompt_cmd[*index]) || prompt_cmd[*index] == '_'))
	{
		var_name[i] = prompt_cmd[*index];
		(*index)++;
		i++;
	}
	var_name[i] = 0;
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

char	*valid_content(char *prompt_cmd, int *index, char *var_content, int i)
{
	char	*tmp;
	char	*tmp01;
	// int		i;

	// i = *index - 1;
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

char	*check_env(char *prompt_cmd, int *index)
{
	char *tmp;
	int	i;

	i = 0;
	*index = *index + 1;
	tmp = check_is_alpha(prompt_cmd, index);
	if (tmp)
		return (tmp);
	else if (ft_isdigit(prompt_cmd[*index]))
		return (check_is_digit(prompt_cmd, index));
	else if (prompt_cmd[*index] == '?')
		return (check_exit_code(prompt_cmd, index));
	else if (prompt_cmd[*index] == '\'' || prompt_cmd[*index] == '"')
		return (check_is_quote(prompt_cmd, index));
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