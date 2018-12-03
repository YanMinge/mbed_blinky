#include "mbed.h"
#include "delay.h"

DigitalOut myled(LED1);

int main() {
    while(1) {
        myled = 1;
        delay_s(0.5);
        myled = 0;
        delay_s(0.5);
    }
}
