\# STM32 Linked LED



\## Description

STM32 register-level project demonstrating GPIO control, EXTI interrupt handling, and runtime vector table remapping using VTOR.



\## Features

\- GPIO input/output control

\- Push button LED control

\- EXTI external interrupt handling

\- NVIC interrupt configuration

\- Runtime Vector Table Relocation

\- Custom Interrupt Service Routine (ISR)

\- Dynamic ISR remapping using VTOR

\- Register-level programming



\## Debugging \& Verification

\- Verified EXTI0 interrupt execution using breakpoints

\- Monitored GPIO and EXTI registers during runtime

\- Traced NVIC interrupt flow using STM32CubeIDE debugger



\## Hardware

\- STM32F411VET6



\## Toolchain

\- STM32CubeIDE

\- STM32 HAL Driver



\## Concepts Learned

\- GPIO configuration

\- EXTI interrupt handling

\- NVIC configuration

\- Interrupt vector table

\- VTOR register

\- ISR remapping

\- Register-level programming

\- Interrupt debugging



\## Future Improvements

\- Software debouncing

\- UART communication

\- Timer interrupt integration

\- Bootloader implementation



\## Author

Hung Vo

