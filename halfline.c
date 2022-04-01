/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halfline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:50:25 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/01 15:14:48 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

static void	set_to_max(t_info *info)
{
	int	row;
	int	col;
	int	max;

	max = 99;
	row = 0;
	while (row < info->board_size.rows)
	{
		col = 0;
		while (col < info->board_size.cols)
		{
			info->heatmap[row][col] = distance_to_enemy(info, row, col);
			col++;
		}
		row++;
	}
}

void	update_heatmap_new(t_info *info)
{
	set_to_max(info);
}
