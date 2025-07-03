/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:37:04 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/04 00:37:19 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_space(char c)
{
	return (c == ' ');
}

int	ft_is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
