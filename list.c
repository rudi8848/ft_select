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

void		ft_set_fields(t_dslist *lst, char *name)
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
		/*else if (name[lst->len - 2] == '.' && name[lst->len - 1] == 'o')
			lst->color = YELLOW;
		else if (name[lst->len - 2] == '.' && name[lst->len - 1] == 'c')
			lst->color = CYAN;*/
		else if (S_IXUSR & buf.st_mode)
			lst->color = RED;
		else
			lst->color = BLUE;
	}
	else
		lst->color = "";

}

t_dslist	*ft_init_list(char *name)
{
	t_dslist	*lst;

	lst = (t_dslist*)ft_memalloc(sizeof(t_dslist));
	if (!lst)
		return (NULL);
	//lst->name = ft_strdup(name);
	//lst->len = ft_strlen(name);
	ft_set_fields(lst, name);
	//lst->modes = 0;
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
	//printf("--> add [%s]\n", name);
	//sleep(1);
	//temp->name = ft_strdup(name);
	//temp->len = ft_strlen(name);
	ft_set_fields(temp, name);
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
