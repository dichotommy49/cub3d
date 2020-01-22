NAME := cub3d
SRCDIR := ./
MLXDIR := ./mlx/
MLX := libmlx.a
SRC := main raycast vector img hooks parse
CC := gcc
CFLAGS := -Wall -Werror -Wextra
CFILES := $(addsuffix .c, $(SRC))
OBJECTS := $(addsuffix .o, $(SRC))

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(MAKE) -C $(MLXDIR) all
	cp $(MLXDIR)$(MLX) $(SRCDIR)
	$(CC) $(CFLAGS) -L. -lmlx -framework OpenGL -framework AppKit $(OBJECTS) -o $(NAME)
run :
	$(SRCDIR)$(NAME) ./maps/testmap1.cub

clean : 
	rm -f $(OBJECTS)
	$(MAKE) -C $(MLXDIR) clean

fclean : clean
	rm -f $(NAME) $(MLX)

re: fclean all

bonus : all

.PHONY : all clean fclean re bonus
