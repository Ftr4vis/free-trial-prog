#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <termios.h>

using namespace std;

void offer();

struct passwd* pw = getpwuid(getuid());
const char* homedir = pw->pw_dir;
string homedir_str(homedir);

int main() {
	time_t time_now;
	time_t birth_time;
	int time_limit; // seconds to use
	int count; // times to launch
	bool is_ok = 1;
	ifstream file_license(homedir_str + "/.lab2_licenseinfo");
	if (file_license >> count && count != -1) {
		if (count <= 0) {
			cout << "License is expired" << endl;
			is_ok = 0;
			offer();
			return 1;
		}
		count--;
	}
	if (file_license >> birth_time && file_license >> time_limit) {
		time_now = time(nullptr);
		if (time_now - birth_time >= time_limit && birth_time != -1) {
			cout << "License is expired" << endl;
			is_ok = 0;
			offer();
			return 1;
		}
	}
	ofstream file_license_out(homedir_str + "/.lab2_licenseinfo", ios_base::trunc);
	file_license_out << count << endl << birth_time << endl << time_limit;
	if (!(count == -1 || birth_time == -1 || time_limit == -1)) {
		cout << "You have " << count << " launches and " << time_limit - time_now + birth_time << " seconds left" << endl;
	}
	else {
		cout << "You have full version" << endl;
	}
	bool is_registered = 0;
	if (is_ok) {
		string name;
		cout << "Type your name" << endl;
		cin >> name;
		ifstream file_with_names(homedir_str + "/.lab2_names");
		string name_input;
		while (file_with_names >> name_input) {
			if (name_input == name) {
				cout << "You are already registered" << endl;
				is_registered = 1;
				break;
			}
		}
		if (!(is_registered)) {
			ofstream file_with_names_out(homedir_str + "/.lab2_names", ios_base::app);
			file_with_names_out << name << endl;
		}
	}

	return 0;
}

void offer(){
	int mode;	
	cout << "Would you like to type the license key or uninstall it? 0 - type the key, 1 - uninstall" << endl;
	cin >> mode;
	while (mode != 0 && mode != 1) {
		cout << "Uncorrect mode number! Try again." << endl;
		cin >> mode;
	}
	if (mode == 0) {
		cout << "Type the license key" << endl; // "itmo"
		string keyInput;
		termios oldt;
		tcgetattr(STDIN_FILENO, &oldt);
		termios newt = oldt;
		newt.c_lflag &= ~ECHO;
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		cin >> keyInput;
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		unsigned int hashInput = 0;
		for (int i = 0; i < keyInput.length(); i++) {
		    hashInput += (char)(keyInput[i]) * pow(129, i);
		}
		if (hashInput == 240111417) {
			ofstream file_license_out(homedir_str + "/.lab2_licenseinfo", ios_base::trunc);
			file_license_out << -1 << endl << -1 << endl << -1;
			cout << "Congratulations! You have received the full version of the program" << endl;
		}
		else {
			cout << "Invalid password! Bye." << endl;
		}
	}
	else {
		system("./uninstall.sh");
	}
	
}
