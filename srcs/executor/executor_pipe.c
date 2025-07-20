/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyoo < jyoo@student.42gyeongsan.kr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:37:07 by yoshin            #+#    #+#             */
/*   Updated: 2025/07/20 16:14:45 by jyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "tokenizer.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

void	execute_pipline(t_token *tokens, int n_pipe)
{
	int		fd[2];
	pid_t	pid;
	int		outfile_fd;

	while (n_pipe-- > 0)
	{
		pid = fork();
		if (pid < 0)
		{
			perror();
			break ;
		}

	}
}

int	count_pipe(t_token *tokens)
{
	int	n;

	n = 0;
	while (tokens)
	{
		if (tokens->type == STR_PIPE)
			n++;
		tokens = tokens->next;
	}
	return (n);
}

int	execute(t_token *tokens)
{
	int	n_pipe;

	n_pipe = count_pipe(tokens);
	execute_pipline(tokens, n_pipe);
}
