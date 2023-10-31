/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:29:47 by djames            #+#    #+#             */
/*   Updated: 2023/10/31 10:29:43 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include <stdio.h>
#include <sys/time.h>

void	ft_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		handle_exit(param);
	}
}

static void	render_frame(t_data *data)
{
	data->pool.ready = false;
	while (42)
	{
		if (data->pool.ready)
			break ;
		usleep(15);
	}
	pthread_mutex_lock(&data->pool.queue);
	reset_job_list(data->pool.job_list);
	pthread_mutex_unlock(&data->pool.queue);
	pthread_cond_broadcast(&data->pool.cond);
}

void	render(void *param)
{
	double			elapsed;
	t_data			*data;
	struct timeval	start;
	struct timeval	end;

	data = (t_data *)param;
	gettimeofday(&start, NULL);
	render_frame(data);
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)
		/ 1000000.0;
	printf("Frame took %f seconds to render\n", elapsed);
}
