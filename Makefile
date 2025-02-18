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
BONUS_FLAG = .b

SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_BONUS = $(wildcard $(SRC_DIR_BONUS)/*_bonus.c)

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)


all: $(NAME)

$(NAME): $(OBJ) $(MAIN)
	@$(CC) $(FLAGS) $(OBJ) $(MAIN) -o $(NAME)
	@echo "$(GREEN)Compilation successful!$(RESET)"

bonus: $(BONUS_FLAG)

$(BONUS_FLAG): $(OBJ_BONUS) $(MAIN_BONUS)
	@$(RM) $(NAME)
	@$(CC) $(FLAGS) $(OBJ_BONUS) $(MAIN_BONUS) -o $(NAME)
	@touch $(BONUS_FLAG)
	@echo "$(GREEN)Bonus compilation successful!$(RESET)"

%.o: %.c ./src/pipe.h ./src_bonus/pipe_bonus.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(SRC_DIR)/*.o $(SRC_DIR_BONUS)/*.o
	@$(RM) $(BONUS_FLAG)
	@echo "$(YELLOW)Object files removed.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Executable removed.$(RESET)"

re: fclean all
	@echo "$(CYAN)Rebuilding everything...$(RESET)"

.PHONY: all clean fclean re bonus
