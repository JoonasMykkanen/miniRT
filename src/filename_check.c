/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:08:09 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/31 15:08:20 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[len - 1] != 't')
		return (ERROR);
	if (file[len - 2] != 'r')
		return (ERROR);
	if (file[len - 3] != '.')
		return (ERROR);
	return (OK);
}