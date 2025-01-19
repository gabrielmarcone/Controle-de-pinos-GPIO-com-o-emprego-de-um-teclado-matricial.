#include <pico/stdlib.h>
#include <stdio.h>
// Definindo linhas e colunas do teclado matricial
#define ROW1 8  
#define ROW2 7  
#define ROW3 6  
#define ROW4 5  
#define COL1 4 
#define COL2 3  
#define COL3 2  
#define COL4 28  

// Definições dos LEDs RGB
#define LED_RED 13
#define LED_BLUE 12
#define LED_GREEN 11

// Definição do buzzer
#define BUZZER 21

// Configuração inicial dos GPIOs
void setup_gpio() {
    // Configurando linhas do teclado como saídas
    gpio_init(ROW1); gpio_set_dir(ROW1, GPIO_OUT);
    gpio_init(ROW2); gpio_set_dir(ROW2, GPIO_OUT);
    gpio_init(ROW3); gpio_set_dir(ROW3, GPIO_OUT);
    gpio_init(ROW4); gpio_set_dir(ROW4, GPIO_OUT);

    // Configurando colunas do teclado como entradas com pull-down
    gpio_init(COL1); gpio_set_dir(COL1, GPIO_IN); gpio_pull_down(COL1);
    gpio_init(COL2); gpio_set_dir(COL2, GPIO_IN); gpio_pull_down(COL2);
    gpio_init(COL3); gpio_set_dir(COL3, GPIO_IN); gpio_pull_down(COL3);
    gpio_init(COL4); gpio_set_dir(COL4, GPIO_IN); gpio_pull_down(COL4);

    // Configurando LEDs RGB como saidas
    gpio_init(LED_RED); gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_BLUE); gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_GREEN); gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Configurando buzzer como saída
    gpio_init(BUZZER); gpio_set_dir(BUZZER, GPIO_OUT);
}

// Função para acionar LEDs
void control_leds(uint8_t red, uint8_t blue, uint8_t green) {
    gpio_put(LED_RED, red);
    gpio_put(LED_BLUE, blue);
    gpio_put(LED_GREEN, green);
}

// Função para ativar e desativar o buzzer
void control_buzzer(uint8_t state) {
    gpio_put(BUZZER, state);
}

// Função para ler o teclado matricial 4x4
char read_keypad() {
    const char keys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    uint8_t rows[4] = {ROW1, ROW2, ROW3, ROW4};
    uint8_t cols[4] = {COL1, COL2, COL3, COL4};

    for (int r = 0; r < 4; r++) {
        gpio_put(rows[r], true); // ativação da linha
        sleep_us(50); 

        for (int c = 0; c < 4; c++) {
            if (gpio_get(cols[c])) { // Verificação de sinal na coluna
                gpio_put(rows[r], false); // Desativa a linha
                return keys[r][c]; // Retorna a tecla pressionada
            }
        }
        gpio_put(rows[r], false); // Desativa a linha
    }

    return 0; 
}

int main() {
    stdio_init_all();
    setup_gpio();

    while (true) {
        char key = read_keypad(); // Leitura do teclado matricial 4x4

        if (key != 0) { // Se alguma tecla for pressionada
            printf("Tecla pressionada: %c\n", key);

            switch (key) {
                case '1': // Liga o LED vermelho
                    control_leds(1, 0, 0);
                    break;
                case '2': // Liga o LED azul
                    control_leds(0, 1, 0);
                    break;
                case '3': // Liga o LED verde
                    control_leds(0, 0, 1);
                    break;
                case '4': // Liga todos os LEDs
                    control_leds(1, 1, 1);
                    break;
                case 'A': // Aciona o buzzer
                    control_buzzer(1);
                    break;
                case 'B': // Desliga o buzzer
                    control_buzzer(0);
                    break;
                default: // Desliga os LEDs
                    control_leds(0, 0, 0);
                    break;
            }
        }

        sleep_ms(100); // delay para evitar leituras repetidas
    }

    return 0;
}
