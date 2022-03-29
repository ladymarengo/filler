/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:10:08 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/29 14:27:06 by nsamoilo         ###   ########.fr       */
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

int	fit_piece(t_info *info, t_coord board, t_coord piece)
{
	(void) info;
	(void) board;
	(void) piece;
	return (-1);
}

void	place_piece(t_info *info, t_coord board_coord)
{
	int		piece_row;
	int		piece_col;
	int		temp_value;
	t_coord	temp_coord;

	piece_row = 0;
	while (piece_row < info->piece_size.rows)
	{
		piece_col = 0;
		while (piece_col < info->piece_size.cols)
		{
			if (info->piece[piece_row][piece_col] == '*')
			{
				temp_coord.row = piece_row;
				temp_coord.col = piece_col;
				temp_value = fit_piece(info, board_coord, temp_coord);
				if (temp_value > 0
					&& (temp_value < info->best || info->best == -1))
					save_result(info, temp_value, board_coord, temp_coord);
			}
			piece_col++;
		}
		piece_row++;
	}
}

int	find_solution(t_info *info)
{
	int		row;
	int		col;
	t_coord	temp_coord;

	info->best = -1;
	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			temp_coord.row = row;
			temp_coord.col = col;
			if (can_place(info, row, col))
				place_piece(info, temp_coord);
			col++;
		}
		row++;
	}
	return (print_result(info));
}
