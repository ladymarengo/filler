/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:50:25 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/05 16:29:26 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static bool	center_is_captured(t_info *info)
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

static bool	center_row_is_captured(t_info *info)
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

static int	distance_to_enemy(t_info *info, int check_row, int check_col)
{
	int	best;
	int	temp;
	int	row;
	int	col;

	best = info->board_size.rows + info->board_size.cols;
	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			if (ft_toupper(info->board[row][col]) == info->enemy)
			{
				temp = ft_abs(check_row - row) + ft_abs(check_col - col);
				if (temp < best)
					best = temp;
			}
			col++;
		}
		row++;
	}
	return (best);
}

static int	distance_to_center(t_info *info, int row, int col)
{
	int	center_row;
	int	center_col;

	center_row = info->board_size.rows / 2;
	center_col = info->board_size.cols / 2;
	return (ft_abs(center_row - row) + ft_abs(center_col - col));
}

void	update_heatmap(t_info *info)
{
	int	row;
	int	col;

	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			if (center_row_is_captured(info) && center_is_captured(info))
				info->heatmap[row][col] = distance_to_enemy(info, row, col);
			else if (center_row_is_captured(info))
				info->heatmap[row][col] = distance_to_center(info, row, col);
			else
				info->heatmap[row][col] = \
				ft_abs(info->board_size.rows / 2 - row);
			col++;
		}
		row++;
	}
}
