\+ successfully installed iperf along with completing a set of experiments.
\+ compared wireless and wired results using different geographical locations.

\+ completed the link rate vs. delay experiment 


\- OWAMP was missing. Tried a version of ping instead 

\- clock seems not synchronized. 

\- results were not well presented and described. 

\- need to pay more attention to the slide quality and result analysis 

## Problem1

iperf3不好用， -p 有问题， iperf反而好用。
```
iperf -s # launch server
iperf -c  mcnode36 # connect server
```

When buffer length is small, wired is similar with wireless network.

Bandwidth vs TCP window size

Explain: 

1. Reducing the TCP window size to half means that the sender can send fewer unacknowledged packets before pausing, resulting in a lower data transmission rate and decreased bandwidth. 可以发的packet更少了。 
2. Smaller window sizes lead to increased acknowledgment overhead and less efficient utilization of network capacity, causing a decrease in bandwidth.

**Parallel Connections**

Explain: 

multiple connections can take advantage of the available network capacity simultaneously,they can potentially lead to increased overhead and resource utilization so that the sum bandwidth is smaller than basic connection. 合起来更小。 

#### Wireless basic (WiFi)

connect multiple times, each time the bandwidth is dramatically faster , why ? Because wifi in office is unstable and share with others. We can test on dorm.

I use a computer connected via an Ethernet cable. For wireless, I use Wi-Fi. However, the bandwidth is almost the same. Why? Because the Ethernet cable is capped at a network speed of 125MB/s.

The bandwidth is the throughput.

### Problem2

Installing owamp. I meet configure: error: Couldn't find I2util library http://software.internet2.edu/sources/I2util/

I use https://docs.perfsonar.net/install_docker.html  to use the docker image: perfsonar/testpoint

No need to compile from source code.

```bash
owampd -c /etc/owamp-server -Z #  -c /etc/ , specifc the conf path.
twampd -c /etc/twamp-server -Z #-Z don't need to test packets.
twping localhost
docker run -d
```

When running `twampd` inside Docker with the command `twampd -c /etc/twamp-server -Z`, if you can't connect to it from the outside and need to do port forwarding, `twampd` is listening on port 862.

Manual: http://software.internet2.edu/owamp/owampd.conf.man.html

We can get the link rate by  `sudo ethtool eth0 | grep Speed`  Get kaust server Speed: 1000Mb/s

I tried to use netperf to measure latency

```bash
netperf -H mcnode36 -t TCP_RR -- -o mean_latency
netperf -H 34.176.178.193 -t TCP_RR -- -o mean_latency
```

I find there are some iperf public servers. I connect with them and measure the bandwidth.

```bash
iperf -c iperf.he.net # USA
```

I bought a Google Cloud server to test  the delay and link rate in different geographical locations.

I also use ping and traceroute to measure hops.

The setup needs to be complete.

I should report both the average and standard deviation, not just a single measurement. Perform multiple tests with different MSS (Maximum Segment Size).

Vary the window size from 0 to 3000 and generate plots. Automation is required for all testing.

The network may not converge in a single attempt; it might take up to five hours to achieve convergence.

Multithreading can significantly accelerate operations in a wireless network.



