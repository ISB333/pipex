# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 09:53:02 by adesille          #+#    #+#              #
#    Updated: 2024/03/09 10:57:18 by isb3             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = libft.a
CFLAGS += -Wall -Wextra -Werror
CC = cc

######################## SOURCES ########################

SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c \
		ft_isascii.c ft_isprint.c ft_strlen.c \
		ft_memset.c  ft_bzero.c   ft_memcpy.c \
		ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c \
		ft_memcmp.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_atoi.c  ft_strnstr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_strmapi.c ft_striteri.c \
		ft_itoa.c

OBJDIR = obj
OBJS = ${SRCS:%.c=${OBJDIR}/%.o}

######################## RULES ########################

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling libft..."
	@ar rcs $(NAME) $(OBJS)

${OBJDIR}/%.o: %.c
	@mkdir -p ${@D}
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) -r $(OBJDIR) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
