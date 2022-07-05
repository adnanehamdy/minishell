/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:27:53 by ahamdy            #+#    #+#             */
/*   Updated: 2022/07/04 17:43:00 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_valid_content(char *prompt_cmd, int *index, char *var_content, int i)
{
	char *tmp;

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
		return (valid_content(prompt_cmd, index, var_content, i));
	return (NULL);
}

char	*check_is_alpha(char *prompt_cmd, int *index)
{
	 int	i;
	char *tmp;
	//char *tmp01;
	char *var_content;

	 i = *index - 1;
	if(ft_isalpha(prompt_cmd[*index]) || prompt_cmd[*index] == '_')
	{
		tmp = get_var_name(prompt_cmd, index);
		var_content = search_in_env(tmp);
		free(tmp);
		return (check_valid_content(prompt_cmd, index, var_content, i));
	}
	return (NULL);
}

char	*check_exit_code(char *prompt_cmd, int *index)
{
	char	*tmp;
	char	*var_content;
	int		i;
	char	*tmp01;

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

char	*check_is_digit(char *prompt_cmd, int *index)
{
	char	*tmp;
	int		i;

	tmp = prompt_cmd;
	prompt_cmd[*index - 1] = 0;
	i = ft_strlen(tmp);
	prompt_cmd = ft_strjoin(prompt_cmd, prompt_cmd + (*index) + 1);
	free(tmp);
	*index = i;
	return (prompt_cmd);
}

char	*check_is_quote(char *prompt_cmd, int *index)
{
	char	*tmp;
	int		i;

	tmp = prompt_cmd;
	prompt_cmd[*index - 1] = 0;
	i = ft_strlen(&prompt_cmd[*index - 1]);
	prompt_cmd = ft_strjoin(prompt_cmd, prompt_cmd + *index);
	free(tmp);
	*index = i;
	return (prompt_cmd);
}