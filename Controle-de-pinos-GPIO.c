#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pwm.h"

#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13

#define BUZZER_PIN 10

void tocar_buzzer(uint32_t FAIXA, uint32_t CANAL, uint32_t freguencia, uint32_t duracao);

int main() {
	stdio_init_all();
	char buffer[1024];
    int num;
    char* endptr;
	char* token;

	gpio_init(LED_PIN_GREEN);
	gpio_init(LED_PIN_BLUE);
	gpio_init(LED_PIN_RED);
	gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
	gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
	gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    gpio_init(BUZZER_PIN);
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);

    uint32_t numero_faixa = pwm_gpio_to_slice_num(BUZZER_PIN);//Obtendo o número da faixa do PWM
    uint32_t canal = pwm_gpio_to_channel(BUZZER_PIN);//Obtendo o canal do PWM

	while(1)
	{
		scanf("%1024s", buffer);
		printf("%s\n", buffer);
		token = strtok(buffer, "-");
		if (strcmp(buffer, "ON") == 0)
		{
			gpio_put(LED_PIN_GREEN, 0);
			gpio_put(LED_PIN_BLUE, 1);
			gpio_put(LED_PIN_RED, 1);
		} else if (strcmp(buffer, "OFF") == 0)
		{
			gpio_put(LED_PIN_GREEN, 0);
			gpio_put(LED_PIN_BLUE, 0);
			gpio_put(LED_PIN_RED, 0);
		} else if (strcmp(buffer, "REBOOT") == 0)
		{
			reset_usb_boot(0,0);
		} else if (strcmp(token, "BUZZER") == 0)
        {
            printf("%s\n",token);

			token = strtok(NULL, "-");
			printf("%s\n",token);

            num = strtol(token, &endptr, 10);
            printf("%d\n", num);

            if (num%1==0) num=50;
            tocar_buzzer(numero_faixa, canal, num, 2000);
        }
	}	

}

//Função para acionamento do buzzer
void tocar_buzzer(uint32_t FAIXA, uint32_t CANAL, uint32_t freguencia, uint32_t duracao)
{
    uint32_t Freq_clock = 125000000;                           // Frequência do clock padrão da RP2040
    uint32_t divisor_clock = (Freq_clock / freguencia) / 4096; // Divisor correto do clock

    // Configurando o PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, divisor_clock);
    pwm_init(FAIXA, &config, true);

    uint16_t level = 2048; // Nível do duty cycle (50%)
    pwm_set_gpio_level(BUZZER_PIN, level);
    pwm_set_wrap(FAIXA, 4095);
    pwm_set_enabled(FAIXA, true);

    // Tempo de duração do som
    sleep_ms(duracao);

    // Desliga o PWM
    pwm_set_enabled(FAIXA, false);
}