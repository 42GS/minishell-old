/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyoo < jyoo@student.42gyeongsan.kr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:37:07 by yoshin            #+#    #+#             */
/*   Updated: 2025/07/17 16:39:43 by jyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "tokenizer.h"
#include <unistd.h>

void	execute_pipline(t_token *tokens)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		outfile_fd;

	outfile_fd = -1;
	pipe(fd);
	if
}

int	execute(t_command *cmd)
{

}
