const char* ssid = "ESP32_ROBv1"; //Enter SSID
const char* password = "yourpasswd"; //Enter Password

#define AIN1 13
#define BIN1 12
#define AIN2 14
#define BIN2 25
#define PWMA 26
#define PWMB 27
#define STBY 17

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

Motor motor2 = Motor(AIN1, AIN2, PWMA, offsetA, STBY,5000 ,8,1 );
Motor motor1 = Motor(BIN1, BIN2, PWMB, offsetB, STBY,5000 ,8,2 );
 
using namespace websockets;
WebsocketsServer server;
AsyncWebServer webserver(80);

int LValue, RValue, commaIndex;