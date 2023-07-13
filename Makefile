# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 05:42:52 by tjukmong          #+#    #+#              #
#    Updated: 2023/07/14 00:28:54 by tjukmong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRCS		= philo.c utils.c utils2.c message.c threading.c basic_utils.c lib.c lib2.c

SRC_DIR		= ./
BUILD_DIR	= ./build/

SRC			= ${addprefix ${BUILD_DIR},${SRCS}}
OBJ			= ${SRC:.c=.o}

CC			= cc
CFLAGS		= -g -Wall -Werror -Wextra -O3

all: ${BUILD_DIR} ${NAME}

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f ${NAME}

re: fclean all

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}%.o:${SRC_DIR}%.c
	$(CC) $(CFLAGS) -c -o $@ $^

${NAME}: ${OBJ}
	$(CC) ${OBJ} -o ${NAME} $(CFLAGS)

.PHONY:	all library clean fclean re
