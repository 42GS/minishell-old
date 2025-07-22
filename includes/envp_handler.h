/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyoo < jyoo@student.42gyeongsan.kr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:23:42 by jyoo              #+#    #+#             */
/*   Updated: 2025/07/20 20:31:17 by jyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_HANDLER_H
# define ENVP_HANDLER_H

typedef struct s_envps
{
	char			*value;
	struct s_envps	*prev;
	struct s_envps	*next;
}	t_envps;

#endif
