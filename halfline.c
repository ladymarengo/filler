/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halfline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:50:25 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/01 13:13:35 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	set_to_max(t_info *info)
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
			if (info->board[row][col] != '.')
				info->heatmap[row][col] = 0;
			else
				info->heatmap[row][col] = max;
			col++;
		}
		row++;
	}
}

int	ft_abs(int value)
{
	if (value >= 0)
		return (value);
	else
		return (-value);
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

// static int	closer_to_enemy(t_info *info, int old_row, int old_col, int new_row, int new_col)
// {
// 	int	old_distance;
// 	int	new_distance;

// 	old_distance = distance_to_enemy(info, old_row, old_col);
// 	new_distance = distance_to_enemy(info, new_row, new_col);
// 	if (new_distance > old_distance)
// 		return (3);
// 	else if (new_distance < old_distance)
// 		return (1);
// 	else
// 		return (2);
// }

static void	set_neighbours(t_info *info, int depth, int row, int col)
{
	int	max;

	max = ft_max_int(info->board_size.rows, info->board_size.cols);
	if (on_board(info, row - 1, col) && info->heatmap[row - 1][col] == max)
		info->heatmap[row - 1][col] = depth + distance_to_enemy(info, row - 1, col);
	if (on_board(info, row + 1, col) && info->heatmap[row + 1][col] == max)
		info->heatmap[row + 1][col] = depth + distance_to_enemy(info, row + 1, col);
	if (on_board(info, row, col - 1) && info->heatmap[row][col - 1] == max)
		info->heatmap[row][col - 1] = depth + distance_to_enemy(info, row, col - 1);
	if (on_board(info, row, col + 1) && info->heatmap[row][col + 1] == max)
		info->heatmap[row][col + 1] = depth + distance_to_enemy(info, row, col + 1);
	if (on_board(info, row - 1, col - 1) && info->heatmap[row - 1][col - 1] == max)
		info->heatmap[row - 1][col - 1] = depth + distance_to_enemy(info, row - 1, col - 1);
	if (on_board(info, row + 1, col + 1) && info->heatmap[row + 1][col + 1] == max)
		info->heatmap[row + 1][col + 1] = depth + distance_to_enemy(info, row + 1, col + 1);
	if (on_board(info, row + 1, col - 1) && info->heatmap[row + 1][col - 1] == max)
		info->heatmap[row + 1][col - 1] = depth + distance_to_enemy(info, row + 1, col - 1);
	if (on_board(info, row - 1, col + 1) && info->heatmap[row - 1][col + 1] == max)
		info->heatmap[row - 1][col + 1] = depth + distance_to_enemy(info, row - 1, col + 1);
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
				set_neighbours(info, depth, row, col);
			col++;
		}
		row++;
	}
}

void	update_heatmap_new(t_info *info)
{
	int	depth;

	set_to_max(info);
	depth = 0;
	while (depth < 1000)
	{
		set_heatmap(info, depth);
		depth++;
	}
}