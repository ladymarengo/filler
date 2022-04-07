# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 14:27:47 by nsamoilo          #+#    #+#              #
#    Updated: 2022/04/07 19:04:14 by nsamoilo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nsamoilo.filler
FUNCTIONS = main arrays heatmap parse result solve helpers center
FILES = $(patsubst %, %.c, $(FUNCTIONS))
OBJECTS = $(patsubst %, %.o, $(FUNCTIONS))

all: $(NAME)

$(NAME):
	make -C libft/
	gcc -Wall -Wextra -Werror -g -c $(FILES)
	gcc -Wall -Werror -Wextra -g  $(OBJECTS) libft/libft.a -o $(NAME)
	make fclean -C libft/

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all