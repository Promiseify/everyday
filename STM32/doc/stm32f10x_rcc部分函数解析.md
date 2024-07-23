### RCC_APB1PeriphClockCmd

- 用于使能 APB1 总线上的外设时钟。
- APB1 总线一般运行在较低的时钟频率下，通常是系统时钟的一半或四分之一。
- APB1 总线上的外设通常是那些不需要高频率时钟的外设，例如定时器、UART、I2C、SPI 等。

#### APB1 总线上的外设 (使用 RCC_APB1PeriphClockCmd 使能)

- TIM2, TIM3, TIM4, TIM5, TIM6, TIM7
- USART2, USART3, UART4, UART5
- I2C1, I2C2
- CAN1, CAN2
- DAC
- PWR

### RCC_APB2PeriphClockCmd

#### APB2 总线上的外设 (使用 RCC_APB2PeriphClockCmd 使能)

- TIM1, TIM8, TIM9, TIM10, TIM11
- USART1
- ADC1, ADC2, ADC3
- SPI1
- SYSCFG
- GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH