/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 10:46:29 by gvynogra          #+#    #+#             */
/*   Updated: 2018/06/07 11:42:19 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_select.h"

void	ft_switch_mode(t_dslist *ptr, int mode)
{
	if (!(ptr->modes & mode))
		ptr->modes |= mode;
	else
		ptr->modes &= ~(mode);
}

void	ft_restore_settings(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_attr.def_settings);
}

int		ft_maxlen(t_dslist *lst)
{
	t_dslist	*ptr;
	int			max;

	max = lst->len;
	ptr = lst->next;
	while (ptr != lst)
	{
		if (ptr->len > max)
			max = ptr->len;
		ptr = ptr->next;
	}
	return (max);
}

void	ft_exit(void)
{
	ft_restore_settings();
	ft_del_list(g_attr.args);
	exit(EXIT_SUCCESS);
}
