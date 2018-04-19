#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <cstring>
#include <sstream>

#define MAX_VALUE 1900
#define MIN_VALUE 1100


using namespace std;
unsigned int ESC=4;


void stop(void) {
    gpioServo(ESC, 0);
    gpioTerminate();

}

void control(void) {
    cout<<"Starting the motor.. Guess its calibrated and armed"<<endl;
    usleep(1000);
    char input = '0';
    unsigned int speed= 1500;
    cout<<"CONTROLS= 'a' to decrease speed && 'd' to increase the speed"<<endl;
    cout<<"CONTROLS= 's' to stop"<<endl;
    while(1) {
        gpioServo(ESC, speed);
        cin>>input;
        if(input=='a')
            speed-=10;
        else if(input == 'd')
            speed+=10;
        else if(input=='s') {
            stop();
            break;
        }
        else
            cout<<"Press one of the controls!!"<<endl;

    }

}

void arm(void) {
    cout<<"Connect the battery and press Enter"<<endl;
    char input= '0';
    cin>>input;
    if(input==' ') {
        gpioServo(ESC, 0);
        usleep(1000);
        gpioServo(ESC, 1500); //in the main program the value is sent to 1500
        usleep(1000);
        gpioServo(ESC, MIN_VALUE);
        usleep(1000);
        control();
    }

}


void calibrate() {
    gpioServo(ESC, 0);
    cout<<"Disconnect the battery and press space bar"<<endl;
    char input1='0', input2='0', input3='0';
    cin>>input1;
    if(input1==' ')
    {
        gpioServo(ESC, MAX_VALUE);
        cout<<"CONNECT the battery now... you will hear two beeps, then wait for a gradual falling tone then press space"<<endl;
        cin>>input2;
        if(input2==' ')
        {
            gpioServo(ESC, MIN_VALUE);
            cout<<"Weird Tone!!!!"<<endl;
            usleep(7000);
            cout<<"WAIT FOR IT"<<endl;
            usleep(5000);
            cout<<"Working on it!!"<<endl;
            gpioServo(ESC, 0);
            usleep(2000);
            cout<<"Arming ESC now!!!"<<endl;
            gpioServo(ESC, MIN_VALUE);
            usleep(1000);
            cout<<"See it worksYAY!"<<endl;
            control();

        }

    }

}

void manual_drive() {
    cout<<"You have selected manual option----select a value between "<<MAX_VALUE<<" and "<<MIN_VALUE<<endl;
    while(1){
        string input;
        if(input == "stop")
        {
            stop();
            break;
        }

        else if(input == "control")
        {
            control();
            break;
        }

        else if (input == "arm")
        {
            arm();
            break;
        }
        else{
            stringstream numsinput(input);
            unsigned int num_input=0;
            numsinput>>num_input;
            gpioServo(ESC, num_input);
        }


    }

}




int main() {

    int ok= gpioInitialise();
    if(ok> 0)
        cout<<"Library initialised!!"<<endl;
    else
    {
        cout<<"Initialisation failed"<<endl;
        return 0;
    }

    usleep(1000);
    if(gpioServo(ESC, 0 )!=0){
        cout<<"Setting servo pulse failed!!!"<<endl;
        return 0;
    }

    cout<<"For the first time, Launch calibrate"<<endl;
    cout<<"Type the word that you want to use"<<endl;
    cout<<"calibrate----OR---manual---OR----stop---OR-------arm"<<endl;

    string input;
    if(input == "stop")
        stop();

    else if(input == "control")
        control();


    else if (input == "arm")
        arm();

    else if(input=="manual")
        manual_drive();

    else if(input =="calibrate")
        calibrate();

    else
        cout<<"Restart the program and enter one of the above fucking values"<<endl;

    return 0;
}