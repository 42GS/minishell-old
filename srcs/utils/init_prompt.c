/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:14:35 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/16 19:03:09 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

#include "utils.h"

char	*get_prompt(void)
{
	char	*prompt;
	char	*work_dir;
	char	*username;

	work_dir = getcwd(NULL, NULL);
	prompt = ft_strjoin( ":", work_dir);
	free(work_dir);
}
