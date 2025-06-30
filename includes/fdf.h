/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:35:37 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 18:00:28 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include "../minilibx-linux/mlx.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define BUFFER_SIZE 42
# define DEFAULT_COLOR 0xFF6B6B
# define BG_COLOR 0x000000
# define BG_COLOR_ALT 0x111111

# define KEY_ESC 65307
# define KEY_ESC_ALT 53
# define KEY_PLUS 65451
# define KEY_PLUS_ALT 43
# define KEY_MINUS 65453
# define KEY_MINUS_ALT 45
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_A 97
# define KEY_S 115
# define KEY_W 119
# define KEY_D 100
# define KEY_X 120
# define KEY_Z 122
# define KEY_R 114
# define KEY_C 99
# define KEY_SPACE 32

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	proj_x;
	float	proj_y;
	int		color;
}	t_point;

typedef struct s_map
{
	t_point	*points;
	int		width;
	int		height;
	int		total;
}	t_map;

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	map;
	float	zoom;
	float	offset_x;
	float	offset_y;
	int		bg_color;
}	t_fdf;

/* parsing.c */
int		count_words(char *str, char delimiter);
int		atoi_hex(char *str);
int		get_dimensions(char *filename, int *width, int *height);
void	parse_line(char *line, t_point *points, int y, int width);
t_map	*parse_map(char *filename);

/* parsing_utils.c */
int		hex_to_int(char c);
int		extract_color(char *str);
void	fill_point(t_point *point, char *value, int x, int y);
void	free_split(char **split);
char	**allocate_split_array(int word_count);

/* split.c */
char	*skip_delimiters(char *str, char delimiter);
int		get_word_length(char *str, char delimiter);
char	*allocate_and_copy_word(char *str, int len);
int		fill_split_array(char **result, char *str, char delimiter, int count);
char	**split_line(char *str, char delimiter);

/* init.c */
float	calc_zoom(t_map *map);
int		init_mlx(t_fdf *fdf);
int		init_image(t_fdf *fdf);
void	cleanup_fdf(t_fdf *fdf);
int		init_fdf(t_fdf *fdf, char *filename);

/* rendering.c */
void	clear_image(t_fdf *fdf);
void	apply_projection(t_map *map, float zoom);
void	center_map(t_map *map, float ox, float oy);
void	draw_connections(t_fdf *fdf);
void	render_map(t_fdf *fdf);

/* draw.c */
int		in_bounds(int x, int y);
void	put_pixel(t_fdf *fdf, int x, int y, int color);
void	init_line(t_line *line, t_point p1, t_point p2);
void	draw_step(int *x, int *y, t_line *line);
void	draw_line(t_fdf *fdf, t_point p1, t_point p2, int color);

/* events.c */
void	zoom_map(t_fdf *fdf, float factor);
void	translate_map(t_fdf *fdf, float dx, float dy);
void	rotate_map(t_fdf *fdf);
int		handle_close(t_fdf *fdf);

/* events_2.c */
void	handle_zoom_keys(int key, t_fdf *fdf);
void	handle_movement_keys(int key, t_fdf *fdf);
void	reset_view(t_fdf *fdf);
void	handle_utility_keys(int key, t_fdf *fdf);
int		is_zoom_key(int key);
int		handle_key(int key, t_fdf *fdf);

/* get_next_line.c */
char	*gnl_read_buffer(int fd);
char	*gnl_join_free(char *s1, char *s2);
char	*gnl_extract_line(char **save);
char	*gnl_read_until_newline(int fd, char **save);
char	*get_next_line(int fd);

/* utils.c */
int		ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *str);
void	exit_error(char *msg);

/* utils_2.c */
char	*ft_strncpy_fdf(char *dst, const char *src, int n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putendl(char *str);
int		hex_char_to_int(char c);

/* utils_3.c */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memset(void *ptr, int value, size_t num);
int		is_in_bounds(int x, int y);
char	*ft_strcpy_fdf(char *dst, const char *src);

/* debug.c */
void	print_key_code(int key);
int		handle_key_debug(int key, t_fdf *fdf);
void	print_controls_in_terminal(void);
void	activate_debug_mode(t_fdf *fdf);
int		should_use_debug_mode(int argc, char **argv);

/* main.c */
void	print_usage(void);
int		check_extension(char *filename);
int		check_access(char *filename);
int		validate_file(char *filename);

#endif