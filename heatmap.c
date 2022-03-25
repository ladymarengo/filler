/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:14:58 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/25 14:10:41 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	set_to_max(t_info *info)
{
	int	row;
	int	col;
	int	max;

	max = ft_max_int(info->board_size.rows, info->board_size.cols);
	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			if (info->board[row][col] == ft_tolower(info->enemy))
				info->heatmap[row][col] = 0;
			else
				info->heatmap[row][col] = max;
			col++;
		}
		row++;
	}
}

void	set_neighbours(t_info *info, int depth, int row, int col)
{
	int	x;
	int	y;
	int	max;

	max = ft_max_int(info->board_size.rows, info->board_size.cols);
	x = row - 1;
	while (x <= row + 1)
	{
		y = col - 1;
		while (y <= col + 1)
		{
			if (x > 0 && x < info->board_size.rows
				&& y > 0 && y < info->board_size.cols
				&& (x != row && y != col)
				&& info->heatmap[x][y] == max)
				info->heatmap[x][y] = depth;
			y++;
		}
		x++;
	}
}

void	set_heatmap(t_info *info, int depth)
{
	int	row;
	int	col;

	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			if (info->heatmap[row][col] == depth)
				set_neighbours(info, depth + 1, row, col);
			col++;
		}
		row++;
	}
}

void	update_heatmap(t_info *info)
{
	int	depth;

	set_to_max(info);
	depth = 0;
	while (depth < ft_max_int(info->board_size.rows, info->board_size.cols))
	{
		set_heatmap(info, depth);
		depth++;
	}
}
