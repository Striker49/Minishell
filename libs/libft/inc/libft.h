/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:11:05 by Juan              #+#    #+#             */
/*   Updated: 2023/12/02 14:10:41 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*--- HEADER FILE NAME ---*/

# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* DEFINES */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

/* DATA STRUCTURES */

typedef struct s_struct
{
	int		reads;
	char	*buf;
	char	*line;
}				t_struct;

typedef struct s_list
{
	void						*content;
	struct s_list				*next;
}								t_list;

typedef struct s_string
{
	char						*buffer;
	size_t						len;
	size_t						cap;
}								t_string;

typedef struct s_atof
{
	size_t						i;
	int							n;
	long double					r;
	int							has_decimal;
	int							decimal_digits;
}								t_atof;

typedef struct s_memory_addresses
{
	void						*data;
	struct s_memory_addresses	*next;

}								t_memory_addresses;

typedef struct s_garbage_collector
{
	t_memory_addresses			*head;

}								t_garbage_collector;

char							*ft_strchr(const char *s, int c);
char							*ft_strrchr(const char *s, int c);
char							*ft_strdup(const char *str);
char							*ft_strnstr(const char *haystack,
									const char *needle,
									size_t len);
char							*ft_substr(char const *s, unsigned int start,
									size_t len);
char							*ft_strjoin(char const *s1, char const *s2);
char							*ft_strtrim(char const *s1, char const *set);
char							**ft_split(char const *s, char c);
char							*ft_itoa(int n);
char							*ft_strmapi(char const *s,
									char (*f)(unsigned int, char));
char							**ft_free_table(char **tab);
int								ft_strcmp(char *s1, char *s2);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
int								ft_isalpha(int c);
int								ft_isdigit(int c);
int								ft_isalnum(int c);
int								ft_isascii(int c);
int								ft_isprint(int c);
int								ft_isspace(int c);
int								ft_issign(int c);
int								ft_issymbol(int c);
int								ft_toupper(int c);
int								ft_tolower(int c);
int								ft_atoi(const char *str);
long							ft_atol(const char *str);
double							ft_atof(const char *str);

void							ft_init_vars(t_atof *vars);
void							ft_limits(t_atof *vars);
void							ft_parse_integer(t_atof *vars, const char *str);
void							ft_sign_handler(t_atof *vars, const char *str);
void							ft_is_decimal(t_atof *vars, const char *str);

int								ft_lstsize(t_list *lst);
int								ft_memcmp(const void *s1, const void *s2,
									size_t n);
void							*ft_memset(void *b, int c, size_t len);
void							*ft_memcpy(void *dst, const void *src,
									size_t n);
void							*ft_memchr(const void *s, int c, size_t n);
void							*ft_memmove(void *dst, const void *src,
									size_t len);
void							ft_bzero(void *s, size_t n);
void							*ft_calloc(size_t count, size_t size);
void							ft_striteri(char *s, void (*f)(unsigned int,
										char *));
void							ft_putchar_fd(char c, int fd);
void							ft_putstr_fd(char *s, int fd);
void							ft_putendl_fd(char *s, int fd);
void							ft_putnbr_fd(int n, int fd);
void							ft_lstadd_front(t_list **lst, t_list *new);
void							ft_lstadd_back(t_list **lst, t_list *new);
void							ft_lstdelone(t_list *lst, void (*del)(void *));
void							ft_lstclear(t_list **lst, void (*del)(void *));
void							ft_lstiter(t_list *lst, void (*f)(void *));
void							ft_strfree(t_string *str);
size_t							ft_strlen(const char *str);
size_t							ft_count_table(char **table);
char							*ft_strcpy(char *s1, char *s2);
size_t							ft_strlcpy(char *dest, const char *src,
									size_t dstsize);
size_t							ft_strlcat(char *dest, const char *src,
									size_t size);
t_list							*ft_lstnew(void *content);
t_list							*ft_lstlast(t_list *lst);
t_list							*ft_lstmap(t_list *lst, void *(*f)(void *),
									void (*del)(void *));
t_string						*ft_strnew(t_string *dst, const char *str);
t_string						*ft_strappend(t_string *dst, const char *src);
t_string						*ft_strpush(t_string *dst, char src);
char							*get_next_line(int fd);
void							*gc_malloc(t_garbage_collector *gc,
									size_t size);
t_garbage_collector				*init_garbage_collector(void);
void							gc_collect_address(t_garbage_collector *gc,
									void *address);
void							gc_collect(t_garbage_collector *gc);
char							**ft_gc_split(t_garbage_collector *gc,
									char const *s,
									char c);
char							*ft_gc_substr(t_garbage_collector *gc,
									char const *s,
									unsigned int start,
									size_t len);
char							*ft_gc_strndup(t_garbage_collector *gc,
									const char *src,
									size_t n);
char							*ft_gc_strdup(t_garbage_collector *gc,
									const char *src);
char							**ft_gc_table_dup(t_garbage_collector *gc,
									char **table);
char							*ft_gc_strjoin(t_garbage_collector *gc,
									char const *s1,
									char const *s2);
t_string						*ft_gc_strpush(t_garbage_collector *gc,
									t_string *dst,
									char src);
t_string						*ft_gc_strnew(t_garbage_collector *gc,
									t_string *dst,
									const char *str);
t_string						*ft_gc_strappend(t_garbage_collector *gc,
									t_string *dst,
									const char *src);
void							ft_gc_strfree(t_garbage_collector *gc,
									t_string *str);

#endif
