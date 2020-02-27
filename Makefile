# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 01:29:34 by arhallab          #+#    #+#              #
#    Updated: 2020/02/27 23:34:01 by arhallab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	Cub3D

SRC		=	c3drestoffuncts.c even_mo_tools.c file_reader.c\
			ft_atoi.c ft_c3d.c ft_split.c ft_strlcpy.c\
			ft_strncmp.c ft_strtrim.c ft_substr.c gadgets.c\
			gen_n_tools.c get_next_line.c get_next_line_utils.c\
			mo_tools.c updaters.c screenshot.c
all:$(NAME)

$(NAME) :
	gcc -g -Wall -Werror -Wextra -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -fsanitize=address -framework appkit $(SRC) -o $(NAME)

clean :

fclean : clean
	rm -f $(NAME)

re : fclean all

.Phony : all fclean clean bonus re