#include "pico/stdlib.h"

// Definições das linhas e colunas do teclado matricial
#define ROW1 5
#define ROW2 6
#define ROW3 7
#define ROW4 8
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

int main() {
    stdio_init_all();
    setup_gpio();

    while (true) {
    }
    return 0;
}