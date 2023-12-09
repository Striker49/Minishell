# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seroy <seroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 16:06:24 by Juan              #+#    #+#              #
#    Updated: 2023/11/22 15:22:22 by seroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- PROGRAM NAME ---#

NAME        =   libft.a

#--- COMMAND VARIABLES ---#

CC          =   gcc

CFLAGS      =   -Wall -Wextra -Werror -O3 -g

AR          =   ar rcs

MK          =   mkdir -p

RM          =   rm -rf

#--- COLORS ---#

GREEN       =   \033[0;32m

RED         =   \033[0;31m

WHITE       =   \033[0m

#--- SOURCE DIRECTORIES ---#

INCDIR      =   inc

SRCDIR      =   src

#--- BINARY OBJECTS DIRECTORY ---#

BINDIR      = bin

# Extract object file names without paths
BIN         = $(notdir $(OBJ_PATHS))

#--- SUBDIRECTORIES ---#

GC_COLLECTOR    =   garbage_collector
GNL             =	get_next_line

#--- SOURCES FILES ---#

SRCS            =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_issymbol.c ft_issign.c ft_isprint.c ft_isspace.c \
        ft_strlen.c ft_count_table.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strcpy.c ft_strlcpy.c \
        ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strcmp.c ft_strrchr.c ft_strncmp.c \
        ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_atol.c ft_atof.c ft_atof_utils.c ft_substr.c ft_strjoin.c \
        ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
        ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_calloc.c \
        ft_strdup.c ft_strnew.c ft_strappend.c ft_free_table.c ft_strfree.c ft_strsfree.c ft_lstnew.c \
        ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
        ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_strpush.c get_next_line.c \
		garbage_collector.c ft_gc_split.c ft_gc_strjoin.c ft_gc_strdup.c ft_gc_strndup.c ft_gc_substr.c ft_gc_table_dup.c ft_gc_strfree.c \
        ft_gc_strnew.c ft_gc_strpush.c ft_gc_strappend.c 

OBJ_PATHS   = $(addprefix $(BINDIR)/, $(notdir $(SRCS:.c=.o)))

# VPATH for source files
VPATH       = $(SRCDIR) \
              $(SRCDIR)/$(GC_COLLECTOR) \
              $(SRCDIR)/$(GNL)


#--- RULES ---#

$(BINDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -I. -c $< -o $@
	@echo "$(GREEN)Compiling... $(WHITE) $(@F)"

all: $(NAME)

$(NAME): $(BINDIR) $(OBJ_PATHS)
	@$(AR) $(NAME) $(OBJ_PATHS)
	@echo "$(GREEN)Libft successfully created 📂$(WHITE)"

$(BINDIR):
	@$(MK) $(BINDIR)

clean:
	@$(RM) $(BINDIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)Libft object files and archive successfully removed 🗑$(WHITE)"

re: fclean all

.PHONY: all libft clean fclean re