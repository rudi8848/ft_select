/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:25:15 by gvynogra          #+#    #+#             */
/*   Updated: 2018/06/07 11:29:16 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_select.h"

static void		ft_print_elem(t_dslist *ptr, int width)
{
	int i;

	i = ptr->len;
	ft_putstr_fd(ptr->color, STDERR_FILENO);
	if (ptr->modes & M_CRSR && ptr->modes & M_SLCT)
		ft_putstr_fd(S_SLCRS, STDERR_FILENO);
	else if (ptr->modes & M_CRSR)
		ft_putstr_fd(S_CRSR, STDERR_FILENO);
	else if (ptr->modes & M_SLCT)
		ft_putstr_fd(S_SLCT, STDERR_FILENO);
	ft_putstr_fd(ptr->name, STDERR_FILENO);
	ft_putstr_fd(S_NORM, STDERR_FILENO);
	while (i < width)
	{
		ft_putchar_fd(' ', STDERR_FILENO);
		i++;
	}
}

int				ft_count_elem(t_dslist *lst)
{
	t_dslist	*ptr;
	int			res;

	res = 1;
	ptr = lst->next;
	while (ptr != lst)
	{
		ptr = ptr->next;
		res++;
	}
	return (res);
}

t_printp		ft_get_params(t_dslist *lst)
{
	t_printp	res;

	res.total = ft_count_elem(lst);
	res.col_width = ft_maxlen(lst) + 1;
	res.cols = g_attr.width / res.col_width;
	if (!res.cols)
		res.cols = 1;
	return (res);
}

t_dslist		*ft_get_nth(t_dslist *head, int n)
{
	int			i;
	t_dslist	*ptr;

	i = 1;
	if (n == 0)
		return (head);
	ptr = head->next;
	while (i < n && ptr != head)
	{
		ptr = ptr->next;
		i++;
	}
	return (ptr);
}

void			ft_print_forward(t_dslist *lst)
{
	t_dslist	*ptr;
	t_printp	curp;
	int			i;
	int			j;

	ptr = lst;
	i = 0;
	curp = ft_get_params(lst);
	ft_putstr_fd(CLEAR, STDERR_FILENO);
	while (i < curp.total)
	{
		j = 0;
		while (j < curp.cols && i + j < curp.total)
		{
			if ((i + j) < curp.total)
			{
				ptr = ft_get_nth(lst, i + j);
				ft_print_elem(ptr, curp.col_width);
			}
			j++;
		}
		i += j;
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}
