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

void	ft_move_h(t_dslist **ptr, uint64_t direction)
{
	(*ptr)->modes &= ~(M_CRSR);
	if (direction == K_RIGHT)
		(*ptr) = (*ptr)->next;
	else if (direction == K_LEFT)
		(*ptr) = (*ptr)->prev;
	(*ptr)->modes |= (M_CRSR);
}

void	ft_move_v(t_dslist **ptr, uint64_t direction)
{
	t_printp param;
	int	n;
	
	param = ft_get_params(g_attr.args);
	n = ft_count_elem(*ptr);
	(*ptr)->modes &= ~(M_CRSR);
	if (direction == K_DOWN)
	{
		(*ptr) = ft_get_nth((*ptr), param.cols % n);
	}
	else if (direction == K_UP)
	{
		(*ptr) = ft_get_nth((*ptr), param.cols % n);
	}
	(*ptr)->modes |= (M_CRSR);
}

void	ft_processing(void)
{
	int rr;
	uint64_t rb;
	t_dslist *ptr = g_attr.args;
	
	rb = 0;
	ft_putstr_fd(CLEAR, STDERR_FILENO);
	ft_print_forward(ptr);
	while ((rr = read(STDIN_FILENO, &rb, 8)) > 0)
	{
		if (rb == K_RIGHT || rb == K_LEFT)
			ft_move_h(&ptr, rb);
		else if (rb == K_DOWN || rb == K_UP)
			ft_move_v(&ptr, rb);
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
			return;
		}
		else if (rb == K_ESC)
			ft_exit();
		//ft_printf("%s", CLEAR);
		ft_putstr_fd(CLEAR, STDERR_FILENO);
		ft_print_forward(g_attr.args);
		rb = 0;
	}
}
