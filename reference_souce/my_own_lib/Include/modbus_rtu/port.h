/*
 * port.h
 *
 *  Created on: Apr 9, 2026
 *      Author: vantien
 */

#ifndef PORT_H_
#define PORT_H_

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f1xx.h"

#define INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define PR_END_EXTERN_C             }

#define ENTER_CRITICAL_SECTION()    __disable_irq()

#define EXIT_CRITICAL_SECTION()     __enable_irq()


typedef uint8_t         BOOL;
typedef unsigned char   UCHAR;
typedef char            CHAR;
typedef uint16_t        USHORT;
typedef int16_t         SHORT;
typedef uint32_t        ULONG;
typedef int32_t         LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif


#endif /* PORT_PORT_H_ */
