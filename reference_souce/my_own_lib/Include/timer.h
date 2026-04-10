/*
 * timer.h
 *
 *  Created on: Mar 29, 2026
 *      Author: vantien
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "stm32f1xx.h"
#define TIMER2_CLOCK_EN	(1U << 0)
#define TIMx_OCM2_TOGGLE	(3U << 12)	// Output compare with toggle in channel 2
#define TIMx_CC2_EN		(1U << 4)	// Capture (input)/ Compare (output) enable in channel 2
#define TIMx_CR1_CEN	(1U << 0)	// timer counter enable
#define GPIOA_EN  (1U << 2)	// 0b 0000 0000 0000 0100
#define TIMx_SR_UIF	(1U << 0) 	// Update interrupt flag
#define TIMx_DIER_UIE		(1u << 0)	// Upadte interrupt enable (DMA, interrupt enable register)

/** @defgroup TIM_definition TIM definition (General purpose timer)
 *
 */
#define GP_TIM2							   TIM2
#define GP_TIM3							   TIM3
#define GP_TIM4							   TIM4
#define GP_TIM5							   TIM5

/** @defgroup TIM_Flag_definition TIM Flag Definition
  * @{
  */
#define TIM_FLAG_UPDATE                    TIM_SR_UIF                           /*!< Update interrupt flag         */
#define TIM_FLAG_CC1                       TIM_SR_CC1IF                         /*!< Capture/Compare 1 interrupt flag */
#define TIM_FLAG_CC2                       TIM_SR_CC2IF                         /*!< Capture/Compare 2 interrupt flag */
#define TIM_FLAG_CC3                       TIM_SR_CC3IF                         /*!< Capture/Compare 3 interrupt flag */
#define TIM_FLAG_CC4                       TIM_SR_CC4IF                         /*!< Capture/Compare 4 interrupt flag */
#define TIM_FLAG_COM                       TIM_SR_COMIF                         /*!< Commutation interrupt flag    */
#define TIM_FLAG_TRIGGER                   TIM_SR_TIF                           /*!< Trigger interrupt flag        */
#define TIM_FLAG_BREAK                     TIM_SR_BIF                           /*!< Break interrupt flag          */
#define TIM_FLAG_CC1OF                     TIM_SR_CC1OF                         /*!< Capture 1 overcapture flag    */
#define TIM_FLAG_CC2OF                     TIM_SR_CC2OF                         /*!< Capture 2 overcapture flag    */
#define TIM_FLAG_CC3OF                     TIM_SR_CC3OF                         /*!< Capture 3 overcapture flag    */
#define TIM_FLAG_CC4OF                     TIM_SR_CC4OF                         /*!< Capture 4 overcapture flag    */
/**
  * @}
  */

/** @defgroup TIM_Interrupt_definition TIM interrupt Definition
  * @{
  */
#define TIM_IT_UPDATE                      TIM_DIER_UIE                         /*!< Update interrupt            */
#define TIM_IT_CC1                         TIM_DIER_CC1IE                       /*!< Capture/Compare 1 interrupt */
#define TIM_IT_CC2                         TIM_DIER_CC2IE                       /*!< Capture/Compare 2 interrupt */
#define TIM_IT_CC3                         TIM_DIER_CC3IE                       /*!< Capture/Compare 3 interrupt */
#define TIM_IT_CC4                         TIM_DIER_CC4IE                       /*!< Capture/Compare 4 interrupt */
#define TIM_IT_COM                         TIM_DIER_COMIE                       /*!< Commutation interrupt       */
#define TIM_IT_TRIGGER                     TIM_DIER_TIE                         /*!< Trigger interrupt           */
#define TIM_IT_BREAK                       TIM_DIER_BIE                         /*!< Break interrupt             */
/**
  * @}
  */

/** @defgroup TIM suporting and exported macro.
 * @{
 */
