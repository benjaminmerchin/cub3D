/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:03:33 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/12 16:04:35 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int security_check(t_data *data)
{
	if (data->security[8] != 1)
	{
		ft_putstr_bn("Error\nThere is not the correct amount of starting directions");
		return (1);
	}
	if (data->security[9] != 0)
	{
		ft_putstr_bn("Error\nThere is at least one missing wall on the map");
		return (1);
	}
	if (data->security[10] != 0)
	{
		ft_putstr_bn("Error\nThere is an invalid character on the map");
		return (1);
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i + 1 < n)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int security_cub(int ac, char **av, t_data *data, int fd)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(av[1]);
	data->save = 0;
	while (i < 20)
		data->security[i++] = 0;
	if (ac != 2)
	{
		if (ft_strncmp(av[2], "--save", 10) == 0)
			data->save = 1;
		else
		{
			ft_putstr_bn("Error\nWrong number of arguments");
			return (1);
		}
	}
	if (av[1][len - 1] != 'b' || av[1][len - 2] != 'u'||
			av[1][len - 3] != 'c' || av[1][len - 4] != '.')
	{
		ft_putstr_bn("Error\nYour map fomat must be .cub");
		return (1);
	}
	if (fd < 0)
	{
		ft_putstr_bn("Error\nOpen Folder");
		return (1);
	}
	return (0);
}

int security_data(t_data *data)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (data->security[i] == 0)
		{
			ft_putstr_bn("Error\nData Missing in .cub");
			printf("The security issue %d was trigerred\n", i);
			return (1);
		}
		if (data->security[i] > 1)
		{
			ft_putstr_bn("Error\nData Provided Multiple Times in .cub");
			printf("The security issue %d was trigerred\n", i);
			return (1);
		}
		i++;
	}
	if (data->x_screen_size > 10000 || data->y_screen_size > 10000)
	{
		ft_putstr_bn("Error\nYour Map resolution is too big");
		return (1);
	}
	return (0);
}
