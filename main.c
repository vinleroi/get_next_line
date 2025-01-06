#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int fd = open("test", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	for (int i = 0; i < 8; ++i)
	{
		printf("===========\n");
		printf("%s", get_next_line(fd));
	}
	close(fd);
	return (0);
}