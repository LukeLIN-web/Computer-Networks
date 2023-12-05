#!/bin/bash

# tx_sizes=(256 512 1024 2048 4096 8192)
# Loop to set each TX queue size
for tx_size in "${tx_sizes[@]}"
do
    echo "Setting TX queue size to $tx_size"
    sudo tc qdisc replace dev enp0s1 root handle 1: pfifo limit ${tx_size}
    # sudo tc qdisc replace dev enp0s1 root tbf rate 256kbit buffer ${tx_size} limit 3000
    tc qdisc show dev enp0s1
    iperf3 -c 34.176.178.193 > "${tx_size}.log"
done
