#include "ft_select.h"

void		ft_print_selected(t_dslist *lst)
{
	t_dslist *ptr;

	ptr = lst;
//	ft_printf("%s", CLEAR);
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

void	ft_processing(void)
{
	int rr;
	uint64_t rb;
	t_dslist *ptr = g_attr.args;
	t_printp param;
	rb = 0;
	ft_putstr_fd(CLEAR, STDERR_FILENO);
	ft_print_forward(ptr);
	param = ft_get_params(g_attr.args);
	while ((rr = read(STDIN_FILENO, &rb, 8)) > 0)
	{
		if (rb == K_RIGHT)
		{
			ptr->modes &= ~(M_CRSR);
			ptr = ptr->next;
			ptr->modes |= (M_CRSR);
		}
		else if (rb == K_LEFT)
		{
			ptr->modes &= ~(M_CRSR);
			ptr = ptr->prev;
			ptr->modes |= (M_CRSR);
		}
		else if (rb == K_DOWN)
		{
			ptr->modes &= ~(M_CRSR);
			ptr = ft_get_nth(ptr, param.cols);
			ptr->modes |= (M_CRSR);	
		}
		else if (rb == K_UP)
		{
			ptr->modes &= ~(M_CRSR);
		
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
		else if (rb == K_ENTER)
		{
			ft_print_selected(g_attr.args);
			//return g_attr.args;
			return;
		}
		//ft_printf("%s", CLEAR);
		ft_putstr_fd(CLEAR, STDERR_FILENO);
		ft_print_forward(g_attr.args);
		rb = 0;
	}
}
