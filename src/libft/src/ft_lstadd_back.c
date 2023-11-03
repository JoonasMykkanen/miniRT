/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:07:29 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:08:57 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	if (new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			curr = *lst;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			curr->next = new;
		}
	}
}
