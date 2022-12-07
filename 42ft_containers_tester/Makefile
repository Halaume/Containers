# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdetune <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 19:47:28 by bdetune           #+#    #+#              #
#    Updated: 2022/11/28 13:10:33 by bdetune          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FT = test_ft

STD = test_std

SRC = main_benchmark.cpp

INC = vector.hpp stack.hpp

OBJ = $(SRC:.cpp=.o)

PREC = 1

CXX = g++

CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -O3 -g -std=c++98

all: $(FT) $(STD)
.PHONY: all

$(FT): $(SRC) $(INC)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=ft -DPREC=$(PREC) $(SRC) -o $@
	
$(STD): $(SRC) $(INC)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=std -DPREC=$(PREC) $(SRC) -o $@

$(OBJ): $(INC)

$(SRC): $(INC)

clean:
	rm -rf $(OBJ) ft.log std.log
.PHONY: clean

fclean: clean
	rm -rf $(FT) $(STD)
.PHONY: fclean

test: $(FT) $(STD)
	sh test.sh
.PHONY: test

re: fclean all
.PHONY: re

.SECONDARY : $(OBJ)
