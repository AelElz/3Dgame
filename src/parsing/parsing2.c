#include "parsing.h"

void freeing_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void exiting(char *msg, t_parsing *p)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (p)
	{
		if (p->first_six)
			freeing_arr(p->first_six);
		if (p->file)
			freeing_arr(p->file);
		if (p->map)
			freeing_arr(p->map);
		freeing_arr(p->elements_splited.f);
		freeing_arr(p->elements_splited.c);
		freeing_arr(p->elements_splited.no);
		freeing_arr(p->elements_splited.so);
		freeing_arr(p->elements_splited.we);
		freeing_arr(p->elements_splited.ea);
		free(p);
	}
	exit(1);
}

void	remove_newline(char *str)
{
	int	len;

	if (!str)
		return;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

int is_empty(char *str)
{
	int i;

	i = 0;

	if(str[0] == '\0')
		return 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == '\n')
		return (1);
	return (0);
}

int contain_two_parts(char *str)
{
	int i;
	int parts;

	i = 0;
	parts = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i] || str[i] == '\n')
			break;
		else if (str[i] != ' ' && str[i] != '\t')
			parts++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
	}
	if (parts != 2)
		return (0);
	return (1);
}