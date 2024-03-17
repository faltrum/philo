# Print PHILOSOPHER and author name
PHILO_MSG = PHILOSOPHER
AUTHOR_MSG = by oseivane "el calamidades"
MESSAGE_LEN = $$(($(shell echo $(PHILO_MSG) | wc -c) - 1))

PRINT_PHILO = @printf "$(VIOLET)%*s$(RESET)\n" $(MESSAGE_LEN) $(PHILO_MSG)
PRINT_AUTHOR = @echo "$(BLUE)$(AUTHOR_MSG)$(RESET)"

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
VIOLET = \033[0;35m
RESET = \033[0m

NAME = philo

SRC_DIR = src/

OBJ_DIR = obj/

INCLUDES_DIR = ./includes/*.h

INCLUDES = -I./includes

CFLAGS = -Werror -Wall -Wextra
OFLAGS = -g -fsanitize = address

OBJF = .cache_exists

SRC = 	main \
		printing \
		utils \
		init_check \
		threads \
		philoest

SOURCES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJECTS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all: print_message $(NAME)
	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

print_message:
	$(PRINT_PHILO)
	$(PRINT_AUTHOR)

$(NAME):	$(OBJECTS)
	@echo "$(YELLOW)Linking...$(RESET)"
	gcc $(CFLAGS) $(OBJECTS) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)Linked!$(RESET)✅"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES_DIR) | $(OBJF) 
			gcc $(CFLAGS) $(INCLUDES) -c $< -o $@
$(OBJF):
		@mkdir -p $(OBJ_DIR)
clean:
			rm -f $(OBJECTS)
	
fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re 