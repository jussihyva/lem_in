# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/23 13:36:07 by jkauppi           #+#    #+#              #
#    Updated: 2020/04/05 09:41:46 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in
NAME_2		=	checker
CC			=	clang
C_FLAGS		=	-g -Wall -Werror -Wextra

MAIN_SRC	=	lem_in.c
MAIN_2_SRC	=	checker.c
HEADER		=	lem_in.h
INCLUDES	=	-I ./ -I libft -I libftprintf/src
LIB			=	-L libft -l ft -L libftprintf -l ftprintf

SRC_FOLDER	=	src
SRC_FILES	=	input_1.c input_2.c ft_read_opt.c ft_strtoi.c ft_arraydel.c \
				room_data_1.c room_data_2.c room_data_3.c \
				result_1.c result_2.c result_3.c \
				connection_data.c ft_step_args.c ft_lstlen.c \
				calc_distance.c ants_1.c ants_2.c \
				select_paths_1.c select_paths_2.c select_paths_3.c \
				instruction_1.c instruction_2.c memory_1.c memory_2.c output.c \
				algorithm_ford_fulkerson1.c algorithm_ford_fulkerson2_1.c \
				algorithm_ford_fulkerson2_2.c \
				algorithm_ford_fulkerson3.c

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
	norminette $(MAIN_SRC) $(HEADER) $(SRC_FOLDER)

clean:
	@\rm -rf $(NAME).dSYM
	@\rm -rf $(OBJ_FILES)

fclean: clean
	@\rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re norm
