/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 10:56:47 by gvynogra          #+#    #+#             */
/*   Updated: 2018/06/01 10:57:07 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_dslist	*ft_loop(t_dslist *lst)
{
	int fd;
	int	ret = 0;
	char *str = NULL;
	char *name;
	struct termios buf;
	int rr;
	//char rb[100];
	char bp[1024];
	fd = 0;
	uint64_t rb;

struct termios *argp;

name = ctermid(str);
//get the fd of terminal
fd = open(name, O_RDONLY);

if (tcgetattr(fd, &buf) < 0)
{
	perror("tcgetattr");
	exit (1);
	//return(-1);
}
//делаем копию, чтобы вернуть все взад
g_cpattr = buf;

//устанавливаем неканоничный режим и отключаем эхо
buf.c_lflag &= ~(ECHO | ICANON);

//считываем минимум 1 байт, время ожидания не ограничено
buf.c_cc[VMIN] = 1;
buf.c_cc[VTIME] = 0;

//устанавливаем атрибуты
if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
{
	perror("tcsetattr");
	exit(1);
	//return (-1);
}

//проверяем
if (tcgetattr(fd, &buf) < 0)
{
	perror("tcgetattr2");
	tcsetattr(fd, TCSAFLUSH, &g_cpattr);
	perror("tcsetattr2");
	exit (0);
	//return (-1);
}
rb = 0;
t_dslist *ptr = lst;
ft_printf("%s", CLEAR);
ft_print_forward(lst);
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
			if (ptr != lst)
				ptr = ft_del_elem(ptr);
			ptr->modes |= (M_CRSR);
		}
		else if ((int)rb == K_ENTER)
		{
			ft_print_selected(lst);
			return lst;
		}
		ft_printf("%s", CLEAR);
		ft_print_forward(lst);
		rb = 0;
	}
}

int		main(int argc, char **argv)
{
	int i = 1;
	t_dslist *new;

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
		new->modes |= M_CRSR;
		new = ft_loop(new);
		ft_del_list(new);
	}
	else
		ft_printf("No args\n");
	test_termcap();
	return 0;
}