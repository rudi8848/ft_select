/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 10:43:52 by gvynogra          #+#    #+#             */
/*   Updated: 2018/06/07 10:45:26 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_select.h"

static void		ft_print_selected(t_dslist *lst)
{
	t_dslist *ptr;

	ptr = lst;
	ft_putstr_fd(CLEAR, STDERR_FILENO);
	if (ptr->modes & M_SLCT)
		ft_printf("%s ", ptr->name);
	ptr = ptr->next;
	while (ptr != lst)
	{
		if (ptr->modes & M_SLCT)
			ft_printf("%s ", ptr->name);
		ptr = ptr->next;
	}
	ft_putchar('\n');
}

static void		ft_move_h(t_dslist **ptr, uint64_t direction)
{
	(*ptr)->modes &= ~(M_CRSR);
	if (direction == K_RIGHT)
		(*ptr) = (*ptr)->next;
	else if (direction == K_LEFT)
		(*ptr) = (*ptr)->prev;
	(*ptr)->modes |= (M_CRSR);
}

static void		ft_move_v(t_dslist **ptr, uint64_t direction)
{
	t_printp	param;
	int			n;

	param = ft_get_params(g_attr.args);
	n = ft_count_elem(*ptr);
	(*ptr)->modes &= ~(M_CRSR);
	if (direction == K_DOWN)
	{
		(*ptr) = ft_get_nth((*ptr), param.cols % n);
	}
	else if (direction == K_UP)
	{
		(*ptr) = ft_get_nth((*ptr), n - param.cols);
	}
	(*ptr)->modes |= (M_CRSR);
}

static void		ft_delete_active(t_dslist **ptr)
{
	if ((*ptr) != g_attr.args)
	{
		(*ptr) = ft_del_elem((*ptr));
		(*ptr)->modes |= (M_CRSR);
	}
	else if ((*ptr) == g_attr.args && g_attr.args != g_attr.args->next)
	{
		(*ptr) = ft_del_elem((*ptr));
		(*ptr) = (*ptr)->next;
		g_attr.args = g_attr.args->next;
		(*ptr)->modes |= (M_CRSR);
	}
	else
	{
		ft_putstr_fd(CLEAR, STDERR_FILENO);
		ft_exit();
	}
}

void			ft_processing(void)
{
	int			rr;
	uint64_t	rb;
	t_dslist	*ptr;

	ptr = g_attr.args;
	rb = 0;
	ft_print_forward(ptr);
	while ((rr = read(STDIN_FILENO, &rb, 8)) > 0)
	{
		if (rb == K_RIGHT || rb == K_LEFT)
			ft_move_h(&ptr, rb);
		else if (rb == K_DOWN || rb == K_UP)
			ft_move_v(&ptr, rb);
		else if (rb == K_SPACE)
			ft_switch_mode(ptr, M_SLCT);
		else if (rb == K_DELETE || rb == K_BSPACE)
			ft_delete_active(&ptr);
		else if (rb == K_ENTER)
			return (ft_print_selected(g_attr.args));
		else if (rb == K_ESC)
			ft_exit();
		ft_print_forward(g_attr.args);
		rb = 0;
	}
}
