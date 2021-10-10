#ifndef GET_NEXT_LINE_H
 #define GET_NEXT_LINE_H
 
 #include <stddef.h>

typedef unsigned int uint;

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list; 

typedef struct s_line
{
	uint sz;
	char *buf;
	t_list *parts;
	t_list **tail;
} t_line;

char *get_next_line(int fd);
t_list *ft_lstnew(void *content);
void ft_lstclear(t_list **lst, void (*del) (void *));
void *ft_malloc_errcode(size_t nbytes, int *errcode);
char *ft_us_streamcpy(char *dest, char const *src);

#endif
