# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 14:27:47 by nsamoilo          #+#    #+#              #
#    Updated: 2022/04/01 12:45:33 by nsamoilo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nsamoilo.filler
FUNCTIONS = main arrays heatmap parse result solve helpers halfline
FILES = $(patsubst %, %.c, $(FUNCTIONS))
OBJECTS = $(patsubst %, %.o, $(FUNCTIONS))

all: $(NAME)

$(NAME):
	make -C libft/
	gcc -Wall -Wextra -Werror -c $(FILES)
	gcc -Wall -Werror -Wextra $(OBJECTS) libft/libft.a -o $(NAME)
	make fclean -C libft/

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all