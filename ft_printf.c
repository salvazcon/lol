/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:58:36 by saazcon-          #+#    #+#             */
/*   Updated: 2023/11/15 16:38:38 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdlib.h"
#include "stdarg.h"

void	ft_put_str(char *str, int *len)
{
	int n;
	
	n = 0;
	if(!str)
		str = "(null)";
	while(str[n])
	{
		write(1, &str[n], 1);	
		(*len)++;
		n++;
	}
}

void	ft_put_nbr(long long int nbr, int base, int *len)
{
	char *b = "0123456789abcdef";
	
	if (nbr < 0)
	{
		write(1, "-", 1);
		(*len)++;
		nbr = nbr * -1;
	}
	if(nbr >= base)
		ft_put_nbr(nbr / base, base, len);
	write(1, &b[nbr % base], 1);
	(*len)++;
}

int ft_printf(const char *text, ... )
{
	int			i;
	int			len;
	va_list		str;

	va_start(str, text);
	i = 0;
	len = 0;
	while(text[i])
	{
		if(text[i] == '%' && text[i + 1])
		{
			i++;
			if(text[i] == 's')
				ft_put_str(va_arg(str, char *), &len);
			else if(text[i] == 'd')
				ft_put_nbr((long long int)va_arg(str, int), 10, &len);
			else if(text[i] == 'x')
				ft_put_nbr((long long int)va_arg(str, unsigned int), 16, &len);
		}
		else
		{
			write(1, &text[i], 1);
			len++;
		}
		i++;
	}
	va_end(str);
	return (len);
}
int main()
{
	ft_printf("%s\n", "toto");
	ft_printf("Magic %s is %d\n", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
}