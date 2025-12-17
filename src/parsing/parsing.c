#include "gnl/get_next_line.h"
#include <stdio.h>

typedef struct s_element
{
	int		f;
	int		c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}			t_element;


void	erroring(int n)
{
	perror("");
	// printf("Error: ");
	if (n == 1)
		printf("Can't open the file\n");
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	init_elements(t_element *elem)
{
	elem->f = -1;
	elem->c = -1;
	elem->no = NULL;
	elem->so = NULL;
	elem->we = NULL;
	elem->ea = NULL;
}

void	pars_color(t_element *elem, char *line)
{
	if (ft_strcmp("F", line))
	{
		
	}
}

int	reading_map(char *input)
{
	t_element	elem;
	int			fd;
	char		*line;

	init_elements(&elem);
	fd = open(input, O_RDONLY);
	if (fd < 0)
		return (perror(""), 1);
	line = get_next_line(fd);
	while (line)
	{
		if ((ft_strcmp("F", line) && elem.f == -1)
			|| (ft_strcmp("C", line) && elem.c == -1))
			pars_color(&elem, line);
		// else if (ft_strcmp("C", line) && elem.c == -1)
		// else if (ft_strcmp("NO", line) && !elem.no)
		// else if (ft_strcmp("SO", line) && !elem.so)
		// else if (ft_strcmp("WE", line) && !elem.we)
		// else if (ft_strcmp("EA", line) && !elem.ea)
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 2 || reading_map(av[1]))
		return (1);
	printf("good :)\n");
}