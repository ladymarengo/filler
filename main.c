/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:16:17 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/31 16:31:16 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	initialize_info(t_info *info)
{
	ft_bzero(info, sizeof (*info));
	if (parse_player(info) == -1
		|| parse_size(&info->board_size.rows, &info->board_size.cols) == -1)
		return (-1);
	info->board = create_char_array(info);
	info->heatmap = create_int_array(info);
	if (!info->board || !info->heatmap)
		return (-1);
	return (0);
}

int	cleanup(t_info *info, int ret)
{
	if (info->board)
		free_char_array(info->board);
	if (info->piece)
		free_char_array(info->piece);
	if (info->heatmap)
		free_int_array(info->heatmap, info);
	return (ret);
}

int	main(void)
{
	t_info	info;
	int		status;
	FILE *f = fopen("file.txt", "w+");

	// fprintf(f, "Start\n");
	
	if (initialize_info(&info) == -1)
		return (cleanup(&info, -1));
	// fprintf(f, "Player '%c'\n", info.player);
	fclose(f);
	status = 1;
	while (status >= 0)
	{
		if (parse_board(&info) == 0 && parse_piece(&info) == 0)
		{
			update_heatmap(&info);
			// make_log(&info);
			status = find_solution(&info);
		}
		else
			status = -1;
	}
	return (cleanup(&info, status));
}
