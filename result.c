/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:11:30 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/05 16:30:50 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	save_result(t_info *info, int value, t_coord board, t_coord piece)
{
	info->best_val = value;
	info->result.row = board.row - piece.row;
	info->result.col = board.col - piece.col;
}

int	print_result(t_info *info)
{
	if (info->best_val >= 0)
	{
		ft_printf("%d %d\n", info->result.row, info->result.col);
		return (0);
	}
	else
	{
		ft_printf("0 0\n");
		return (-1);
	}
}
