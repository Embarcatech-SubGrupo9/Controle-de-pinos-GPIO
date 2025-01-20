#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pwm.h"
#include "hardware/watchdog.h"

// Variáveis dos LEDs
#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BUZZER_PIN 10

void tocar_buzzer(uint32_t FAIXA, uint32_t CANAL, uint32_t frequencia, uint32_t duracao);
void inicializar();
void desligar_leds();
void ligar_leds(uint led);
void ligar_todosLeds();
void reboot_sistema();

int main()
{
	stdio_init_all();
	inicializar();
	char buffer[1024];
	int num;
	char *endptr;
	char *token;

	gpio_init(BUZZER_PIN);
	gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);

	uint32_t numero_faixa = pwm_gpio_to_slice_num(BUZZER_PIN); // Obtendo o número da faixa do PWM
	uint32_t canal = pwm_gpio_to_channel(BUZZER_PIN);		   // Obtendo o canal do PWM

	while (1)
	{
		scanf("%1024s", buffer);
		printf("%s\n", buffer);
		token = strtok(buffer, "-");

		if (strcmp(buffer, "green") == 0)
		{
			ligar_leds(LED_VERDE);
			printf("Ligando LED Verde\n");
			sleep_ms(100);
		}
		else if (strcmp(buffer, "blue") == 0)
		{
			ligar_leds(LED_AZUL);
			printf("Ligando LED Azul\n");
			sleep_ms(100);
		}
		else if (strcmp(buffer, "red") == 0)
		{
			ligar_leds(LED_VERMELHO);
			printf("Ligando LED Vermelho\n");
			sleep_ms(100);
		}
		else if (strcmp(buffer, "white") == 0)
		{
			ligar_todosLeds();
			printf("Ligando todos os LEDs\n");
			sleep_ms(100);
		}
		else if (strcmp(buffer, "off") == 0)
		{
			desligar_leds();
			printf("Desligando todos os LEDs\n");
			sleep_ms(100);
		}
		else if (strcmp(buffer, "boot") == 0)
		{
			reboot_sistema();
		}
		else if (strcmp(token, "buzzer") == 0)
		{
			printf("%s\n", token);

			token = strtok(NULL, "-");
			printf("%s\n", token);

			num = strtol(token, &endptr, 10);
			printf("%d\n", num);

			if (num % 1 == 0)
				num = 50;
			tocar_buzzer(numero_faixa, canal, num, 2000);
		}
	}
}

void inicializar()
{
	gpio_init(LED_VERDE);
	gpio_init(LED_AZUL);
	gpio_init(LED_VERMELHO);
	gpio_set_dir(LED_VERDE, GPIO_OUT);
	gpio_set_dir(LED_AZUL, GPIO_OUT);
	gpio_set_dir(LED_VERMELHO, GPIO_OUT);
}

// Função para desligar os LEDs
void desligar_leds()
{
	gpio_put(LED_VERDE, 0);
	gpio_put(LED_AZUL, 0);
	gpio_put(LED_VERMELHO, 0);
}

void ligar_leds(uint led)
{
	desligar_leds();
	gpio_put(led, 1);
}

void ligar_todosLeds()
{
	gpio_put(LED_VERDE, 1);
	gpio_put(LED_AZUL, 1);
	gpio_put(LED_VERMELHO, 1);
}

// Função para acionamento do buzzer
void tocar_buzzer(uint32_t FAIXA, uint32_t CANAL, uint32_t frequencia, uint32_t duracao)
{
	uint32_t Freq_clock = 125000000;						   // Frequência do clock padrão da RP2040
	uint32_t divisor_clock = (Freq_clock / frequencia) / 4096; // Divisor correto do clock

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

void reboot_sistema(){
	reset_usb_boot(0,0);
}