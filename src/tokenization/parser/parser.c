/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:00:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This file serves as the main parser entry point.
 * Parser functionality is distributed across:
 * - parser_utils.c: Core parsing utilities
 * - utils/parser_pipes_utils.c: Pipe-specific parsing
 * 
 * Future parser enhancements (quotes, escapes, etc.) should be added here.
 */