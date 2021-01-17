#include "types.h"
#include "stm32f030x8.h"
#include "gpio.h"
#include "uart.h"

#define FIFO_SIZE 512
typedef struct
{
  uint16 ri;
  uint16 wi;
  uchar fifo[FIFO_SIZE];
} TCircularBuf;

TCircularBuf Input;
TCircularBuf Output;

void PutToSerial(uint8 *value, uint16 len)
{
  // fill circular buffer
  while (len--)
  {
    Output.fifo[Output.wi++] = *value++;
    if (Output.wi == FIFO_SIZE) Output.wi = 0;
  }
  // and send 1st byte
  USART1->TDR = Output.fifo[Output.ri++];
}

// simple fnc to test serial
// send few bytes and set transmission flag
// after complet unset flag and let send again
uint8 test_string[] = "Temp:";
uint8 test_temp[] = "18";

uint8 test_flag = 1; // 1 - allow send again
void TESTSERIALFNC(void)
{
  if (test_flag)
  {
    PutToSerial(test_string, 5);
    PutToSerial(test_temp, 2);
    test_flag = 0;
  }
}

void UARTInit(void)
{
  EnablePortGpio(B);
  SetGpioAsAlternate(GPIOB, RX1);
  SetGpioAsAlternate(GPIOB, TX1);
  SetGpioToHighSpeed(GPIOB, RX1);
  SetGpioToHighSpeed(GPIOB, TX1);

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Enable clock for USART1

  USART1->BRR = HSI_VALUE / 9600L; // Baud-rate

  USART1->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE | USART_CR1_TCIE;
}

void USART1_IRQHandler(void)
{
  // RX register not empty (RXNE)
  if ((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
  {
    uchar rx_char;
    rx_char = (uchar)(USART1->RDR); // Receive data, clear flag

    if (rx_char == 'e')
    {
      ;
    }
    else if (rx_char == 'd')
    {
      ;
    }

    Input.fifo[Input.wi++] = rx_char;
    if (Input.wi == FIFO_SIZE) Input.wi = 0;
  }

  // Transmission complete (TC)
  if ((USART1->ISR & USART_ISR_TC) == USART_ISR_TC)
  {
    USART1->ICR |= USART_ICR_TCCF;
    if (Output.ri != Output.wi)
    {
      USART1->TDR = Output.fifo[Output.ri++];
      if (Output.ri == FIFO_SIZE) Output.ri = 0; // move index to the begin
    }
    else
    {
      // transmission done
      test_flag = 1;
    }
  }
}
