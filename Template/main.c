#include "Project/app/app.h"
#include "Project/api/api.h"
#include "Project/sys/sys.h"
#include "Project/sys/headerfile.h"
#include "Project/protocol/protocol.h"
#include "Project/filter/filter.h"

void handerLowPowerConsumption()
{
    nrf_pwr_mgmt_init();
    nrf_pwr_mgmt_run();		 // initConverterMCUState
		NRF_POWER->DCDCEN = 1; // initConverterDCDC
}

void initPeripherals()
{
		initNRF52Port();
    initUART();
		initSeggerRTT();
    initI2C();
//    initSPI();
//		initADC();
		initPinChangeInterrupt();
	
		nrf_delay_ms(20);
    NRF_LOG_INFO("initPeripherals Completed");
    NRF_LOG_FLUSH();
}

void initSensors()
{
		initBMA456();		
		nrf_delay_ms(50);
    NRF_LOG_INFO("initSensors Completed");
    NRF_LOG_FLUSH();
}

int main()
{
		handerLowPowerConsumption();
		initPeripherals();
		initSensors();
//		initTimerInterrupt();
  
    while (true)
    {
				if(isBMA456ReadyPin100Hz())
				{
						BMA456();
						disableBMA456ReadyPin100Hz();
				}
    } // while
} // main
