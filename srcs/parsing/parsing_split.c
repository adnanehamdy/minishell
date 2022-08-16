/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 09:25:47 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/14 09:28:03 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	arr_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '"' || s[i] == '\'')
				i = i + check_second_quote((char *)&s[i], s[i]);
			i++;
		}
	count++;
	}
	return (count);
}

static int	ft_free(char **split, size_t j)
{
	if (split[j])
		return (0);
	while (j--)
		free(split[j]);
	free(split);
	split = 0;
	return (1);
}

void	sub_count_char(const char *s, size_t *count, size_t *i, char c)
{
	while (s[*i + *count] && s[*i + *count] != c)
	{
		if (s[*i + *count] == '"' || s[*i + *count] == '\'')
			*count = *count + check_second_quote((char *)&s[*i + *count],
					s[*i + *count]);
		(*count)++;
	}
}

static void	count_char(const char *s, char c, char	**split)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	j = 0;
	i = 0;
	while (s[i])
	{
		count = 0;
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		sub_count_char(s, &count, &i, c);
		split[j] = ft_substr(s, i, count);
		if (ft_free(split, j))
			return ;
		i += count;
		j++;
	}
	split[j] = 0;
}

char	**parsing_split(char const *s, char c)
{
	char	**split;
	size_t	count;

	if (!s)
		return (NULL);
	count = arr_count(s, c);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	count_char(s, c, split);
	if (!split)
		return (0);
	return (split);
}
