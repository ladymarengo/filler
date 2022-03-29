/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:11:30 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/29 15:52:08 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	save_result(t_info *info, int value, t_coord board, t_coord piece)
{
	(void) info;
	(void) value;
	(void) board;
	(void) piece;
}

int	print_result(t_info *info)
{
	FILE *f = fopen("file.txt", "a");

	if (info->best_val >= 0)
	{
		ft_printf("%d %d\n", info->result.row, info->result.col);
		fprintf(f, "%d %d\n", info->result.row, info->result.col);
		fclose(f);
		return (0);
	}
	else
	{
		ft_printf("0 0\n");
		fprintf(f, "0 0\n");
		fclose(f);
		return (-1);
	}
}
