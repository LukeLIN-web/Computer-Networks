+ successfully enabled all TCP flavours and compared them against each other by the throughput experiments.
+ compared wireless and wired results along with the delay on both
+ came to a correct conclusion that TCP BBR has a superior performance for your rest of experiments.
+ I like the comprehensive analysis provided in your document. (Table comparison) 

- Throughput results are unclear to me. It seems that your cwnd size is very large and needs some adjustments.
- the above applies to the delay results. 
- in your table comparison, you need to watch that higher throughput results into higher delay with higher cwnd.


## Problem1

iperf3 is different with iperf.  Moreover, macos iperf3 default it doesn't print `cwnd`.  only linux iperf3 can print `cwnd`

#### Algorithm

BBR, cubic, reno, and vegas

How to see my TCP design?

congestion window size应该指cc算法自己选择的size

iperf的 -w 指定的  window size可能指最大的congestion window size.

more thoughput , 肯定delay会大.

```bash
cat /proc/sys/net/ipv4/tcp_congestion_control
cat /proc/sys/net/ipv6/tcp_congestion_control
cat /proc/sys/net/ipv4/tcp_available_congestion_control
sudo sysctl -w net.ipv4.tcp_congestion_control=bbr
sysctl net.ipv4.tcp_congestion_control # check my 
iperf3 -s
iperf3 -c 34.176.178.193

-O, --omit N : omit the first n seconds (to ignore TCP slowstart)
-C, --linux-congestion : set congestion control algorithm (Linux and FreeBSD only) (-Z in iPerf2)
```

My server doesn't have ipv6

macOS run perfsonar/testpoint docker container, only has two tcp_available_congestion_control, reno and cubic.

reno cubic

From this link https://superuser.com/questions/865896/which-congestion-control-algorithm-is-used-by-the-tcp-stack-in-os-x and practice we can know OSX use cubic.

Docker container linux cannot change tcp_congestion_control , Because Docker cannot change linux kernel.  We need to use Virtual machine .

```
modprobe tcp_bbr
sudo echo "tcp_bbr" > /etc/modules-load.d/bbr.conf
# -bash: /etc/modules-load.d/bbr.conf: Permission denied
```

I try WSL2. It even doesn't have tcp_congestion_control.

I use my Windows to run VM Station Pro. Successfully run four TCP favor.

I should show tradeoff:  No congestion,   ,  throughput is better. Conestion, something is better. 

bbr , 

some  ,recover is time consuming 

Setting up:

1. Remote server location : southamerica-west 
2. Local Server: mac multipass  VM

比较方便, 快速共享文件夹. 

Results: 

1. bbr can reach higher cwnd. Why? 
2. Vegas and renowireless has very large thourghput in first second, then it decrease cwnd drastically. 
3. In wireless networks, packet loss can occur due to factors like signal interference, fading, or collisions. TCP Reno interprets these losses as congestion and responds by reducing its congestion window. This aggressive reduction can lead to suboptimal throughput, especially in networks with high wireless packet loss rates. Therefore, Reno is expected to gain worse performance over links with multiple losses. And the result proves it. 

## Problem2

If you add `-J` in iperf3 command, you will find the rtt for each interval in json file. I guess this is much better than doing ping command.

## Problem3 

If the network is pretty unstable, we can use box plot to write the variance.

plot the optimal pint that corresponds to the tcp congestion window size for each flavor.


#### Connect

```
connect failed: Operation now in progress
```

By default, Google Cloud VPS firewalls only permit ICMP traffic and do not allow incoming HTTP traffic. After creating a new firewall rule, you can now access the HTTP server on the VPS using `http://localhost:8000`.





