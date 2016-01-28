/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperraul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:26:45 by aperraul          #+#    #+#             */
/*   Updated: 2016/01/28 15:22:02 by aperraul         ###   ########.fr       */
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

#include "debug.h"

static int				ft_last_line(char **text, int ret)
{
	int		i;
	char	*str;

	str = *text;
	ft_putstr("ret = ");
	ft_putnbr(ret);
	ft_putchar('\n');
	if (ret < BUFF_SIZE)
	{
		if (!str)
			return (0);
		if (str && (!(ft_strchr(str, '\n'))))
		{
			ft_memdel((void **)&str);
			ft_putstr("SORTIE 1\n");
			return (0);
		}
		else
		{
			i = 0;
			while (str[i] && str[i] != '\n')
				i++;
			if (str[i] == '\0')
			{
				ft_memdel((void **)&str);
				ft_putstr("SORTIE 2\n");
				return (0);
			}
			else
			{
				ft_putstr("SORTIE 3\n");
				return (1);
			}
		}
	}
	else
	{
		if ((int)ft_strlen(str) > 0)
		{
			ft_putstr("SORTIE 4\n");
			return (1);
		}
		else
		{
			ft_putstr("SORTIE 5\n");
			ft_memdel((void **)&str);
			return (0);
		}
	}
}

int				get_next_line(const int fd, char **line)
{
	static char	*text = NULL;
	char		*buff;
	char		*temp;
	int			ret;

	if ((ret = 1) && (!(buff = ft_strnew(BUFF_SIZE + 1))))
		return (-1);
	if (!(text))
	{
		if (!(text = ft_strnew(1)))
			return (-1);
	}
	while (!(ft_strchr(text, '\n')) && ret > 0)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		buff[ret] = 0;
		temp = text;
		text = ft_strjoin(text, buff);
		ft_memdel((void **)&temp);
	}
	ft_memdel((void **)&buff);
	*line = ft_get_line(text);
	text = ft_other_lines(text);
	return (ft_last_line(&text, ret) == 0 ? 0 : 1);
}
