# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alcohen <alcohen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 20:45:50 by alcohen           #+#    #+#              #
#    Updated: 2020/02/24 20:07:49 by alcohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
NAME = fdf
SNAKE = snake

MAIN = main.c
SRCS = $(MAIN) lines_to_map.c draw.c
OBJS=$(notdir $(SRCS:.c=.o))
SNAKE_MAIN = snake.c
LIBFT = libft/libft.a
MAKE_LIB=make -C libft/ fclean && make -C libft/
MLX = -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL \
-framework AppKit

all: $(NAME)

noflags:
	@$(MAKE_LIB)
	gcc -c $(SRCS)
	gcc $(MLX) -o $(NAME) $(OBJS) $(LIBFT)

$(NAME):
	@$(MAKE_LIB)
	gcc $(FLAGS) -c $(SRCS)
	gcc $(FLAGS) $(MLX) -o $(NAME) $(OBJS) $(LIBFT)

$(SNAKE):
	gcc -I $(INCLUDES) $(SNAKE_MAIN) $(SRCS) -o $(NAME) -lmlx -framework OpenGL \ 
	-framework AppKit

re: fclean $(NAME)

clean:
	/bin/rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean
