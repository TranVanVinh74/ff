#include "DHT11.h"
#include "cmsis_os.h"

#define DHT11_PORT GPIOA
#define DHT11_PIN  GPIO_PIN_2

TIM_HandleTypeDef *dht11_timer;

void DHT11_Init(TIM_HandleTypeDef *htim) {
    dht11_timer = htim;
  
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
}

static void delay_us(uint16_t us) {
    __HAL_TIM_SET_COUNTER(dht11_timer, 0);
    while ((__HAL_TIM_GET_COUNTER(dht11_timer)) < us);
}

uint8_t DHT11_Read(DHT11_Data_t *DHT_Data) {
    uint8_t data[5] = {0, 0, 0, 0, 0};
    uint8_t i, j;

   
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
    osDelay(20); 
    
   
    taskENTER_CRITICAL(); //Khoa ngat tam thoi 
    
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
    delay_us(30); 

    
    if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET) {
        taskEXIT_CRITICAL();
        return 0; 
    }
    delay_us(80);
    if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_RESET) {
        taskEXIT_CRITICAL();
        return 0;
    }
    delay_us(80);


    for (i = 0; i < 5; i++) {
        for (j = 0; j < 8; j++) {
         
            while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_RESET);
            
            delay_us(40); 
            
            if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET) {
                
                data[i] |= (1 << (7 - j));
                // Ch? h?t m?c cao c?a Bit 1
                while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET);
            }
        }
    }

    // M? khóa b? l?p l?ch RTOS
    taskEXIT_CRITICAL();

    // 4. Ki?m tra Checksum
    if ((data[0] + data[1] + data[2] + data[3]) == data[4]) {
        DHT_Data->Humidity = (float)data[0] + (float)data[1] / 10.0;
        DHT_Data->Temperature = (float)data[2] + (float)data[3] / 10.0;
        return 1; 
    }

    return 0; 
}