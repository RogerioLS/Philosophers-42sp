# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 11:52:36 by codespace         #+#    #+#              #
#    Updated: 2024/09/27 23:43:23 by roglopes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= philo

SOURCES_DIR			= sources/
OBJECTS_DIR			= objects/

HEADERS				= -I ./includes/mandatory/ 

MAIN_DIR			= $(SOURCES_DIR)mandatory/

CFLAGS				= 

CFLAGS				= -pthread -Wall -Wextra -Werror #-fsanitize=address
CC					= gcc

VALGRIND_LOG		= valgrind.log

MAIN_SOURCES		= $(MAIN_DIR)dinner.c \
					$(MAIN_DIR)getters_setters.c \
					$(MAIN_DIR)init.c \
					$(MAIN_DIR)main.c \
					$(MAIN_DIR)monitor.c \
					$(MAIN_DIR)parsing_input.c \
					$(MAIN_DIR)safe_functions.c \
					$(MAIN_DIR)synchro_utils.c \
					$(MAIN_DIR)utils.c \
					$(MAIN_DIR)wirte.c

SOURCES				= $(MAIN_SOURCES)

OBJS				= $(patsubst $(SOURCES_DIR)%.c,$(OBJECTS_DIR)%.o, $(SOURCES))

COUNT				:= 0
RED					= \033[0;31m
GREEN				= \033[0;32m
MAGENTA				= \033[0;35m
RESET				= \033[0m
CYAN				= \033[36;1;3;208m
YELLOW				= \033[0;33m
COLOR_LIMITER		= "\033[0m"

all: create_objects_dir $(OBJECTS_DIR) $(NAME)

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(@D)
	@$(eval COUNT=$(shell expr $(COUNT) + 1))
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@printf "$(GREEN)Compiling Philosophers %d%%\r$(RESET)" $$(echo $$(($(COUNT) * 100 / $(words $(SOURCES_DIR)))))

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)

create_objects_dir:
	@mkdir -p $(OBJECTS_DIR)

clean:
	@rm -rf $(OBJECTS_DIR)
	@rm -rf $(VALGRIND_LOG)
	@printf "$(RED)Deleted objects Philosophers$(RESET)\n"

fclean: clean
	@echo "Cleaning all... 🧹"
	@rm -rf $(NAME)
	@printf "$(RED)Project is deleted Philosophers$(RESET)\n"
	@printf "$(RED)File valgrind.log deleted$(RESET)\n"
	@echo "✨ Cleaning complete! ✨"

norm:
	@norminette -R CheckForbiddenSource
	@echo "$(CYAN)NORMINETTE SUCESS $(RESET)"

valgrind:
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--log-file=$(VALGRIND_LOG) \
	./$(NAME) 5 800 200 200 7
	@cat $(VALGRIND_LOG)

re: fclean all
	@echo "$(BLUE) $(NAME) Cleaned and rebuilt everything!"

.PHONY: all clean fclean re norm create_objects_dir valgrind