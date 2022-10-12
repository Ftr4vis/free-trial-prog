# free-trial-prog
The program that has a limited number of launches and time since installation

# Description
The program "main" is run from the command line interface. Displays license information found in the ".lab2_licenseinfo" file in the home directory of the user who installed the program. If the license has not expired, the user is prompted to enter a name, which is entered in the ".lab2_names" file (also located in the user's home directory), in case there is no such name in the file. When running a program with an expired license, the user can either uninstall it without removing ".lab2_licenseinfo", or enter a license key to get the full version of the program and remove all restrictions.

The "license_info" program allows you to get license information.

The "install.sh" installer compiles the programs "main" and "license_info" and creates the ".lab2_licenseinfo" and ".lab2_names" files. The program code sets limits on the number of runs and time. Reinstallation before or after uninstallation does not update the license.

The "uninstall.sh" uninstaller removes the executable files and the "./lab2_names file".

In the ".lab2_licenseinfo" file, data is stored line by line in the following order: the remaining number of runs, the installation time of the program from January 1, 1970 in seconds, the time limit.

# Install
./install.sh

# Usage
./main

# Uninstall
make clean
