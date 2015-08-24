#!/bin/bash

while true
do
	./TX_sample japha &
	sleep 4s
	killall TX_sample
done
