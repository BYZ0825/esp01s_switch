/* *****************************************************************
 *
 * Download latest Blinker library here:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * 
 * Blinker is a cross-hardware, cross-platform solution for the IoT. 
 * It provides APP, device and server support, 
 * and uses public cloud services for data transmission and storage.
 * It can be used in smart home, data monitoring and other fields 
 * to help users build Internet of Things projects better and faster.
 * 
 * Make sure installed 2.7.4 or later ESP8266/Arduino package,
 * if use ESP8266 with Blinker.
 * https://github.com/esp8266/Arduino/releases
 * 
 * Make sure installed 1.0.5 or later ESP32/Arduino package,
 * if use ESP32 with Blinker.
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * Docs: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************
 * 
 * Blinker 库下载地址:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * Blinker 是一套跨硬件、跨平台的物联网解决方案，提供APP端、设备端、
 * 服务器端支持，使用公有云服务进行数据传输存储。可用于智能家居、
 * 数据监测等领域，可以帮助用户更好更快地搭建物联网项目。
 * 
 * 如果使用 ESP8266 接入 Blinker,
 * 请确保安装了 2.7.4 或更新的 ESP8266/Arduino 支持包。
 * https://github.com/esp8266/Arduino/releases
 * 
 * 如果使用 ESP32 接入 Blinker,
 * 请确保安装了 1.0.5 或更新的 ESP32/Arduino 支持包。
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * 文档: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************/

#define BLINKER_WIFI
#define BLINKER_MIOT_MULTI_OUTLET
#define BLINKER_WITHOUT_SSL //非SSL加密通信接入，省堆栈

#include <Blinker.h>

char auth[] = "1572b2d4cafd";
char ssid[] = "HomeSlow";
char pswd[] = "kxc1220a1b2c3";
#define LED 2                     // 板子上的灯
BlinkerButton Button1("btn-abc"); //注意：要和APP组件’数据键名’一致
bool wsState;
uint8_t wsMode = BLINKER_CMD_MIOT_DAY;
// 按下BlinkerAPP按键即会执行该函数
void button1_callback(const String &state)
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED, !digitalRead(GPIO));
    Blinker.vibrate();
}

//小爱电源类操作的回调函数:
//当小爱同学向设备发起控制, 设备端需要有对应控制处理函数
void miotPowerState(const String &state)
{
    BLINKER_LOG("need set power state: ", state);
    if (state == BLINKER_CMD_ON)
    {
        digitalWrite(LED, LOW); //低电平点灯
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
        wsState = true;
    }
    else if (state == BLINKER_CMD_OFF)
    {
        digitalWrite(LED, HIGH); //高电平开灯
        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
        wsState = false;
    }
}

//小爱同学 的回调查询函数，照抄即可。主要是查询 当前灯的状态
void miotQuery(int32_t queryCode)
{
    BLINKER_LOG("MIOT Query codes: ", queryCode);
    switch (queryCode)
    {
    case BLINKER_CMD_QUERY_ALL_NUMBER:
        BLINKER_LOG("MIOT Query All");
        BlinkerMIOT.powerState(wsState ? "on" : "off");
        BlinkerMIOT.color(0);
        BlinkerMIOT.mode(0);
        BlinkerMIOT.colorTemp(1000);
        BlinkerMIOT.brightness(1);
        BlinkerMIOT.print();
        break;
    case BLINKER_CMD_QUERY_POWERSTATE_NUMBER:
        BLINKER_LOG("MIOT Query Power State");
        BlinkerMIOT.powerState(wsState ? "on" : "off");
        BlinkerMIOT.print();
        break;
    default:
        BlinkerMIOT.powerState(wsState ? "on" : "off");
        BlinkerMIOT.color(0);
        BlinkerMIOT.mode(0);
        BlinkerMIOT.colorTemp(1000);
        BlinkerMIOT.brightness(1);
        BlinkerMIOT.print();
        break;
    }
}

void setup()
{
    // 初始化串口，并开启调试信息，调试用可以删除
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    // 初始化IO
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH); // 初始化 led 高电平 ，则灯熄灭状态

    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);

    //小爱同学务必在回调函数中反馈该控制状态
    BlinkerMIOT.attachPowerState(miotPowerState); //注册回调函数
    BlinkerMIOT.attachQuery(miotQuery);
}
void loop()
{
    Blinker.run();
}