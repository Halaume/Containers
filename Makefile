# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 12:52:11 by ghanquer          #+#    #+#              #
#    Updated: 2022/11/28 18:36:46 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT = Containers_ft
STD = Containers_std

vpath %.hpp ./inc/
vpath %.cpp ./src/

OBJ_DIR = 		obj_ft

OBJ_DIR_STD = 		obj_std

INC =			$(addsuffix .hpp, stack vector map rbTree set enable_if is_integral integral_constant lexicographical_compare pair Iterator_traits reverse_iterator remove_cv is_same)

SRC =			$(SRC_FT:%=./%.cpp)

OBJ =			$(SRC:./%.cpp=$(OBJ_DIR)/%.o)

OBJ_STD =			$(SRC:./%.cpp=$(OBJ_DIR_STD)/%.o)

OBJ_DIRS =		$(OBJ_DIR)

OBJ_DIRS_STD =	$(OBJ_DIR_STD)

CXX = c++ $(CXXFLAGS)

PREC = 1

RM = rm -fr

CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -O3 -g -std=c++98

.cpp.o:
	$(CXX) -c $< -o $(<:.cpp=.o)

#HOW TO LIST .cpp
#	ls -l | awk '{print $9}' | grep -E ".cpp$"| sed "s/\.cpp/ \\\/g" | sed '$s/\\$//g'

SRC_FT = main 
#		 vector_test \
#		 stack_test

all: $(STD) $(FT) 

$(OBJ) : $(INC) | $(OBJ_DIR)

$(OBJ_DIRS):
	mkdir -p $@

$(OBJ_DIR)/%.o: ./%.cpp
	$(CXX) -DNAMESPACE=ft -DPREC=$(PREC) -c $< -o $@

$(FT): $(OBJ_DIRS) $(SRC) $(OBJ)
	$(CXX) -DNAMESPACE=ft -DPREC=$(PREC) $(OBJ) -o $@

$(OBJ_STD) : $(INC) | $(OBJ_DIR_STD)

$(OBJ_DIRS_STD):
	mkdir -p $@

$(OBJ_DIR_STD)/%.o: ./%.cpp
	$(CXX) -DNAMESPACE=std -DPREC=$(PREC) -c $< -o $@

$(STD): $(OBJ_DIRS_STD) $(SRC) $(OBJ_STD)
	$(CXX) -DNAMESPACE=std -DPREC=$(PREC) $(OBJ_STD) -o $@

test: $(FT) $(STD)
	sh test.sh

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJ_DIR_STD)
	@$(RM) ft_output std_output ft_output_val std_output_val diff diff_val
	@echo "Cleaned object and outputs"

fclean: clean
	@$(RM) $(FT)
	@$(RM) $(STD)
	@$(RM) ft.log
	@$(RM) std.log
	@echo "Cleaned program"

re: fclean all

define print_aligned_coffee
    @t=$(FT); \
    @t=$(STD); \
	l=$${#t};\
	i=$$((8 - l / 2));\
	echo "             \0033[1;32m\033[3CXX\033[$${i}CXXAnd Your program Container "
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

.SECONDARY: $(OBJ) $(OBJ_DIR) $(OBJ_STD) $(OBJ_DIR_STD)

.PHONY: all clean fclean re coffee
