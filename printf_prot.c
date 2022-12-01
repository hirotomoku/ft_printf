#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void	ft_print_char(char c , int *n , va_list *ap){
	write(1,&c,1);
}

void	ft_putstr(char *str, int *j){
	size_t count;

	count = 0;
	while (str[count] != '\0')
	{
		write(1, &str[count], 1);
		count++;
	}
	//printf("str文字数%zu",count);

	*j = *j + (int)count - 1;
}

static char	*myputstr(char *p, int amari, size_t i, int digit_z)
{
	int		kazu;

	while (digit_z > 0)
	{
		kazu = amari / digit_z;
		amari = amari % digit_z;
		p[i] = kazu + '0';
		digit_z /= 10;
		i++;
	}
	p[i] = '\0';
	return (p);
}

static char	*ft_henkan_minus(int n, size_t i)
{
	int		digit;
	int		digit_z;
	int		amari;
	char	*p;

	amari = n;
	digit = 1;
	digit_z = 1;
	while (n >= 10)
	{
		n = n / 10;
		digit++;
		digit_z *= 10;
	}
	p = (char *)malloc(sizeof(char) * (digit + 2));
	if (p == NULL)
		return (NULL);
	p[0] = '-';
	p = myputstr(p, amari, i, digit_z);
	return (p);
}

static char	*ft_henkan_pulus(int n, size_t i)
{
	int		digit;
	int		digit_z;
	int		amari;
	char	*p;

	amari = n;
	digit = 1;
	digit_z = 1;
	while (n >= 10)
	{
		n = n / 10;
		digit++;
		digit_z *= 10;
	}
	p = (char *)malloc(sizeof(char) * (digit + 1));
	if (p == NULL)
		return (NULL);
	p = myputstr(p, amari, i, digit_z);
	return (p);
}

static char	*ft_int_min(void)
{
	char	*newstr;
	char	*int_min;
	size_t	i;

	i = 0;
	int_min = "-2147483648";
	newstr = (char *)malloc(12);
	if (newstr == NULL)
		return (NULL);
	while (i < 12)
	{
		newstr[i] = int_min[i];
		i++;
	}
	return (newstr);
}

char	*ft_itoa(int n)
{
	size_t		i;
	char		*p;

	if (n == -2147483648)
		p = ft_int_min();
	else if (n == 0)
	{
		p = (char *)malloc(sizeof(char) * 2);
		if (p == NULL)
			return (NULL);
		p[0] = '0';
		p[1] = '\0';
	}
	else if (n > 0)
	{
		i = 0;
		p = ft_henkan_pulus(n, i);
	}
	else
	{
		i = 1;
		n = n * -1;
		p = ft_henkan_minus(n, i);
	}
	return (p);
}

char	check_base(int n){
	char c;

	if(n < 10){
		c = n + '0';
	}else if (n == 10){
		c = 'a';
	}else if (n == 11){
		c = 'b';
	}else if (n == 12){
		c = 'c';
	}else if (n == 13){
		c = 'd';
	}else if (n == 14){
		c = 'e';
	}else if (n == 15){
		c = 'f';
	}
	return c;
}

void	ft_putnbr_base2(unsigned long long nb, int *j){
	unsigned long long b;
	int c = 16;
	char str[256];
	size_t i;

	i = 0;
	b = nb;
	while(b){
		b /= 16;
		i++;
	}
	str[i] = '\0';
	while(0 < i){
		str[i - 1] = check_base(nb % 16);
		nb /= 16;
		i--;
	}
	write(1, "0x", 2);
	*j = *j + 2;
	ft_putstr(str, j);
	// printf("%c\n",str[i]);
	// printf("%zu\n",i);

	// //printf("%d\n",i);
	// printf("%s\n",str);
}

void ft_printf_c(va_list *ap){
	char c;

	c = (char)va_arg(*ap, int);
	write(1, &c, 1);
}

void ft_printf_str(va_list *ap, int *j){
	char *str;

	if(ap == NULL || j == NULL)
		return;
	str = (char *)va_arg(*ap, char *);
	ft_putstr(str, j);
}

void ft_printf_int_d(va_list *ap, int *j){
	int d;
	char *p;

	if(ap == NULL || j == NULL)
		return;
	d = (int)va_arg(*ap, int);
	p = ft_itoa(d);
	ft_putstr(p, j);
}

void ft_printf_pointer(va_list *ap, int *j){
	unsigned long long p;

	if(ap == NULL || j == NULL)
		return;
	p = (unsigned long long)va_arg(*ap, void *);
	ft_putnbr_base2(p, j);
}


void ft_test(const char *tmp, int *i ,va_list *ap, int *j){
	int count;

	count = *i;
	if(ap == NULL)
		return;
	if(tmp[count + 1] =='c')
		ft_printf_c(ap);
	else if(tmp[count + 1] =='s')
		ft_printf_str(ap, j);
	else if(tmp[count + 1] =='p')
		ft_printf_pointer(ap, j);
	else if(tmp[count + 1] =='d' || tmp[count + 1] == 'i')
		ft_printf_int_d(ap, j);
	else if(tmp[count + 1] =='%')
		write(1,"%%", 1);
	else
		return;
}

int	ft_printf(const char *format,...){
	int i;
	va_list ap;
	va_start(ap,format);
	const char *temp;
	int n;
	int j;

	i = 0;
	j = 0;
	n = 0;
	temp = format;
	if(ap == NULL)
		return -1;
	while(format[i] != '\0'){
		if(format[i] != '%')
			write(1,&temp[i],1);
		else{
			ft_test(temp,&i,&ap,&j);
			i++;
			n++;
		}
		i++;
	}
	va_end(ap);
	return i - n + j;
}



int main (){
	int a = 2;
	char t;
	int count = 0;
	char *str = "uuuu";
	int *p;
	int i = 2147483648;
	unsigned int u = 4294967295;
	unsigned long long addr = (unsigned long long)&i;
	p = &i;
	count = printf("%caaaa%c%s%pooo%innn%u\n",'z','Z',str, &i, i, u);
	printf("本家：%d\n",count);
	count = ft_printf("%caaaa%c%s%pooo%innn\n",'z','Z',str, &i, i);
	printf("俺：%d\n",count);
	//ft_putstr("uuuu");
	// printf("%p\n",&i);
	// printf("%lld\n",addr);
	// printf("%llx\n",addr);
	//ft_putnbr_base2(addr);
	// t = 2 + '0';
	// printf("%c\n",t);
	return 0;
}
