# Controle de pinos GPIO com BitDogLab

## Sobre o projeto
Esta atividade consiste no controle de pinos GPIO do microcontrolador RP2040 utilizando a ferramenta educacional **BitDogLab** (versão 6.3). Os periféricos envolvidos são:

1. **LED RGB** conectado aos GPIOs 11, 12 e 13.
2. **Buzzer** conectado ao GPIO 5, acionado pelo Botão A.

A comunicação entre o usuário e o sistema embarcado será feita por comandos interpretados pelo microcontrolador, enviados através da interface serial UART.

---

## Componentes necessários
- Ferramenta educacional **BitDogLab** (versão 6.3).
- Cabo micro-USB para USB-A.
- Computador pessoal com **Visual Studio Code**.
- Software de emulação de terminal **PuTTY**.
- Simulador **Wokwi** integrado ao VS Code.

---

## Funcionalidades
As funcionalidades implementadas incluem:

1. **Controle do LED RGB**:
   - **Luz verde**: GPIO 11 ativado; GPIOs 12 e 13 desativados.
   - **Luz azul**: GPIO 12 ativado; GPIOs 11 e 13 desativados.
   - **Luz vermelha**: GPIO 13 ativado; GPIOs 11 e 12 desativados.
   - **Luz branca**: GPIOs 11, 12 e 13 ativados simultaneamente.
   - **Desligar todos os LEDs**: Todos os GPIOs desativados.

2. **Controle do buzzer**:
   - Ativação do buzzer (GPIO 10) por 2 segundos.

3. **Reboot** (opcional): Habilitar o modo de gravação via software.

---

## Estrutura do repositório

```
├── src
│   ├── Controle-de-pinos-GPIO.c       # Código principal da aplicação
|   |-- driagram.json                  # Código do digrama da placa raspberry pi pico W
├── README.md        # Documentação do projeto
├── .gitignore       # Arquivo de configuração para ignorar arquivos desnecessários
└── Makefile         # Configuração de compilação
```

---

## 👥 Equipe de Desenvolvimento

- **Líder**: *Fernando Hali Santos Andrade*  
- **Desenvolvedores**
- Angela Marim Bosetti  
- Leandro Alves dos Santos  
- Heli Neres Silva  
- Gabriel Adriano de Jesus Reis  
- Luis Eduardo F. S. Pereira  

---

## Instruções de uso

1. Conecte o **BitDogLab** ao computador usando o cabo micro-USB.
2. Abra o PuTTY e configure a conexão serial UART.
3. Execute os comandos abaixo para controlar os periféricos:

   - `LED_GREEN` - Liga o LED verde (GPIO 11).
   - `LED_BLUE` - Liga o LED azul (GPIO 12).
   - `LED_RED` - Liga o LED vermelho (GPIO 13).
   - `LED_WHITE` - Liga todos os LEDs (luz branca).
   - `LED_OFF` - Desliga todos os LEDs.
   - `BUZZER` - Aciona o buzzer por 2 segundos.
   - `REBOOT` - Reinicia o microcontrolador.

---

## Testes

Os seguintes testes básicos foram implementados:
- Verificação do acionamento correto dos LEDs.
- Geração de sinal sonoro pelo buzzer.
- Resposta do sistema aos comandos enviados via UART.

---


## Link do vídeo ensaio
[Vídeo da prática](#) *(Adicionar link após a produção do vídeo)*
