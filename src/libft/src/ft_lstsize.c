/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:08:09 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/08 11:08:13 by jmykkane         ###   ########.fr       */
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
