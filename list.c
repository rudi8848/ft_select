/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 10:21:59 by gvynogra          #+#    #+#             */
/*   Updated: 2018/06/07 11:22:00 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_set_fields(t_dslist *lst, char *name)
{
	int				ret;
	struct stat		buf;

	lst->modes = 0;
	lst->name = ft_strdup(name);
	lst->len = ft_strlen(name);
	ret = lstat(name, &buf);
	if (ret >= 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			lst->modes |= M_DIR;
			lst->color = GREEN;
		}
		else if (S_IXUSR & buf.st_mode)
			lst->color = RED;
		else
			lst->color = BLUE;
	}
	else
		lst->color = "";
}

t_dslist		*ft_init_list(char *name)
{
	t_dslist	*lst;

	lst = (t_dslist*)ft_memalloc(sizeof(t_dslist));
	if (!lst)
		return (NULL);
	ft_set_fields(lst, name);
	lst->next = lst;
	lst->prev = lst;
	return (lst);
}

t_dslist		*ft_addelem(t_dslist *lst, char *name)
{
	t_dslist	*temp;
	t_dslist	*ptr;

	temp = (t_dslist*)ft_memalloc(sizeof(t_dslist));
	if (!temp)
		return (NULL);
	ptr = lst->next;
	lst->next = temp;
	ft_set_fields(temp, name);
	temp->next = ptr;
	temp->prev = lst;
	ptr->prev = temp;
	return (temp);
}

t_dslist		*ft_del_elem(t_dslist *lst)
{
	t_dslist	*prev;
	t_dslist	*next;

	prev = lst->prev;
	next = lst->next;
	prev->next = lst->next;
	next->prev = lst->prev;
	free(lst->name);
	free(lst);
	return (prev);
}

void			ft_del_list(t_dslist *lst)
{
	t_dslist *ptr;

	ptr = lst->next;
	while (ptr != lst)
	{
		ft_del_elem(ptr);
		ptr = ptr->next;
	}
	ft_del_elem(lst);
}
