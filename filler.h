/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:28 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/25 13:13:29 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"

typedef struct s_grid_size
{
	int	rows;
	int	cols;
}	t_grid_size;

typedef struct s_info
{
	t_grid_size	board_size;
	t_grid_size	piece_size;
	char		player;
	char		enemy;
	char		**board;
	char		**piece;
}	t_info;

int		parse_player(t_info *info);
int		parse_size(int *rows, int *columns);
char	**create_char_arr(int rows, int columns);

#endif