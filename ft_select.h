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

typedef struct s_dslist
{
	char	*name;
	size_t	len;
	int		modes;
	struct  s_dslist *prev;
	struct  s_dslist *next;
} t_dslist;

#endif