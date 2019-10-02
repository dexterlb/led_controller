#include "error.h"
#include <stdbool.h>

void error() {
    Error_Handler();
}

// error handlers
void Error_Handler(void)
{
    while(true);
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    while(true);
}
#endif

