/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:46:22 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/06 17:29:10 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	pwd_command(void)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, STANDARD_OUTPUT);
	free(pwd);
}

// int main(void)
// {
// 	pwd_command();
// 	return (0);
// }