#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>

static struct termios cpy;

int		main(int argc, char **argv)
{
	int fd;
	int	ret = 0;
	char *str = NULL;
	char *name;
	struct termios buf;

	char rb[100];
	int rr;
	fd = 0;



// get a name of terminal
name = ctermid(str);


//get the fd of terminal
fd = open(name, O_RDONLY);
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
//делаем копию, чтобы все вернуть взад
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

//считываем
while ((rr = read(fd, &rb, 100)) > 0)
{
	rb[rr] = '\0';
	//printf("---> rr: %d, rb: %s %d\n", rr, rb, rb[0]);
	if (rr > 1)
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