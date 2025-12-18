#include "parsing.h"

int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**read_file(char *file)
{
	char	**store_lines;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	store_lines = malloc((count_lines(file) + 1) * sizeof(char *));
	if (!store_lines)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		store_lines[i++] = line;
		// free(line);
		line = get_next_line(fd);
	}
	store_lines[i] = NULL;
	// if (line)
	// 	free(line);
	close(fd);
	return (store_lines);
}
