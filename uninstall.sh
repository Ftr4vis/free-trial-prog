#!/bin/bash

rm main
rm license_info
if ls ~/.lab2_names 1>/dev/null 2>/dev/null; 
then
	rm ~/.lab2_names
	echo "The program was deleted"
else
	echo "The program is already deleted"
fi


