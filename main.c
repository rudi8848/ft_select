#include "ft_select.h"

void	ft_check_terminal(void)
{
	char	*name;
	int		ret;

	name = getenv("TERM");
	if (!name)
	{
		ft_putstr_fd("Terminal is not set\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ret = tgetent(NULL, name);
	if (ret < 1)
	{
		ft_putstr_fd("No settings for terminal\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	ft_get_winsize(void)
{
	struct winsize 	argp;
	int 			ret;

	ret = ioctl(STDIN_FILENO, TIOCGWINSZ, &argp);
	if (ret != 0)
	{
		ft_putstr_fd("Cannot get window size\n", STDERR_FILENO);
		ft_exit();
	}
	g_attr.width = argp.ws_col;
	g_attr.height = argp.ws_row;
	printf("---> %s width: [%d], height: [%d]\n", __FUNCTION__, g_attr.width, g_attr.height);
	sleep(1);
}

void	ft_init_attr(void)
{
	struct termios	buf;
	int 			ret;

	ret = tcgetattr(STDIN_FILENO, &buf);
	if (ret < 0)
	{
		ft_putstr_fd("Cannot get attributes\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	g_attr.def_settings = buf;
	ft_get_winsize();
	buf.c_lflag &= ~(ECHO | ICANON);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &buf) < 0)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
	if (tcgetattr(STDIN_FILENO, &buf) < 0)
	{
		perror("tcgetattr");
		ft_exit();
	}
	g_attr.cur_settings = buf;
}

void	ft_restore_settings(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_attr.def_settings);
}

void	ft_get_args(int argc, char **argv)
{
	int 	i;

	i = 1;
	g_attr.args = ft_init_list(argv[i]);
	i++;
	while (i < argc)
	{
		g_attr.args = ft_addelem(g_attr.args, argv[i]);
		i++;
	}
	g_attr.args = g_attr.args->next;
	g_attr.args->modes |= M_CRSR;
}

int		main(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_check_terminal();
		ft_init_attr();
		ft_set_signals();
		ft_get_args(argc, argv);
		ft_processing();
	ft_restore_settings();
	ft_del_list(g_attr.args);
	}
	else
		ft_putstr_fd("Usage: ./ft_select <arguments>\n", STDERR_FILENO);
	
	return (0);
}
