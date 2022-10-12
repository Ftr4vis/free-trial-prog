#!/bin/bash

g++ license_info.cpp -o license_info
g++ main.cpp -o main

launches_limit=5
time_limit=90
if ls ~/.lab2_names 1>/dev/null 2>/dev/null; 
then
	echo "It is already installed"
else
	if ! ls ~/.lab2_licenseinfo 1>/dev/null 2>/dev/null;
	then
		touch ~/.lab2_licenseinfo
		echo "${launches_limit}" > ~/.lab2_licenseinfo
		date "+%s" >> ~/.lab2_licenseinfo
		echo "${time_limit}" >> ~/.lab2_licenseinfo
	fi
	touch ~/.lab2_names
	echo "The program was installed"
	./license_info
fi
