/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:45:13 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/17 15:40:05 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

# define WIDTH 2560
# define HEIGHT 1400

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum
{
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	MOUSE_WHEEL_DOWN = 4,
	MOUSE_WHEEL_UP = 5,
	MOUSE_WHEEL_RIGHT = 6,
	MOUSE_WHEEL_LEFT = 7
};

enum
{
	KEY_A = 0,
	KEY_B = 11,
	KEY_C = 8,
	KEY_D = 2,
	KEY_E = 14,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_M = 46,
	KEY_N = 45,
	KEY_O = 31,
	KEY_P = 35,
	KEY_Q = 12,
	KEY_R = 15,
	KEY_S = 1,
	KEY_T = 17,
	KEY_U = 32,
	KEY_V = 9,
	KEY_W = 13,
	KEY_X = 7,
	KEY_Y = 16,
	KEY_Z = 6,
	KEY_ESC = 53,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_UP = 125,
	KEY_RIGHT = 124,
	KEY_DOWN = 126,
	KEY_LEFT = 123,
	KEY_0 = 82,
	KEY_1 = 83,
	KEY_2 = 84,
	KEY_3 = 85,
	KEY_4 = 86,
	KEY_5 = 87,
	KEY_6 = 88,
	KEY_7 = 89,
	KEY_8 = 91,
	KEY_9 = 92,
	KEY_PLUS_PAD = 69,
	KEY_MINUS_PAD = 78
};

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	colour;
	float	projected_x;
	float	projected_y;
	int		height;
	int		width;
}			t_point;

typedef struct s_image
{
	void	*image_ptr;
	char	*image_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		size_line;
}			t_image;

typedef struct s_mlx_data
{
	void	*mlx_connection;
	void	*mlx_window;
	int		width;
	int		height;
	char	**argv;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		error;
	int		error2;
	float	translated_x;
	float	translated_y;
	float	rotated_x;
	float	rotated_y;
	t_image	*image;
	t_point	*point;
}			t_mlx_data;

int			main(int ac, char **av);

void		draw(t_mlx_data *data, t_point *points);

void		free_points_tab(t_point **array);
void		free_tab_error(t_point **array, int i);
void		free_tab(char **array);

int			count_columns(char *file_name);
int			count_lines(char *file_name);
int			count_number(char **array);

void		exit_error(void);
void		exit_malloc(void);
void		window_error(void);
int			bad_file(t_mlx_data *data);

t_point		*parsing(char **argv);

void		projection(t_point *points, t_mlx_data *data);

t_mlx_data	*make_window(void);
int			closed_window(t_mlx_data *data);

int			key_handle(int key, t_mlx_data *data);
void		translate_down(t_point *points, t_mlx_data *data);
void		translate_up(t_point *points, t_mlx_data *data);
void		translate_left(t_point *points, t_mlx_data *data);
void		translate_right(t_point *points, t_mlx_data *data);
void		rotation_x(t_point *points, t_mlx_data *data);

#endif