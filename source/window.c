/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:24:55 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/15 18:34:16 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx_data	*make_window(void)
{
	t_mlx_data	*data;

	data = malloc(sizeof(t_mlx_data));
	data->image = malloc(sizeof(t_image));
	data->mlx_connection = mlx_init();
	if (!data->mlx_connection)
		exit_malloc();
	data->mlx_window = mlx_new_window(data->mlx_connection, WIDTH, HEIGHT,
			"fdf");
	if (!data->mlx_window)
	{
		free(data->image);
		free(data);
		window_error();
		mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
		mlx_destroy_window(data->mlx_connection, data->mlx_window);
		exit(1);
	}
	return (data);
}

int	closed_window(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
	mlx_destroy_window(data->mlx_connection, data->mlx_window);
	free(data->point);
	free(data->mlx_connection);
	free(data->image);
	free(data);
	write(1, "The window got closed\n", 22);
	exit(1);
	return (0);
}
