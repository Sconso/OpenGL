#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sconso <sconso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/12 18:13:08 by sconso            #+#    #+#              #
#    Updated: 2014/06/17 20:17:11 by sconso           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = tuto

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wno-deprecated -Wno-deprecated-declarations
DFLAGS = -pedantic -g -ggdb
INC = -I includes/ -I libft/includes
LFLAGS = -L libft -lft -framework GLUT -framework OpenGL

FILES = src/main.c

SRCDIR = src/

OBJ = $(patsubst src/%,obj/%,$(FILES:.c=.o))
OBJDIR = $(addsuffix .dir,$(OBJ))

all : lib $(OBJDIR) $(NAME) $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ) $(LFLAGS)
		@echo "\033[4;32m$@\033[0m created !"

obj/%.dir:
		@mkdir -p $(dir $@)

obj/%.o: src/%.c
		@$(CC) -o $@ -c $< $(CFLAGS) $(INC)

run : re
		@/usr/bin/clear
		@./$(NAME)

clean : libclean
		@/bin/rm -rf obj a.out.dSYM
		@/bin/rm -f a.out
		@echo "\033[1;30mobj\033[0m removed !"

fclean : clean libfclean
		@/bin/rm -f $(NAME)
		@echo "\033[1;30m$(NAME)\033[0m removed !"

lib :
		@make -C libft all

libclean :
		@make -C libft clean

libfclean :
		@make -C libft fclean

libre :
		@make -C libft re
		@make re

re : fclean all

debug : CFLAGS += $(DFLAGS)
debug : re

.PHONY : all clean fclean re
