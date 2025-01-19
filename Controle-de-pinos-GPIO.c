#include <stdio.h>
#include "pico/stdlib.h"
// Variaveis dos LEDs
#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13

void inicializar() {
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
}
// funcao para desligar os LEDs
void desligar_leds() {
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
}

void ligar_leds(uint led) {
    desligar_leds();
    gpio_put(led, 1);
}

void ligar_todosLeds() {
    gpio_put(LED_VERDE, 1);
    gpio_put(LED_AZUL, 1);
    gpio_put(LED_VERMELHO, 1);
}

int main()
{
    stdio_init_all();
    inicializar();

    char comando;
    //funcao para pegar o comando do usuario e ligar o respectivo LED
    while (true) {
        comando = getchar_timeout_us(1000000);
        switch (comando)
        {
        case '1':
            ligar_leds(LED_VERDE);
            printf("Ligando LED Verde\n");
            break;
        case '2':
            ligar_leds(LED_AZUL);
            printf("Ligando LED Azul\n");
            break;
        case '3':
            ligar_leds(LED_VERMELHO);
            printf("Ligando LED Vermelho\n");
            break;
        case '4':
            ligar_todosLeds();
            printf("Ligando todos os LEDs\n");
            break;
        case '0':
            desligar_leds();
            printf("Desligando todos os LEDs\n");
            break;
        default:
            break;
        }
    }
    return 0;
}
