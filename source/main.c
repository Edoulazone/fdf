/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:32:24 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/17 15:11:15 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_mlx_data	*data;
	t_point		*points;

	if (argc == 2)
	{
		points = parsing(argv);
		data = make_window();
		data->point = points;
		data->argv = argv;
		data->width = count_columns(argv[1]);
		data->height = count_lines(argv[1]);
		if (data->width <= 1 && data->height <= 1)
			bad_file(data);
		projection(points, data);
		draw(data, points);
		mlx_hook(data->mlx_window, 17, 0, &closed_window, data);
		mlx_key_hook(data->mlx_window, &key_handle, data);
		mlx_loop(data->mlx_connection);
	}
	else
		ft_putendl("Usage: ./fdf <map_file>");
	return (0);
}
