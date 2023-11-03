/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:27:47 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:09:00 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;

	if (lst)
	{
		curr = lst;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		return (curr);
	}
	return (NULL);
}
