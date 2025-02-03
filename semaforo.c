#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/timer.h" 
// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

#define LED_PIN_RED 11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 13

// Estado atual do semáforo (0 = Vermelho, 1 = Amarelo, 2 = Verde)
volatile int estado_semaforo = 0;

//  Alterna entre as cores do semáforo
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de mudar de estado
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_YELLOW, 0);
    gpio_put(LED_PIN_GREEN, 0);

    
    switch (estado_semaforo) {
        case 0:
            printf("Semáforo: VERMELHO, PARE!\n");
            gpio_put(LED_PIN_RED, 1);  // Acende o LED vermelho
            estado_semaforo = 1; // Muda para amarelo na próxima repeticao
            break;
        case 1:
            printf("Semáforo: AMARELO, ATENCAO!\n");
            gpio_put(LED_PIN_YELLOW, 1);  // Acende o LED amarelo
            estado_semaforo = 2; // Muda para verde na próxima repeticao
            break;
        case 2:
            printf("Semáforo: VERDE, SIGA EM FRENTE!\n");
            gpio_put(LED_PIN_GREEN, 1);  // Acende o LED verde
            estado_semaforo = 0; // Retorna para vermelho 
            break;
    }

    return true; // Mantém o temporizador ativo
}

int main()
{
    stdio_init_all();

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
    
    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, " Hello, UART!\n");
    
    // configuracao e inicializacao dos pinos dos LEDs 
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);


    // Declaração do temporizador 
    struct repeating_timer timer;

    //configurdo para mudar o semáforo a cada 3 segundos (3000 ms)
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    
    while (true) {
        printf("Sistema em contagem... aguarde a próxima mudança do semáforo\n");
        sleep_ms(1000); // imprime mensagens a cada 1 segundo
    }

    return 0;
    
}
