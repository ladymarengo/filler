/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:29:09 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/07 19:33:16 by nsamoilo         ###   ########.fr       */
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

static void	reset_points(t_info *info)
{
	info->piece_start.row = -1;
	info->piece_start.col = -1;
	info->piece_end.row = -1;
	info->piece_end.col = -1;
}

void	find_borders(t_info *info)
{
	int	row;
	int	col;

	reset_points(info);
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
}

char	parse_char(char c)
{
	if (c == 'x')
		return ('X');
	else if (c == 'o')
		return ('O');
	else
		return (c);
}
