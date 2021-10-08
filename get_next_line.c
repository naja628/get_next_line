#include <unistd.h>
#include <stdlib.h>

#define BUFFSIZE 10

typedef unsigned int uint;

#include <stdio.h>

char *get_next_line(int fd)
{
	static char buff[BUFFSIZE];
	static uint ibuf = 0;
	uint line_sz;
	char *line_buf;
	t_list *line_parts;
	int nread;
	char guard;

	line_sz = 0;
	line_buf = &guard; // see (1)
	while (buff[ibuf] != '\n' && ibuf != (uint) nread)
	{
		if (ibuf == 0)
		{
			line_buf[line_sz++ % (BUFFSIZE + 1)] = '\0';
			ft_lstadd_front(&line_parts, ft_lstnew(line_buf));
			//TODO ext fst time (1) ^^^
			nread = read(fd, buff, BUFFSIZE);
			line_buf = malloc(BUFFSIZE + 1);
		}
		line[line_sz++ % (BUFFSIZE + 1)] = buff[ibuf++];
		ibuf %= BUFFSIZE;
	}
	if (ibuf != (uint) nread)
		line_parts[line_sz++ % (BUFFSIZE + 1)] = buff[ibuf++];
	line_buf[line_sz++ % (BUFFSIZE + 1)] = '\0';
	ft_lstadd_front(line_parts, ft_lstnew(line_buf));
	if (line_sz == 0)
		return (NULL);
	return (ft_merge_parts(line_parts, line_sz));
}

#include <fcntl.h>
#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 2)
		exit(-1);
	int fd = open(av[1], O_RDONLY);
	char *line;
	
	line = get_next_line(fd);
	int i = 0;
	while (line != NULL)
	{
		printf("line %d : %s\n", i++, line);
		line = get_next_line(fd);
		//printf("line %d : %s\n", i++, line);
	}
	return (0);
}
