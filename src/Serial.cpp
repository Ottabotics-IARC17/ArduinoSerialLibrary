#include "Serial.h"

Serial::Serial(char* port)
{
    this->port = port;

    fd_set rdset;

    memset(&stdio,0,sizeof(stdio));

    stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=1;
    stdio.c_cc[VTIME]=0;

    //tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    //tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    set_baud();
    set_blocking(false);
    mask_flag();

}

void Serial::open_communication()
{
    tty_fd = open(port, O_RDWR | O_NONBLOCK);
}

void Serial::close_communication()
{
    close(tty_fd);
}

std::string Serial::send_message(char* message)
{
    tcsetattr(tty_fd,TCSANOW,&tio);

    write(tty_fd, message, strlen(message));

    std::string retval = "";
    unsigned char c = ' ';

    // TODO: add timeout

    //while (c != '\n')
    //{
        if (read(tty_fd, &c, 1) > 0)
        {
            if (c != '\n')
            {
                retval += c;
            }
        }
    //}




    return retval;
}

void Serial::set_baud()
{
    cfsetospeed(&tio, BAUD_RATE);
    cfsetispeed(&tio, BAUD_RATE);
}

void Serial::add_flag(int flag)
{
    tio.c_cflag &= ~flag;
}

void Serial::mask_flag()
{
    // set character size to 8 bits
    tio.c_cflag |= CS8;
}

void Serial::set_blocking(bool enabled)
{
    if(enabled) {
        tio.c_cc[VMIN] = 1;
    } else {
        tio.c_cc[VMIN] = 0;
    }
}
