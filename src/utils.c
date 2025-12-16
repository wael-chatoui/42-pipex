/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:18:38 by wael              #+#    #+#             */
/*   Updated: 2025/12/09 15:29:03 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("./pipex infile cmd1 cmd2 ... cmdN outfile\n", 2);
	else if (n_exit == 2)
		ft_putstr_fd("Error\n", 2);
	if (n_exit == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	free_parent(char **path)
{
	int	i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
