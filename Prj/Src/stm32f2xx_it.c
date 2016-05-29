/**
  ******************************************************************************
  * @file    stm32f2xx_it.c
  * @date    20/09/2014 15:15:54
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2014 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"
#include "stm32f2xx.h"
#include "stm32f2xx_it.h"

/* External variables --------------------------------------------------------*/

extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;
extern UART_HandleTypeDef huart6;
extern TIM_HandleTypeDef    TimHandle2;
extern TIM_HandleTypeDef    TimHandle3;
extern TIM_HandleTypeDef    TimHandle4;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
  HAL_TIM_IRQHandler(&TimHandle2);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
  HAL_TIM_IRQHandler(&TimHandle3);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET);
  HAL_TIM_IRQHandler(&TimHandle4);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);

}

void HAL_DMA_IRQHandler1_1(DMA_HandleTypeDef *hdma);

/**
* @brief This function handles DMA1 Stream1 global interrupt.
*/
void DMA1_Stream1_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(DMA1_Stream1_IRQn);
  HAL_DMA_IRQHandler1_1(&hdma_usart3_rx);
}
void HAL_DMA_IRQHandler2_7(DMA_HandleTypeDef *hdma);
void HAL_DMA_IRQHandler1_6(DMA_HandleTypeDef *hdma);
void HAL_DMA_IRQHandler1_3(DMA_HandleTypeDef *hdma);
/**
* @brief This function handles DMA2 Stream7 global interrupt.
*/
void DMA2_Stream7_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(DMA2_Stream7_IRQn);
  HAL_DMA_IRQHandler2_7(&hdma_usart1_tx);
}

/**
* @brief This function handles DMA2 Stream6 global interrupt.
*/
void DMA2_Stream6_IRQHandler(void)
{
	UART_HandleTypeDef* huart = ( UART_HandleTypeDef* )(hdma_usart6_tx.Parent);

  HAL_NVIC_ClearPendingIRQ(DMA2_Stream6_IRQn);
  HAL_DMA_IRQHandler(&hdma_usart6_tx);
  huart->State  = HAL_UART_STATE_READY;

}

extern UART_HandleTypeDef huart1;
void USART1_IRQHandler(void)
{
  //HAL_GPIO_WritePin (GPIOF,GPIO_PIN_8, GPIO_PIN_SET );
  HAL_NVIC_ClearPendingIRQ(USART1_IRQn);

  USART1->CR1 &=~(USART_CR1_TXEIE | USART_CR1_TCIE);
  USART1->CR1 |= USART_CR1_RE;
  HAL_UART_TxCpltCallback(&huart1);
  //HAL_GPIO_WritePin (GPIOF,GPIO_PIN_8, GPIO_PIN_RESET );

}
extern UART_HandleTypeDef huart2;
void USART2_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART2_IRQn);

  USART2->CR1 &=~(USART_CR1_TXEIE | USART_CR1_TCIE);
  USART2->CR1 |= USART_CR1_RE;
  HAL_UART_TxCpltCallback(&huart2);

}

extern UART_HandleTypeDef huart3;
void USART3_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART2_IRQn);

  USART3->CR1 &=~(USART_CR1_TXEIE | USART_CR1_TCIE);
  USART3->CR1 |= USART_CR1_RE;
  HAL_UART_TxCpltCallback(&huart3);

}
/**
* @brief This function handles DMA1 Stream3 global interrupt.
*/
void DMA1_Stream3_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(DMA1_Stream3_IRQn);
  HAL_DMA_IRQHandler1_3(&hdma_usart3_tx);
}

/**
* @brief This function handles DMA1 Stream3 global interrupt.
*/
void DMA2_Stream2_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(DMA2_Stream2_IRQn);
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
}

/**
* @brief This function handles DMA1 Stream6 global interrupt.
*/
void DMA1_Stream6_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(DMA1_Stream6_IRQn);
  HAL_DMA_IRQHandler1_6(&hdma_usart2_tx);
}


/**
* @brief This function handles DMA1 Stream5 global interrupt.
*/
void DMA1_Stream5_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(DMA1_Stream5_IRQn);
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
}
/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}



/**
  * @brief  Handles DMA interrupt request.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Stream.
  * @retval None
  */
