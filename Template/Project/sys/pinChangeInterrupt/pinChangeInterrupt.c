//
// Created by joey on 2024-06-18.
//

#include "pinChangeInterrupt.h"

/****************************/
/****** ready pin flag ******/
/****************************/

volatile bool flag100HzBMA456 = false;

void enableBMA456ReadyPin100Hz()
{
		flag100HzBMA456 = true;
}

void disableBMA456ReadyPin100Hz()
{
		flag100HzBMA456 = false;
}

bool isBMA456ReadyPin100Hz()
{
		return flag100HzBMA456;
}

/****************************/
/********* handler **********/
/****************************/

void handlerBMA456(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
		enableBMA456ReadyPin100Hz();
}

void initRDYPinBMA456()
{
		ret_code_t err_code;
		
		nrf_drv_gpiote_in_config_t configBMA456 = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    configBMA456.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(12, &configBMA456, handlerBMA456);
    APP_ERROR_CHECK(err_code);
		
    nrf_drv_gpiote_in_event_enable(12, true);
}

void initPinChangeInterrupt()
{
    ret_code_t err_code;
	
    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);
		
		initRDYPinBMA456();
}