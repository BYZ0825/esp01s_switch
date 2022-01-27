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

#include <Blinker.h>

char auth[] = "1572b2d4cafd";
char ssid[] = "HomeSlow";
char pswd[] = "kxc1220a1b2c3";

#define SW0 0;
#define SW1 1;
#define SW2 2;
#define SW3 3;
uint8_t sw0 = SW0;
uint8_t sw1 = SW1;
uint8_t sw2 = SW2;
uint8_t sw3 = SW3;

BlinkerButton Button0("sw0");
BlinkerButton Button1("sw1");
BlinkerButton Button2("sw2");
BlinkerButton Button3("sw3");

bool oState[4] = {false};
// 按下按键即会执行该函数
void button0_callback(const String &state)
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(sw0, !digitalRead(sw0));
    Blinker.vibrate();
    oState[sw0] = !oState[sw0];
}
void button1_callback(const String &state)
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(sw1, !digitalRead(sw1));
    Blinker.vibrate();
    oState[sw1] = !oState[sw1];
}

void button2_callback(const String &state)
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(sw2, !digitalRead(sw2));
    Blinker.vibrate();
    oState[sw2] = !oState[sw2];
}
void button3_callback(const String &state)
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(sw3, !digitalRead(sw3));
    Blinker.vibrate();
    oState[sw3] = !oState[sw3];
}

void miotPowerState(const String &state, uint8_t num)
{
    BLINKER_LOG("need set outlet: ", num, ", power state: ", state);

    if (state == BLINKER_CMD_ON)
    {
        if (num == 0)
        {
            digitalWrite(sw0, HIGH);
            BlinkerMIOT.powerState("on", num);
            BlinkerMIOT.print();
            oState[num] = true;
        }
        else if (num == 1)
        {
            digitalWrite(sw1, HIGH);
            BlinkerMIOT.powerState("on", num);
            BlinkerMIOT.print();
            oState[num] = true;
        }
        else if (num == 2)
        {
            digitalWrite(sw2, HIGH);
            BlinkerMIOT.powerState("on", num);
            BlinkerMIOT.print();
            oState[num] = true;
        }
        else if (num == 3)
        {
            digitalWrite(sw3, HIGH);
            BlinkerMIOT.powerState("on", num);
            BlinkerMIOT.print();
            oState[num] = true;
        }
    }
    else if (state == BLINKER_CMD_OFF)
    {
        if (num == 0)
        {
            digitalWrite(sw0, LOW);
            BlinkerMIOT.powerState("off", num);
            BlinkerMIOT.print();
            oState[num] = false;
        }
        else if (num == 1)
        {
            digitalWrite(sw1, LOW);
            BlinkerMIOT.powerState("off", num);
            BlinkerMIOT.print();
            oState[num] = false;
        }
        else if (num == 2)
        {
            digitalWrite(sw2, LOW);
            BlinkerMIOT.powerState("off", num);
            BlinkerMIOT.print();
            oState[num] = false;
        }
        else if (num == 3)
        {
            digitalWrite(sw3, LOW);
            BlinkerMIOT.powerState("off", num);
            BlinkerMIOT.print();
            oState[num] = false;
        }
        // if (num == 0)
        // {
        //     for (uint8_t o_num = 0; o_num < 5; o_num++)
        //     {
        //         oState[o_num] = false;
        //     }
        // }
    }
}

void miotQuery(int32_t queryCode, uint8_t num)
{
    BLINKER_LOG("MIOT Query outlet: ", num, ", codes: ", queryCode);

    switch (queryCode)
    {
    case BLINKER_CMD_QUERY_ALL_NUMBER:
        BLINKER_LOG("MIOT Query All");
        BlinkerMIOT.powerState(oState[num] ? "on" : "off", num);
        BlinkerMIOT.print();
        break;
    case BLINKER_CMD_QUERY_POWERSTATE_NUMBER:
        BLINKER_LOG("MIOT Query Power State");
        BlinkerMIOT.powerState(oState[num] ? "on" : "off", num);
        BlinkerMIOT.print();
        break;
    default:
        BlinkerMIOT.powerState(oState[num] ? "on" : "off", num);
        BlinkerMIOT.print();
        break;
    }
}

void dataRead(const String &data)
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();

    uint32_t BlinkerTime = millis();

    Blinker.print("millis", BlinkerTime);
}

void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);

    pinMode(sw0, OUTPUT);
    digitalWrite(sw0, LOW);

    pinMode(sw1, OUTPUT);
    digitalWrite(sw1, LOW);

    pinMode(sw2, OUTPUT);
    digitalWrite(sw2, LOW);

    pinMode(sw3, OUTPUT);
    digitalWrite(sw3, LOW);
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);

    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachQuery(miotQuery);
}

void loop()
{
    Blinker.run();
}