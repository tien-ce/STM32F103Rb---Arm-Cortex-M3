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
#include <string.h>
#include "stm32f1xx.h"

#define INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define PR_END_EXTERN_C             }

#define ENTER_CRITICAL_SECTION()    __disable_irq()

#define EXIT_CRITICAL_SECTION()     __enable_irq()


typedef bool         BOOL;
typedef unsigned char   UCHAR;
typedef char            CHAR;
typedef uint16_t        USHORT;
typedef int16_t         SHORT;
typedef uint32_t        ULONG;
typedef int32_t         LONG;
typedef uint8_t			UINT8;
#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

/* Port function */
static inline UINT8 uiPortMemcpy(UCHAR *des, const UCHAR *src, UINT8 length)
{
	memcpy(des,src,length);
	return length;
}

#endif /* PORT_PORT_H_ */
