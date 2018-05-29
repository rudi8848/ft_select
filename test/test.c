#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>

static struct termios cpy;
static int g_fd;
	
void	handler(int signum)
{
	if (signum == SIGINT)
	{
		tcsetattr(g_fd, TCSAFLUSH, &cpy);
		exit (0);
	}
}


int		main(int argc, char **argv)
{
	int fd;
	int	ret = 0;
	char *str = NULL;
	char *name;
	struct termios buf;
	int rr;
	char rb[100];
	char bp[1024];
	fd = 0;

struct termios *argp;

printf("\033[7mReversed\033[m Normal\n");		//reversed
printf("\033[4mUnderlined\033[m Normal\n");		//underlined
printf("\033[7;4mRev+Underlined\033[m Normal\n");	//both

//ret = tgetent(bp, "co");
//printf("[%s]\n", ret ? "YES" : "NO");

// get a name of terminal
name = ctermid(str);


//get the fd of terminal
fd = open(name, O_RDONLY);
if (fd < 0)
{
	perror("open");
	return (-1);
}
g_fd = fd;

//ret = ioctl(fd, TIOCGLCKTRMIOS, &argp);
//printf("ret ioctl: %d\n", ret); 

printf("ctermid:	%s, [%d]\n", name, fd);
// is fd a terminal?
printf("isatty:		[%s]\n", isatty(fd) ? "YES" : "NO");

str = ttyname(fd);
printf("ttyname:	%s\n", str);

//получаем атрибуты в буфер
if (tcgetattr(fd, &buf) < 0)
{
	perror("tcgetattr");
	return(-1);
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
	return (-1);
}

//проверяем
if (tcgetattr(fd, &buf) < 0)
{
	perror("tcgetattr2");
	tcsetattr(fd, TCSAFLUSH, &cpy);
	perror("tcsetattr2");
	return (-1);
}
signal(SIGINT, handler);
//считываем
while ((rr = read(fd, &rb, 100)) > 0)
{
	rb[rr] = '\0';
	
	
	if (rr > 0)
	{
		int i = 0;
		while (i < rr)
		{
			printf("[%d]", rb[i]);
			i++;
		}
		printf("\n");
	}
}

fd = 0;
	while (fd < 5)
	{
		ret = isatty(fd);
		if (ret)
		{
			str = ttyname(fd);
			printf("%s\n", str);
		}
		else
			printf("NO\n");
		fd++;
	}
close(fd);

	return (0);
}