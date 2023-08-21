/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:21:39 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/29 19:21:40 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_p(va_list *args, int count)
{
	void	*ptr;
	int		len;

	ptr = va_arg(*args, void *);
	ft_putstr_fd("0x", 1);
	len = ft_hexlen((unsigned long long)ptr);
	ft_puthex_lower_fd((unsigned long long)ptr, 1);
	count = count + len + 2;
	return (count);
}
