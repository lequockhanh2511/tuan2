#include "stm32f1xx.h"
volatile uint16_t cnt1;
volatile uint16_t cnt2;
volatile uint16_t cnt3;
void SysTick_Handler(void){
    HAL_IncTick();
    
    cnt1++;
    cnt2++;
    cnt3++;
    if(cnt1 == 5000){
        cnt1 = 0;
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
    }
    if(cnt2 == 500){
        cnt2 = 0;
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
    }
    if(cnt3 == 50){
        cnt3 = 0;
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
    }
}

void SystemClock_Config(void);
void GPIOA_Init(void);

int main(){
    HAL_Init();
    SystemClock_Config();

    GPIOA_Init();

    while(1){

    }
}

/*Config*/
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* 1. Cấu hình HSE + PLL => Bật thạch anh ngoại */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    /*→ Cho PLL lấy HSE làm nguồn. 8 MHz × 9 = 72 MHz*/
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;  
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /* 2. Cấu hình các bus clock */
    RCC_ClkInitStruct.ClockType =
          RCC_CLOCKTYPE_HCLK
        | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1
        | RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

void  GPIOA_Init(void){
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

