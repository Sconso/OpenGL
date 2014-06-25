#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sconso <sconso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/12 18:13:08 by sconso            #+#    #+#              #
#    Updated: 2014/06/24 19:58:07 by Myrkskog         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = tuto

CC = g++
CFLAGS = -Wall -Werror -Wextra -Wno-deprecated -Wno-deprecated-declarations
DFLAGS = -pedantic -g -ggdb
INC = -I includes/
LFLAGS = -framework GLUT -framework OpenGL

FILES = src/main.cpp        \
        src/Game.cpp        \
        src/Player.cpp      \
        src/Resources.cpp   \
        src/Square.cpp      \
        src/Team.cpp        \
        src/tools.cpp       \
        src/ft_errors.cpp   \
        src/Render.cpp      \
        src/Camera.cpp

SRCDIR = src/

OBJ = $(patsubst src/%,obj/%,$(FILES:.cpp=.o))
OBJDIR = $(addsuffix .dir,$(OBJ))

all : $(OBJDIR) $(NAME) $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ) $(LFLAGS)
		@echo "\033[4;32m$@\033[0m created !"

obj/%.dir:
		@mkdir -p $(dir $@)

obj/%.o: src/%.cpp
		@$(CC) -o $@ -c $< $(CFLAGS) $(INC)

run : re
		@/usr/bin/clear
		@./$(NAME)

clean :
		@/bin/rm -rf obj a.out.dSYM
		@/bin/rm -f a.out
		@echo "\033[1;30mobj\033[0m removed !"

fclean : clean
		@/bin/rm -f $(NAME)
		@echo "\033[1;30m$(NAME)\033[0m removed !"

re : fclean all

debug : CFLAGS += $(DFLAGS)
debug : re

.PHONY : all clean fclean re
