/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperraul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 16:02:49 by aperraul          #+#    #+#             */
/*   Updated: 2016/02/03 15:40:30 by aperraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int		k;
	int		fd;
	char	*line;
	int		state;
	int		temp;

	if (argc >= 2)
	k = 1;
	while (k < argc)
	{
		state = 1;
		fd = open(argv[k], O_RDONLY);
		while ((state = get_next_line(fd, &line) > 0))
		{
//			state = get_next_line(fd, &line); 
			printf("state : %d\n", state);
			printf("line : %s\n", line);
			temp = state;// La boucle s	'execute en fonction du retour de gnl.
			//state--;// la boucle for				ce 13 tours.
		}
		k++;
	}
	close(fd);
	return (0);
}
