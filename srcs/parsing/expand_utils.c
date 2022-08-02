/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:19:32 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/02 18:43:42 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_var_cmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i]
		&& (unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i + 1] && s1[i + 1] != '=')
		i++;
	if (ft_strlen(s2) != i + 1)
		return (1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] || ft_isdigit(var[i]) || ft_isalpha(var[i]) || var[i] == '_')
		i++;
	return (i);
}

char	*check_is_io_alpha(char *prompt_cmd, int *index)
{
	int		i;
	char	*tmp;
	char	*var_content;

	i = *index - 1;
	if (ft_isalpha(prompt_cmd[*index]) || prompt_cmd[*index] == '_')
	{
		tmp = get_var_name(prompt_cmd, index);
		var_content = search_in_env(tmp);
		free(tmp);
		return (check_io_valid_content(prompt_cmd, index, var_content, i));
	}
	return (NULL);
}

char	*check_env(char *prompt_cmd, int *index, int is_redirection)
{
	char	*tmp;
	int		i;

	i = 0;
	*index = *index + 1;
	if (is_redirection)
		tmp = check_is_io_alpha(prompt_cmd, index);
	else
		tmp = check_is_alpha(prompt_cmd, index);
	if (tmp)
		return (tmp);
	else if (ft_isdigit(prompt_cmd[*index]))
		return (check_is_digit(prompt_cmd, index));
	else if (prompt_cmd[*index] == '?')
		return (check_exit_code(prompt_cmd, index));
	else if ((prompt_cmd[*index] == '\'' || prompt_cmd[*index] == '"')
		&& prompt_cmd[*index + 1] != prompt_cmd[*index])
		return (check_is_quote(prompt_cmd, index));
	else
		*index = *index + 1;
	return (prompt_cmd);
}

char	*check_io_valid_content(char *cmd, int *index, char *var_content, int i)
{
	if (!var_content)
		return (cmd);
	else
		return (valid_content(cmd, index, var_content, i));
	return (NULL);
}
