/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:07:04 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/04/07 17:05:11 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#include <stdio.h>

int	parse_number(char last)
{
	char	temp;
	int		n;

	temp = last;
	n = 0;
	while (ft_isdigit(temp))
	{
		n = n * 10 + (temp - '0');
		read(STDIN_FILENO, &temp, 1);
	}
	return (n);
}

int	parse_player(t_info *info)
{
	char	temp;

	temp = '$';
	while (!ft_isdigit(temp))
		read(STDIN_FILENO, &temp, 1);
	if (temp == '1')
	{
		info->player = 'O';
		info->enemy = 'X';
	}
	else if (temp == '2')
	{
		info->player = 'X';
		info->enemy = 'O';
	}
	else
		return (-1);
	return (0);
}

int	parse_size(int *rows, int *columns)
{
	char	temp;

	temp = ',';
	while (!ft_isdigit(temp))
		read(STDIN_FILENO, &temp, 1);
	*rows = parse_number(temp);
	read(STDIN_FILENO, &temp, 1);
	while (!ft_isdigit(temp))
		read(STDIN_FILENO, &temp, 1);
	*columns = parse_number(temp);
	if (*rows <= 0 || *columns <= 0)
		return (-1);
	return (0);
}

int	parse_board(t_info *info)
{
	int		row;
	int		column;
	char	temp[1];

	// FILE *f = fopen("file.txt", "a");

	// fprintf(f, "\n");

	row = 0;
	while (row < info->board_size.rows)
	{
		column = 0;
		while (column < info->board_size.cols)
		{
			read(STDIN_FILENO, temp, 1);
			if (ft_strchr("XxOo.", temp[0]))
			{
				if (temp[0] == 'x')
					info->board[row][column] = 'X';
				else if (temp[0] == 'o')
					info->board[row][column] = 'O';
				else
					info->board[row][column] = temp[0];
				// fprintf(f, "%c", info->board[row][column]);
				column++;
			}
		}
		// fprintf(f, "\n");
		row++;
	}
	update_centers(info);
	// fclose(f);
	return (0);
}

int	parse_piece(t_info *info)
{
	int		row;
	int		column;
	char	temp[1];

	info->piece = create_char_array(info);
	if (parse_size(&info->piece_size.rows, &info->piece_size.cols) == -1
		|| !info->piece)
		return (-1);
	row = 0;
	while (row < info->piece_size.rows)
	{
		column = 0;
		while (column < info->piece_size.cols)
		{
			read(STDIN_FILENO, temp, 1);
			if (ft_strchr("*.", temp[0]))
			{
				info->piece[row][column] = temp[0];
				column++;
			}
		}
		row++;
	}
	find_borders(info);
	return (0);
}
