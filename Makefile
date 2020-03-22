# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pi <pi@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/23 13:36:07 by jkauppi           #+#    #+#              #
#    Updated: 2020/03/22 18:52:32 by pi               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in
NAME_2		=	checker
CC			=	clang
C_FLAGS		=	-Wall -Werror -Wextra -g

MAIN_SRC	=	lem_in.c
MAIN_2_SRC	=	checker.c
HEADER		=	lem_in.h
INCLUDES	=	-I ./ -I libft -I libftprintf/src
LIB			=	-L libft -l ft -L libftprintf -l ftprintf

SRC_FOLDER	=	src
SRC_FILES	=	input.c ft_read_opt.c ft_strtoi.c ft_arraydel.c \
				manage_room_data.c manage_room_data_1.c manage_room_data_2.c \
				result_1.c result_2.c manage_connection_data.c ft_step_args.c \
				calc_distance.c memory.c transportation.c ants.c \
				select_paths_1.c select_paths_2.c select_paths_3.c \
				instruction_1.c

OBJ_FOLDER	=	obj
OBJ_FILES	=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRC_FILES)))

all: $(NAME) $(NAME_2)

$(NAME): $(OBJ_FILES) $(MAIN_SRC) $(HEADER) | $(OBJ_FOLDER)
	@$(CC) $(C_FLAGS) -o $(NAME) $(MAIN_SRC) $(OBJ_FILES) $(INCLUDES) $(LIB)

$(NAME_2): $(OBJ_FILES) $(MAIN_2_SRC) $(HEADER) | $(OBJ_FOLDER)
	@$(CC) $(C_FLAGS) -o $(NAME_2) $(MAIN_2_SRC) $(OBJ_FILES) $(INCLUDES) $(LIB)

$(OBJ_FILES): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER) | $(OBJ_FOLDER)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

norm:
	@norminette $(MAIN_SRC) $(HEADER) $(SRC_FOLDER)

clean:
	@\rm -rf $(NAME).dSYM
	@\rm -rf $(OBJ_FILES)

fclean: clean
	@\rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re norm
