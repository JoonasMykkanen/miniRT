/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:16:02 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/26 10:45:20 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

void	handle_exit(void *param)
{
	t_data *data;
	
	data = (t_data *)param;
	kill_workers(data);
	free_job_list(data->pool.job_list);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	exit(0);
}
