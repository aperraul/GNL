/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperraul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:26:45 by aperraul          #+#    #+#             */
/*   Updated: 2016/03/12 15:24:15 by aperraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_strncpy(ft_strnew(i), str, i);
	line[i] = 0;
	return (line);
}

static char		*ft_other_lines(char *str)
{
	int		i;
	char	*other_lines;

	i = 0;
	other_lines = NULL;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	other_lines = ft_strdup(&str[i + 1]);
	if (i == (int)ft_strlen(str))
		ft_memdel((void **)&other_lines);
	ft_memdel((void **)&str);
	return (other_lines);
}

static int		ft_last_line(char **text, int ret)
{
	if (ret == 0 && !(*text))
	{
		ft_memdel((void **)*&text);
		return (0);
	}
	return (1);
}

static int		gnl_alloc(char **text, char **buff, int fd)
{
	if (fd < 0 || fd > 256)
		return (-1);
	if ((!(*buff = ft_strnew(BUFF_SIZE + 1))))
		return (-1);
	if (!(*text))
	{
		if (!(*text = ft_strnew(1)))
			return (-1);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*text[256] = {NULL};
	char		*buff;
	char		*temp;
	int			ret;

	if (((ret = 1) && gnl_alloc(&text[fd], &buff, fd) == -1) || line == NULL)
		return (-1);
	while (!(ft_strchr(text[fd], '\n')) && ret > 0)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		buff[ret] = 0;
		temp = text[fd];
		text[fd] = ft_strjoin(text[fd], buff);
		ft_memdel((void **)&temp);
	}
	ft_memdel((void **)&buff);
	*line = ft_get_line(text[fd]);
	text[fd] = ft_other_lines(text[fd]);
	if ((int)ft_strlen(*line))
		return (1);
	return (ft_last_line(&text[fd], ret) == 0 ? 0 : 1);
}
