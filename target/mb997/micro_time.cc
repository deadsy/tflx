
#include "stm32f4xx_hal.h"
#include "tensorflow/lite/micro/micro_time.h"

namespace tflite {
uint32_t ticks_per_second() { return (1000U/HAL_TICK_FREQ_1KHZ); }
uint32_t GetCurrentTimeTicks() { return HAL_GetTick(); }
}  // namespace tflite
