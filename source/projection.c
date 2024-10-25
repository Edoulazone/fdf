/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:32:18 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/15 18:20:25 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	zoom_factor(t_mlx_data *data)
{
	float	zoom;

	if (data->height * data->width > 100000)
		zoom = 1.7;
	else if (data->height * data->width > 5000)
		zoom = 5;
	else if (data->height * data->width > 500)
		zoom = 7;
	else
		zoom = 20;
	return (zoom);
}

void	projection(t_point *points, t_mlx_data *data)
{
	int		i;
	float	zoom;

	i = -1;
	zoom = zoom_factor(data);
	while (points[++i].x != -1)
	{
		points[i].x *= zoom;
		points[i].y *= zoom;
		points[i].z *= zoom;
		points[i].projected_x = (points[i].x - points[i].y) * (sqrt(3) / 2);
		points[i].projected_y = ((points[i].x + points[i].y) / 2) - points[i].z;
		points[i].projected_x += WIDTH / 2;
		points[i].projected_y += HEIGHT / 2;
	}
}
