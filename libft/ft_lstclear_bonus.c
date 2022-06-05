/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:41:59 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/08 20:42:02 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = *lst;
	if (!*lst || !del)
		return ;
	while (ptr)
	{
		ptr2 = ptr->next;
		ft_lstdelone(ptr, del);
		ptr = ptr2;
	}
	*lst = 0;
}
