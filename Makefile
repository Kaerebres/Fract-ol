# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csimon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/14 12:36:13 by csimon            #+#    #+#              #
#    Updated: 2017/05/14 12:36:15 by csimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractolc
NAMECU = fractol
SRC = main.c parser.c julia.c generic.c bship.c mandalgo.c arrow.c
SRC2 = ship2.c mandalgo2.c julia2.c main.c parser.c generics.c arrow2.c shroom.c
SRCU = ship3.cu  mandalgo3.cu julia3.cu arrow3.cu shroom.cu
OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJCU = $(SRCU:.cu=.o)

all: $(NAMECU)

nocuda: $(NAME)

$(NAMECU): $(SRCU) $(SRC2)
	cd libft && make
	cd minilibx_macos && make
	/Developer/NVIDIA/CUDA-9.0/bin/nvcc -o $(NAMECU) -gencode=arch=compute_30,code=sm_30 $(SRCU) $(SRC2) libft/libft.a minilibx_macos/libmlx.a -Xcompiler "-framework OpenGL -framework AppKit"

$(NAME): $(SRC)
	cd libft && make
	cd minilibx_macos && make
	cc -o $(NAME) $(SRC) libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit 

clean:
	$(MAKE) -C libft/ clean
	$(MAKE) -C minilibx_macos/ clean
	rm -rf $(OBJCU)
	rm -rf $(OBJ2)

cleanc:
	$(MAKE) -C libft/ clean
	$(MAKE) -C minilibx_macos/ clean
	rm -rf $(OBJ)

fcleanc: clean
	$(MAKE) -C libft/ fclean
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAMECU)

rec: fcleanc nocuda

re: fclean all
