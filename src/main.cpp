// Template_Application_ESP32_V2.0

#include "../src/apps/atApp_ABC.h"
#include "../src/apps/atApp_Wifi.h"
#include "../src/apps/atApp_CP.h"
#include "../src/apps/atApp_MB_RTU_SL.h"
#include "../src/apps/atApp_MB_TCP_SL.h"
void setup() {
// uncomment to put the app in debug mod
  // atApp_ABC.Debug();
  atApp_Wifi.Debug();
  // atApp_CP.Debug();
  // atApp_MB_RTU_SL.Debug();
  // atApp_MB_TCP_SL.Debug();

//---------------------------------------------  Tasks table -------------------------------------------------------------------------------------------------------//     
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// || Creation           ||     Task function         ||     PC name                    || heap size  || Parameter || Priority  || Task handle          || CoreID   ||
  xTaskCreatePinnedToCore(  atApp_CP_Task_Func        , "atApp_CP_Application"          ,  10000      ,     NULL    ,   1       , &Task_atApp_CP        ,    0     );
  xTaskCreatePinnedToCore(  atApp_Wifi_Task_Func      , "atApp_Wifi_Application"        ,  10000      ,     NULL    ,   1       , &Task_atApp_Wifi      ,    1     );
  xTaskCreatePinnedToCore(  atApp_MB_RTU_SL_Task_Func , "atApp_MB_RTU_SL_Application"   ,  50000      ,     NULL    ,   1       , &Task_atApp_MB_RTU_SL ,    1     );
  xTaskCreatePinnedToCore(  atApp_MB_TCP_SL_Task_Func , "atApp_MB_TCP_SL_Application"   ,  50000      ,     NULL    ,   1       , &Task_atApp_MB_TCP_SL ,    1     );

// Some tasks need to wait some task init..
  vTaskSuspend(Task_atApp_MB_TCP_SL);
}

void loop() {}