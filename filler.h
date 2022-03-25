/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:28 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/03/25 13:53:09 by nsamoilo         ###   ########.fr       */
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
	int			**heatmap;
}	t_info;

int		parse_player(t_info *info);
int		parse_size(int *rows, int *columns);
char	**create_char_arr(t_info *info);
int		**create_int_array(t_info *info);
void	free_char_array(char **array);
void	free_int_array(char **array, t_info *info);

#endif