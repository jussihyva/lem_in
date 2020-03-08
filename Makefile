# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/23 13:36:07 by jkauppi           #+#    #+#              #
#    Updated: 2020/03/08 09:59:43 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in
CC			=	clang
C_FLAGS		=	-g -Wall -Werror -Wextra

MAIN_SRC	=	lem_in.c
HEADER		=	lem_in.h
INCLUDES	=	-I ./ -I libft -I libftprintf/src
LIB			=	-L libft -l ft -L libftprintf -l ftprintf

SRC_FOLDER	=	src
SRC_FILES	=	ft_read_opt.c ft_strtoi.c manage_room_data.c ft_arraydel.c \
				result.c manage_connection_data.c ft_step_args.c \
				calc_distance.c memory.c

OBJ_FOLDER	=	obj
OBJ_FILES	=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(MAIN_SRC) $(HEADER) | $(OBJ_FOLDER)
	@$(CC) $(C_FLAGS) -o $(NAME) $(MAIN_SRC) $(OBJ_FILES) $(INCLUDES) $(LIB)

$(OBJ_FILES): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER) | $(OBJ_FOLDER)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

norm:
	@norminette $(MAIN_SRC) $(HEADER) $(SRC_FOLDER)

clean:
	@\rm -rf $(NAME).dSYM

fclean: clean

re: fclean all

.PHONY: all clean fclean re norm
