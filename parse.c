/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:07:04 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/21 13:16:12 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	parse_number(char last)
{
	char	temp;
	int		n;

	temp = last;
	n = 0;
	while (ft_isdigit(temp))
	{
		n = n * 10 + (temp - '0');
		read(STDIN_FILENO, &temp, 1);
	}
	return (n);
}

int	parse_player(t_info *info)
{
	char	temp;
	
	temp = '$';
	while (!ft_isdigit(temp))
		read(STDIN_FILENO, &temp, 1);
	if (temp == '1')
	{
		info->player = 'O';
		info->enemy = 'X';
	}
	else if (temp == '2')
	{
		info->player = 'X';
		info->enemy = 'O';
	}
	else
		return (-1);
	return (0);
}

int	parse_board_size(t_info *info)
{
	char	temp;

	read(STDIN_FILENO, &temp, 1);
	while (!ft_isdigit(temp))
		read(STDIN_FILENO, &temp, 1);
	info->board_size.rows = parse_number(temp);
	read(STDIN_FILENO, &temp, 1);
	while (!ft_isdigit(temp))
		read(STDIN_FILENO, &temp, 1);
	info->board_size.columns = parse_number(temp);
	if (info->board_size.rows <= 0 || info->board_size.columns <= 0)
		return (-1);
	return (0);
}
