/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_d_i_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:22:06 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/29 19:22:07 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_d_i(va_list *args, int count)
{
	char	*str;
	int		num;
	int		len;

	num = va_arg(*args, int);
	str = ft_itoa(num);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (count + len);
}
