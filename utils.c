#include<stdlib.h>
#include "get_next_line.h"

t_list *ft_lstnew(void *content)
{
	t_list *createme;

	createme = malloc(sizeof(t_list));
	if (!createme)
		return (NULL);
	createme->content = content;
	createme->next = NULL;
	return (createme);
}

void ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	del(lst->content);
	free(lst);
}

void ft_lstclear(t_list **lst, void (*del) (void *))
{

	if (*lst == NULL)
		return ;
	ft_lstclear(&(*lst) -> next, del);
	ft_lstdelone(*lst, del);
	*lst = NULL;
}

void *ft_malloc_errcode(size_t nbytes, int *errcode)
{
	void	*p;

	p = malloc(nbytes);
	if (!p)
		*errcode = -1;
	return (p);
}

char *ft_us_streamcpy(char *dest, char const *src)
{
	while (*src)
	{
		*(dest++) = *(src++);
	}
	*dest = '\0';
	return (dest);
}
