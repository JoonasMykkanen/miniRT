/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:29:47 by djames            #+#    #+#             */
/*   Updated: 2023/10/26 12:07:56 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

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
	pthread_mutex_lock(&data->pool.queue);
	reset_job_list(data->pool.job_list);
	pthread_mutex_unlock(&data->pool.queue);
	pthread_cond_broadcast(&data->pool.cond);
}

void	render(void *param)
{
    double 		cpu_time_used;
	clock_t		start;
	clock_t		end;
	t_data		*data;
	
	data = (t_data *)param;
	start = clock();

	render_frame(data);
	
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("frame took %f seconds render\n", cpu_time_used);
}
