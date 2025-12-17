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

static int	words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**freeing(char **m, int i)
{
	while (i-- > 0)
		free(m[i]);
	free(m);
	return (NULL);
}

static char const	*skip(char const *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**m;

	i = 0;
	if (!s)
		return (NULL);
	m = malloc(sizeof(char *) * (words(s, c) + 1));
	if (!m)
		return (NULL);
	while (*s)
	{
		len = 0;
		s = skip(s, c);
		if (*s == '\0')
			break ;
		while (s[len] != c && s[len])
			len++;
		m[i] = ft_substr(s, 0, len);
		if (m[i++] == NULL)
			return (freeing (m, i));
		s += len;
	}
	m[i] = NULL;
	return (m);
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

void	erroring(int n)
{
	perror("");
	// printf("Error: ");
	if (n == 1)
		printf("Can't open the file\n");
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

void	exctract_colors()
{
	char	**colors;

}
void	pars_color(t_element *elem, char *line)
{
	int	i;
	elem->f = 1;
	i = 0;
	while (line)
	{
		i++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		exctract_colors();
		printf("%s", &line[i]);
		break ;
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
		if ((*(line + 1) == ' ' || *(line + 1) == '\t')
			&& ((ft_strcmp("F", line) && elem.f == -1)
			|| (ft_strcmp("C", line) && elem.c == -1)))
			pars_color(&elem, line);
			// printf("good\n");
		// else if (ft_strcmp("NO", line) && !elem.no)
		// else if (ft_strcmp("SO", line) && !elem.so)
		// else if (ft_strcmp("WE", line) && !elem.we)
		// else if (ft_strcmp("EA", line) && !elem.ea)
		break ;
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 2 || reading_map(av[1]))
		return (1);
	// printf("good :)\n");
}