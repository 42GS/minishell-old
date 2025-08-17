/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyoo < jyoo@student.42gyeongsan.kr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:13:41 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/18 03:05:12 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "def.h"

#include "libft.h"

#include "debug.h"

static void	read_input(char **input, const char *limiter);

char	*heredoc(const char *limiter)
{
	char	*input;

	debug("[heredoc] called");
	input = NULL;
	read_input(&input, limiter);
	debug("[heredoc] called");
	return (input);
}

static void	read_input(char **input, const char *limiter)
{
	char	*temp;
	char	*line;

	debug("[read_input] called !! - limiter : %s", limiter);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, limiter, ft_strlen(line) + 1) == 0)
			break ;
		temp = *input;
		if (temp)
		{
			*input = ft_strjoin(temp, line);
			free(temp);
		}
		else
			*input = ft_strdup(line);
		free(line);
		temp = *input;
		*input = ft_strjoin(temp, "\n");
		free(temp);
	}
	debug("[read_input] loop out !!");
}
