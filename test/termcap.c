/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 11:04:46 by gvynogra          #+#    #+#             */
/*   Updated: 2018/06/02 11:05:37 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		test_termcap(void)
{
	char	*name;
	//char	bp[2048];
	int ret;
	char *ptr;
	char PC;
	char BC;

/*------------------------------------------------
** нашли свой терминал (имя взято из окружения)
** проверили, есть ли он в термкап. 1 значит есть
**------------------------------------------------
*/
	name = ft_strdup(getenv("TERM"));
	ret = tgetent(NULL, name);
	printf("terminal name: %s tgetent: %d\n", name, ret);
	if (ret == 1)
		ft_printf("terminal is in termcap\n");
	

/*------------------------------------------------
** значения полей библиотеки могут быть численными,
** флагом(буль), строковыми
** для получения каждого типа есть своя ф-ция:
** int tgetnum (char *name);	для численных
** int tgetflag (char *name);	для флагов
** char *tgetstr (char *name, char **area);	для строк
** если вместо **area кинуть НУЛЬ, ф-ция сама выделит
** память, а мы должны будем освободить в конце
**------------------------------------------------
*/
ft_printf("co: [%d], li: [%d]\n",tgetnum("co"),tgetnum("li"));
ptr = tgetstr("cm", NULL);	//cursor
ft_printf("cm:	%s\n", ptr);

/*------------------------------------------------
** char PC - padding character
**  temp = tgetstr ("pc", BUFFADDR);
**  PC = temp ? *temp : 0;
**------------------------------------------------
*/

ptr = tgetstr("us", NULL);	//underline
ft_printf("us:	%s%s%s %s\n", tgetstr("us", NULL), "hehehe", tgetstr("ue", NULL), "lalala");

ft_printf("%s%s", tgetstr("ks", NULL), tgetstr("ke", NULL));

}