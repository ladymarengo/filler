/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:29:09 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/31 16:31:07 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

bool	on_board(t_info *info, int row, int col)
{
	return (row >= 0 && col >= 0
		&& row < info->board_size.rows
		&& col < info->board_size.cols);
}

t_coord	calculate_offset(int row, int col, t_coord piece, t_coord board)
{
	t_coord	temp;

	temp.row = - piece.row + row + board.row;
	temp.col = - piece.col + col + board.col;
	return (temp);
}

void	make_log(t_info *info)
{
	FILE *f = fopen("file.txt", "a");

	fprintf(f, "Start logging\n");
	
	int		row;
	int		col;

	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			fprintf(f, "%c ", info->board[row][col]);
			col++;
		}
		fprintf(f, "\n");
		row++;
	}
	fprintf(f, "\n");

	row = 0;
	while (row < info->piece_size.rows)
	{
		col = 0;
		while (col < info->piece_size.cols)
		{
			fprintf(f, "%c ", info->piece[row][col]);
			col++;
		}
		fprintf(f, "\n");
		row++;
	}
	fprintf(f, "\n");
	
	fclose(f);
}
