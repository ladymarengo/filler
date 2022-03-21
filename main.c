/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:16:17 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/21 13:28:56 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	initialize_info(t_info *info)
{
	ft_bzero(info, sizeof (*info));
	if (parse_player(info) == -1 || parse_board_size(info) == -1)
		return (-1);
	info->board = create_char_array(info->board_size.rows, info->board_size.columns);
	if (!info->board)
		return (-1);
	
}

int	main()
{
	t_info	info;
	
	if (initialize_info(&info) == -1)
		return (-1);
}