/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:10:08 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/29 15:51:04 by nsamoilo         ###   ########.fr       */
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
			if (on_board(info, x, y)
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
	int		row;
	int		col;
	t_coord	temp;

	row = -1;
	while (row++ < info->piece_size.rows - 1)
	{
		col = -1;
		while (col++ < info->piece_size.cols - 1)
		{
			temp = calculate_offset(row, col, piece, board);
			if (info->piece[row][col] == '*'
				&& info->board[temp.row][temp.col] == '*')
			{
				if (!on_board(info, temp.row, temp.col))
					return (-1);
				info->connections++;
			}
			else if (info->piece[row][col] == '*')
				info->temp_val += info->heatmap[temp.row][temp.col];
		}
	}
	if (info->connections == 1)
		return (info->temp_val);
	return (-1);
}

void	place_piece(t_info *info, t_coord board_coord)
{
	int		piece_row;
	int		piece_col;
	int		temp_value;
	t_coord	piece_coord;

	piece_row = 0;
	while (piece_row < info->piece_size.rows)
	{
		piece_col = -1;
		while (piece_col++ < info->piece_size.cols - 1)
		{
			if (info->piece[piece_row][piece_col] == '*')
			{
				piece_coord.row = piece_row;
				piece_coord.col = piece_col;
				info->connections = 0;
				info->temp_val = 0;
				temp_value = fit_piece(info, board_coord, piece_coord);
				if (temp_value > 0
					&& (temp_value < info->best_val || info->best_val == -1))
					save_result(info, temp_value, board_coord, piece_coord);
			}
		}
		piece_row++;
	}
}

int	find_solution(t_info *info)
{
	int		row;
	int		col;
	t_coord	temp_coord;

	info->best_val = -1;
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
