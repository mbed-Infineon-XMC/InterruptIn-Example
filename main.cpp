/* mbed Example Program
 * Copyright (c) 2006-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************* Includes */
#include "mbed.h"
#include "rtos.h"

/******************************************************************** Globals */
InterruptIn button(SW2);
DigitalOut flash(LED1);
DigitalOut led(LED2, 1);

/****************************************************************** Callbacks */

/**
 * Callback if rising edge detected
 */
void rise() {
    led.write(1);
}

/**
 * Callback if falling edge detected
 */
void fall() {
    led.write(0);
}

/****************************************************************** Functions */

/**
 * Main Function
 */
int main() {
    /* Attach rising & falling callback functions */
    button.rise(&rise);
    button.fall(&fall);

    /* Flash LED1 periodically */
    while(1) {
        flash = !flash;
        wait(0.25);
    }
}

/*EOF*/

