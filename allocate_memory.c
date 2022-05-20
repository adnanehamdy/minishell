/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 08:04:54 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/20 07:47:14 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int skip_io_redirection(char *sub_prompt_cmd)
{
	int	index;

	index = 0;
	while (sub_prompt_cmd[index] && sub_prompt_cmd[index] != '|')
	{
		if ((sub_prompt_cmd[index] >= 9 && sub_prompt_cmd[index] <= 13) || sub_prompt_cmd[index] == ' ' || sub_prompt_cmd[index] == '<' || sub_prompt_cmd[index] == '>')
			break ;
		if (sub_prompt_cmd[index] == '"')
			index = index + check_second_quote(&sub_prompt_cmd[index], '"');
		else if (sub_prompt_cmd[index] == '\'')
			index = index + check_second_quote(&sub_prompt_cmd[index], '\'');
		index++;
	}
	return (index);
}

int	count_io_redirection(char *prompt_cmd)
{
	int	index;
	int	number;

	index = 0;
	number = 0;
	while (prompt_cmd[index] && prompt_cmd[index] != '|')
	{
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>')
		{
			if (prompt_cmd[index + 1] == prompt_cmd[index])
				index = index + 1;
			number++;
		}
		index++;
	}
	return (number);
}

int	count_arg_number(char *prompt_cmd)
{
	int	index;
	int	number;

	number = 0;
	index = 0;
	while (prompt_cmd[index] && prompt_cmd[index] != '|')
	{
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>')
		{
			if (prompt_cmd[index + 1] == prompt_cmd[index])
				index = index + 1;
			index++;
			if ((prompt_cmd[index] >= 9 && prompt_cmd[index] <= 13) || prompt_cmd[index] == ' ')
				index = index + skip_white_spaces(&prompt_cmd[index],0);
			index = index + skip_io_redirection(&prompt_cmd[index]);
		}
		else if ((prompt_cmd[index] < 9 || prompt_cmd[index] > 13) && prompt_cmd[index] != ' ' && prompt_cmd[index] != '<' && prompt_cmd[index] != '>')
		{
			while (prompt_cmd[index] && ((prompt_cmd[index] < 9 && prompt_cmd[index] > 13) || prompt_cmd[index] != ' ') && prompt_cmd[index] != '<' && prompt_cmd[index] != '>')
			{
				if (prompt_cmd[index] == '"')
					index = index + check_second_quote(&prompt_cmd[index], '"');
				else if (prompt_cmd[index] == '\'')
					index = index + check_second_quote(&prompt_cmd[index], '\'');
				index++;
			}
			number++;
		}
		else
			index++;
	}
	return (number);
}

int	count_each_arg(char *prompt_cmd)
{
	int	index;
	int	number;
	int	tmp;

	tmp = 0;
	number = 0;
	index = 0;
	while (prompt_cmd[index] && prompt_cmd[index] != '|')
	{
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>')
		{
			if (prompt_cmd[index + 1] == prompt_cmd[index])
				index = index + 1;
			index++;
			if ((prompt_cmd[index] >= 9 && prompt_cmd[index] <= 13) || prompt_cmd[index] == ' ')
				index = index + skip_white_spaces(&prompt_cmd[index],0);
			index = index + skip_io_redirection(&prompt_cmd[index]);
		}
		else if ((prompt_cmd[index] < 9 || prompt_cmd[index] > 13) && prompt_cmd[index] != ' ' && prompt_cmd[index] != '<' && prompt_cmd[index] != '>')
		{
			while (prompt_cmd[index] && ((prompt_cmd[index] < 9 && prompt_cmd[index] > 13) || prompt_cmd[index] != ' ') && prompt_cmd[index] != '<' && prompt_cmd[index] != '>')
			{
				if (prompt_cmd[index] == '"')
				{
					tmp = index;
					index = index + check_second_quote(&prompt_cmd[index], '"');
					number = number + (index - tmp - 1);
				}
				else if (prompt_cmd[index] == '\'')
				{
					tmp = index;
					index = index + check_second_quote(&prompt_cmd[index], '\'');
					number = number + (index - tmp - 1);
				}
				else
					number++;
				index++;
			}
		}
		else
			index++;
	}
	return (number);
}

char	*fill_each_arg(char *cmd_arg, char *prompt_cmd)
{
	int	index;
	int	number;
	int	count;

	count = 0;
	number = 0;
	index = 0;
	while (prompt_cmd[index] && prompt_cmd[index] != '|')
	{
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>')
		{
			if (prompt_cmd[index + 1] == prompt_cmd[index])
				index = index + 1;
			index++;
			if ((prompt_cmd[index] >= 9 && prompt_cmd[index] <= 13) || prompt_cmd[index] == ' ')
				index = index + skip_white_spaces(&prompt_cmd[index],0);
			index = index + skip_io_redirection(&prompt_cmd[index]);
		}
		else if ((prompt_cmd[index] < 9 || prompt_cmd[index] > 13) && prompt_cmd[index] != ' ' && prompt_cmd[index] != '<' && prompt_cmd[index] != '>')
		{
			while (prompt_cmd[index] && ((prompt_cmd[index] < 9 && prompt_cmd[index] > 13) || prompt_cmd[index] != ' ') && prompt_cmd[index] != '<' && prompt_cmd[index] != '>')
			{
				if (prompt_cmd[index] == '"' || prompt_cmd[index] == '\'')
					index++;
				cmd_arg[count] = prompt_cmd[index];
				count++;
			}
		}
		else
			index++;
	}
	return (cmd_arg);
}

char **allocate_cmd_arguments(char *prompt_cmd, int cmd_number, t_cmd_line *cmd)
{
	int	number_of_arg;
	int	number_of_io_redirection;
	char	**cmd_arg;
	int		i;

	i = 0;
	cmd_arg = (char **)malloc(count_arg_number(prompt_cmd));
	while (i < number_of_arg)
	{
		cmd_arg = (char *)malloc(count_each_arg(prompt_cmd));
		cmd_arg[i] = fill_each_arg(cmd_arg[i], prompt_cmd);
		printf("cmd[%d] = '%s'\n");
		i++;
	}
}

t_cmd_line *initialize_cmd_line(char *prompt_cmd, int cmd_number)
{
	t_cmd_line	*cmd;

	cmd = (t_cmd_line *)malloc(sizeof(t_cmd_line) * cmd_number);
	cmd->command = allocate_cmd_arguments(prompt_cmd, cmd_number, cmd);
}