/** Simple On-board LED flashing program
*
*    This program uses USR LED 3 and can be executed in 5 ways:
*         makeLED-hw6 on
*         makeLED-hw6 off
*         makeLED-hw6 flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED-hw6 status (get the trigger status)
*         makeLED-hw6 blink 10 (blink the LED 10 times)
*/

#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   if(argc!=2 && argc!=3){
	cout << "Usage is makeLED-hw6 and one of: " << endl;
        cout << "   on, off, flash, status, or blink <num blinks>" << endl;
	cout << " e.g. makeLED-hw6 blink 5" << endl;
        return 2;
   }
   string cmd(argv[1]);
   int n = *argv[2]-'0';
   cout << "Starting the makeLED-hw6 program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else if (cmd=="blink"){
   	cout << "Blinking the LED " << n << " times." <<endl;
   	for (int i=0; i<n; i++){
	writeLED("/brightness", "1");
	sleep(1);
	writeLED("/brightness", "0");
	sleep(1);
   	}
   }
   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
