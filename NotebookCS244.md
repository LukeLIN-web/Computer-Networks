当时整个CS 只有5个faculty, 一个班30-40人. 持续了几年直到招收到更多教授. 

因为课程人很少, 老师可以叫出每个同学的名字, 用同学名字举例子, 讲reliable的特点, 保证顺序. 

上课总是回答学生问题是很费时间的, 所以培养学生的提问能力是要付出很高的教师时间成本的. 

学生太多了, 学生就只能听从, 没有时间提问. 就只会干活, 不会质疑, 培养小镇做题家, 这和科研的思想是相悖的. 

## Lec1

#### 作业1反馈

\- OWAMP 失踪了。尝试了 ping 的一个版本 

\- 时钟似乎不同步。  delay测量要同步时钟. 

\- 需要更加关注结果分析。 

delay也用ping,   traceroute可以来测 hop.

 setup要写完整.  要写出平均值和标准差, 不能只测一次.

 测多组, 不同MSS. windows size 从0 到3000. 画图. 

不管做啥都要自动化测试. 要写出每个实验的结论.  

可以画出网络的拓扑图. ,比如内网, 外网. 网络用云icon 表示. 

网络一次没有converage, 需要测五个小时可能才收敛.  多线程 ,在 wireless network 可以有大量加速. 

有啥区别?  

**Circuit Switching**  建立了一个专用的物理连接，

**Packet Switching**：在分组交换中，数据被划分为小数据包，每个数据包独立传输，它们可以按需通过网络的不同路径传输。没有专用的物理  连接，而是按需使用网络资源。 each packet uses full link bandwidth。

### packet switching

packet switching  比circuit switching 可以承载更多用户,  比如同时35个用户, active 超过10个人的可能性<0.004

Goodput is always fresh data.  重发的不算在goodput.

a=average packet arrival rate，  traffic intensity = La/R， La/R > 1: more “work” arriving than can be serviced, average delay infinite!

VPN , 为啥叫virtual? 因为需要build private network, 但是实际上并不存在这么一个private network. 

## Lec2 Transport Layer & Congestion Control

#### congestion collapse

原因：Undelivered packets -》 solution： congestion control for all traffic

原因2：spurious retransmissions of packets still in flight  -》 solution：  better timers and TCP congestion control

即使buffer是无限的, 处理能力有限也会导致无限的delay, buffer有限, 就会packet loss

两种方法都常用: 

end-end congestion control,网络没有explicit feedback. 用在TCP.

network-assisted congestion control, router 提供 feedback to end systems. single bit indicating congestion. 

#### TCP 拥塞控制

Congwin就是congestion window size.

congestion window size 怎么增减都是可以配置的, 但是标准是  probing +1 ,  congestion 丢包的话  *0.5.  因为这样是公平的. 

Window to fill links = propagation RTT * bottleneck bandwidth

## 异构网络中的TCP

可以用tcp ping测试delay. 

lossy link,  就是wireless. 

95%的网络流量都是用TCP, 第二是UDP.

TCP 下面分类很多, 有dropping base的 Reno, delay based 的Vegas, mix delay和dropping的 FAST TCP. 对于window的调整都不同.  linux kernel有一些代码. 但是只有一两种在用. 作业要研究这几个的区别. 

**基于丢包的拥塞控制**：将丢包视为出现拥塞，采取缓慢探测的方式，逐渐增大拥塞窗口，当出现丢包时，将拥塞窗口减小，如 Reno、Cubic 等

**基于时延的拥塞控制**：将时延增加视为出现拥塞，延时增加时增大拥塞窗口，延时减小时减小拥塞窗口，如 Vegas、FastTCP 等

**基于链路容量的拥塞控制**：实时测量带宽和时延，认为网络上报文总量大于带宽时延乘积时出现了拥塞，如 BBR。

#### Reno

– The most widely implemented TCP in current systems 

– Reno is expected to gain worse performance over links with Reno is expected to gain worse performance over links with multiple losses  丢包多的时候性能差.

**RTT 可变性**：由于信号传播、干扰和设备移动性，无线网络通常具有可变且不可预测的往返时间 (RTT)。TCP Reno 的拥塞控制假设 RTT 相对稳定，可能无法很好地适应无线环境中 RTT 的快速变化。这可能导致可用带宽的利用不足。

#### BBR

