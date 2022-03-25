/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:24:48 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/25 13:22:22 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_strdel(*(array[i]));
		i++;
	}
}

char	**create_char_array(t_info *info)
{
	char	**array;
	int		i;

	array = (char **)malloc(sizeof(char *) * (info->board_size.rows + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < info->board_size.rows)
	{
		array[i] = ft_strnew(info->board_size.cols);
		if (!array[i])
		{
			free_char_array(array);
			return (NULL);
		}
		i++;
	}
	array[i] = 0;
	return (array);
}

void	free_int_array(char **array, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->board_size.rows)
	{
		free(array[i]);
		i++;
	}
}

int	**create_int_array(t_info *info)
{
	int	**array;
	int	i;

	array = (int **)malloc(sizeof(int *) * info->board_size.rows);
	if (!array)
		return (NULL);
	i = 0;
	while (i < info->board_size.rows)
	{
		array[i] = (int *)malloc(sizeof(int) * info->board_size.cols);
		if (!array[i])
		{
			free_int_array(array, info);
			return (NULL);
		}
		i++;
	}
	return (array);
}
