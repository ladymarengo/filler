/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:24:48 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/21 13:28:05 by nsamoilo         ###   ########.fr       */
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

char	**create_char_array(int rows, int columns)
{
	char	**array;
	int		i;

	array = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		array[i] = ft_strnew(columns);
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
