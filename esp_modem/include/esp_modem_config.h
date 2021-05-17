// Copyright 2021 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _ESP_MODEM_CONFIG_H_
#define _ESP_MODEM_CONFIG_H_
#include "driver/uart.h"
#include "esp_modem_dce_config.h"

/**
 * @defgroup ESP_MODEM_CONFIG
 * @brief Configuration structures for DTE and DCE
 */

/** @addtogroup ESP_MODEM_CONFIG
 * @{
 */

/**
 * @brief Modem flow control type
 *
 */
typedef enum {
    ESP_MODEM_FLOW_CONTROL_NONE = 0,
    ESP_MODEM_FLOW_CONTROL_SW,
    ESP_MODEM_FLOW_CONTROL_HW
} esp_modem_flow_ctrl_t;

/**
 * @brief DTE configuration structure
 *
 */
struct esp_modem_uart_term_config {
    uart_port_t port_num;           /*!< UART port number */
    uart_word_length_t data_bits;   /*!< Data bits of UART */
    uart_stop_bits_t stop_bits;     /*!< Stop bits of UART */
    uart_parity_t parity;           /*!< Parity type */
    esp_modem_flow_ctrl_t flow_control; /*!< Flow control type */
    int baud_rate;             /*!< Communication baud rate */
    int tx_io_num;                  /*!< TXD Pin Number */
    int rx_io_num;                  /*!< RXD Pin Number */
    int rts_io_num;                 /*!< RTS Pin Number */
    int cts_io_num;                 /*!< CTS Pin Number */
    int rx_buffer_size;             /*!< UART RX Buffer Size */
    int tx_buffer_size;             /*!< UART TX Buffer Size */
    int event_queue_size;           /*!< UART Event Queue Size, set to 0 if no event queue needed */
};

/**
 * @brief Resources used by VFS terminal
 *
 */
typedef enum {
    ESP_MODEM_VFS_IS_EXTERN = 0,    /*!< External resource: internal VFS terminal takes no action to setup this */
    ESP_MODEM_VFS_IS_UART,          /*!< VFS uses UART: internal VFS initializes UART based on esp_modem_uart_term_config */
} esp_modem_vfs_resource_t;


struct esp_modem_vfs_term_config {
    const char* dev_name;               /*!< VFS device name, e.g. /dev/uart/n */
    esp_modem_vfs_resource_t resource;  /*!< Underlying device which gets initialized during VFS init */
};

struct esp_modem_dte_config {
    size_t dte_buffer_size;                             /*!< DTE buffer size */
    uint32_t task_stack_size;                           /*!< Terminal task stack size */
    int task_priority;                                  /*!< Terminal task priority */
    struct esp_modem_uart_term_config uart_config;      /*!< Configuration for UART Terminal */
    struct esp_modem_vfs_term_config vfs_config;        /*!< Configuration for VFS Terminal */
};


/**
 * @brief ESP Modem DTE Default Configuration
 *
 */
#define ESP_MODEM_DTE_DEFAULT_CONFIG() \
    {                                  \
        .dte_buffer_size = 512,        \
        .task_stack_size = 4096, \
        .task_priority = 5,      \
        .uart_config = {               \
            .port_num = UART_NUM_1,                 \
            .data_bits = UART_DATA_8_BITS,          \
            .stop_bits = UART_STOP_BITS_1,          \
            .parity = UART_PARITY_DISABLE,          \
            .flow_control = ESP_MODEM_FLOW_CONTROL_NONE,\
            .baud_rate = 115200,                    \
            .tx_io_num = 25,                        \
            .rx_io_num = 26,                        \
            .rts_io_num = 27,                       \
            .cts_io_num = 23,                       \
            .rx_buffer_size = 4096,                 \
            .tx_buffer_size = 512,                  \
            .event_queue_size = 30,                 \
       },                                           \
       .vfs_config = {                              \
            .dev_name = "/null",                    \
       }\
    }

typedef struct esp_modem_dte_config esp_modem_dte_config_t;

/**
 * @}
 */

#endif // _ESP_MODEM_CONFIG_H_
