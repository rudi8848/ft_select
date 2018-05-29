#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>

#define M_NORM		0
#define M_SLCT		1
#define M_CRSR		2

#define S_NORM		"\033[0m"
#define S_SLCT		"\033[7m"
#define S_CRSR		"\033[4m"
#define S_SLCRS		"\033[7;4m"

/*
#define K_LEFT
#define K_RIGHT
#define K_UP
#define K_DOWN

#define K_ENTER
#define K_SPACE
#define K_ESC
#define K_DELETE
#define K_BSPACE
*/

typedef struct s_slist
{
	char	*name;
	size_t	len;
	int		modes;
	struct  s_slist *next;
} t_slist;

void			ft_print_columns(t_slist *head, int total, int c, int r);

void	ft_push(t_slist **head, char *arg, short mode)
{
		t_slist		*temp;

		temp = (t_slist*)ft_memalloc(sizeof(t_slist));
		if (!temp)
		{
			ft_printf("Cannot allocate memory\n");
			exit(1);
		}
		temp->name = arg;
		temp->len = ft_strlen(arg);
		temp->modes = mode;
		temp->next = (*head);
		(*head) = temp;
}

int		ft_get_args(int argc, char **argv, t_slist **head)
{
		int		i;

		//------------
		int m = 0;
		//-----------
		i = argc - 1;
		while (i)
		{
			ft_push(head, argv[i], m);
			m++;
			i--;
		}
	return (1);
}

void	ft_print_item(t_slist *cur, int width)
{
	if (cur->modes == M_NORM)
		ft_printf("%*s", -width, cur->name);
	else if (cur->modes & M_SLCT && cur->modes & M_CRSR)
		ft_printf("%s%*s%s", S_SLCRS, -width, cur->name, S_NORM);
	else if (cur->modes & M_SLCT)
		ft_printf("%s%*s%s", S_SLCT, -width, cur->name, S_NORM);
	else if (cur->modes & M_CRSR)
		ft_printf("%s%*s%s", S_CRSR, -width, cur->name, S_NORM);
	else
		ft_printf("%*s", -width, "error");
}



size_t			ft_maxlen(t_slist *head)
{
	size_t			len;
	size_t			max;

	max = 0;
	while (head)
	{
		if ((len = head->len) > max)
			max = len;
		head = head->next;
	}
	return (max);
}

int				ft_get_rows(int total, int cols)
{
	int			rows;

	rows = total / cols;
	if (!rows)
		rows = 1;
	else if (total % cols)
		rows++;
	return (rows);
}

void			ft_get_nbr_columns(t_slist *head, int *cols, int *col_width)
{
	int				fd;
	struct winsize	argp;
	int				ret;
	int				width;

	fd = open("/dev/tty", O_RDONLY);
	if (fd < 0)
	{
		perror("Error open");
		exit(EXIT_FAILURE);
	}
	ret = ioctl(fd, TIOCGWINSZ, &argp);
	if (ret != 0)
	{
		perror("Error ioctl");
		exit(EXIT_FAILURE);
	}
	width = argp.ws_col;
	*col_width = ft_maxlen(head) + 1;
	if (width < *col_width)
		width = *col_width;
	*cols = width / *col_width;
	//printf("---> %s, width: %d, col_width: %d\n", __FUNCTION__, width, *col_width);
}

int				ft_flist_counter(t_slist *head)
{
	int			i;

	i = 0;
	if (!head)
		return (0);
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

t_slist			*ft_get_nth(t_slist *head, int n)
{
	int			i;

	i = 0;
	while (i < n && head)
	{
		head = head->next;
		i++;
	}
	return (head);
}

void			ft_print_columns(t_slist *head, int total, int c, int r)
{
	//printf("---> %d %s\n", total, __FUNCTION__);
	int			cols;
	int			col_width;
	int			rows;
	t_slist		*ptr;
	int			j;

	ft_get_nbr_columns(head, &cols, &col_width);
	rows = ft_get_rows(total, cols);
	//printf("---> cols: %d, rows: %d\n", cols, rows);
	while (c < total && r < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (c + rows * j < total)
			{
				ptr = ft_get_nth(head, c + rows * j);
				ft_print_item(ptr, col_width);
				//ft_printf("%s%*s%s", ptr->color, -col_width,ptr->name, S_NORM);
			}
			j++;
		}
		write(1, "\n", 1);
		r++;
		c++;
	}
}

void	ft_print_slist(t_slist *head)
{
	//while (head)
	//{
		ft_print_columns(head, ft_flist_counter(head), 0, 0);
	//	head = head->next;
	//}
}

int		main(int argc, char **argv)
{
	//printf("---> %s\n", __FUNCTION__);
	t_slist		*head;

	head = NULL;
	if (argc == 1 || !ft_get_args(argc, argv, &head))
	{
		ft_printf("no args\n");
		exit (1);
	}
	ft_print_slist(head);
	return (0);
}