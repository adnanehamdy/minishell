/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 08:04:54 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/16 17:36:33 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_arg_number(char *prompt_cmd)
{
	int	index;
	int	number;

	index = 0;
	number = 0;
	while (prompt_cmd[index] && prompt_cmd[index] != '|')
	{
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>')
			skip_non_arg(&prompt_cmd[index], &index);
		else if ((prompt_cmd[index] < 9 || prompt_cmd[index] > 13) 
			&& prompt_cmd[index] != ' ' && prompt_cmd[index] != '<'
			&& prompt_cmd[index] != '>' && prompt_cmd[index] != '|')
		{
			sub_count_arg_number(prompt_cmd, &index);
			number++;
		}
		else
			index++;
	}
	return (number);
}

int	count_each_arg(char *prompt_cmd, int reset)
{
	static int	index;
	int			number;

	number = 0;
	if (reset)
	{
		reset_var(&index);
		return (0);
	}
	while (prompt_cmd[index] && prompt_cmd[index] != '|')
	{
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>')
			skip_non_arg(prompt_cmd, &index);
		else if ((prompt_cmd[index] < 9 || prompt_cmd[index] > 13)
			&& prompt_cmd[index] != ' ' && prompt_cmd[index] != '<'
			&& prompt_cmd[index] != '>' && prompt_cmd[index] != '|')
			{
				number = sub_count_each_arg(prompt_cmd, &index, &number);
				break;
			}
		else
			index++;
	}
	return (number);
}

char	*fill_each_arg(char *cmd_arg, char *prompt_cmd, int reset)
{
	static int	index;

	if (reset)
		return (reset_var(&index));
	while (prompt_cmd[index] && prompt_cmd[index] != '|')
	{
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>')
		{
			if (prompt_cmd[index + 1] == prompt_cmd[index])
				index = index + 1;
			index++;
			if ((prompt_cmd[index] >= 9 && prompt_cmd[index] <= 13)
				|| prompt_cmd[index] == ' ')
				index = index + skip_white_spaces(&prompt_cmd[index], 0);
			index = index + skip_io_redirection(&prompt_cmd[index]);
		}
		else if ((prompt_cmd[index] < 9 || prompt_cmd[index] > 13)
			&& prompt_cmd[index] != ' '
			&& prompt_cmd[index] != '<' && prompt_cmd[index] != '>'
			&& prompt_cmd[index] != '|')
			return (sub_fill_each_arg(cmd_arg, prompt_cmd, &index));
		else
			index++;
	}
	return (cmd_arg);
}

char	**allocate_cmd_arguments(char *prompt_cmd)
{
	int		number_of_arg;
	char	**cmd_arg;
	int		i;

	i = 0;
	number_of_arg = count_arg_number(prompt_cmd);
	cmd_arg = (char **)malloc(sizeof(char *) * (number_of_arg + 1));
	while (i < number_of_arg)
	{
		cmd_arg[i] = (char *)malloc(sizeof(char)
				* (count_each_arg(prompt_cmd, 0) + 1));
		cmd_arg[i] = fill_each_arg(cmd_arg[i], prompt_cmd, 0);
		i++;
	}
	// cmd_arg[i] = (char *)malloc(1);
	cmd_arg[i] = 0;
	return (cmd_arg);
}

t_cmd_line	**initialize_cmd_line(char *prompt_cmd, int cmd_number)
{
	t_cmd_line	**cmd;
	int			i;
	char		**cmd_after_split;

	count_each_arg(NULL, 1);
	fill_each_arg(NULL, NULL, 1);
	cmd_after_split = parsing_split(prompt_cmd, '|');
	cmd = (t_cmd_line **)malloc(sizeof(t_cmd_line*) * (cmd_number + 1));
	i = 0;
	while (i < cmd_number)
		cmd[i++] = (t_cmd_line *)malloc(sizeof(t_cmd_line));
	here_doc_handler(cmd_after_split, cmd);
	i = 0;
	while (i < cmd_number)
	{
		cmd[i]->command = allocate_cmd_arguments(cmd_after_split[i]);
		cmd[i]->is_executable = 0;
		if (cmd[i]->command)
			cmd[i]->cmd_path = allocate_cmd_path(cmd[i], envp_handler(GETENV, NULL), cmd[i]->command[0]);
		count_each_arg(NULL, 1);
		fill_each_arg(NULL, NULL, 1);
		i++;
	}
	cmd[i] = 0;
	open_io_redirections(cmd_after_split, cmd);
	/* ------> cmd_after_split should be freed */
	return (cmd);
}
