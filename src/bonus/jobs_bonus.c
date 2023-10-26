/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:32:04 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/26 10:48:55 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

int	create_jobs(t_data *data)
{
	int	idx;

	idx = 0;
	data->pool.job_list = new_job(idx);
	if (!data->pool.job_list)
	{
		ft_putstr_fd("Error: Job list could not be created\n", 2);
		return (ERROR);
	}
	while (++idx < HEIGHT)
	{
		if (push_job_list(&data->pool.job_list, idx) != OK)
		{
			ft_putstr_fd("Error: Job list could not be created\n", 2);
			return (ERROR);
		}
	}
	return (OK);
}