void HAL_DMA_IRQHandler2_7(DMA_HandleTypeDef *hdma)
{
	UART_HandleTypeDef* huart = ( UART_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  /* Transfer Complete Interrupt management ***********************************/
  //if(__HAL_DMA_GET_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma)) != RESET)
  if(DMA2->HISR  & DMA_FLAG_TCIF3_7 )
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != RESET)
    {
      {
        if((hdma->Instance->CR & DMA_SxCR_CIRC) == 0)
        {
          /* Disable the transfer complete interrupt */
          __HAL_DMA_DISABLE_IT(hdma, DMA_IT_TC);
        }
        /* Clear the transfer complete flag */
        //__HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma));
        DMA2->HIFCR |= DMA_FLAG_TCIF3_7;

        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_NONE;

        /* Change the DMA state */
        hdma->State = HAL_DMA_STATE_READY_MEM0;

        /* Process Unlocked */
        __HAL_UNLOCK(hdma);

        //if(hdma->XferCpltCallback != NULL)
        {
          /* Transfer complete callback */
        	//  hdma->XferCpltCallback(hdma);
        }
        huart->TxXferCount = 0;
         /* Disable the DMA transfer for transmit request by setting the DMAT bit
            in the UART CR3 register */
        huart->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DMAT);
         huart->Instance->CR1 |= USART_CR1_TCIE;
      }
    }
  }
}

void HAL_DMA_IRQHandler1_6(DMA_HandleTypeDef *hdma)
{
	UART_HandleTypeDef* huart = ( UART_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  /* Transfer Complete Interrupt management ***********************************/
  //if(__HAL_DMA_GET_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma)) != RESET)
  if(DMA1->HISR  & DMA_FLAG_TCIF2_6 )
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != RESET)
    {
      {
        if((hdma->Instance->CR & DMA_SxCR_CIRC) == 0)
        {
          /* Disable the transfer complete interrupt */
          __HAL_DMA_DISABLE_IT(hdma, DMA_IT_TC);
        }
        /* Clear the transfer complete flag */
        //__HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma));
        DMA1->HIFCR |= DMA_FLAG_TCIF2_6;

        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_NONE;

        /* Change the DMA state */
        hdma->State = HAL_DMA_STATE_READY_MEM0;

        /* Process Unlocked */
        __HAL_UNLOCK(hdma);

        //if(hdma->XferCpltCallback != NULL)
        {
          /* Transfer complete callback */
        	//  hdma->XferCpltCallback(hdma);
        }
        huart->TxXferCount = 0;
         /* Disable the DMA transfer for transmit request by setting the DMAT bit
            in the UART CR3 register */
        huart->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DMAT);
         huart->Instance->CR1 |= USART_CR1_TCIE;
      }
    }
  }
}

void HAL_DMA_IRQHandler1_3(DMA_HandleTypeDef *hdma)
{
	UART_HandleTypeDef* huart = ( UART_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  /* Transfer Complete Interrupt management ***********************************/
  //if(__HAL_DMA_GET_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma)) != RESET)
  if(DMA1->LISR  & DMA_FLAG_TCIF3_7 )
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != RESET)
    {
      {
        if((hdma->Instance->CR & DMA_SxCR_CIRC) == 0)
        {
          /* Disable the transfer complete interrupt */
          __HAL_DMA_DISABLE_IT(hdma, DMA_IT_TC);
        }
        /* Clear the transfer complete flag */
        //__HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma));
        DMA1->LIFCR |= DMA_FLAG_TCIF3_7;

        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_NONE;

        /* Change the DMA state */
        hdma->State = HAL_DMA_STATE_READY_MEM0;

        /* Process Unlocked */
        __HAL_UNLOCK(hdma);

        //if(hdma->XferCpltCallback != NULL)
        {
          /* Transfer complete callback */
        	//  hdma->XferCpltCallback(hdma);
        }
        huart->TxXferCount = 0;
         /* Disable the DMA transfer for transmit request by setting the DMAT bit
            in the UART CR3 register */
        huart->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DMAT);
         huart->Instance->CR1 |= USART_CR1_TCIE;
      }
    }
  }
}

