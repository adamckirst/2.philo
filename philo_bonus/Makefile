# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 14:48:48 by achien-k          #+#    #+#              #
#    Updated: 2023/09/22 19:33:56 by achien-k         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
LFLAGS		=	-lpthread -lrt
INC_DIR		=	includes
SRC_DIR		=	src
SRCS		=	general_fts inits think routines main monitoring
OBJ_DIR		=	bin
OBJ			=	$(foreach src, $(SRCS), $(OBJ_DIR)/$(src)_bonus.o)
VPATH		=	$(SRC_DIR) $(SUB_FOLDERS)

all: 			$(NAME)

$(OBJ_DIR):		
				mkdir $(OBJ_DIR)

$(NAME):		$(OBJ_DIR) $(OBJ) 
				$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

$(OBJ_DIR)/%.o:	%.c
				$(CC) $(CFLAGS) -o $@ -c $< -I$(INC_DIR)

leak:			$(OBJ_DIR) $(OBJ)
				$(CC) $(CFLAGS) -fsanitize=leak -o $(NAME) $(OBJ) $(LFLAGS) 

thread:			$(OBJ_DIR) $(OBJ)
				$(CC) $(CFLAGS) -fsanitize=thread -o $(NAME) $(OBJ) $(LFLAGS) 

clean:
				find . -type f -name "*.o" -delete
				[ -d bin ] && rmdir $(OBJ_DIR) || true

fclean:			clean
				rm -rf $(NAME) 
				rm -rf $(NAME_BONUS)

re:				fclean all

.PHONY:			clean fclean re
