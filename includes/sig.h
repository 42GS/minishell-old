/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:34:16 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/17 18:29:03 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

void	init_signals(void);
void	set_heredoc_child_signal(void);
void	set_heredoc_signals(void);
void	restore_signals(void);

#endif
