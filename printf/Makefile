

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m


CC = cc
CFLAGS = -Wall -Wextra -Werror


NAME = tester
PRINTF_LIB = libftprintf.a


SRCS = ft_printf_tester.c
OBJS = $(SRCS:.c=.o)

# Main rules
all: $(NAME)

$(NAME): $(PRINTF_LIB) $(OBJS)
	@echo "$(YELLOW)Building tester...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L. -lftprintf -o $(NAME)
	@echo "$(GREEN)Tester built successfully!$(RESET)"

$(PRINTF_LIB):
	@echo "$(YELLOW)Building ft_printf library...$(RESET)"
	@$(MAKE) -C .. > /dev/null 2>&1
	@cp ../$(PRINTF_LIB) .
	@echo "$(GREEN)Library built successfully!$(RESET)"

# Test rules
test: $(NAME)
	@echo "$(YELLOW)Running mandatory tests...$(RESET)"
	@./$(NAME) mandatory

bonus_test: $(NAME)
	@echo "$(YELLOW)Running mandatory and bonus tests...$(RESET)"
	@./$(NAME) bonus

# Clean rules
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C .. clean > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Cleaning all generated files...$(RESET)"
	@rm -f $(NAME) $(PRINTF_LIB)
	@$(MAKE) -C .. fclean > /dev/null 2>&1

re: fclean all

# Additional rules
.PHONY: all clean fclean re test bonus_test

# Compilation rule
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
