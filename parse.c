/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:07:04 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/07 19:31:39 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#include <stdio.h>

int	parse_number(char last)
{
	char	temp;
	int		n;

	temp = last;
	n = 0;
	while (ft_isdigit(temp))
	{
		n = n * 10 + (temp - '0');
		if (read(STDIN_FILENO, &temp, 1) < 0)
			return (-1);
	}
	return (n);
}

int	parse_player(t_info *info)
{
	char	temp;

	temp = '$';
	while (!ft_isdigit(temp))
	{
		if (read(STDIN_FILENO, &temp, 1) < 0)
			return (-1);
	}
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

int	parse_size(int *rows, int *columns)
{
	char	temp;
	int		status;

	temp = ',';
	status = 1;
	while (!ft_isdigit(temp) && status > 0)
		status = read(STDIN_FILENO, &temp, 1);
	*rows = parse_number(temp);
	status = read(STDIN_FILENO, &temp, 1);
	while (!ft_isdigit(temp) && status > 0)
		status = read(STDIN_FILENO, &temp, 1);
	*columns = parse_number(temp);
	if (*rows <= 0 || *columns <= 0 || status == -1)
		return (-1);
	return (0);
}

int	parse_board(t_info *info)
{
	int		row;
	int		column;
	char	temp[1];

	row = 0;
	while (row < info->board_size.rows)
	{
		column = 0;
		while (column < info->board_size.cols)
		{
			if (read(STDIN_FILENO, temp, 1) == -1)
				return (-1);
			if (ft_strchr("XxOo.", temp[0]))
			{
				info->board[row][column] = parse_char(temp[0]);
				column++;
			}
		}
		row++;
	}
	update_centers(info);
	return (0);
}

int	parse_piece(t_info *info)
{
	int		row;
	int		column;
	char	temp[1];

	if (parse_size(&info->piece_size.rows, &info->piece_size.cols) == -1)
		return (-1);
	info->piece = create_char_array(info->piece_size.rows, \
		info->piece_size.cols);
	if (!info->piece)
		return (-1);
	row = 0;
	while (row < info->piece_size.rows)
	{
		column = 0;
		while (column < info->piece_size.cols)
		{
			if (read(STDIN_FILENO, temp, 1) == -1)
				return (-1);
			if (ft_strchr("*.", temp[0]))
				info->piece[row][column++] = temp[0];
		}
		row++;
	}
	find_borders(info);
	return (0);
}
