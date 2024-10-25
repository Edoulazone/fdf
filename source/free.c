/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:09:45 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/10 18:49:02 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab(char **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}

void	free_tab_error(t_point **array, int i)
{
	while (i >= 0)
		free(array[i--]);
	free(array);
	exit(1);
}

void	free_points_tab(t_point **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}
