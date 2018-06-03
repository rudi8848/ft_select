/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:06:24 by gvynogra          #+#    #+#             */
/*   Updated: 2018/06/02 10:06:37 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_stp_handler(int signum)
{
	;
}

void		ft_int_handler(int signum)
{
	;
}

void		ft_winch_handler(int signum)
{
	;
}

void		ft_count_handler(int signum)
{
	;
}

void		ft_set_signals(void)
{
	//	signal(SIGSTP, ft_stp_handler);	
		signal(SIGINT, ft_int_handler);	
		signal(SIGABRT, ft_int_handler);	
		signal(SIGQUIT, ft_int_handler);	
	//	signal(SIGCOUNT, ft_count_handler);	
		signal(SIGSTOP, ft_stp_handler);	
		signal(SIGWINCH, ft_winch_handler);	
		signal(SIGKILL, ft_int_handler);	
}
