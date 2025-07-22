/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyoo < jyoo@student.42gyeongsan.kr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:31:32 by jyoo              #+#    #+#             */
/*   Updated: 2025/07/22 15:57:40 by jyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "envp_handler.h"

void	destory_envp(t_envps *envp_lst, t_envps *unset_envp)
{
	int		next_node;
	int		prev_node;
	t_envps	*temp_envp;

	if (!envp_lst || !unset_envp)
		exit ;
	while (envp_lst != unset_envp)
		envp_lst->next;
	temp_envp = unset_envp;
	envp_lst->next = next_node;
	envp_lst->prev = prev_node;
	envp_lst = envp_lst->prev;
	envp_lst->next = next_node;
	envp_lst = envp_lst->next;
	envp_lst->prev = prev_node;
	free(temp_envp->value);
	free(temp_envp);
}

void	insert_envp_to_lst(t_envps *envp_lst, t_envps *new_envp)
{
	int	temp;

	while (envp_lst->next)
		envp_lst = envp_lst->next;
	if (!envp_lst)
		envp_lst = new_envp;
	else
	{
		envp_lst = temp;
		new_envp->prev = temp;
		envp_lst->next = new_envp;
	}
}

t_envps	*creat_envp(char *envp)
{
	t_envps	*new_envp;
	int		len;
	int		i;

	len = 0;
	while (envp[len])
		len++;
	new_envp = (t_envps *) malloc(sizeof(t_envps));
	if (errno == ENOMEM)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	new_envp->value = (char *) malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		new_envp->value[i] = envp[i];
		i++;
	}
	return (new_envp);
}

t_envps	*creat_envp_lst(void)
{
	t_envps	*envp_lst;

	envp_lst = (t_envps *) malloc(sizeof(t_envps));
	if (errno == ENOMEM)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (envp_lst);
}

t_envps	envp_handler(char **envp)
{
	t_envps	*envp_lst;
	t_envps	*new_envp;
	int		i;

	envp_lst = creat_envp_lst();
	i = 0;
	while (!envp[i])
	{
		new_envp = creat_envp(envp[i]);
		insert_envp_to_lst(envp_lst, new_envp);
		i++;
	}
}
