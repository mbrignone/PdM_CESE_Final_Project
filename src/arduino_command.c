/* ===== [arduino_command.c] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/20
 */


/* ===== Dependencies ===== */
#include "arduino_command.h"


/* ===== Macros of private constants ===== */
#define ASCII_RSP_OK '1' 


/* ===== Prototypes of private functions ===== */


/* ===== Implementations of public functions ===== */
void reset_arduino_cmd(arduino_cmd_t * cmd)    {
    cmd->cmd        = 0;
    cmd->rsp_header = 0;
    cmd->rsp        = 0;
    delayConfig(&cmd->delay, ARDUINO_TIMEOUT);
}


void start_arduino_timeout (arduino_cmd_t * cmd)    {
    delayConfig(&cmd->delay, ARDUINO_TIMEOUT);
    // the delay starts after being read once
    delayRead(&cmd->delay);
}

uint8_t check_arduino_rsp(arduino_cmd_t * cmd)  {
    if (cmd->rsp_header != 'A') {
        return RSP_ERROR;
    } 

    // there must be an additional byte ready to be received
    if (!uartReadByte(UART_USB, &cmd->rsp))  {
        return RSP_ERROR;
    }

    if (cmd->rsp != ASCII_RSP_OK) {
        return RSP_ERROR;
    }

    // if the function reaches this point, everything is ok
    return RSP_OK;
}

void send_cmd_to_arduino(uint8_t id)    {
    char cmd_string[5];
    sprintf(cmd_string, "A_%c\r\n", id);
    
    uartWriteString(UART_USB, cmd_string);
}

void setup_arduino_command(arduino_cmd_t * cmd, uint8_t rx_byte)    {
    reset_arduino_cmd(cmd);
    cmd->cmd = rx_byte;
    start_arduino_timeout(cmd);
}

/* ===== Implementations of private functions ===== */