void HAL_DMA_IRQHandler1_1(DMA_HandleTypeDef *hdma)
{
	UART_HandleTypeDef* huart = ( UART_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  /* Transfer Complete Interrupt management ***********************************/
  //if(__HAL_DMA_GET_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma)) != RESET)
  if(DMA1->LISR  & DMA_FLAG_TCIF1_5 )
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != RESET)
    {
      {
        if((hdma->Instance->CR & DMA_SxCR_CIRC) == 0)
        {
          /* Disable the transfer complete interrupt */
          __HAL_DMA_DISABLE_IT(hdma, DMA_IT_TC);
        }
        /* Clear the transfer complete flag */
        //__HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma));
        DMA1->LIFCR |= DMA_FLAG_TCIF1_5;

        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_NONE;

        /* Change the DMA state */
        hdma->State = HAL_DMA_STATE_READY_MEM0;

        /* Process Unlocked */
        __HAL_UNLOCK(hdma);

        if(hdma->XferCpltCallback != NULL)
        {
          /* Transfer complete callback */
        	hdma->XferCpltCallback(hdma);
        }
      }
    }
  }
}

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
	  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
  }
}


void HardFault_HandlerC(unsigned long *hardfault_args);
/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{


    __asm volatile
    (
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
        " ldr r1, [r0, #24]                                         \n"
        " ldr r2, handler2_address_const                            \n"
        " bx r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack    \n"
    );
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {

  }
}

void prvGetRegistersFromStack(unsigned long *hardfault_args)
{
	volatile unsigned long stacked_r0 ;
	        volatile unsigned long stacked_r1 ;
	        volatile unsigned long stacked_r2 ;
	        volatile unsigned long stacked_r3 ;
	        volatile unsigned long stacked_r12 ;
	        volatile unsigned long stacked_lr ;
	        volatile unsigned long stacked_pc ;
	        volatile unsigned long stacked_psr ;
	        volatile unsigned long _CFSR ;
	        volatile unsigned long _HFSR ;
	        volatile unsigned long _DFSR ;
	        volatile unsigned long _AFSR ;
	        volatile unsigned long _BFAR ;
	        volatile unsigned long _MMAR ;

	        stacked_r0 = ((unsigned long)hardfault_args[0]) ;
	        stacked_r1 = ((unsigned long)hardfault_args[1]) ;
	        stacked_r2 = ((unsigned long)hardfault_args[2]) ;
	        stacked_r3 = ((unsigned long)hardfault_args[3]) ;
	        stacked_r12 = ((unsigned long)hardfault_args[4]) ;
	        stacked_lr = ((unsigned long)hardfault_args[5]) ;
	        stacked_pc = ((unsigned long)hardfault_args[6]) ;
	        stacked_psr = ((unsigned long)hardfault_args[7]) ;

	        // Configurable Fault Status Register
	        // Consists of MMSR, BFSR and UFSR
	        _CFSR = (*((volatile unsigned long *)(0xE000ED28))) ;

	        // Hard Fault Status Register
	        _HFSR = (*((volatile unsigned long *)(0xE000ED2C))) ;

	        // Debug Fault Status Register
	        _DFSR = (*((volatile unsigned long *)(0xE000ED30))) ;

	        // Auxiliary Fault Status Register
	        _AFSR = (*((volatile unsigned long *)(0xE000ED3C))) ;

	        // Read the Fault Address Registers. These may not contain valid values.
	        // Check BFARVALID/MMARVALID to see if they are valid values
	        // MemManage Fault Address Register
	        _MMAR = (*((volatile unsigned long *)(0xE000ED34))) ;
	        // Bus Fault Address Register
	        _BFAR = (*((volatile unsigned long *)(0xE000ED38))) ;

    /* When the following line is hit, the variables contain the register values. */
    for( ;; )
    	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
	  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
	  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
	  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
	  /* Go to infinite loop when Bus Fault exception occurs */
	  while (1)
	  {
		  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
	  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
	  /* Go to infinite loop when Bus Fault exception occurs */
	  while (1)
	  {
		  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
	  }
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
	  /* Go to infinite loop when Bus Fault exception occurs */
	  while (1)
	  {
		  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
	  }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
