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

void		ft_tstp_handler(int signum)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_attr.def_settings);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, SUSPEND);
}

void		ft_int_handler(int signum)
{
	ft_exit();
}

void		ft_winch_handler(int signum)
{
	ft_get_winsize();
	ft_putstr_fd(CLEAR, STDERR_FILENO);
	ft_print_forward(g_attr.args);
}

void		ft_cont_handler(int signum)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_attr.cur_settings);
	ft_set_signals();
	ft_putstr_fd(CLEAR, STDERR_FILENO);
	ft_print_forward(g_attr.args);
}

void		ft_set_signals(void)
{
		signal(SIGTSTP, ft_tstp_handler);
		signal(SIGCONT, ft_cont_handler);	
		signal(SIGINT, ft_int_handler);	
		signal(SIGTERM, ft_int_handler);	
		signal(SIGABRT, ft_int_handler);	
		signal(SIGQUIT, ft_int_handler);
		//signal(SIGSTOP, ft_stp_handler);	
		signal(SIGWINCH, ft_winch_handler);	
		//signal(SIGKILL, ft_int_handler);	
}
