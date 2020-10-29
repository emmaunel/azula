#!/usr/bin/python

import sys
from scapy.all import IP, ICMP, sr1

# Give IP when running this

if len(sys.argv) != 2:
    print("Usage: " + sys.argv[0] + " ip")
    sys.exit(1)

# Craft IP header

ip_packet = IP()
ip_packet.dst = sys.argv[1]
icmp_packet = ICMP()
icmp_packet.code = 1
sr1(ip_packet/icmp_packet/"abcdefghijklmnopqrstuvwxyz")