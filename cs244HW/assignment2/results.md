## **Setting** up

1.Remote server location: Google Cloud southamerica-west 

2.Local Server: mac multipass VM

3.Linux version: Ubuntu 22.04

4.Iperf version: 3.9

## Problem1

1. bbr can reach a higher congestion window because it is more suitable for high throughput situations.
2. Reno gains worse throughput over the wireless network. In wireless networks, packet loss can occur due to signal interference, fading, or collisions. TCP Reno interprets these losses as congestion and responds by reducing its congestion window. This aggressive reduction can lead to suboptimal throughput, especially in networks with high wireless packet loss rates.
3. TCP Vegas has a lower congestion window size and relatively good throughput. Because it detects congestion by monitoring changes in Round-Trip Time and responds more proactively to early signs of congestion before packet loss occurs. This can result in better utilization of available bandwidth in wireless networks.
4. Cubic also has worse performance over wireless networks than delay-based Vegas algorithms. Because it is dropping based, CUBIC's response to packet losses may aggressively reduce its congestion window, leading to suboptimal throughput. 

## Problem2

1. Bbr has a bigger RTT on wireless networks than cubic and Vegas algorithms. Because bbr also considers bandwidth to change the congestion window size, this is the tradeoff to achieve higher total performance in stream data transfer.
2. On a wireless network, reno and cubic use a small congestion window. Because TCP Reno and TCP CUBIC rely heavily on packet loss as a signal of network congestion, packet loss is frequent in wireless networks.

## Problem3

1. Bbr has a high throughput and relatively low delay on the wired network, and reaches the best throughput on the wireless network. Because BBR is designed to maximize the utilization of available bandwidth in **wired networks** with low and stable RTTs, BBR can quickly adapt to changes in network conditions. Its responsiveness to changes in RTT helps in maintaining low latency.
2. Vegas has pretty **low RTT** because Vegas does not rely on packet loss to determine network available bandwidth but instead uses changes in RTT to make judgments. It can more accurately detect the available bandwidth of the network. It is pretty **sensitive** to RTT.
3. Reno has a relatively **small congestion window size**. Because to maintain a dynamic equilibrium, it is necessary to periodically generate a certain amount of loss, along with the AIMD mechanism - reduce fast, grow slowly. Especially in large window environments, it takes a long time to recover from the window reduction caused by data packet loss. As a result, it is not possible to achieve high bandwidth utilization.
4. Cubic has a **large congestion window size** and the best throughput on the wired network because it uses a cubic function to determine how to increase the sending rate when the network is underutilized. This allows CUBIC to probe for available bandwidth more aggressively. CUBIC is particularly well-suited for high-speed, high-bandwidth networks with substantial available capacity. It is designed to maximize the utilization of such networks.

rank: bbr >   cubic > reno > vegas



