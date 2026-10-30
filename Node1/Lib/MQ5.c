#include "MQ5.h"

static ADC_HandleTypeDef *mq5_adc;

void MQ5_Init(ADC_HandleTypeDef *hadc) {
    mq5_adc = hadc;
    HAL_ADCEx_Calibration_Start(mq5_adc);
}

uint16_t MQ5_ReadRaw(void) {
    uint16_t adc_val = 0;
    HAL_ADC_Start(mq5_adc);
    if (HAL_ADC_PollForConversion(mq5_adc, 10) == HAL_OK) {
        adc_val = (uint16_t)HAL_ADC_GetValue(mq5_adc);
    }
    HAL_ADC_Stop(mq5_adc);
    return adc_val;
}

uint16_t MQ5_ReadAverage(uint8_t samples) {
    if (samples == 0) samples = 1;
    uint32_t sum = 0;
    for (uint8_t i = 0; i < samples; i++) {
        sum += MQ5_ReadRaw();
    }
    return (uint16_t)(sum / samples);
}

/**
 * @brief Ð?c di?n áp th?c t? t?i d?u ra c?a MQ-5 (0.0V - 5.0V)
 */
float MQ5_ReadVoltage(void) {
    uint16_t raw_adc = MQ5_ReadAverage(10);
    // Tính di?n áp do du?c t?i chân PA1 (0V - 3.3V)
    float v_pin = ((float)raw_adc / 4095.0f) * 3.3f;
    // Khôi ph?c l?i di?n áp g?c c?a c?m bi?n tru?c c?u phân áp
    float v_sensor = v_pin * MQ5_VOLTAGE_DIVIDER_RATIO;
    return v_sensor;
}