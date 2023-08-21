/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:07:30 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/25 16:07:31 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dir_check(char *file)
{
	int		fd;
	char	buf[1];

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(-1);
	if (read(fd, buf, 1) == -1)
	{
		close(fd);
		perror("dir check");
		exit(-1);
	}
	close(fd);
}
