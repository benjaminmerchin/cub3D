/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:45:12 by bmerchin          #+#    #+#             */
/*   Updated: 2021/02/24 15:45:13 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_in(char c, char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

void	victory_exit_check(t_data *data)
{
	if (BONUS && (int)data->x_pos == 1 && (int)data->y_pos == 3)
		data->victory = 1;
	if (data->escape == 1 || data->victory == 1)
		exit_free(data);
}
