/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:29:09 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/07 17:00:23 by nsamoilo         ###   ########.fr       */
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
	row = -1;
	while (row++ < info->piece_size.rows)
	{
		col = -1;
		while (col++ < info->piece_size.cols)
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
		}
	}
}
