# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 16:43:49 by tmelvin           #+#    #+#              #
#    Updated: 2020/01/22 15:20:56 by tmelvin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
SRCDIR := ./
BONUSDIR := ./
SRC := ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove ft_memchr ft_memcmp ft_strlen ft_strlcpy ft_strlcat ft_strchr ft_strrchr ft_strnstr ft_strncmp ft_atoi ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_toupper ft_tolower ft_calloc ft_strdup ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_realloc ft_uitoa ft_convert_base ft_strrev ft_ultoa ft_lltoa ft_ulltoa ft_convert_base_unsigned ft_wcharlen ft_wstrlen ft_strcmp
BONUS_SRC := ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus
CFLAGS := -Wall -Wextra -Werror
OPTIONS := -c
CFILES := $(patsubst %, $(SRCDIR)%.c, $(SRC))
BONUS_CFILES := $(patsubst %, $(BONUSDIR)%.c, $(BONUS_SRC))
OBJECTS := $(patsubst %, $(SRCDIR)%.o, $(SRC))
BONUS_OBJECTS := $(patsubst %, $(BONUSDIR)%.o, $(BONUS_SRC))

all : $(NAME)

%.o : %.c
	gcc $(CFLAGS) $(OPTIONS) -o $@ $<
$(NAME) : $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)
clean :
	rm -f $(OBJECTS) $(BONUS_OBJECTS)
fclean : clean
	rm -f $(NAME)
re : fclean all

bonus : $(BONUS_OBJECTS)
	ar rc $(NAME) $(BONUS_OBJECTS)
	ranlib $(NAME)

.PHONY : all clean fclean re bonus
