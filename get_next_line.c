#include <unistd.h>
#include <stdlib.h>

#define BUFFSIZE 10

typedef unsigned int uint;

#include <stdio.h>

char *get_next_line(int fd)
{
	static char buff[BUFFSIZE];
	static uint ibuf = 0;
	uint iline = 0;
	char *line;
	int nread;

	line = malloc(10000);
	while (buff[ibuf] != '\n' && ibuf != (uint) nread)
	{
		if (ibuf == 0)
			nread = read(fd, buff, BUFFSIZE);
		line[iline] = buff[ibuf];
		//printf("char %u in buff : %c\n", ibuf, buff[ibuf]);
		++iline;
		ibuf = (ibuf + 1) % BUFFSIZE;
	}
	if (ibuf != (uint) nread)
		++ibuf;
	else if (iline == 0)
		return (NULL);
	line[iline] = '\n';
	line[iline + 1] = '\0';
	return (line);
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



