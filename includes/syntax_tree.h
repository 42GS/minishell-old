/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:19:50 by yoshin            #+#    #+#             */
/*   Updated: 2025/07/15 21:36:12 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_TREE_H
# define SYNTAX_TREE_H

typedef enum e_syntax_node_type
{
	NODE_AND_IF,		// &&
	NODE_OR_IF,			// ||
	NODE_PIPE,			// |
	NODE_REDIR_IN,		// <
	NODE_REDIR_OUT		// >
}	t_syntax_node_type;

typedef struct s_syntax_node
{
	t_syntax_node_type		type;
	void					*value;
	struct s_syntax_node	*left;
	struct s_syntax_node	*right;
}	t_syntax_node;

typedef struct s_syntax_tree
{
	t_syntax_node	*root;
}	t_syntax_tree;

#endif
