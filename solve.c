/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:10:08 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/25 14:37:14 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

bool	can_place(t_info *info, int row, int col)
{
	int	x;
	int	y;

	if (info->board[row][col] != ft_tolower(info->player))
		return (false);
	x = row - 1;
	while (x <= row + 1)
	{
		y = col - 1;
		while (y <= col + 1)
		{
			if (x > 0 && x < info->board_size.rows
				&& y > 0 && y < info->board_size.cols
				&& (x != row && y != col)
				&& info->board[x][y] == '.')
				return (true);
			y++;
		}
		x++;
	}
	return (false);
}

bool	place_piece(t_info *info, int row, int col)
{
	int	piece_row;
	int	piece_col;
	int	temp_value;
	int	best_value;

	piece_row = 0;
	while (piece_row < info->piece_size.rows)
	{
		piece_col = 0;
		while (piece_col < info->piece_size.cols)
		{
			if (info->piece[piece_row][piece_col] == '*')
			{
				temp_value = fit_piece(info, row, col, piece_row, piece_col);
				if (temp_value > 0 && temp_value < best_value)
					save_result(info);
			}
			piece_col++;
		}
		piece_row++;
	}
	return (print_result(info));
}

int	find_solution(t_info *info)
{
	int	row;
	int	col;

	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			if (can_place(info, row, col) && place_piece(info, row, col))
				return (0);
			col++;
		}
		row++;
	}
	return (-1);
}
