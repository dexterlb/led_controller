#pragma once

void error();
void Error_Handler(void);
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line);
#endif

