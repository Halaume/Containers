# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdetune <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 19:47:28 by bdetune           #+#    #+#              #
#    Updated: 2022/12/08 15:34:05 by bdetune          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all :			vector

vector :
				cd vector && ./start_tests.sh build


clean:			clean-vector

clean-vector:
				cd vector && ./start_tests.sh clean

fclean:			fclean-vector

fclean-vector:
				cd vector && ./start_tests.sh fclean

re:				re-vector

re-vector:
				cd vector && ./start_tests.sh re

test:			test-vector

test-vector:
				cd vector && ./start_tests.sh

.PHONY: all vector clean clean-vector fclean fclean-vector re re-vector test test-vector
