void uart_init(int baudrate)
{
	/* baudrate stuff */
	UBRR0H = (unsigned char)(((F_CPU / (16L * baudrate)) - 1) >> 8);
	UBRR0L = (unsigned char)((F_CPU / (16L * baudrate)) - 1);

	/* 8,N,1 frame */
	UCSR0C = (0 << UMSEL0) | (0 << UPM0) | (1 << USBS0) | (3 << UCSZ0);

	//UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0B = (1 << RXEN0);
	//UCSR0B |= (1 << RXCIE0);	// interrupt on receive
}

void uart_putchar(char c)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0))) ;
	/* Put data into buffer, sends the data */
	UDR0 = c;
}

void uart_puts(char *c)
{
	while (*c) {
		uart_putchar(*c);
		c++;
	}
}

void newline(void)
{
	char s[] = "\r\n";
	uart_puts(s);
}

char uart_getchar(void)
{
	while (!(UCSR0A & (1 << RXC0))) ;
	return UDR0;
}

void uart_puthexchar(unsigned char c)
{
	char n[] =
	    { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c',
	     'd', 'e', 'f' };
	uart_putchar(n[c >> 4]);
	uart_putchar(n[c & 15]);
}
