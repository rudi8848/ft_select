#include "ft_select.h"

void		ft_print_selected(t_dslist *lst)
{
	t_dslist *ptr;

	ptr = lst;
	ft_printf("%s", CLEAR);
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

void	ft_processing(void)
{
	t_dslist *ptr = g_attr.args;
ft_printf("%s", CLEAR);
ft_print_forward(g_attr.args);
	while ((rr = read(fd, &rb, 8)) > 0)
	{
		//ft_printf("[ %lld ]\n", rb);
		if (rb == K_DOWN)
		{
			ptr->modes &= ~(M_CRSR);
			ptr = ptr->next;
			ptr->modes |= (M_CRSR);
		}
		else if (rb == K_UP)
		{
			ptr->modes &= ~(M_CRSR);
			ptr = ptr->prev;
			ptr->modes |= (M_CRSR);
		}
		else if (rb == K_SPACE)
		{
			if (! (ptr->modes & M_SLCT))
				ptr->modes |= M_SLCT;
			else
				ptr->modes &= ~(M_SLCT);
		}
		else if (rb == K_DELETE || rb == K_BSPACE)
		{
			if (ptr != g_attr.args)
				ptr = ft_del_elem(ptr);
			ptr->modes |= (M_CRSR);
		}
		else if ((int)rb == K_ENTER)
		{
			ft_print_selected(g_attr.args);
			return g_attr.args;
		}
		ft_printf("%s", CLEAR);
		ft_print_forward(g_attr.args);
		rb = 0;
	}
}