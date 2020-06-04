# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/23 13:36:07 by jkauppi           #+#    #+#              #
#    Updated: 2020/06/03 23:07:50 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in
NAME_2			=	checker
CC				=	clang
C_FLAGS			=	-g -Wall -Werror -Wextra

MAIN_SRC		=	lem_in.c
MAIN_2_SRC		=	checker.c
HEADER			=	lem_in.h
INCLUDES		=	-I ./ -I libft -I libftprintf/src
LIBFT_FOLDER	=	libft
LIBFT_PRINTF_FOLDER	=	libftprintf
LIBFT			=	$(LIBFT_FOLDER)/libft.a
LIBFT_PRINTF	=	$(LIBFT_PRINTF_FOLDER)/libftprintf.a
LIB				=	-L libft -l ft -L libftprintf -l ftprintf

SRC_FOLDER		=	src
SRC_FILES		=	input_1.c input_2.c ft_read_opt.c ft_strtoi.c \
					ft_arraydel.c room_data_1.c room_data_2.c room_data_3.c \
					result_1.c result_2.c result_3.c \
					connection_data_1.c connection_data_2.c connection_data_3.c \
					ft_step_args.c ft_lstlen.c ft_lstrem.c ft_lstadd_sort.c \
					calc_distance.c ants_1.c ants_2.c \
					select_paths_1.c select_paths_2.c select_paths_3.c \
					instruction_1.c instruction_2.c memory_1.c memory_2.c \
					output.c \
					algorithm_ford_fulkerson1.c algorithm_ford_fulkerson2_1.c \
					algorithm_ford_fulkerson2_2.c \
					algorithm_ford_fulkerson3_1.c \
					algorithm_ford_fulkerson3_2.c \
					algorithm_ford_fulkerson4.c \
					algorithm_ford_fulkerson5.c \
					algorithm_ford_fulkerson6.c \
					breadth_first_search.c \
					depth_first_search_1.c depth_first_search_2.c \
					algorithm_depth_first_search1.c \
					path_1.c path_2.c

OBJ_FOLDER		=	obj
OBJ_FILES		=	$(addprefix $(OBJ_FOLDER)/, \
					$(patsubst %.c, %.o, $(SRC_FILES)))

all: $(LIBFT) $(LIBFT_PRINTF) $(NAME) $(NAME_2)

$(NAME): $(OBJ_FILES) $(MAIN_SRC) $(HEADER) | $(OBJ_FOLDER)
	@$(CC) $(C_FLAGS) -o $(NAME) $(MAIN_SRC) $(OBJ_FILES) $(INCLUDES) $(LIB)

$(NAME_2): $(OBJ_FILES) $(MAIN_2_SRC) $(HEADER) | $(OBJ_FOLDER)
	@$(CC) $(C_FLAGS) -o $(NAME_2) $(MAIN_2_SRC) $(OBJ_FILES) $(INCLUDES) $(LIB)

$(OBJ_FILES): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER) | $(OBJ_FOLDER)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(LIBFT):
	make -C ${LIBFT_FOLDER}

$(LIBFT_PRINTF):
	make -C ${LIBFT_PRINTF_FOLDER}

norm:
	norminette $(MAIN_SRC) $(HEADER) $(SRC_FOLDER)

clean:
	make -C ${LIBFT_FOLDER} clean
	make -C ${LIBFT_PRINTF_FOLDER} clean
	@\rm -rf $(NAME).dSYM
	@\rm -rf $(OBJ_FOLDER)/*.o

fclean: clean
	make -C ${LIBFT_FOLDER} fclean
	make -C ${LIBFT_PRINTF_FOLDER} fclean
	@\rm -rf $(NAME)
	@\rm -rf $(NAME_2)

re: fclean all

.PHONY: all clean fclean re norm
