#!/bin/bash

curl -X PUT --upload-file /var/log/test http://129.21.228.226:8000
sleep 10

# Execute command