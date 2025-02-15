NAME = pipex
CC = cc
FLAGS = -Wall -Werror -Wextra 

RM = rm -rf

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
CYAN = \033[0;36m
RESET = \033[0m

SRC_DIR = .
MAIN = main.c

BONUS_SRC = $(wildcard $(SRC_DIR)/*_bonus.c)
SRC = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
OBJ = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJ) $(MAIN)
	@$(CC) $(FLAGS) $(OBJ) $(MAIN) -o $(NAME)
	@echo "$(GREEN)Compilation successful!$(RESET)"

%.o: %.c pipe.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) *.o
	@echo "$(YELLOW)Object files removed.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Executable removed.$(RESET)"

re: fclean all
	@echo "$(CYAN)Rebuilding everything...$(RESET)"

bonus: $(BONUS_SRC:.c=.o)
	$(CC) $(FLAGS) $(BONUS_SRC:.c=.o) -o $(NAME)_bonus
	echo "$(GREEN)Bonus compilation successful!$(RESET)"

.PHONY: all clean fclean re bonus
