/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 10:19:25 by gvynogra          #+#    #+#             */
/*   Updated: 2018/06/01 10:19:27 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <fcntl.h>

# define M_NORM		0
# define M_SLCT		1
# define M_CRSR		2

# define S_NORM		"\033[0m"
# define S_SLCT		"\033[7m"
# define S_CRSR		"\033[4m"
# define S_SLCRS		"\033[7;4m"


#define K_LEFT		4479771
#define K_RIGHT		4414235
#define K_UP		4283163
#define K_DOWN		4348699

#define K_ENTER		10
#define K_SPACE 	32
#define K_ESC		27
#define K_DELETE	2117294875L
#define K_BSPACE	127

typedef struct s_dslist
{
	char	*name;
	size_t	len;
	int		modes;
	struct  s_dslist *prev;
	struct  s_dslist *next;
} t_dslist;

t_dslist	*ft_init_list(char *name);
t_dslist	*ft_addelem(t_dslist *lst, char *name);
t_dslist	*ft_del_elem(t_dslist *lst);
void		ft_del_list(t_dslist *lst);



void	ft_print_forward(t_dslist *lst);

#endif