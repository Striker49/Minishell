# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seroy <seroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 23:05:11 by jupallar          #+#    #+#              #
#    Updated: 2023/12/08 19:02:36 by seroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- PROGRAM NAME ---#

NAME	=	minishell

#--- COLORS ---#

RED		= \033[1;31m

GREEN	= \033[1;32m

BLUE	= \033[1;34m

YELLOW	= \033[1;33m

DARKGRAY= \033[1;30m

DEFAULT = \033[1;30m

#--- LIBRARIES AND HEADERS ---#

HEADER_FILES	=	minishell.h colors.h token.h print.h parsing.h syntax.h exec.h env.h

HEADERS			=	$(addprefix $(INCDIR)/, $(HEADER_FILES))

LIBFT			=	${LIBDIR}/libft

MAKELIB			=	${MAKE} -C ${LIBFT}

SLIB_LIBFT		=	${LIBFT}/libft.a

LIBRLINE 		=	readline-8.2

LIBRLINE_DIR 	=	./libs/readline/

RLPATH			=	./libs/readline/libreadline.a

#--- COMMAND VARIABLES ---#

CC		=	clang

CFLAGS 	=	-Wall -Wextra -Werror -g -std=c17 #-fsanitize=address
#-std=c89 si on doit utiliser une version antérieur à c17

RLFLAGS	=	-lreadline -lcurses

MK		=	mkdir -p

RM		=	rm -rf

#--- SOURCE, INCLUDE, LIBRARY AND BINARIES DIRECTORIES ---#

INCDIR	=	inc

LIBDIR	=	libs

SRCDIR	=	src

BINDIR	=	bin

#--- SOURCES ---#

SRCS	=	main.c parsing/expand.c parsing/expand_utils.c parsing/expand_utils2.c parsing/quotes.c\
			parsing/quotes_utils.c parsing/syntax.c parsing/syntax_utils.c\
			parsing/build_token.c parsing/tokenizer.c \
			parsing/tokenizer_utils.c parsing/token_handlers.c parsing/print.c builtins/env.c builtins/env2.c \
			builtins/export.c builtins/export_utils.c exec/env_utils.c initialisation/init_minishell.c \
			initialisation/init_data.c error/error.c \
			exec/exec.c exec/exec_utils.c exec/exec_utils2.c exec/exec_utils3.c exec/exec_utils4.c exec/exec_utils5.c exec/exec_utils6.c exec/exec_utils7.c exec/redir_utils.c exec/processes.c exec/redirections.c\
			exec/pipe.c exec/commands.c exec/heredoc.c exec/heredoc_utils.c exec/signals.c \
			builtins/cd.c builtins/echo.c builtins/pwd.c builtins/unset.c builtins/exit.c

SRC		=	$(addprefix $(SRCDIR)/, $(SRCS))

BIN     =	$(patsubst $(SRCDIR)%.c,bin/%.o,$(SRC))

#--- RULES ---#

bin/%.o		: $(SRCDIR)%.c  $(HEADERS)
	@mkdir -p $(@D)
	@echo "${DARKGRAY}Compiling : $(@F) ... ${DEFAULT}"
	@$(CC) $(CFLAGS) -c $< -o $@

all			: ${NAME}

${RLPATH}	:
	@echo "${BLUE}Building Readline directory ... ${DARKGRAY}"; \
		mkdir -p $(LIBRLINE_DIR); \
		echo "${BLUE}Downloading and extracting Readline library ... ${DARKGRAY}"; \
		curl -O https://ftp.gnu.org/gnu/readline/$(LIBRLINE).tar.gz > /dev/null 2>&1; \
		tar -xf $(LIBRLINE).tar.gz > /dev/null 2>&1; \
		rm -rf $(LIBRLINE).tar.gz; \
		echo "${BLUE}Configuring Readline files and paths ... ${DARKGRAY}"; \
		cd $(LIBRLINE) && ./configure --with-curses > /dev/null 2>&1 && make > /dev/null 2>&1;\
		mv ./libreadline.a ../libs/readline > /dev/null 2>&1; \
		mkdir ../libs/readline/inc > /dev/null 2>&1; \
		mv ./*.h ../libs/readline/inc > /dev/null 2>&1; \
		echo "${BLUE}Cleaning Readline directory ... ${DARKGRAY}"; \
		rm -rf ../$(LIBRLINE); \
		echo "${BLUE}Readline library successfully created 🗄${DEFAULT}";

${NAME}		:	${RLPATH} ${BIN}
	@${MAKELIB}
	@${CC} ${CFLAGS} ${BIN} ${RLFLAGS} -L${LIBRLINE_DIR} ${SLIB_LIBFT} -o ${NAME} 
	@echo "${GREEN}Minishell successfully created. 📂${DEFAULT}"

clean		:
	@${MAKELIB} clean
	@${RM} ${BINDIR}
	@echo "${YELLOW}Minishell binary files successfully removed 🗑${DEFAULT}"

fclean		:	clean
	@${MAKELIB} fclean
	@${RM} ${NAME}
	@echo "${RED}Minishell executable successfully removed 🗑${DEFAULT}"

re	 		:	fclean all

bonus		:	all

leaks		:	${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --suppressions=supp.txt ./minishell
#--- PHONY ---#
.PHONY	 	:	all clean fclean re readline norm bonus