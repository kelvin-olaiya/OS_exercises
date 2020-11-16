#ifndef __UTIL_H__
#define __UTIL_H__
#include <stdlib.h>
#include <stdint.h>

#define MEMORY_ALLOC(dest) do{\
				dest = malloc(10 * sizeof(int32_t));\
				if (dest != NULL) {\
					int i;\
					for(i = -1000; i  <= -991; i++) {\
						(dest)[i + 1000] = i;\
					}\
				}\
			} while (0)
#endif
