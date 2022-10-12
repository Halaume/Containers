# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 12:52:11 by ghanquer          #+#    #+#              #
#    Updated: 2022/10/12 13:54:15 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Containers

vpath %.hpp ./inc/
vpath %.cpp ./src/

OBJ_DIR = 		obj

INC =			$(addsuffix .hpp, stack vector map rbTree set)

SRC =			$(SRC_FT:%=./%.cpp)

OBJ =			$(SRC:./%.cpp=$(OBJ_DIR)/%.o)

OBJ_DIRS =		$(OBJ_DIR)

CC = c++ $(CFLAGS)

RM = rm -fr

CFLAGS = -Wall -Wextra -Werror -Wshadow -Wconversion -g -std=c++98

.cpp.o:
	$(CC) -c $< -o $(<:.cpp=.o)

#HOW TO LIST .cpp
#	ls -l | awk '{print $9}' | grep -E ".cpp$"| sed "s/\.cpp/ \\\/g" | sed '$s/\\$//g'

SRC_FT = main \

all: $(NAME)

$(OBJ) : $(INC) | $(OBJ_DIR)

$(OBJ_DIRS):
	mkdir -p $@

$(OBJ_DIR)/%.o: ./%.cpp
	$(CC) -c $< -o $@

$(NAME): $(OBJ_DIRS) $(SRC) $(OBJ)
	$(CC) $(OBJ) -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "Cleaned object"

fclean: clean
	@$(RM) $(NAME)
	@echo "Cleaned program"

re: fclean all

define print_aligned_coffee
    @t=$(NAME); \
	l=$${#t};\
	i=$$((8 - l / 2));\
	echo "             \0033[1;32m\033[3C\033[$${i}CAnd Your program \"$(NAME)\" "
endef

coffee: all clean
	@echo ""
	@echo "                                {"
	@echo "                             {   }"
	@echo "                              }\0033[1;34m_\0033[1;37m{ \0033[1;34m__\0033[1;37m{"
	@echo "                           \0033[1;34m.-\0033[1;37m{   }   }\0033[1;34m-."
	@echo "                          \0033[1;34m(   \0033[1;37m}     {   \0033[1;34m)"
	@echo "                          \0033[1;34m| -.._____..- |"
	@echo "                          |             ;--."
	@echo "                          |            (__  \ "
	@echo "                          |             | )  )"
	@echo "                          |   \0033[1;96mCOFFEE \0033[1;34m   |/  / "
	@echo "                          |             /  / "
	@echo "                          |            (  / "
	@echo "                          \             | "
	@echo "                            -.._____..- "
	@echo ""
	@echo ""
	@echo "\0033[1;32m\033[3C                    Take Your Coffee"
	$(call print_aligned_coffee)

.SECONDARY: $(OBJ) $(OBJ_DIR)
.PHONY: all clean fclean re coffee
