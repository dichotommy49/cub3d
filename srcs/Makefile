NAME := cub3d
SRCDIR := ./srcs/
MLXDIR := ./mlx/
MLX := libmlx.a
LIBFTDIR := ./libft/
LIBFT := libft.a
SRC := main raycast vector img hooks parse tools core
CC := gcc
CFLAGS := -Wall -Werror -Wextra 
CFILES := $(addprefix $(SRCDIR), $(addsuffix .c, $(SRC)))
OBJECTS := $(addprefix $(SRCDIR), $(addsuffix .o, $(SRC)))

all : $(NAME)

%.c : %.o


$(NAME) : $(OBJECTS)
	$(MAKE) -C $(MLXDIR) all
	$(MAKE) -C $(LIBFTDIR) all
	mv $(MLXDIR)$(MLX) ./
	mv $(LIBFTDIR)$(LIBFT) ./
	$(CC) $(CFLAGS) -L. -lmlx -lft -framework OpenGL -framework AppKit $(OBJECTS) -o $(NAME)
run :
	./$(NAME) ./maps/testmap0.cub

clean : 
	rm -f $(OBJECTS)
	$(MAKE) -C $(MLXDIR) clean
	$(MAKE) -C $(LIBFTDIR) clean

fclean : clean
	rm -f $(NAME) $(MLX) $(LIBFT)

re: fclean all

bonus : all

.PHONY : all clean fclean re bonus
