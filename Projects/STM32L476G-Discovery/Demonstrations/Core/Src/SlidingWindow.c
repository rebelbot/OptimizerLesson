#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "SlidingWindow.h"
#include "main.h"

//Clear data
void SlidingWindow16Clear(SlidingWindow16* window)
{
  memset(window->window,0, window->maxlength * sizeof(uint16_t));
	window->length = 0;
	window->index = 0;
	window->average = 0;
  window->sum = 0;  
}

// Initialize structure
//Input declared buffer
void SlidingWindow16Init(SlidingWindow16* window, uint32_t Size, int16_t* buffer)
{
  window->window = buffer;
	window->maxlength = Size;
	SlidingWindow16Clear(window);
}

#ifdef LAB5
#pragma push 
#pragma O3
#endif
//Insert new sample into running average window and update indices, length, etc...
Error_t SlidingWindowInsertSampleAndUpdateAverage16(SlidingWindow16* pwindow, int16_t sample)
{
	if (!pwindow)
		return ERROR_EMPTY;
#ifdef LAB3  
	//Place sample into window, update index in buffer, 
	// then calculate average over entire window from scratch
	
	pwindow->window[pwindow->index] = sample;
	
	if (pwindow->length < pwindow->maxlength)
	{//not full	
		pwindow->length++;
	}
	
	pwindow->index = (pwindow->index + 1) % pwindow->maxlength;
	pwindow->sum = 0;
	for(int i = 0; i < pwindow->length; i++)
		pwindow->sum += pwindow->window[i];
	pwindow->average = (pwindow->sum /pwindow->length); 
	
#elif LAB4 | LAB5
	pwindow->sum -= pwindow->window[pwindow->index];
	pwindow->window[pwindow->index] = sample;
  pwindow->sum += sample;
  
  //check if window buffer is full
	if (pwindow->length < pwindow->maxlength)
	{//not full	
		pwindow->length++;
	}
	else
	{//full buffer

	}

	pwindow->index = (pwindow->index + 1) % pwindow->maxlength;
#ifdef LAB5
	//You could always do a compare for a power of 2 but in this, we have forced it to
	//be a power of 2, so let's not do the check. 
	//In practice this should not be assumed unless well documented.
	//if(pwindow->length && !(pwindow->length & (pwindow->length - 1))) //power of 2?
		
		pwindow->average = (unsigned short)(pwindow->sum >> AVERAGE_WINDOW_SHIFT_DIVISOR);

#else	 //LAB4
		pwindow->average = (unsigned short)(pwindow->sum /pwindow->length); 
#endif
	
#endif
	return ERROR_SUCCESS;
}
#ifdef LAB5
#pragma pop
#endif
	
Error_t SlidingWindowGetAverage16(SlidingWindow16* pwindow, int16_t * average)
{
	if (!pwindow)
		return ERROR_EMPTY;
 	*average = pwindow->average;
	return ERROR_SUCCESS;	

}
