# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdetune <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 19:47:28 by bdetune           #+#    #+#              #
#    Updated: 2022/12/08 18:08:50 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VECTOR_LOCATION = ../..

NAME = 01.constructor
SRC = 01.constructor.cpp 

DEP = $(VECTOR_LOCATION)/vector.hpp
INC = ConstClass.hpp
SRC_DIR = srcs
INC_DIR = includes
OBJ_DIR = objs
BIN_DIR = bin

ISFT = 0

ifeq ($(ISFT), 0)
	NAMESPACE = std
else
	NAMESPACE = ft
endif

OBJS := $(SRC:%.cpp=$(OBJ_DIR)/%_$(NAMESPACE).o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -Wshadow -g -std=c++98


$(BIN_DIR)/$(NAME)_$(NAMESPACE): $(OBJS) $(INC_DIR)/$(INC) $(DEP)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

all: $(BIN_DIR)/$(NAME)_$(NAMESPACE)
.PHONY: all

$(OBJ_DIR)/%_$(NAMESPACE).o: $(SRC_DIR)/%.cpp
				$(CXX) $(CXXFLAGS)  -I$(VECTOR_LOCATION) -I$(INC_DIR) -D ISFT=$(ISFT) -c -o $@ $<

$(OBJS):	$(INC_DIR)/$(INC) $(DEP)

clean:
	rm -rf $(OBJS)
.PHONY: clean

fclean: clean
	rm -rf $(BIN_DIR)/$(NAME)_$(NAMESPACE)
.PHONY: fclean

re: fclean all
.PHONY: re

.SECONDARY : $(OBJS)
