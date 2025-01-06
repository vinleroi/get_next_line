#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);

int	main(void)
{
	int fd = open("test", O_RDONLY);
	for (int i = 0; i < 7; ++i)
	{
		printf("===========\n");
		printf("%s", get_next_line(fd));
	}
	close(fd);
	return (0);
}