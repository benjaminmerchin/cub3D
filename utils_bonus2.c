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

int		is_in(char c, char *str)
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

int		ft_strncmp_loc(const char *s1, const char *s2, int n)
{
	int i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i + 1 < n)
		i++;
	return (s1[i] - s2[i]);
}

void	victory_exit_check(t_data *data)
{
	if (BONUS && (int)data->x_pos == 1 && (int)data->y_pos == 3
	&& ft_strncmp_loc(data->av, "mapbonus_lvl0.cub", 18) == 0)
		data->victory = 1;
	if (data->escape == 1 || data->victory == 1)
		exit_free(data);
}

void	attack_if_possible(t_data *data)
{
	if (!BONUS)
		return ;
	//printf("%f\n",data->sprite[data->sprite_num - 1][3]);
	//printf("%d\n",data->crew);
	if (data->attack == 300)
	{
		if (there is a crewmate in a radius of 1)
		{
			remove 1 from list;
			data->crew--;
		}
		else
			data->attack = 0;
		printf("Kill confirmed, %d crew members left\n", data->crew);
	}
	if (data->attack > 0)
		data->attack--;
}
