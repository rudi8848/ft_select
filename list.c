/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 10:21:59 by gvynogra          #+#    #+#             */
/*   Updated: 2018/06/01 10:22:01 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_dslist	*ft_init_list(char *name)
{
	t_dslist	*lst;

	lst = (t_dslist*)ft_memalloc(sizeof(t_dslist));
	if (!lst)
		return (NULL);
	lst->name = ft_strdup(name);
	lst->len = ft_strlen(name);
	lst->modes = 0;
	lst->next = lst;
	lst->prev = lst;
	return (lst);
}

t_dslist	*ft_addelem(t_dslist *lst, char *name)
{
	t_dslist	*temp;
	t_dslist	*ptr;

	temp = (t_dslist*)ft_memalloc(sizeof(t_dslist));
	if (!temp)
		return (NULL);
	ptr = lst->next;
	lst->next = temp;
	temp->name = ft_strdup(name);
	temp->len = ft_strlen(name);
	temp->next = ptr;
	temp->prev = lst;
	ptr->prev = temp;
	return (temp);
}

t_dslist	*ft_del_elem(t_dslist *lst)
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

void	ft_print_forward(t_dslist *lst)
{
	t_dslist	*ptr;

	ptr = lst;
	if (ptr->modes & M_CRSR && ptr->modes & M_SLCT)
		ft_printf("%s%s%s\n", S_SLCRS, ptr->name, S_NORM);
	else if (ptr->modes & M_CRSR)
		ft_printf("%s%s%s\n", S_CRSR, ptr->name, S_NORM);
	else if (ptr->modes & M_SLCT)
		ft_printf("%s%s%s\n", S_SLCT, ptr->name, S_NORM);
	else
		ft_printf("%s\n", ptr->name);
		//ft_printf("%s%s%s\n", (ptr->modes & M_CRSR)  ? S_CRSR : "", ptr->name, S_NORM);

	ptr = lst->next;
	while (ptr != lst)
	{
		if (ptr->modes & M_CRSR && ptr->modes & M_SLCT)
			ft_printf("%s%s%s\n", S_SLCRS, ptr->name, S_NORM);
		else if (ptr->modes & M_CRSR)
			ft_printf("%s%s%s\n", S_CRSR, ptr->name, S_NORM);
		else if (ptr->modes & M_SLCT)
			ft_printf("%s%s%s\n", S_SLCT, ptr->name, S_NORM);
		else
			ft_printf("%s\n", ptr->name);
		//ft_printf("%s%s%s\n", (ptr->modes & M_CRSR) ? S_CRSR : "", ptr->name, S_NORM);
		ptr = ptr->next;
	}
}

void	ft_del_list(t_dslist *lst)
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

/*
int		main(int argc, char **argv)
{
	t_dslist *new;
	int i = 1;

	if (argc > 1)
	{
		new = ft_init_list(argv[i]);
		i++;
		while (i < argc)
		{
			new = ft_addelem(new, argv[i]);
			i++;
		}
		new = new->next;
		ft_print_forward(new);
		ft_del_list(new);
	}
	return 0;
}
*/