# homework6 transport

homework 6 network transport layer

1 In both parts of Fig. 6-6, there is a comment that the value of SERVERPORT must be the same in both client and server. Why is this so important?

If the client sends a packet to SERVER\_PORT and the server is not listening to that port, the packet will not be delivered to the server.

解决方案：如果客户端向SERVER PORT发送数据包，而服务器没有监听该端口，则数据包不会被传递到服务器的上层应用程序。

2.想象一下使用双向握手而不是三次握手来建立连接。 换句话说，不需要第三条消息。 现在可能出现死锁吗？举个例子或证明不存在死锁。解决方案：死锁是可能的。 例如，一个数据包突然到达 A，并且 A 确认了它。 确认丢失了，但 A 现在是开放的，而 B 对发生的事情一无所知。 现在同样的事情发生在 B 上，两者都是开放的，但期望不同的序列号。 必须引入超时以避免死锁。

•2. Imagine that a two-way handshake rather than a three-way handshake were used to set up connections. In other words, the third message was not required. Are deadlocks now possible? Give an example or show that none exist.

失效的报文段滞留了很久又到达server, 如果两次握手, 那么server 立刻建立连接, 等待数据, 这样会浪费很多server的资源.

如果没有超时机制可能会deadlock, A 发一个给B , B 回复后等待数据, 如果A没有收到, 那 B 就会死锁, 所以需要 timeout机制. 超时重传.

•3. Why does UDP exist? Would it not have been enough to just let user processes send raw IP packets?

比起TCP, 我们可以减少 开销. 比起直接发 raw IP 包的好处在于, UDP可以实现 不同的 source/destination ports 复用和解复用.

3.UDP为什么存在？ 仅仅让用户进程发送原始 IP 数据包还不够吗？解决方案：不可以。IP 数据包包含指定目标机器的 IP 地址。 一旦这样的数据包到达，网络处理程序如何知道将它交给哪个进程？ UDP 数据包包含一个目标端口。 此信息是必不可少的，因此可以将它们交付给正确的流程。

1. A client sends a 128-byte request to a server located 100 km away over a 1-gigabit optical fiber. What is the efficiency of the line during the remote procedure call?

Sending 1000 bits over a 1 Gbps line takes 1 μsec. The speed of light in fiber optics is 200 km/msec, so it takes 0.5 msec for the request to arrive and another 0.5 msec for the reply to get back.

In all, 1000 bits have been transmitted in 1 msec. This is equivalent to 1 megabit/sec, 0.1% efficiency.

解决方案：同上

•5. Datagram fragmentation and reassembly are handled by IP and are invisible to TCP. Does this mean that TCP does not have to worry about data arriving in the wrong order?

Even though each datagram arrives intact, it is possible that datagrams arrive in the wrong order, so TCP has to be prepared to reassemble the parts of a message报文 properly. 答案如上.

•6. The maximum payload of a TCP segment is 65,495 bytes. Why was such a strange number chosen?

IP 头 total length 是2个byte, ip数据最长就是 2的16次方65535 - 20 = 65515 bytes. The entire TCP segment 要装在里面. TCP header is a minimum of 20 bytes, only 65,495 bytes are left for TCP data.

答案同上

1. If the TCP round-trip time, RTT, is currently 30 msec and the following acknowledgements come in after 26, 32, and 24 msec, respectively, what is the new RTT estimate using the Jacobson algorithm? Use α=0.9.

SRTT = α SRTT + (1- α) R

SRTT1 =0.9×30+(1–0.9)×26 = 29.6

SRTT2 =0.9×29.6+(1–0.9)×32 = 29.84

SRTT3 =0.9×29.84+(1–0.9)×24 = 29.256

答案同上

•8. To get around the problem of sequence numbers wrapping around 卷绕 while old packets still exist, one could use 64-bit sequence numbers. However, theoretically, an optical fiber can run at 75 Tbps. What maximum packet lifetime is required to make sure that future 75-Tbps networks do not have wrap around problems even with 64-bit sequence numbers? Assume that each byte has its own sequence number, as TCP does.

**The Sequence number (using 64 bits) will wrap around after (2^64 bytes \* 8 bits/byte) / (75 \* 10^12 bit/sec) = 1.97 \* 10^6 sec = 1970000 sec \~ 22.7 days so the maximum segment lifetime must be limited to under 22 days. I computed that the sequence number would wrap around in 0.00046 sec using 32 bit sequence numbers.**

32位可能一下子都用光了, 64位可以22天不重复.

答案同上

1. Consider that only a single TCP (Reno) connection uses one 10Mbps link which does not buffer any data. Suppose that this link is the only congested link between the sending and receiving hosts. Assume that the TCP sender has a huge file to send to the receiver, and the receiver’s receive buffer is much larger than the congestion window. We also make the following assumptions: each TCP segment size is 1,500 bytes; the two-way propagation delay of this connection is 150 msec; and this TCP connection is always in congestion avoidance phase, that is, ignore slow start.

a. What is the maximum window size (in segments) that this TCP connection can achieve?

The maximum window size:

`10Mbps * 0.15s /(8 *1500 bytes) = 10^6*0.15/(8*1.5*10^3)` = 125 Therefore, the maximum window size is 125 segments.

–b. What is the average window size (in segments) and average throughput (in bps) of this TCP connection?

average window size is 3\*W/4 = 93.75 segments

and average throughput is segments 数量 乘 segment 大小除以two way propagation `93.75*1500*8/0.15s = 7.5 Mbps`

–c. How long would it take for this TCP connection to reach its maximum window again after recovering from a packet loss?

减半后恢复, It would take 125/2 乘上 RTT = 9.375 sec.
