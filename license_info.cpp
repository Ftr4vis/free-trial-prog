#include <iostream>
#include <fstream>
#include <ctime>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

struct passwd* pw = getpwuid(getuid());
const char* homedir = pw->pw_dir;
string homedir_str(homedir);

int main() {
	
	int count;
	time_t time_limit;
	time_t time_now;
	time_t birth_time;
	
	ifstream filelog(homedir_str + "/.lab2_licenseinfo");
	if (filelog >> count && filelog >> birth_time && filelog >> time_limit) {
		if (!(count == -1 || birth_time == -1 || time_limit == -1)) {
			time_now = time(nullptr);
			cout << "You have " << count << " launches and " << time_limit - time_now + birth_time << " seconds left" << endl;
		}
		else {
			cout << "You have full version" << endl;
		}
	}
	else {
		return 1;
	}
	
	return 0;
}


