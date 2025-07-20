/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:32:07 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 19:32:10 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ctrl + C: SIGINT: exibe um novo prompt em uma nova linha, sai com o status 130.
//ctrl + \: encerra uma execução causando core dump, não imprimir ^\.
//ctrl + D: SIGQUIT: sai do shell se estiver vazio, sobre um texto ele deleta os char, serve como (DELETE), não altera o status de saida