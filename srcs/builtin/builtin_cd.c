/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyoo < jyoo@student.42gyeongsan.kr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:10:09 by jyoo              #+#    #+#             */
/*   Updated: 2025/07/22 22:55:24 by jyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "minishell.h"
#include "tokenizer.h"

void	cd(t_toke)
{
	char	cwd[1024];

	if (chdir(path) != 0)
		perror ();
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf ("Current working directory: %s\n", cwd);
	else
		perror ();
}