/** @brief  Check whether the specified TIM interrupt flag is set or not.
  * @param  __HANDLE__ specifies the TIM Handle.
  *        	This parameter can be one of the following values:
  *            @arg GP_TIM2:
  *            @arg GP_TIM3:
  *            @arg GP_TIM4:
  *            @arg GP_TIM5:
  *
  * @param  __FLAG__ specifies the GPTIM interrupt flag to check.
  *        	This parameter can be one of the following values:
  *            @arg TIM_FLAG_UPDATE: Update interrupt flag
  *            @arg TIM_FLAG_CC1: Capture/Compare 1 interrupt flag
  *            @arg TIM_FLAG_CC2: Capture/Compare 2 interrupt flag
  *            @arg TIM_FLAG_CC3: Capture/Compare 3 interrupt flag
  *            @arg TIM_FLAG_CC4: Capture/Compare 4 interrupt flag
  *            @arg TIM_FLAG_COM:  Commutation interrupt flag
  *            @arg TIM_FLAG_TRIGGER: Trigger interrupt flag
  *            @arg TIM_FLAG_BREAK: Break interrupt flag
  *            @arg TIM_FLAG_CC1OF: Capture/Compare 1 overcapture flag
  *            @arg TIM_FLAG_CC2OF: Capture/Compare 2 overcapture flag
  *            @arg TIM_FLAG_CC3OF: Capture/Compare 3 overcapture flag
  *            @arg TIM_FLAG_CC4OF: Capture/Compare 4 overcapture flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_GPTIM_GET_FLAG(__HANDLE__, __FLAG__)          ((__HANDLE__->SR &(__FLAG__)) == (__FLAG__))
/* Example
 * TIM2->SR (16 bit - 2 byte) 0x1001, __FLAG__ : TIM_FLAG_UPDATE (1U << 0) 0x0001
 * --> (0x1001 & 0x0001) == 0x0001
 * --> 0x0001 == 0x0001 --> 1
 */


/**
  * @brief  Check whether the specified GPTIM interrupt source is enabled or not.
  * @param  __HANDLE__ TIM handle
  * @param  __INTERRUPT__ specifies the GPTIM interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg TIM_IT_UPDATE: Update interrupt
  *            @arg TIM_IT_CC1:   Capture/Compare 1 interrupt
  *            @arg TIM_IT_CC2:  Capture/Compare 2 interrupt
  *            @arg TIM_IT_CC3:  Capture/Compare 3 interrupt
  *            @arg TIM_IT_CC4:  Capture/Compare 4 interrupt
  *            @arg TIM_IT_COM:   Commutation interrupt
  *            @arg TIM_IT_TRIGGER: Trigger interrupt
  *            @arg TIM_IT_BREAK: Break interrupt
  * @retval The state of TIM_IT (SET or RESET).
  */
#define __HAL_GPTIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->DIER & (__INTERRUPT__)) \
                                                             == (__INTERRUPT__)))

/**
 * @brief	Clear the specified GPTIM interrupt.
 *
 * @param  __HANDLE__ specifies the TIM Handle.
  *        	This parameter can be one of the following values:
  *            @arg GP_TIM2:
  *            @arg GP_TIM3:
  *            @arg GP_TIM4:
  *            @arg GP_TIM5:
  * @param  __INTERRUPT__ specifies the GPTIM interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg TIM_FLAG_UPDATE: Update interrupt flag
  *            @arg TIM_FLAG_CC1: Capture/Compare 1 interrupt flag
  *            @arg TIM_FLAG_CC2: Capture/Compare 2 interrupt flag
  *            @arg TIM_FLAG_CC3: Capture/Compare 3 interrupt flag
  *            @arg TIM_FLAG_CC4: Capture/Compare 4 interrupt flag
  *            @arg TIM_FLAG_COM:  Commutation interrupt flag
  *            @arg TIM_FLAG_TRIGGER: Trigger interrupt flag
  *            @arg TIM_FLAG_BREAK: Break interrupt flag
  *            @arg TIM_FLAG_CC1OF: Capture/Compare 1 overcapture flag
  *            @arg TIM_FLAG_CC2OF: Capture/Compare 2 overcapture flag
  *            @arg TIM_FLAG_CC3OF: Capture/Compare 3 overcapture flag
  *            @arg TIM_FLAG_CC4OF: Capture/Compare 4 overcapture flag
  */
#define __HAL_GPTIM_CLEAR_FLAG(__HANDLE__,__FLAG__)			((__HANDLE__)->SR &= ~(__FLAG__))

/*
 * @}
 */

void timer2_1hz_init(void);
void timer2_mHz_init(unsigned int usTim1Timerout50us);
void timer2_interrupt_enable(void);
void timer2_enable(void);
void timer2_disable(void);
#endif /* TIMER_H_ */
