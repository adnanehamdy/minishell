/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:54:57 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/22 11:30:28 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sub_expand(char **prompt_cmd, int *index, char *last_char)
{
	*last_char = (*prompt_cmd)[*index];
	if ((*prompt_cmd)[*index])
		(*index)++;
}

int	sub_expand_redirection(char **prompt_cmd, int *index,
		char last_char, int is_first)
{
	if (((*prompt_cmd)[*index]) == '$' && ((*prompt_cmd)[*index + 1]))
	{
		if ((last_char == '\'' || last_char == '"')
			&& (*prompt_cmd)[*index + 1] == last_char)
		{
			*index = *index + 1;
			return (1);
		}
		*prompt_cmd = check_env(*prompt_cmd, index, 1, is_first);
		if ((*prompt_cmd)[*index] == '<' || (*prompt_cmd)[*index] == '>')
		{
			*index = *index + skip_white_spaces(&(*prompt_cmd)[*index], 0);
			*index = *index + skip_io_redirection(&(*prompt_cmd)[*index]);
		}
		if (!(*prompt_cmd[0]))
			return (1);
	}
	return (0);
}

void	sub_open_outfile(int fd, char *filename, int true)
{
	if (fd == -1)
	{
		if (!access(filename, F_OK))
			ft_fprintf(STANDARD_ERROR,
				"minishell : permission denied : %s\n", filename);
		else if (true == 1)
			ft_fprintf(STANDARD_ERROR,
				"minishell : ambiguous redirect : %s\n", filename);
		else
			ft_fprintf(STANDARD_ERROR,
				"minishell : no such file or directory : %s\n", filename);
	}
}

int	sub_file_len(char *filename, int *index, int *number)
{
	int	tmp;

	tmp = 0;
	if (filename[*index] == '"')
	{
		tmp = *index;
		*index = *index + check_second_quote(&filename[*index], '"', 0);
		*number = *number + (*index - tmp - 1);
		return (0);
	}
	else if (filename[*index] == '\'')
	{
		tmp = *index;
		*index = *index + check_second_quote(&filename[*index], '\'', 0);
		*number = *number + (*index - tmp - 1);
		return (0);
	}
	return (1);
}

void	initialize_last_io(int *last_io)
{
	last_io[0] = 0;
	last_io[1] = 0;
}
