#ifndef __SLIDING_WINDOW_H_
#define __SLIDING_WINDOW_H_

#include "Error.h"

//structure to keep track of several moving average windows
#ifdef LAB5 
__packed
#endif
typedef struct _SlidingWindow16
{
	int16_t *window; //sliding window buffer
	uint32_t length;
	uint32_t index;
	uint32_t maxlength; //max size of window- cannot be greater than MOVING_AVERAGE_WINDOW_SIZE
	volatile int16_t average;
  int32_t sum;
}SlidingWindow16;


void SlidingWindow16Init(SlidingWindow16* window, uint32_t Size, int16_t* buffer);
void SlidingWindow16Clear(SlidingWindow16* window);
Error_t SlidingWindowInsertSampleAndUpdateAverage16(SlidingWindow16* pwindow, int16_t sample);
Error_t SlidingWindowGetAverage16(SlidingWindow16* pwindow, int16_t* average);

#endif
