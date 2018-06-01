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

struct termios cpy;

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
cpy = buf;

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
	tcsetattr(fd, TCSAFLUSH, &cpy);
	perror("tcsetattr2");
	exit (0);
	//return (-1);
}
rb = 0;
t_dslist *ptr = lst;
system("clear");
ft_print_forward(lst);
	while ((rr = read(fd, &rb, 8)) > 0)
	{
	//ft_printf("[ %lld ]\n", rb);
	if (rb == K_DOWN)
	{
		ptr->modes = 0;
		ptr = ptr->next;
		ptr->modes = 1;
	}
	else if (rb == K_UP)
	{
		ptr->modes = 0;
		ptr = ptr->prev;
		ptr->modes = 1;
	}
	else if ((int)rb == 10)
	{

		return lst;
	}
	system("clear");
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

		new->modes = 1;

		new = ft_loop(new);
		
		
		ft_del_list(new);
	}
	return 0;
}