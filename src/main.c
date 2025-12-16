/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:33:09 by wael              #+#    #+#             */
/*   Updated: 2025/12/09 15:31:08 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdio.h>

void	child_loop(char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_handler(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_handler(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(cmd, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

static void	open_outfile(int ac, char **av, int *outfile)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		*outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
		exit_handler(EXIT_FAILURE);
}

static int	open_infile(int ac, char **av, int *i)
{
	int	infile;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		*i = 3;
		if (ac < 5)
			return (ft_putstr_fd("./pipex here_doc LIMITER cmd1 \
				... cmdN outfile\n", 2), -1);
		infile = get_here_doc(av[2]);
	}
	else
	{
		*i = 2;
		infile = open(av[1], O_RDONLY);
		if (infile < 0)
			exit_handler(EXIT_FAILURE);
	}
	return (infile);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		infile;
	int		outfile;

	if (ac < 5)
		return (ft_putstr_fd("./pipex infile cmd1 ... cmdN outfile\n", 2), 1);
	infile = open_infile(ac, av, &i);
	if (infile == -1)
		return (1);
	dup2(infile, STDIN_FILENO);
	close(infile);
	while (i < ac - 2)
		child_loop(av[i++], envp);
	open_outfile(ac, av, &outfile);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute(av[ac - 2], envp);
	return (EXIT_SUCCESS);
}
