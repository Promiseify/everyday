### 操作STM32的GPIO需要三个步骤：

1. 使用RCC开启GPIO的时钟
2. 使用GPIO_Init函数初始化GPIO （不显示代码提示的话，可以按一下快捷键Ctrl+Alt+空格）
3. 使用输出或者输入的函数控制GPIO口



### GPIO八种工作模式

1. GPIO_Mode_AIN AIN(Analog IN) 模拟输入
2. GPIO_Mode_IN_FLOATING 浮空输入
3. GPIO_Mode_IPD IPD(In Pull Down) 下拉输入
4. GPIO_Mode_IPU  IPU(In Pull Up) 上拉输入
5. GPIO_Mode_Out_OD Out_OD(Out Open Drain) 开漏输出
6. GPIO_Mode_Out_PP Out_PP(Out Push Pull) 推挽输出
7. GPIO_Mode_AF_OD AF_OD(Atl Open Drain) 复用开漏输出
8. GPIO_Mode_AF_PP AF_PP(Atl Push Pull) 复用推挽输出