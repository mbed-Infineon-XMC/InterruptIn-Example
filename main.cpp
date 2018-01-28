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
InterruptIn sw(SW2);
DigitalOut led1(LED1);
Serial device(P0_5, P0_4); // tx, rx

/****************************************************************** Callbacks */

/**
 * Callback if rising edge detected
 */
void rise_handler(void) {
    // Toggle LED
    led1 = !led1;
}


/**
 * Callback if falling edge detected
 */
void fall_handler(void) {
    device.printf("fall_handler in context %p\r\n", Thread::gettid());
    // Toggle LED
    led1 = !led1;
}

/****************************************************************** Functions */

/**
 * Main Function
 */
int main() {

    // Request the shared queue
    EventQueue *queue = mbed_event_queue();
    device.printf("Starting in context %p\r\n", Thread::gettid());

    // The 'rise' handler will execute in IRQ context
    sw.rise(rise_handler);
    // The 'fall' handler will execute in the context of the shared queue thread
    sw.fall(queue->event(fall_handler));
}

/*EOF*/

