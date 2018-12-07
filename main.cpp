#include "mbed.h"
#include "delay.h"
#include "stdint.h"
#include "status_codes.h"
#include "uart_serial.h"
#include "stdio_serial.h"

DigitalOut myled(LED1);

static void configure_console(void)
{
  const usart_serial_options_t uart_serial_options = 
  {
    .baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
    .charlength = CONF_UART_CHAR_LENGTH,
#endif
    .paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
    .stopbits = CONF_UART_STOP_BITS,
#endif
  };

  /* Configure console UART. */
  sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
  stdio_serial_init(CONF_UART, &uart_serial_options);
}

void send_string(Usart* uart, char *str)
{
  while(*str)
  {
    usart_serial_putchar(uart,*str++);
  }
}

void uart_printf(Usart* uart, char *fmt,...)
{
  va_list ap;
  char string[128];

  va_start(ap,fmt);
  vsprintf(string,fmt,ap);
  send_string(uart,string);
  va_end(ap);
}

int main()
{
  configure_console();
  const ticker_data_t *const ticker = get_us_ticker_data();
  volatile uint32_t start_bak = ticker_read(ticker);
  while(1) 
  {
    myled = 1;
    wait(0.5);
    myled = 0;
    wait(0.5);
    uart_printf(USART1, (char*)"ticker:%d\r\n",ticker_read(ticker));
	#if 0
    volatile uint32_t start = ticker_read(ticker); //ticker_read(ticker);
    //uart_printf(USART1, (char*)"start:%d\r\n",start);
    //uart_printf(USART1, (char*)"ticker:%d\r\n",us_ticker_read());
    if(start - start_bak < 0)
    {
      uart_printf(USART1, (char*)"start_bak:%d\r\n",start);
    }
    start_bak = start;
	#endif

	#if 0
    while (1)  //(now - start) < (uint32_t)1*1000000.0f
    {
      volatile int32_t now = ticker_read(ticker);
      volatile int32_t xx = now - start;
      if(xx < 0)
      {
        uart_printf(USART1, (char*)"now:%d, start:%d\r\n", now, start);
      }
      else if(xx > 1000000)
      {
        uart_printf(USART1, (char*)"xx:%d\r\n",xx);
        break;
      }
    }
	#endif
  }
}
