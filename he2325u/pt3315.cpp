#include <stdio.h>
#include <string>
#include <iostream>
#include <inttypes.h>

using namespace std;

int main(){
    for(string line; getline(cin,line);){
        const char* packet = line.data();
        uint8_t range = packet[0] & 0x0F; // range info in lower 4 Bit
        uint8_t d3 = packet[1] & 0x0F; // d 3 info in lower 4 bits
        uint8_t d2 = packet[2] & 0x0F; // d 2 info in lower 4 bits
        uint8_t d1 = packet[3] & 0x0F; // d 1 info in lower 4 bits
        uint8_t d0 = packet[4] & 0x0F; // d 0 info in lower 4 bits
        uint8_t function = packet[5] & 0x0F; // function
        uint8_t status = packet[6] & 0x0F; // status
        uint8_t option1 = packet[7] & 0x0F; // option 1
        uint8_t option2 = packet[8] & 0x0F; // option 2

        cout << "pt received: " << line << endl;

        if(function == 0x0B){ // Voltage reading
            double v = d3 * 1e3 + d2 * 1e2 + d1 * 1e1 + d0;
            if (status & 0x04) v = -v; // check for sign bit 2 in status byte

            double prec = 0;
            switch(range){
                case 0x00: prec = 1e-1; break;
                case 0x01: prec = 1e-3; break;
                case 0x02: prec = 1e-2; break;
                case 0x03: prec = 1e-1; break;
                case 0x04: prec = 1; break; 
                default: prec = 1; break;
            }
            v *= prec;
            cout << "V: " << v << endl;
        }
    }
    return 0;
}


