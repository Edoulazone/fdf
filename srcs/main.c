/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:35:51 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 17:52:50 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_usage(void)
{
	ft_putendl("Usage: ./fdf <map_file>");
	ft_putendl("");
	ft_putendl("🎮 CONTROLES:");
	ft_putendl("  ESC           - Quitter");
	ft_putendl("  + ou =        - Zoom avant");
	ft_putendl("  - ou _        - Zoom arriere");
	ft_putendl("  ↑ ou W        - Monter");
	ft_putendl("  ↓ ou S        - Descendre");
	ft_putendl("  ← ou A        - Gauche");
	ft_putendl("  → ou D        - Droite");
	ft_putendl("  X             - Rotation (9 degres)");
	ft_putendl("  Z             - Reset rotation seulement");
	ft_putendl("  R             - Rafraichir");
	ft_putendl("  ESPACE        - Reset vue");
	ft_putendl("");
	ft_putendl("💡 CONSEILS:");
	ft_putendl("  - Regardez le terminal pour les confirmations");
	ft_putendl("  - X fait une rotation de 9 degrés par pression");
	ft_putendl("  - ESPACE pour remettre à zero si vous vous perdez");
}

int	check_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".fdf", 4) == 0)
		return (1);
	return (0);
}

int	check_access(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		exit_error("Cannot open file\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	validate_file(char *filename)
{
	if (!check_extension(filename))
	{
		exit_error("File must have .fdf extension\n");
		return (0);
	}
	if (!check_access(filename))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc < 2 || argc > 3)
	{
		print_usage();
		return (1);
	}
	if (!validate_file(argv[1]))
		return (1);
	if (init_fdf(&fdf, argv[1]) < 0)
	{
		cleanup_fdf(&fdf);
		return (1);
	}
	render_map(&fdf);
	printf("\n=== FDF ===\n");
	printf("Carte: %s\n", argv[1]);
	printf("Taille: %dx%d points\n", fdf.map.width, fdf.map.height);
	printf("Zoom initial: %.2f\n", fdf.zoom);
	printf("Appuyez sur les touches pour controler!\n");
	printf("ESC pour quitter\n\n");
	mlx_hook(fdf.win, 2, 1L << 0, handle_key, &fdf);
	mlx_hook(fdf.win, 17, 1L << 17, handle_close, &fdf);
	mlx_loop(fdf.mlx);
	cleanup_fdf(&fdf);
	return (0);
}
