/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:44:57 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/07 17:26:20 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	update_centers(t_info *info)
{
	info->center_captured = center_is_captured(info);
	info->center_row_captured = center_row_is_captured(info);
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
		if (info->board[row][col] == info->player)
			return (true);
		col++;
	}
	return (false);
}

int	distance_to_center(t_info *info, int row, int col)
{
	int	center_row;
	int	center_col;

	center_row = info->board_size.rows / 2;
	center_col = info->board_size.cols / 2;
	return (ft_abs(center_row - row) + ft_abs(center_col - col));
}
