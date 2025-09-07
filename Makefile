# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baelgadi <baelgadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/01 01:41:33 by baelgadi          #+#    #+#              #
#    Updated: 2025/09/08 01:06:39 by baelgadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ─────────────────────────────────
#             🎨 COLORS
# ─────────────────────────────────

RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
GRAY = \033[90m
UNDERLINE = \033[4m

# ─────────────────────────────────
#         🛠️ CONFIGURATION
# ─────────────────────────────────

LIBFT = ./libft/libft.a

SRC_SERVER = server.c
SRC_CLIENT = client.c
SRC_SERVER_BONUS = server_bonus.c
SRC_CLIENT_BONUS = client_bonus.c

SERVER_EXE = server
CLIENT_EXE = client
SERVER_BONUS_EXE = server_bonus
CLIENT_BONUS_EXE = client_bonus

# ─────────────────────────────────
#      🚧 SETUP & DEPENDENCIES
# ─────────────────────────────────

SRCS = $(SRC_SERVER) $(SRC_CLIENT) $(SRC_SERVER_BONUS) $(SRC_CLIENT_BONUS)

OBJ_SERVER = ${SRC_SERVER:.c=.o}
OBJ_CLIENT = ${SRC_CLIENT:.c=.o}
OBJ_SERVER_BONUS = ${SRC_SERVER_BONUS:.c=.o}
OBJ_CLIENT_BONUS = ${SRC_CLIENT_BONUS:.c=.o}

OBJS = $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS)

DEPS = $(OBJS:.o=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./ -I ./libft/include -MMD -MP

# ─────────────────────────────────
#            🎯 TARGETS
# ─────────────────────────────────

all: $(SERVER_EXE) $(CLIENT_EXE)

# ─────────────────────────────────
#        💽 COMPILATION RULES
# ─────────────────────────────────

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -s -C ./libft

$(SERVER_EXE): $(OBJ_SERVER) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@ && printf "$(GREEN)✅ $@ created\n" || printf "$(RED) ❌ $@\n"

$(CLIENT_EXE): $(OBJ_CLIENT) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@ && printf "$(GREEN)✅ $@ created\n" || printf "$(RED) ❌ $@\n"

# ─────────────────────────────────
#            🧹 CLEANING
# ─────────────────────────────────

clean:
	@make -s -C ./libft clean
	@rm -f $(OBJS) $(DEPS)
	@echo "$(YELLOW)🧹 Minitalk objects and dependencies deleted (clean)$(RESET)"

fclean:
	@make -s -C ./libft fclean
	@rm -f $(OBJS) $(DEPS)
	@echo "$(YELLOW)🧹 Minitalk objects and dependencies deleted (clean)$(RESET)"
	@rm -f $(SERVER_EXE) $(CLIENT_EXE) $(SERVER_BONUS_EXE) $(CLIENT_BONUS_EXE)
	@echo "$(RED)❌ All files removed (fclean)$(RESET)"

re:	fclean all

# ─────────────────────────────────
#         🌐 HELP & FOOTER
# ─────────────────────────────────

help:
	@echo "$(BLUE)Available targets:$(RESET)"
	@echo "$(YELLOW)all      $(RESET)– Build server + client"
	@echo "$(YELLOW)bonus    $(RESET)– Build server + client (with bonus)"
	@echo "$(YELLOW)clean    $(RESET)– Delete .o and .d files"
	@echo "$(YELLOW)fclean   $(RESET)– Full clean"
	@echo "$(YELLOW)re       $(RESET)– fclean + all"

-include $(DEPS)

.PHONY: all clean fclean re bonus help
