/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:28 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/29 14:51:43 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"
# include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct s_grid_size
{
	int	rows;
	int	cols;
}	t_grid_size;

typedef struct s_coord
{
	int	row;
	int	col;
}	t_coord;

typedef struct s_info
{
	t_grid_size	board_size;
	t_grid_size	piece_size;
	char		player;
	char		enemy;
	char		**board;
	char		**piece;
	int			**heatmap;
	t_coord		board_coord;
	t_coord		piece_coord;
	int			best;
	t_coord		result;
}	t_info;

int		parse_player(t_info *info);
int		parse_size(int *rows, int *columns);
int		parse_board(t_info *info);
int		parse_piece(t_info *info);
char	**create_char_array(t_info *info);
int		**create_int_array(t_info *info);
void	free_char_array(char **array);
void	free_int_array(int **array, t_info *info);
void	update_heatmap(t_info *info);
int		find_solution(t_info *info);
void	save_result(t_info *info, int value, t_coord board, t_coord piece);
int		print_result(t_info *info);

#endif