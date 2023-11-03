/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:57:14 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:08:37 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	len;
	void	*ptr;

	if (count == 0 || size == 0)
		return (calloc (1, 1));
	len = count * size;
	if (len / size != count)
		return (NULL);
	ptr = malloc(len);
	if (ptr)
	{
		ft_bzero(ptr, len);
		return (ptr);
	}
	return (NULL);
}
