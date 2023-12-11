## feedback

 吞吐量结果之间存在较高的着色，这表明网络稳定。 

\+ 您尝试了设备和操作系统队列限制。 

\+ 您得出了正确的最佳点结论。

\- 您需要遵守将传输速率与队列大小同步的正确方法。通常，人们遵循以下规则：

txqueuelen =（minstrel Tx 速率 * 最大 RTT）/（帧大小（以位为单位）* 平均 A-MPDU 长度）。因此，假设节点通过 300Mbps 链路连接，最大所需 RTT 为 5 毫秒，每个 A-MPDU 可以处理 16 帧，则缓冲区应低至 8 **帧**。您的 iPerf 命令中应考虑此值。否则，您将迫使操作系统层寻找不同的方法来取出数据包。 

#### Disable Optimizations

ubuntu 22.04 can work,  don't use default qdisc, the parameter txqueuelen might be overrided by something else.

```bash
sudo sysctl -w net.core.rmem_max=2097152
iperf3 -s # launch in remote server 
iperf3 -c 34.176.178.193 
ip link set txqueuelen 500 dev eth0 # cannot work because there are other ways to reconfigure the queue size
tc qdisc show dev enp0s1 # see current qdsc
```

default is fq_codel,

```bash
ubuntu@primary:~$ tc qdisc show dev enp0s1
qdisc fq_codel 0: root refcnt 2 limit 10240p flows 1024 quantum 1514 target 5ms interval 100ms memory_limit 32Mb ecn drop_batch 64 
```

```bash
$sudo tc qdisc add dev enp0s1 root pfifo  # change it to pfifo
qdisc pfifo 8001: root refcnt 2 limit 1000p # change success
sudo tc qdisc replace dev enp0s1 root handle 1: pfifo limit 10000#  to set a fifo queue with a 10000 packets length.
```

we need sleep 20 second to let the traffic stable? 

```bash
sudo ethtool -K enp0s1 generic-segmentation-offload off
sudo ethtool -K enp0s1 tso off # tso offload should be also disabled
```

```bash
sudo tc -s qdisc ls dev enp0s1
sudo tc qdisc show dev enp0s1
```

Observe and plot TCP throughput over the wired and wireless channels while manipulating the queue size in Linux.

2 Observe and plot packet delay while manipulating the queue size in Linux.

```
iperf3 -c 34.176.178.193 -J
```

3 Observe and plot the optimal queue size allocation that minimizes the delay. You may select a reasonable threshold value for the packets to arrive at the destination.

#### Conclusion

1. **Increase in Throughput with Larger Queue Size:**
   
   In many cases, a larger queue size can increase throughput, especially in situations where network or system resources experience bursts of traffic. A larger buffer allows the system to absorb short-term bursts of incoming data without dropping packets or requests. This can lead to higher throughput because data is not lost due to congestion.
2. **Mitigating Packet Loss:**
   
   When network or system experiences congestion, a larger queue can reduce packet loss. When the incoming traffic rate briefly exceeds the processing capacity, packets are stored in the queue until they can be transmitted. This minimizes the need to drop packets due to buffer overflows, which can improve overall throughput.

Large queue size drawbacks :

1. **Latency**: Larger queues can introduce additional latency, as data or requests spend more time in the queue before being processed. This can be a concern in real-time applications where low latency is critical.
2. **Bufferbloat**: Excessive queue sizes can lead to a phenomenon known as "bufferbloat," where data accumulates in the queue, causing increased latency and reduced throughput. It's important to strike a balance between buffer size and maintaining low latency.
3. **Resource Allocation**: In some cases, a larger queue may lead to inefficient resource allocation. For example, in networking, it may lead to underutilization of bandwidth because the queue absorbs traffic even when resources are available.

#### Wire

If we choose mean delay < 270ms, we can choose 2048 queue size.

#### Wireless 

If we choose mean delay < 290ms, we can choose 2048 queue size.

其实没有最优的点.  不同的 queue disciplines 也不一样. 

为啥queue变大, delay 下降?  因为queue最后会有delay= zero的packet, 根本没有传输出去, 

默认 bql要关掉. 

network是非常难的, 要看buffer, 要固定 tcp window size. 要固定线程, wireless 更加不稳定.

Reference 

1. https://manpages.ubuntu.com/manpages/focal/en/man8/tc.8.html#qdiscs
2. https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/9/html/configuring_and_managing_networking/linux-traffic-control_configuring-and-managing-networking#overview-of-queuing-disciplines_linux-traffic-control
