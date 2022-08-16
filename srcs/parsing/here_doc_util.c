/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:39:55 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/16 20:33:26 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	there_is_quote(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && (cmd[i] < 9 || cmd[i] > 13)
		&& cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>')
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

int	limiter_len(char *cmd)
{
	int		index;
	char	quote;
	int		quote_number;

	quote_number = 0;
	index = 0;
	while (cmd[index] && (cmd[index] < 9 || cmd[index] > 13)
		&& cmd[index] != ' ' && cmd[index] != '<' && cmd[index] != '>')
	{
		if (cmd[index] == '"' || cmd[index] == '\'')
		{
			quote = cmd[index];
			index++;
			while (cmd[index] != quote)
				index++;
			quote_number += 2;
		}
		index++;
	}
	index -= quote_number;
	return (index);
}

void	store_limiter(char *cmd, char *limiter_name, int len)
{
	int		i;
	int		index;
	char	quote;

	i = 0;
	index = 0;
	while (i < len && cmd[index])
	{
		if (cmd[index] == '"' || cmd[index] == '\'')
		{
			quote = cmd[index];
			index++;
			while (cmd[index] != quote)
			{
				limiter_name[i] = cmd[index];
				i++;
				index++;
			}
			index++;
		}
		limiter_name[i++] = cmd[index++];
	}
	limiter_name[i] = 0;
}

char	*get_limiter(char *cmd, int *mod)
{
	int		index;
	int		len;
	char	*limiter_name;
	int		i;

	i = 0;
	index = 0;
	*mod = there_is_quote(cmd);
	len = limiter_len(cmd);
	limiter_name = (char *)malloc(sizeof(char) * (len + 1));
	store_limiter(cmd, limiter_name, len);
	return (limiter_name);
}

int	get_last_heredoc(char *cmd)
{
	int	index;
	int	fd;
	int	*last_io;

	fd = 0;
	index = 0;
	last_io = check_last_io(cmd, 0);
	if (!last_io[0])
	{
		free(last_io);
		return (STANDARD_INPUT);
	}
	find_here_docs(cmd, &fd, last_io[1]);
	if (last_io[1] != HERE_DOC && fd != PIPE_FAIL)
		fd = STANDARD_INPUT;
	free(last_io);
	return (fd);
}
