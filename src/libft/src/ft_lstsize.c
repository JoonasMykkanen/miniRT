/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:08:09 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:09:12 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*curr;

	len = 1;
	curr = lst;
	if (lst)
	{
		while (curr->next != NULL)
		{
			curr = curr->next;
			len++;
		}
		return (len);
	}
	return (0);
}
