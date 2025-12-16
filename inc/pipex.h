/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:34:31 by wael              #+#    #+#             */
/*   Updated: 2025/12/09 14:13:20 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "get_next_line.h"

void	exit_handler(int n_exit);
void	execute(char *cmd, char **envp);
void	free_parent(char **path);
int		get_here_doc(char *limiter);

#endif
