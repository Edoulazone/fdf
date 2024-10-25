/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:35:28 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/17 15:14:04 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_error(void)
{
	perror("Error");
	exit(1);
}

void	exit_malloc(void)
{
	write(2, "Error while allocating memory\n", 30);
	exit(1);
}

void	window_error(void)
{
	write(2, "Error while crating a new window\n", 33);
}

int	bad_file(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_connection, data->mlx_window);
	free(data->point);
	free(data->mlx_connection);
	free(data->image);
	free(data);
	write(1, "Map has only one point or less\n", 31);
	exit(1);
	return (0);
}
