/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperraul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 16:02:49 by aperraul          #+#    #+#             */
/*   Updated: 2016/01/22 16:09:30 by aperraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		state;
	int		temp;

	state = 1;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	while (state > 0)
	{
		state = get_next_line(fd, &line); 
		printf("state : %d\n", state);
		printf("line : %s\n", line);
		temp = state;// La boucle s	'execute en fonction du retour de gnl.
		//state--;// la boucle for				ce 13 tours.
	}
	close(fd);
	return (0);
}
