<!--
 * @Description: 
 * @Version: 
 * @Author: BaiYiZhuo
 * @Date: 2022-01-28 01:04:26
 * @LastEditTime: 2022-01-28 01:04:42
-->
# ESP8266-01s多孔插座
&emsp;基于Blinker点灯SDK的Ardunio的四孔插座控制，可以实现小爱同学以及Blinker App控制，参考官方源码，这里mark一下，方便自己以后使用。使用时替换如下内容即可：
```c++
char auth[] = "你的blinker的api";
char ssid[] = "WIFI SSID";
char pswd[] = "你的WIFI密码";
```