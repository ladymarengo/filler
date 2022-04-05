/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:29:09 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/05 16:30:15 by nsamoilo         ###   ########.fr       */
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

	temp.row = row + board.row - piece.row;
	temp.col = col + board.col - piece.col;
	return (temp);
}
