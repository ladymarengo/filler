/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:14:12 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/26 15:18:37 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	reset_heatmap(t_info *info)
{
	int	row;
	int	col;

	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			if (info->board[row][col] == info->enemy)
				info->heatmap[row][col] = 0;
			else
				info->heatmap[row][col] = -1;
			col++;
		}
		row++;
	}
}

static void	set_neighbours(t_info *info, int depth, int row, int col)
{
	int	x;
	int	y;

	x = row - 1;
	while (x <= row + 1)
	{
		y = col - 1;
		while (y <= col + 1)
		{
			if (x > 0 && x < info->board_size.rows
				&& y > 0 && y < info->board_size.cols
				&& (x != row && y != col)
				&& info->heatmap[x][y] == -1)
				info->heatmap[x][y] = depth;
			y++;
		}
		x++;
	}
}

static void	set_heatmap(t_info *info, int depth)
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

static void	go_to_center(t_info *info)
{
	int	row;
	int	col;

	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			if (info->center_row_captured)
				info->heatmap[row][col] = distance_to_center(info, row, col);
			else
				info->heatmap[row][col] = \
				ft_abs(info->board_size.rows / 2 - row);
			col++;
		}
		row++;
	}
}

void	update_heatmap(t_info *info)
{
	int	depth;

	if (!info->center_captured)
		go_to_center(info);
	else
	{
		reset_heatmap(info);
		depth = 0;
		while (depth < info->board_size.rows + info->board_size.cols)
		{
			set_heatmap(info, depth);
			depth++;
		}
	}
}
