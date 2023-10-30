/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:29:47 by djames            #+#    #+#             */
/*   Updated: 2023/10/30 10:48:01 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
# include <stdio.h>
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
    struct timeval	start, end;
    double 			elapsed;
	t_data			*data;
	
	data = (t_data *)param;
	

	gettimeofday(&start, NULL);  // Start time
	render_frame(data);
	gettimeofday(&end, NULL);    // End time

	elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
	printf("Frame took %f seconds to render\n", elapsed);
	
}
