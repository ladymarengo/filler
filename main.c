/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:16:17 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/25 13:12:40 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	initialize_info(t_info *info)
{
	ft_bzero(info, sizeof (*info));
	if (parse_player(info) == -1
		|| parse_size(&info->board_size.rows, &info->board_size.cols) == -1)
		return (-1);
	info->board = create_char_arr(info->board_size.rows, info->board_size.cols);
	if (!info->board)
		return (-1);
	return (0);
}

int	main(void)
{
	t_info	info;
	int		status;

	if (initialize_info(&info) == -1)
		return (-1);
	status = 1;
	while (status > 0)
	{
		if (parse_board(&info) == 0 && parse_piece(&info) == 0
			&& update_heatmap(&info) == 0)
		{
			break ;
		}
	}
}