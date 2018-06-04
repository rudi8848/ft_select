
#include "ft_select.h"

void	ft_print_elem(t_dslist *ptr, int width)
{
	int i;

	i = ptr->len;
	ft_putstr_fd(ptr->color, STDERR_FILENO);
	if (ptr->modes & M_CRSR && ptr->modes & M_SLCT)
		ft_putstr_fd(S_SLCRS, STDERR_FILENO);
		//ft_printf("%s%s%s\n", S_SLCRS, ptr->name, S_NORM);
	else if (ptr->modes & M_CRSR)
		ft_putstr_fd(S_CRSR, STDERR_FILENO);
		//ft_printf("%s%s%s\n", S_CRSR, ptr->name, S_NORM);
	else if (ptr->modes & M_SLCT)
		ft_putstr_fd(S_SLCT, STDERR_FILENO);
		//ft_printf("%s%s%s\n", S_SLCT, ptr->name, S_NORM);
	//else
		ft_putstr_fd(ptr->name, STDERR_FILENO);
		ft_putstr_fd(S_NORM, STDERR_FILENO);
		while (i < width)
		{
			ft_putchar_fd(' ', STDERR_FILENO);
			i++;
		}
}

int			ft_count_elem(t_dslist *lst)
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

int 		ft_maxlen(t_dslist *lst)
{
	t_dslist *ptr;
	int 		max;

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

t_printp 	ft_get_params(t_dslist *lst)
{
	t_printp	res;

	res.total = ft_count_elem(lst);
	res.col_width = ft_maxlen(lst) + 1;
	res.cols = g_attr.width / res.col_width;
	if (!res.cols)
	{
		ft_putstr_fd("No space to output\n", STDERR_FILENO);
		ft_exit();
	}
	res.rows = res.total / res.cols;
	if (!res.rows)
		res.rows = 1;
	else if (res.total % res.cols)
		res.rows++;
	return (res);
}

t_dslist			*ft_get_nth(t_dslist *head, int n)
{
	//printf("---> %s [%d]\n", __FUNCTION__, n);
	//sleep(1);
	int			i;
	t_dslist 	*ptr;

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

void	ft_print_forward(t_dslist *lst)
{
	t_dslist	*ptr;
	t_printp	curp;
	int 		c;
	int 		r;
	int 		j;

	ptr = lst;
	curp = ft_get_params(lst);
	c = 0;
	r = 0;

	while (c < curp.total && r < curp.rows)
	{
		j = 0;
		while (j < curp.cols)
		{
			if ((c * r + j) < curp.total)
			{
				ptr = ft_get_nth(lst, c * r + j);
				ft_print_elem(ptr, curp.col_width);
			}
			j++;
		}
		r++;
		ft_putchar_fd('\n', STDERR_FILENO);
		c += curp.cols;
	}
	/*
	ft_print_elem(ptr);
	ptr = lst->next;
	while (ptr != lst)
	{
		ft_print_elem(ptr);
		ptr = ptr->next;
	}*/
}