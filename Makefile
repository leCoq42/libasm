NAME := libasm.a
ASM_SRC := ft_strlen.s ft_strcpy.s ft_strcmp.s #ft_write.s ft_read.s ft_strdup.s
SRC_DIR := src/
OBJ_DIR := obj/
OBJ := $(addprefix $(OBJ_DIR), $(ASM_SRC:.s=.o))
NASM := nasm
NASMFLAGS := -f elf64
CC := gcc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
AR := ar rcs
TEST_BIN := test.out

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.s
	@mkdir -p $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(TEST_BIN)

re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS) main.c -L. -lasm -o $(TEST_BIN)
	./$(TEST_BIN)

test_re: fclean test

.PHONY: all clean fclean re test test_re
