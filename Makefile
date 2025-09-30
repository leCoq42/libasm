NAME := libasm.a

SRCS := ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJS := $(SRCS:.s=.o)

NASM := nasm
NASMFLAGS := -f elf64
CC := gcc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
AR := ar rcs

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	


.PHONY:
	all clean fclean re