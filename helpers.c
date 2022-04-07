/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:29:09 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/07 15:44:05 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#include <stdio.h>

bool	on_board(t_info *info, int row, int col)
{
	return (row >= 0 && col >= 0
		&& row < info->board_size.rows
		&& col < info->board_size.cols);
}

t_coord	calculate_offset(int row, int col, t_coord piece, t_coord board)
{
	t_coord	temp;

	temp.row = row + board.row - piece.row;
	temp.col = col + board.col - piece.col;
	return (temp);
}

void	find_borders(t_info *info)
{
	int	row;
	int	col;

	info->piece_start.row = -1;
	info->piece_start.col = -1;
	info->piece_end.col = -1;
	row = 0;
	while (row < info->piece_size.rows)
	{
		col = 0;
		while (col < info->piece_size.cols)
		{
			if (info->piece[row][col] == '*')
			{
				if (info->piece_start.row == -1)
					info->piece_start.row = row;
				if (info->piece_start.col == -1
					|| info->piece_start.col > col)
					info->piece_start.col = col;
				info->piece_end.row = row;
				if (info->piece_end.col < col)
					info->piece_end.col = col;
			}
			col++;
		}
		row++;
	}
	FILE *f = fopen("file.txt", "a");

	fprintf(f, "%d %d, %d %d\n", info->piece_start.row, info->piece_start.col, info->piece_end.row, info->piece_end.col);
	fclose(f);
}

bool	center_is_captured(t_info *info)
{
	int	row;
	int	col;

	row = info->board_size.rows / 2;
	col = info->board_size.cols / 2;
	while (row <= info->board_size.rows / 2 + 1)
	{
		while (col <= info->board_size.cols / 2 + 1)
		{
			if (info->board[row][col] != '.')
				return (true);
			col++;
		}
		row++;
	}
	return (false);
}

bool	center_row_is_captured(t_info *info)
{
	int	row;
	int	col;

	row = info->board_size.rows / 2;
	col = 0;
	while (col < info->board_size.cols)
	{
		if (ft_toupper(info->board[row][col]) == info->player)
			return (true);
		col++;
	}
	return (false);
}
