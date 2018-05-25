#ifndef SERIAL_H
#define SERIAL_H

#define BAUD_RATE B9600

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <sstream>

#include <string>

#include <inttypes.h>
#include <math.h>
#include <time.h>

class Serial
{
private:
    struct termios tio;
    struct termios stdio;
    int tty_fd;
    unsigned char c;
    char* port;
public:
    Serial(char*);
    void open_communication();
    void close_communication();
    std::string send_message(char*);
    void set_baud();
    void add_flag(int);
    void mask_flag();
    void set_blocking(bool);
    void set_port(char*);
};

#endif
