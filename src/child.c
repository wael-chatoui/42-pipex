/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 01:30:00 by wael              #+#    #+#             */
/*   Updated: 2025/12/09 15:03:45 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static char	*get_command(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static char	**find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (ft_split(*envp + 5, ':'));
}

void	execute(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;
	char	**paths;

	cmd_args = ft_split(cmd, ' ');
	paths = find_path(envp);
	cmd_path = get_command(paths, cmd_args[0]);
	if (!cmd_path)
	{
		cmd_path = ft_strdup(cmd_args[0]);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		if (cmd_path)
			free(cmd_path);
		if (paths)
			free_parent(paths);
		if (cmd_args)
			free_parent(cmd_args);
		exit_handler(127);
	}
}
