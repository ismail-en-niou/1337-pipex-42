NAME = pipex
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
CYAN = \033[0;36m
RESET = \033[0m

SRC_DIR = ./src
SRC_DIR_BONUS = ./src_bonus
MAIN = main.c
MAIN_BONUS = main_bonus.c
BONUS_FLAG = .-
MANDATORY_FLAG = ._

SRC = ./src/ft_memcpy.c ./src/ft_split.c \
./src/ft_strjoin.c ./src/ft_strlcpy.c \
./src/ft_strncmp.c ./src/ft_strtrim.c \
./src/handels.c ./src/split_2.c \
./src/ft_putstr_fd.c ./src/ft_strdup.c \
./src/ft_strlcat.c ./src/ft_strlen.c \
./src/ft_strnstr.c ./src/ft_substr.c \
./src/logic.c ./src/token.c

SRC_BONUS = ./src_bonus/ft_memcpy_bonus.c ./src_bonus/ft_split_bonus.c \
./src_bonus/ft_strjoin_bonus.c ./src_bonus/ft_strlcpy_bonus.c \
./src_bonus/ft_strncmp_bonus.c ./src_bonus/ft_strtrim_bonus.c \
./src_bonus/handels_bonus.c ./src_bonus/split_2_bonus.c\
./src_bonus/ft_putstr_fd_bonus.c ./src_bonus/ft_strdup_bonus.c \
./src_bonus/ft_strlcat_bonus.c ./src_bonus/ft_strlen_bonus.c \
./src_bonus/ft_strnstr_bonus.c ./src_bonus/ft_substr_bonus.c \
./src_bonus/logic_bonus.c ./src_bonus/token_bonus.c\
./src_bonus/ft_itoa_bonus.c ./getline/get_next_line_bonus.c \
./getline/get_next_line_utils_bonus.c ./src_bonus/here_doc_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(MANDATORY_FLAG)

$(MANDATORY_FLAG): $(OBJ) $(MAIN)
	@$(RM) $(BONUS_FLAG)
	@$(CC) $(FLAGS) $(OBJ) $(MAIN) -o $(NAME)
	@touch $(MANDATORY_FLAG)
	@echo "$(GREEN)Mandatory compilation successful!$(RESET)"

bonus: $(BONUS_FLAG)

$(BONUS_FLAG): $(OBJ_BONUS) $(MAIN_BONUS)
	@$(RM) $(MANDATORY_FLAG)
	@$(CC) $(FLAGS) $(OBJ_BONUS) $(MAIN_BONUS) -o $(NAME)
	@touch $(BONUS_FLAG)
	@echo "$(GREEN)Bonus compilation successful!$(RESET)"

%.o: %.c ./src/pipe.h ./src_bonus/pipe_bonus.h ./getline/get_next_line_bonus.h
	$(CC) $(FLAGS) -c $< -o $@
	clear

clean:
	@$(RM) $(SRC_DIR)/*.o $(SRC_DIR_BONUS)/*.o ./getline/*.o
	@$(RM) $(BONUS_FLAG) $(MANDATORY_FLAG)
	@echo "$(YELLOW)Object files removed.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Executable removed.$(RESET)"

re: fclean all
	@echo "$(CYAN)Rebuilding everything...$(RESET)"

.PHONY: all clean fclean re bonus