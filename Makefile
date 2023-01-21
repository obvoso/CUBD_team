# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tson <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 14:07:52 by tson              #+#    #+#              #
#    Updated: 2022/12/24 14:07:53 by tson             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS =
SRCS = srcs/main.c\
	   srcs/keyboard.c\
	   srcs/check_file.c\
	   srcs/init.c\
	   srcs/rendering.c\
	   srcs/calculate.c\
	   srcs/utils.c
OBJS = ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C ./srcs/libft all
	@make -C ./mlx all
	$(CC) $(CFLAGS) -o $@ $^ -L ./mlx -lmlx -framework OpenGL -framework AppKit srcs/libft/libft.a

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean :
	@make -C ./srcs/libft clean
	@make -C ./mlx clean
	rm -f $(OBJS)

fclean : clean
	@make -C ./srcs/libft fclean
	rm -f $(OBJS) $(NAME)

re : fclean all

.PHONY : all clean fclean re