BBR 算法 2016年谷歌, 周期性地探测网络的容量，交替测量一段时间内的带宽极大值和时延极小值，将其乘积作为拥塞窗口大小，使得拥塞窗口的值始终与网络的容量保持一致。

特点: 在有一定丢包率的网络链路上充分利用带宽。适合高延迟、高带宽的网络链路。

similar to vegas, 非常aggressive. bbr快速增长.收敛很快. 

老师compile了这个,  

#### TCP Vegas

TCP Vegas1994年提出，Vegas算法并不急于丢包来判断是否发生了拥塞，而是通过数据包延迟来判断。Vegas通过RTT（roundtrip time）来决定增加或者减小拥塞窗口，它能够拥塞将要发生时就避免拥塞，而不是等到拥塞已经发生之后再减小发送速度，因此能够减小重传和超时的几率.

overcome the problem of RTT fairness at the bottleneck.

#### cubic

TCP BIC（Binary Increase Congestion control）旨在优化高速高延迟网络（即“长肥网络”（long fat network，LFN））的拥塞控制，而CUBIC则是比BIC更温和和系统化的分支版本，其使用三次函数代替[二分算法](https://www.zhihu.com/search?q=二分算法&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"article"%2C"sourceId"%3A"544139753"})作为其拥塞窗口算法（因为实际上BIC的搜索曲线看起来就像一个三次函数，所以干脆就写一个三次函数来模拟曲线），并且[使用函数](https://www.zhihu.com/search?q=使用函数&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"article"%2C"sourceId"%3A"544139753"})拐点作为拥塞窗口的设置值。Linux内核在2.6.19后使用该算法作为默认TCP拥塞算法。

DSACK : 可以undo halving of cwnd. 

#### ECN/ELN

 Uses a single bit to explicitly notify the source of a congestion or a packet loss. – ECN is set by the routers – ELN is set by the intermediate TCP agent

问题

1. not all routers or hosts can issue ECN or ELN
2. ECN may increase the congestion  in the presence of higher network transmission in the next round.
3. Security issues (MITM that falsely sets/unsets the ECN), which can flood a connection in a very short time.

#### Round Trip Time 

• TCP clock is based on RTT,  Longer RTT reduces the transmission rate.

solutions 

• TCP starts with larger cwnd e.g. 4   用更大的拥塞窗口

• Count the received bytes instead of acks.    count bytes 而不是ack 

– Application level: 

• XFTP: using many parallel TCP connections  多个并行TCP 

• Transfer objects at higher rate during congestion avoidance 

Network level: • TCP segmentation e.g. TCP for satellite networks STP 

#### RTT fairness solution

TCP level ：  faster cwnd growth for long RTT ， RTT大， 那就cwnd 增长更快。 

Network level: – Packet dropping policy • Drop Tail 满了扔掉后面来的packet • RED, Flow RED  随机删除一个packet • Class-based queues (CBQ) • Stochastic Fairness Queuing (SFQ)

#### Solutions for Non-congestion Losses

link level：  ARQ ， only 重传corrupted parts

TPC level： indirect TCP， TCP SACK， 

End to end level：  explicit loss/congestion notification.

#### Bandwidth Asymmetry 

Bandwidth Asymmetry damages TCP clocking mechanism. Mention one receiver-side solution.

High bandwidth at the forward direction (cable, satellite) while low speed channel (dial up) that carries the ACKs    ack回来的太慢了，怎么办？ 

– Congestion/dropping at the slow link causes larger RTTs, slower growth of cwnd Damage the TCP clocking mechanism Slow speed link (ack)  Damage the TCP clocking mechanism

 • Receiver side solution using compression  压缩

 • Reducing the number of ACKs   减少ack 数量

• Reducing the TCP burstiness   

#### 拥塞

layed congestion response: 不立刻减半. 两次都失败才减半. 但是这对MAC switching层的ARQ有要求

burst TCP with BACK/BNAK:  这是老师自己在phd时候写的.

multiple simultaneous loss, 就会不断减半, window size很快就到1. 优点:  快速解决拥塞. 

TCP over High Bandwidth-Delay Product

TCP over WRN suffers from  Slow convergence 

#### TCP over Lossy Channels

无线的情况, 更难判断 congestion. 因为 Non-congestion losses caused by transmission errors: – packet corruption, – bad links, – channel fading, – hand offs

解决方法:  Hiding the non-congestion losses 

– Local recovery of losses 本地恢复 , 用备用link， 不同的route 。 e.g. at the link level, such as using backup links, different routes

要用多个transmiter和receiver, 这样增强接收能力. 

光纤和 铜线, 可以2500 Mb 以上. 我们的线, 只能2500Mb/s以下.  因为我们学校的网只有1000Mb/s ，所以我们都卡在这个速度. 

#### CSMA/CA

Carrier Sense Multiple Access

Use CSMA with Collision Avoidance

exposed terminal problem .  

RTS/CTS 可以解决 exposed terminal.  *RTS*/*CTS*协议（Request To Send/Clear To Send）即请求发送/清除发送协议. 

CTS谁先拿到谁发.

同时发就会都损坏, 

A知道C在发,  A就不会重传. 

X 就是access point. 接受信号. 

他们都会不断重传. 

Flow‐in‐the‐middle problem

日本的wifi 路由器, 频率标准是不同的, 在外国都不能用. 

1G , analog, voice only   2.4 kbps

2G, 可以text短信, 大部分地区用GSM 标准, 北美因为太大了用 CDMA.  64Kbps

3G,  2000kbps, 可以视频,

4G , 100Mbps. 

5G,  频率从GHz 继续提高, 

Mesh的缺点, 如果出口的router 坏了, 那么RTT非常大, 吞吐量会剧减.

#### wireless TCP

Wireless ad hoc network，缩写为WANET，又称无线临时网络。源自拉丁文，原意是临时、专用、特设的。它被称为ad hoc，是因为这种网络系统是临时形成，由节点与节点间的动态链接所形成。它不需要依赖一个既存的网络架构，或是无线系统的无线网络基地台。相反的，每个节点都有能力转送网络封包给其他节点

会用 indirect TCP, 每个access point可以通信, 不需要经过ad hoc host.

不同科技对远的定义也不同, wifi 可以甚至到10km. 远的话就要经过adhoc , 近的话,接入点之间之间连, 不用经过host.  Host  就是互联网提供商的 adhoc machine. 

#### Snooping TCP

record seq num in hash table, 让link layer 重发.  像个警察, 有accident就去协调. 

缺点:

isolate 不如 I-TCP

太多state , buffer, 计算量大. 

还有 M-TCP ， FreezeTCP

## Optical Networks

bursty traffic

#### Optical Packet Switching

No.1 problem: lack of optical buffer (RAM)

### OBS 网络

burst signaling for TDM networks.

delay reservation.

#### burst compete solution 

1. deflection偏离 in space, time.
2. preemption先占 of an existing  reservation
3. segmentation of a burst 切分成小块

## hw3

ubuntu,  **QDISCS **默认是fq_codel  

https://manpages.ubuntu.com/manpages/focal/en/man8/tc.8.html#qdiscs

qdisc  是“排队规则”的缩写，它是理解流量控制的基础。每当内核需要将数据包发送到接口时，它就会被排队到为该接口配置的 qdisc 中。之后，内核会立即尝试从 qdisc获取尽可能多的数据包，以便将它们提供给网络适配器驱动程序。 一个简单的 QDISC 是“pfifo”队列，它根本不进行任何处理，是一个纯粹的先进先出队列。但是，当网络接口暂时无法处理流量时，它会存储流量

我们修改了qdisc, 但是bit rate 还有别的因素, tso offload should be also disabled

Explicit loss/congestion notification is proposed to solve false-congestion detection at TCP, mention one problem of such scheme.

这个是ECN,

1. 兼容性有问题,not all rounter 都支持

2. security issue. maybe falsely set ECN 

Consider transferring a file of L bytes. Assume the MSS is 1460 bytes, the RTT is 0.1 second, and a total of 66 bytes of transport, network and data-link headers are added to each segment before the packet is sent out over a 10 Mbps link. How large the TCP congestion window?

1. Calculate the effective bandwidth-delay product (BDP): BDP = Link Bandwidth (in bits per second) x Round-Trip Time (RTT) (in seconds)
2. Calculate the maximum segment size (MSS) considering the headers: 
3. Calculate the number of segments that can be in flight at a given time: Segments in Flight = BDP / MSS

Bandwidth Asymmetry damages TCP clocking mechanism. Mention one receiver-side solution.

Q links,  计算时间 ,circuit不用除 Q,  packet 要除Q

## solution over OBS

### Link layer solutions

link layer 

Statistical AIMD 收集之前的信息, 

burst ack/nack.   

一个burst有太多packets

false timeout是说,  lose cwnd, 但是并不是因为congestion. 





