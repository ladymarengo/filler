#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"

typedef struct s_grid_size
{
	int	rows;
	int	columns;
} t_grid_size;

typedef struct s_info
{
	t_grid_size	board_size;
	t_grid_size	piece_size;
	char	player;
	char	enemy;
	char		**board;
	char		**piece;
} t_info;

int	parse_player(t_info *info);
int	parse_board_size(t_info *info);
char	**create_char_array(int rows, int columns);

#endif