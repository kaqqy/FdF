# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jshi <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/21 09:52:26 by jshi              #+#    #+#              #
#    Updated: 2016/11/21 20:37:14 by jshi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIBFT_DIR = ./libft
PRINTF_DIR = ./ft_printf
HDR_DIR = ./includes
VPATH = $(LIBFT_DIR) $(PRINTF_DIR)

LIBFT_FUNC = memset bzero memcpy memccpy memmove memchr memcmp strlen \
				 strdup strcpy strncpy strcat strncat strlcat strchr strrchr \
				 strstr strnstr strcmp strncmp atoi isalpha isdigit isalnum \
				 isascii isprint toupper tolower memalloc memdel strnew strdel \
				 strclr striter striteri strmap strmapi strequ strnequ strsub \
				 strjoin strtrim strsplit itoa putchar putstr putendl putnbr \
				 putchar_fd putstr_fd putendl_fd putnbr_fd lstnew lstdelone \
				 lstdel lstadd lstiter lstmap numdiv isprime swap qsort sqrt \
				 ln primearr factorial strarrdel arrnew arradd ptrarrnew \
				 ptrarradd is_int
LIBFT_FILES = $(addprefix ft_,$(LIBFT_FUNC)) get_next_line
PRINTF_FILES = ft_printf parse_conversion ft_itoa_base concat utility wchar \
			   print_integer print_string print_char print_float get_float \
			   print_float_e print_float_g print_float_hex print_bonus \
			   print_color
SRC = $(addprefix $(LIBFT_DIR)/,$(addsuffix .c,$(LIBFT_FILES))) \
	  $(addprefix $(PRINTF_DIR)/,$(addsuffix .c,$(PRINTF_FILES)))

OBJ = $(addsuffix .o,$(LIBFT_FILES)) $(addsuffix .o,$(PRINTF_FILES))

CFLAGS = -Wall -Wextra -Werror


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -I$(HDR_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
