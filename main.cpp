/*
 * Copyright (c) 2023, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "pid.h"

// Define the PID rate
#define PID_RATE 100ms

static DigitalOut led1(LED1);

#define PID_FLAG 0x01
Ticker PIDUpdateTicker;
EventFlags PIDFlag;

void PIDFlagUpdate()
{
    PIDFlag.set(PID_FLAG);
}

int main()
{

    // First, convert the rate of the loop in seconds [float]
    auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(PID_RATE);
    float dt_pid = f_secs.count();

    // Then, create a set of PID parameters
    sixtron::PID_params my_pid_parameters;
    my_pid_parameters.Kp = 0.2f;
    my_pid_parameters.Ki = 0.05f;
    my_pid_parameters.Kd = 0.0f;
    my_pid_parameters.dt_seconds = dt_pid;

    // Create a PID using previous parameters
    sixtron::PID my_pid(my_pid_parameters);

    // Setup ticker to update PID flag at exactly the defined rate
    PIDUpdateTicker.attach(&PIDFlagUpdate, PID_RATE);

    // Create blank arguments for PID input/output
    sixtron::PID_args my_pid_args;

    // Update target.
    // MOTOR EXAMPLE:
    //      This should be the motor target speed in [m/s].
    //      But for the purpose of this example, we just put a dummy target.
    my_pid_args.target = 12345.f;

    while (true) {
        // Wait for PID tick
        PIDFlag.wait_any(PID_FLAG);
        led1 = !led1;

        // Update input.
        // MOTOR EXAMPLE:
        //      This should be the sensor output, telling at which speed in [m/s] the motor
        //      is actually running.
        //      But for the purpose of this example, we just loop the output to the input.
        my_pid_args.actual = my_pid_args.output;

        // Compute PID
        my_pid.compute(&my_pid_args);

        // Get output.
        // MOTOR EXAMPLE:
        //      This should be the motor command control, eg the value of the PWM [%].
        //      But for the purpose of this example, we just print the output.
        printf("PID Output : %8.2f\n", my_pid_args.output);
    }
}
