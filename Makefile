# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 13:22:58 by adesille          #+#    #+#              #
#    Updated: 2024/03/09 10:4 by isb3             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = pipex
CFLAGS += -g3
CC = cc

######################## SOURCES ########################

SRCS = pipex.c utils.c utils2.c
OBJDIR = 0_obj
OBJS = ${SRCS:%.c=${OBJDIR}/%.o}

GREEN = \033[0;92m
CURRENT_DATE	:= $(shell date +"%Y-%m-%d %H:%M:%S")

######################## LIBRARY ########################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

######################## RULES ########################

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${OBJDIR}/%.o: %.c
	@mkdir -p ${@D}
	@echo "Compiling $<..."
	@${CC} ${CFLAGS} -c $< -o $@

${LIBFT}:
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf ${OBJDIR} ${NAME}
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f ${NAME}

re: fclean all

git:
	@git add . > /dev/null 2>&1
	@git commit -m "$(CURRENT_DATE)" > /dev/null 2>&1
	@git push > /dev/null 2>&1
	@echo "$(GREEN)┌(メ▼▼)┘ GIT UPDATE └(▼▼メ)┐ $(DEF_COLOR)"

.PHONY: all clean fclean re git
