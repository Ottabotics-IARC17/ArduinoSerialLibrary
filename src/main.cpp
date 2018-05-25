#include <iostream>
#include "Serial.h"


int main()
{
    std::cout << "Arduino serial communication" << std::endl;

    Serial s("/dev/ttyUSB0");
    s.open_communication();
    for (int i = 0; i < 10; ++i)
    {
        std::cout << s.send_message("hi") << std::endl;
    }

    s.close_communication();

    return 0;
}
