/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:34:04 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 17:53:52 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_zoom_keys(int key, t_fdf *fdf)
{
	if (key == KEY_PLUS || key == KEY_PLUS_ALT || key == 61)
		zoom_map(fdf, 1.1f);
	else if (key == KEY_MINUS || key == KEY_MINUS_ALT || key == 45)
		zoom_map(fdf, 1.0f / 1.1f);
}

void	handle_movement_keys(int key, t_fdf *fdf)
{
	if (key == KEY_LEFT || key == KEY_A)
		translate_map(fdf, -30, 0);
	else if (key == KEY_RIGHT || key == KEY_D)
		translate_map(fdf, 30, 0);
	else if (key == KEY_UP || key == KEY_W)
		translate_map(fdf, 0, -30);
	else if (key == KEY_DOWN || key == KEY_S)
		translate_map(fdf, 0, 30);
}

void	reset_view(t_fdf *fdf)
{
	fdf->zoom = calc_zoom(&fdf->map);
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	printf("🏠 Vue remise a zero (zoom: %.2f)\n", fdf->zoom);
	render_map(fdf);
}

void	handle_utility_keys(int key, t_fdf *fdf)
{
	if (key == KEY_R)
	{
		printf("🔄 Rafraichissement de l'affichage...\n");
		render_map(fdf);
	}
	else if (key == KEY_C)
	{
		if (fdf->bg_color == BG_COLOR)
			fdf->bg_color = BG_COLOR_ALT;
		else
			fdf->bg_color = BG_COLOR;
		printf("🎨 Couleur de fond changee (test rafraichissement)\n");
		render_map(fdf);
	}
	else if (key == KEY_SPACE)
		reset_view(fdf);
}

int	is_zoom_key(int key)
{
	if (key == KEY_PLUS || key == KEY_PLUS_ALT || key == 61)
		return (1);
	if (key == KEY_MINUS || key == KEY_MINUS_ALT || key == 45)
		return (1);
	return (0);
}

int	handle_key(int key, t_fdf *fdf)
{
	if (key == KEY_ESC || key == KEY_ESC_ALT)
	{
		printf("👋 Fermeture du programme...\n");
		handle_close(fdf);
	}
	else if (is_zoom_key(key))
		handle_zoom_keys(key, fdf);
	else if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || 
			 key == KEY_DOWN || key == KEY_A || key == KEY_S || 
			 key == KEY_W || key == KEY_D)
		handle_movement_keys(key, fdf);
	else if (key == KEY_X)
		rotate_map(fdf);
	else if (key == KEY_R || key == KEY_C || key == KEY_SPACE)
		handle_utility_keys(key, fdf);
	else
		printf("❓ Touche inconnue: %d\n", key);
	return (0);
}
