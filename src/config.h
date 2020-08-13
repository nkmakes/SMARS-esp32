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