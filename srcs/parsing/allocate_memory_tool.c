/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_memory_tool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:20:41 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/16 08:46:11 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<minishell.h>

t_cmd_line	**initialize_cmd_line(char *prompt_cmd, int cmd_number)
{
	t_cmd_line	**cmd;
	int			i;
	char		**cmd_after_split;

	count_each_arg(NULL, 1);
	fill_each_arg(NULL, NULL, 1);
	cmd_after_split = parsing_split(prompt_cmd, '|');
	cmd = (t_cmd_line **)malloc(sizeof(t_cmd_line *) * (cmd_number + 1));
	i = 0;
	while (i < cmd_number)
		cmd[i++] = (t_cmd_line *)malloc(sizeof(t_cmd_line));
	here_doc_handler(cmd_after_split, cmd);
	i = 0;
	cmd_line_handler(cmd, cmd_after_split, cmd_number);
	redirections_handler(cmd_after_split, cmd);
	free_cmd_args(cmd_after_split);
	return (cmd);
}

void	max_here_doc(int here_doc_number, char **cmd_after_split)
{
	if (here_doc_number > 16)
	{
		ft_fprintf(2, "maximum here_document count exceeded\n");
		free_cmd_args(cmd_after_split);
		exit(2);
	}
}

void	check_max_here_doc(char *prompt_cmd)
{
	char	**cmd_after_split;
	int		i;
	int		here_doc_number;
	int		j;

	j = 0;
	i = 0;
	here_doc_number = 0;
	cmd_after_split = parsing_split(prompt_cmd, '|');
	while (cmd_after_split[i])
	{
		j = 0;
		while (cmd_after_split[i][j])
		{
			if (cmd_after_split[i][j] == '<' && cmd_after_split[i][j] == '<')
				here_doc_number++;
			j++;
		}
		i++;
	}
	max_here_doc(here_doc_number, cmd_after_split);
	free_cmd_args(cmd_after_split);
}

int	skip_here_doc(char **prompt_cmd, int *index, char last_char)
{
	if ((*prompt_cmd)[*index] == '<'
		&& (*prompt_cmd)[*index] == (*prompt_cmd)[*index + 1]
			&& last_char != '"' && last_char != '\'')
	{
		*index += 2;
		*index = *index + skip_io_redirection(*prompt_cmd + *index);
		return (1);
	}
	return (0);
}
