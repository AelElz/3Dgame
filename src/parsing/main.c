#include "parsing.h"

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int check_the_file_extension(char *file)
{
	int i;

	i = ft_strlen(file);
	while (file[i] != '.')
		i--;
	if (ft_strcmp(&file[i], ".cub") && ft_strlen(&file[i]) == 4)
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	t_parsing *p;

	p = malloc (sizeof(t_parsing));
	if (ac != 2)
		exiting("Error: invalid arguments\n", p);
	if (check_the_file_extension(av[1]))
		exiting("Error: invalid file format\n", p);
	p->file = read_file(av[1]);
	if (!p->file)
		exiting("Error: failed to read file\n", p);
	main_parsing(p);

	// print_parsed_elements(p);
	// check_elements_rules(p);
	// check_map_rules(p);
	exiting(NULL, p);
	return (0);
}
