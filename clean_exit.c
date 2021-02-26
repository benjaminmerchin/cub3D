/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:06:22 by bmerchin          #+#    #+#             */
/*   Updated: 2021/02/23 17:07:10 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		clean_exit(int keycode, t_data *data)
{
	(void)data;
	(void)keycode;
	write(1, "o", 1);
	if (keycode == KEY_ESCAPE)
		data->exit = 1;
	return (0);
}

#ifdef __LINUX__

void	exit_free(t_data *data)
{
	if (BONUS)
		echo_the_end(data);	
	free_struct(&data, 1);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(0);
}

#else

void	exit_free(t_data *data)
{
	if (BONUS)
		echo_the_end(data);
	echo_the_end(data); ////////////RETIRER
	//write(1, "WWW", 3);
	free_struct(data, 1);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(0);
}

#endif
