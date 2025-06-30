/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:26:23 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 20:02:05 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_key_code(int key)
{
	ft_printf("Touche pressee: %d\n", key);
	if (key == KEY_ESC || key == KEY_ESC_ALT)
		ft_printf("-> ESC detecte\n");
	else if (key == 61 || key == 43)
		ft_printf("-> PLUS detecte\n");
	else if (key == 45 || key == 95)
		ft_printf("-> MINUS detecte\n");
	else if (key >= 65361 && key <= 65364)
		ft_printf("-> FLECHE detectee\n");
	else if (key == 119 || key == 115 || key == 97 || key == 100)
		ft_printf("-> WASD detecte\n");
	else if (key == 120)
		ft_printf("-> X detecte\n");
	else if (key == 32)
		ft_printf("-> ESPACE detecte\n");
	else if (key == 114)
		ft_printf("-> R detecte\n");
}

int	handle_key_debug(int key, t_fdf *fdf)
{
	print_key_code(key);
	return (handle_key(key, fdf));
}

void	print_controls_in_terminal(void)
{
	ft_printf("\n=== CONTROLES FDF ===\n");
	ft_printf("ESC        : Quitter\n");
	ft_printf("+ ou =     : Zoom avant\n");
	ft_printf("- ou _     : Zoom arriere\n");
	ft_printf("Fleches    : Deplacer\n");
	ft_printf("W/A/S/D    : Deplacer (alternatif)\n");
	ft_printf("X          : Rotation\n");
	ft_printf("R          : Rafraichir\n");
	ft_printf("ESPACE     : Reset vue\n");
	ft_printf("=====================\n\n");
}

void	activate_debug_mode(t_fdf *fdf)
{
	ft_printf("Mode debug active - codes de touches affiches\n");
	print_controls_in_terminal();
	mlx_hook(fdf->win, 2, 1L << 0, handle_key_debug, fdf);
}

int	should_use_debug_mode(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "--debug", 7) == 0
			|| ft_strncmp(argv[i], "-d", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}
