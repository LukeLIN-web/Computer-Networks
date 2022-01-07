

[TOC]

Notebook 1

## lec1 

2021年6月 计算机网络书更新了.十年更新一次.  作业7次, 实验7-8次, 分组pre, 出勤+ quiz 3-4次. 

pre的topic 在第一章ppt上.

 用户其实反应很慢, 大会上学术是引领潮流的.

怎么让人出了基站也不会断网？

5G最快有10Gbps, 在2020年大规模使用.

无服务器计算, 买的时候我直接买一个叫函数计算的东西。去买云计算的资源，我不需要买一台服务器,我甚至不需要买一个容器, 有人发请求,在实时的在云上面给我创建出来一个可以被我运行人脸识别,出来之后运行完了之后，如果没有再有新的请求的话，我就直接销毁掉，那我就不用付钱了.  

巨大的数据中心, 线是怎么链接的?  基本上是个树,

交换机的网口和价格不是线性关系, 口很多的时候非常贵.四口的几十块一两百块.

云栖大会, 把一台机器拔出来, 数字没有出错, 用大量廉价服务器实现高可用.  

数据中心用的电, 除了服务器, 还有很大一块是空调,  之前一大半都是空调, 散热成本非常高, 所以电费昂贵.

IOT 安全, 视频流攻击.  产值达到1.26万亿美元.

RFID , 之前用于苏联窃听美国, 无源无线电波获得信息.  物联网的技术,  电源技术,  让蜻蜓很轻也可以飞起来. 

## lec2

layer有什么好处?我用网线, 无线,  访问的ip地址都是一样的. 分层可以让很多都保持一致.

为什么没有全部用OSI 模型? 因为价格很高. 

考题: actual 怎么走, virtual 怎么走. 

OSI  三要素 , services, interface, protocols.

物理层 : concerned with transmitting raw bits over a communication channel. 

Data link layer (数据链路层):   take a raw transmission facility and transform it into a line that appears free of undetected transmission errors to the network layer

Network layer(网络层) : This layer is concerned with controlling the operation of the subnet. 

传输层: 接受上层, 分成小unit, 传到网络层, 确保发送. To accept data from the session layer, split it up info smaller units if need be, pass these to the network layer, and ensure that the pieces all arrive correctly at the other end.要考虑 multiplexing, 怎么让session layer 多路复用.

会话层:To allow users on different machines to establish sessions between them

表示层: The presentation layer is concerned with the syntax and semantics of the information transmitted.

1kB/s =  1000bytes/second 不是1024

## lec3 物理层

每年都会考noise 的计算. 考试可能告诉你 S , N  , V ,  加入很多干扰项, 取交集.  

data rate == symbol rate 

The maximum data rate of a channel 

 奈奎斯特Nyquist 提出 maximum data rate for a finite bandwidth noiseless channel: Max data rate = 2H log2 V bits/sec, or Max symbol rate = 2H where H is the bandwith, V is the discrete levels
– If we use B to denote the data rate (bits/s), and S to denote the symbol rate (symbol/s), B <= 2H log2 V ,S <= 2H

有限带宽的最大速率:finite bandwidth noiseless channel
$$
Max\ data\ rate= 2 *H*log_2(V)bits/sec
$$
 or Max symbol rate = 2H

 where H is the bandwith, V is the discrete levels。

例如 4个相位，每个相位4种幅度QAM ， 那么 V就等于16

考点就是这几个公式.  有噪声:

$$
Max\ data\ rate= H*log_2(1+S/N)bits/sec
$$
The max data rate of a channel  香浓 Shannon 提出 random noise Max data rate = H log 2 (1+S/N) bits/sec where S/N is the signal to noise ratio
– If we use B to/ denote the data rate (bits/s) B <= H log 2 (1+S/N)
– SNR: typically measured in dB, decibel dB = 10log10 S/N Ex: S/N=10→10dB, S/N=100→20dB, ...

曼彻斯特编码，前面高后面低表示0 或者1。  NRZ， 高为1 ， NRZI 翻转为1 . 

数据传输率C = 波特率B  x log2（N） N为码元可取的离散值个数。   

 

#### 网络设备

中继器和集线器hub在物理层,  

网桥在数据链路层, 可以 隔离冲突域,  但是不能隔离广播域.

交换机switch 在 数据链路层,  相当于多端口的网桥, 冲突域 = 端口个数, 广播域为1

路由器router 在ip层. 可以 隔离冲突域和隔离广播域. 可以防止广播风暴

## lec4 数据链路层

mac层会单独讲. 数据链路层要 给帧确定界限, 也可以实现差错控制和流量控制 

#### services 

无确认的无连接服务. 不需要建立链路连接, 收到后没有确认, 丢失后也不重发而是交给上层处理. 适用于实时通信 或者误码率较低的通信信道, 比如以太网.

wifi 等无线通信 是有确认的无连接服务.  收到后要发回确认, 适合误码率较高的信道. 

#### framing

目的 : 检查发送的数据对还是错

bytecount use a field in the header to specify frame中的character数量 

缺点: 一个错了, 后面的连着都错了, PPP有个类似的版本.  题目可能叫你分哪些是第一个frame,哪些是第二个frame. 

flag,  最前面和最后面 用flag . 

缺点: 可能character流中和flag 一模一样.   解决方法:   转义字符. 会考来回转义.考试经常反向考（给HDLC帧，还原数据）

##### Flag bytes with byte stuffing

让每个帧以特殊字节开始和结束。两个连续的标记字节flag byte表示一个帧的结束和下一个帧的开始。因此，如果接收器失去同步，它可以搜索两个标记字节来找到当前帧的结束和下一帧的开始。 当这个标记字节在**帧中**，用一个转义字符escape byte (ESC) 插入到标记字节前。接收者收到后，又将这个转义字符去掉，这个过程叫byte stuffing字节填充 

缺点：添加这些字节会大大增加消息的大小

##### Flag bits with bit stuffing

每一帧以01111110位模式开始,而中间不会有6个0
•发送者:每当我们在数据中看到五个1时，我们就插入一个0
•接收器:每当我们看到五个1，我们就会移除下面的0
它与byte stuffing 思想一样，但开销更小
唯一问题就是最后的帧可以是任意位数，但字节填充总是字节数
比特填充法是采用一特定的比特组合01111110来标志帧的边界，也就是一个标志字节。这种方法既允许数据帧包含任意长度的字符，也允许每个字符有任意长度的位。为了避免在传送的数据信息中心出现相同比特组合被误认为是帧的首、尾标志，必须对其进行比特填充(bit stuffing)
比特填充法具体地说，发送端的数据链路层遇到数据比特流中出现5个连续“1”的时候，它就自动在输出比特流中插入一个“0”;接收端遇到5个输入比特为“1”，且后面紧接的是“0”时，自动将其删除。字符填充法的主要缺点是依赖于特定的字符模式。

CDMA每个station 的chip sequence 都是 正交的. 

考试题:

01111100 0111111110 framed by HDLC 协议是什么

连续5个1 后面要加个0 

CDMA的发送, 看A发送的是什么

#### error detection and correction

主要考汉明码和CRC循环冗余校验码.

coding scheme的汉明距离就是 所有pair 的汉明距离的最小值. 

把1的个数变成偶数.  汉明距离是多少?  变一个至少变另一个, 所以最小是 2 .

如果要detect d个errors , 需要 d+1 汉明距离 的code. 

To use Hamming distance to correct *d* errors, you need *2d+1* 汉明距离 的code. 

detect 3-bit error,the hamming distance need to be 4.to correct 3-bit error，the hamming distance need to be 7. So the algorithm fails.

汉明校验码:

100个, 至少要 7个校验码,  2的7次 > 107+1  . m+r+1  < 2的r次

 m:信息位      r:检验位     m+r+1<=2^r

##### error detection codes

checksum 校验和 

Polynomial code or CRC (Cyclic Redundancy Check) 会考

https://asecuritysite.com/comms/crc_div?a=101110&b=1001 可以计算CRC

1 Gx 有几阶就加几个0 .  比如 1101 那么 r =3 . 

2  异或 取余. 余数共r位. 

Data link protocols almost always put the CRC in a trailer rather than in a header. Why?



考点：计算机网络的**串行通信**
答：串行通信，接受完帧后可直接看校验位，节省存储，加速；否则要额外存储CRC且效率降低



可以考bit rate.

utilization,  T frame/ (2 Tprop + Tframe)

### Elementary Data Link Protocols

**发送方以高于接收方能处理帧的速度发送帧，导致接收方被淹没，要通过协议防止它**

#### 停等协议(stop-and-wait) 

> 发送方发送一帧，等待对方确认到达后才继续发送，此协议为停等协议 

#### 滑动窗口协议

从Protocol 4 到Protocol 6

Protocol 5: A protocol using go back N 

• Receive Window Size=1 • Send Window Size <= MAX_SEQ (0…N) • Ex: max seqno=5, send window=6 is not allowed since seqno 0 can be assigned to both new pkt or old pkt (retransmission)

• Protocol 6: A protocol using selective repeat

会考最大窗口大小是多少? 

Send Window Size <= (MAX_SEQ+1)/2

####  PPP

Point to Point Protocol 是链路层的标准之一, 其他标准还有 HDLC 和SLIP.     包括 SONET fiber optic links and ADSL links

PPP 有三个 features .  A framing method ,– A link control protocol (链路控制协议, LCP)  a different NCP (Network Control Protocol, 网络控制协议)



## lec7MAC层 

#### CSMA with CD

是CSMA协议的改进方法.   先听后发,边听边发,  冲突停发, 随机重发(二进制退避算法)

**Carrier Sense Multiple Access / Collision Detection**. 载波侦听 多路访问 碰撞检测  in the medium access control layer(MAC层). 它侦听信道是否繁忙for broadcasting and interrupts the broadcast 直到信道空闲. In CSMA/CD collision is detected by broadcast sensing from the other stations. Upon collision detection in CSMA/CD, the transmission is stopped and a jam signal is sent by the stations and then the station waits for a random time context before retransmission. 

   冲突检测, 监听 2tao的时间, 为了使一个站获得成功传输的一些保证，争用间隔（该站正在传输的时间）应该至少有2 tao槽宽度，其中ι是信号在两个最远的站之间传播的时间，即必须有足够的时间让帧的前端到达电缆的末端，然后在整个帧被传输之前将错误信息送回起点。

先解释一下10 Base T. 10代表代表10Mb/s的数据率，BASE表示连接线上的信号是基带信号，T表示双绞线。且以太网发送的数据都是**曼切斯特编码** 的信号。曼切斯特编码：位周期中心向上跳变表示0，向下跳变表示1，也可以反过来定义 

#### collision free的协议 

1. A Bit-Map Protocol

2. Token passing 传输令牌.  传到你有就发, 没有就传给下一个人. 效率还是挺高的, 但是因为一些商业上的原因现在不怎么用了, 2021年 802.3 Ethernet 常用, 还有wifi.
3. Binary Countdown 

wireless LAN 协议

Multiple Access Protocols: Limited-Contention protocols 

#### 自适应树搜索协议

assign stations to slots dynamically

A 是root,  第二层B C 第三层 DEFG  第四层  HIJKLMNO  

Stations 2, 3, 5, 7, 11, and 13 want to send.
Viewing from node A, for slot #1: station 2, 3, 5, 7, 11, 13 will compete. Then,
viewing from node B, for slot #2: station 2, 3, 5, 7 will compete. Then,
viewing from node D, for slot #3: station 2, 3 will compete. Then,
viewing from node H, for slot #4: station 2 will compete and obtain the slot. Then,
viewing from node I, for slot #5: station 3 will compete and obtain the slot. Then,
viewing from node E, for slot #6: station 5, 7 will compete. Then,
viewing from node J, for slot #7: station 5 will compete and obtain the slot. Then,
viewing from node K, for slot #8: station 7 will compete and obtain the slot. Then,
viewing from node C, for slot #9: station 11, 13 will compete. Then,
viewing from node F, for slot #10:station 11 will compete and obtain the slot. Then,
viewing from node G, for slot #11:station 13 will compete and obtain the slot. 
Thus, 11 slots are needed

hidden station problem, exposed station problem.   隐藏终端,  暴露终端问题. 

#### 802.3: MAC Sublayer Protocol:

The Binary Exponential Backoff Algorithm  这个常考 
Time is divided into discrete slots (51.2us).  
After the 1st collision, each station waits either 0 or 1 (k in 0~2-1) slot times before trying again.
After the 2nd collision, each station picks either 0,1,2,3 (k in 0~4-1) at random and waits that number of slot times.
After i-th collisions, each station picks either 0,1,2,…, 2^𝑖− 1 at random and waits that number of slot times.
After 10th collisions, the randomization interval is frozen at a maximum of 1023 slots. 固定在1023不再变 
After 16 consecutive collisions, the controller reports failure back to the computer.   16次失败后,丢弃数据. 

 第一次 0 到1  第三次是 0 到7 是考点

Please show the differences between (a) The Ethernet CSMA/CD protocol and the 802.11 CSMA/CA protocol
(b) The MACA protocol and the 802.11 CSMA/CA protocol

The MACA (Multiple Access with Collision Avoidance) protocol. A sending an RTS to B, B responding with a CTS to A 

#### CSMA/CA

应用在无线局域网, 碰撞避免, 

工作过程
接收方和发送方
发送方发送一个RTS帧给接收方，从而发起发送请求。RTS帧包含整个通讯过程2需要的时间NAV，
接收方接收到RTS帧，如果判断此时信道可以传输，则向发送方发送一个CTS帧进行确认。CTS同样包含发送方要发送的数据帧的长度。
接收方接收到CTS帧，开始发送数据。
接收方接收完数据帧后，向发送方返回一个ACK帧确认。

两个协议都可以解决隐蔽站问题，解决这个问题的关键在于离接收方近的站要保持安静。这个通过CTS就可以实现，只要接收到CTS的其他站保持安静就可以了。
而解决暴露站问题的关键在于，离发送方近的站点不需要保持安静，也就是说不需要对RTS做出任何反应，就像MACA所做的这样。而CSMA/CA中接收到RTS帧的站点也需要保持安静，这就导致了暴露站问题。
那么就到了下一个问题，为什么CSMA/CA要这样做呢?  

最关键的区别在于，MACA是一个不可靠的协议，他只管发送，不管发送出去的东西有没有被正确接收。而CSMA/CA增加了一个ACK帧进行确认，是可靠的通讯协议。而在这段时间里面，发送方同样有可能接受数据->ACK帧。为了保证发送方能无冲突接收到ACK，所有离发送方近的站点同样需要保持安静。所以所有站点无论是接收到RTS还是CTS都需要保持安静一段时间。这也导致CSMA/CA的效率比较低。

## lec8网络层介绍

I. Network Layer Design Issues 

II. Routing Algorithm

learning bridges

自学习,   从1 port 收到A的消息,  网桥就学习到以后发给A 就从1port 发出去. 

为了增加  reliability , redundant link may used.但是会有loop的问题 ,  所以需要,  spanning Tree Bridges. 生成树. 

#### virtual LANs

802.3   802.1Q

提出新协议, 往往加了字段, 

III.Internetworking (网络互连)

IV.The Network Layer in the Internet

网关 gateway

## lec9 网络层详解1

### 1 Network Layer Design Issues

1. Store-and-Forward Packet Switching (存储转发分组交换) 
2. Services Provided to the Transport Layer (为传输层提供的服务) 
3. Implementation of Connectionless Service (无连接服务的实现) 
4. Implementation of Connection-Oriented Service (面向连接服务的实现) 
5. Comparison of Virtual-Circuit and Datagram Subnets (虚电路或数据报子网的比较)

Comparison of Virtual-Circuit and Datagram Subnet

Datagram Subnet 难 保证服务质量和 拥塞控制.  所以用virtual-circuit

### 2 路由算法

静态路由, 手工配置

动态路由, 常见的分为 DV  和LS 两类.

1. The Optimality Principle (最优化原则) 

2. Shortest Path Routing (最短路径路由) 
3. Flooding (泛洪路由) 
4. Distance Vector (DV) Routing (距离向量路由) 
5. Link State (LS) Routing (链路状态路由) 
6. Hierarchical Routing (分层路由) 
7. Broadcast Routing (广播路由) 
8. Multicast Routing (组播路由) 
9. Anycast Routing (选播路由) 
10. Routing for Mobile Hosts (移动主机的路由) 
11. Routing in Ad Hoc Networks (自组织网络的路由)

Routing Patterns and Techniques:

Unicast: point-to-point, one-to-one 

– DV routing – LS routing

 • Broadcast: one-to-all – Flooding – Reverse path forwarding

Multicast: one to many

 • Anycast: one to any 只要求one to 这几个人中其中一个, 比如最近的或者资源最多的. 

 • Collection: all-to-one – Used in sensor network

#### optimality principle

 • Optimality principle (最优化原则): If router J is on the  optimal path from router I to router K (IJK), then the  optimal path from J to K also falls along the same route. 

• Sink tree (汇集树): The set of optimal routes from all  sources to a given destination form a tree rooted at the  destination. (a) A subnet. (b) A sink tree for router B

#### flooding 

占用大量资源,  有时候需要. router不能判断存了的ip地址是不是, 只要没存就会flood. 

#### Distance vector routing  DV

 (距离矢量路由, 也叫 Bellman-Ford routing) 计网考研, 期末考每次都会考

所有节点定期将他们的整个路由选择表传送给所有与之直接相邻的节点. 

Each router maintains a vector or table giving  • the best known distance to each destination and • which line to use to get there.  

– These tables are updated by exchanging information  with the neighbors. To update the table, a node: • Measure its distance to its neighbors • Receive the vectors from its neighbors • Compute its own new vector.

distance vector 怎么创建?  怎么更新? 

先测量和邻居的距离, 

For an n-node network, how many elements in the  DV?  n-1个entries.

更新了之后, 这个结点广播, 然后左边的结点会知道要选哪个邻居. 

 缺点是传bad news 很慢. 

count-to-infinity 原因是  ABC  B 不知道  A 到C 经过B , 所以C挂了的时候B 会认为到C 的距离为 1+ 2 =3. The core of the count-to-infinity problem is that if A tells B that it has a path  somewhere, there is no way for B to know  if the path has B as a part of it

Attempts to solve Count-to-infinity problem

Poisoned reverse 毒性逆转, RFC :If C routes through B to get to A: –C tells B its distance to A is  infinite 

Poison Reverse的理念是当Router A发现Network X的中断後, 在下次做routing update时不会忽略X, 反而会把X包含到routing update当中, 但将其跳跃数Hop count变更为Maximum+1(RIP为15+1), 因为Hop count超过了Maximum, 所以Router B收到更新时会立刻知道Network X为Inaccessible, 而无需等待180秒, 这样便会大大地加快网络收敛的速度。

•will this completely solve count-to-infinity problem? –No

##### RIP

RIP是最常见的 DV算法, 采用跳数作为距离的度量. 

#### Link state routing

Building link state packets. 了解所有邻居的ip地址, 测量delay. 

– Each router builds a packet containing 完全的网络拓扑信息. 然后flooding 发给所有路由器. 

– The packet starts with the identity of the sender,  followed by a sequence number and age and a list of  neighbors (and costs to them)   为了避免循环, 要用age , age设置limit .   sequence number可以检查重复发送. 

最常见的是 OSPF.  

##### Comparison of LS vs. DV

 link state 告诉全世界, message 数量多,  robusteness better,     

DV是告诉 neighbors,不会转发



#### 分层 routing

分成几个region . 记录到每个region的就可以了. 

内部采用的叫IGP interior gateway protocol . 比如RIP , OSPF 外部的叫EGP, 具体的有BGP.

要会计算entries 的数量

比如  10 *9 * 8    每个router 就需要 10 local+ 8 +7  =25个table entries

路由交付, 在一个网段就直接交付. 否则就间接交付.  怎么判断?  子网掩码"与"操作. 

#### 广播

Unicast: point-to-point, one-to-one 比如 DV routing , LS routing

广播 one-to-all 发主机号全1 

Sink-tree based broadcast  

Optimal in terms of # of transmissions is minimum  最少传输次数

Does this optimal broadcasting possible in a network only with DV routing?  no .  不能支持sink-tree的 broadcast 最优. 

reverse path forwarding   才能达到最优

##### reverse path forwarding

When a broadcast packet arrives at a router, the router checks to see if the packet arrived on the line that is normally used for sending packets to the source of the packets. 看是不是常用的路.

如果我见过 M 到I 的路径, 那就是最短路, 那就M continues . 否则 stops.

#### Multicast

 one to many, 组播一定是UDP, 同时送给多个接收者. 一次发送, 在传送路径分叉时 把分组复制后转发.  这需要路由器的支持. 

#### Anycast

one to any

 a packet is delivered to the nearest member of a group. Schemes that find these paths are called anycast routing. 
• Example usage: DNS 找最近的

Routing Algorithms: Routing in Ad Hoc Networks

ad hoc

### 3 INTERNETWORKING 

• How Networks Differ 

• How Networks Can Be Connected 

• Tunneling 

• Internetwork Routing 

• Packet Fragmentation

## lec10  网络层2

###  IV.The Network Layer in the Internet

分组可以发送同时接收， 减少总时间。

#### IPv4 协议

Total length: the length of header and data. The maximum is  65,535 bytes.

• DF: Don't Fragment • MF: More Fragment. The flag is set for all fragments except the last
• Fragment offset: fragment belongs
to tell where in the current datagram this
• Time to Live: a counter used to limit packet lifetimes. 

• Protocol: which transport process to give this datagram to. (http://www.iana.org/assignments/protocol-numbers)
• Header checksum: to verify the header only • Source and destination address: to indicate the network number and host number.

head 前一部分20字节是固定长度, 后面是可选字段. 

header一般长 5个words . 一个words 4个字节 .

Classless Inter-Domain Routing，CIDR可以将路由集中起来，在路由表中更灵活地定义地址。它不区分 A 类、B 类、C 类地址，而是使用 CIDR 前缀的值指定地址中作为网络 ID 的位数。 

longest matching prefix  最长匹配前缀. 有两个路由可以匹配的时候就选长的那个. 

聚合

NAT 实现内部ip到外部ip的翻译, 缓解ipv4 地址紧缺的情况, NAT 有大量争议.  打破了ipv4架构, 很多内网一个ip不一定对应一个地址. 

NAT: reserved private IPs  会考

• 10.0.0.0/8 – 10.0.0.0 ~ 10.255.255.255, 16,777,216 hosts 

• 172.16.0.0/12 – 172.16.0.0 ~ 172.31.255.255, 1,048,576 hosts 

•192.168.0.0/16 – 192.168.0.0 ~ 192.168.255.255, 65,536 hosts

一个链路层数据报最大数据量 叫做最大传送单元MTU. 以太网MTU  为1500字节,  ip数据报过长, 就要分装在多个数据报中.   这些叫做片fragment

小测是读一个 public ip地址. 

读截获的  十六进制  packet , 然后问

P2 的ttl是49

How many routers passed before p6 arrived to host A ?

p1 to p4 , which is not sent by host A ?

public IP of B is ? public IP of A is ?

If p7 will be fragmented into fragments MTU 800 ,  

first fragment: length 1 MF 2 offset 3

second fragment: length  MF  offset 

48bit 位用 49 是DF , 50是 MF   DF(don't fragment)=0时才可以被分片, MF(more fragment)=0 说明是最后一片.  

利用ttl 字段研究经过了多少个路由, 一开始 64 后来. 

经过了15站

哪个不是他发的? 

哪个 total length 小于46?

public 地址

大于800字节,拆成两个fragment.

第一个是796 ,  

第二个是 760 , 一共是 1516,  第一个fra 发了796 ,      740的数据 +20 = 760

The IPv4 Protocol: Header fields

Differentiated service:  – Type of service (past): 3 for priority, 3 for Delay,  Throughput, and Reliability, and 2 unused.  

– Differentiated services (now): 6 for service class, 2 for  congestion (e.g. ECN).

IPV6对智能物件有压缩, 因为energy不够 .

[令牌桶算法](https://baike.baidu.com/item/令牌桶算法)是[网络流量](https://baike.baidu.com/item/网络流量)整形（Traffic Shaping）和速率限制（Rate Limiting）中最常使用的一种算法。典型情况下，[令牌桶算法](https://baike.baidu.com/item/令牌桶算法)用来控制发送到网络上的数据的数目，并允许突发数据的发送。

令牌桶这种控制机制基于令牌桶中是否存在令牌来指示什么时候可以发送流量。令牌桶中的每一个令牌都代表一个字节(对于流量整形来说代表一个bit，就traffic policing来讲代表一个byte。参见CCIE Routing and Switching Official Exam Certification Guide 2nd Edition）。如果令牌桶中存在令牌，则允许发送流量；而如果令牌桶中不存在令牌，则不允许发送流量。因此，如果突发门限被合理地配置并且令牌桶中有足够的令牌，那么流量就可以以峰值速率发送。 

#### ipv6

IPv6 地址由 8 组 16 进制的数字来表示，每组表示 16 比特。这些组数字通过 (":")分割。比如,  2001:0db8:85a3:0000:0000:8a2e:0370:7334 是一个有效的地址。

注意前面0省略要用两个冒号：： 



## lec11 网络层3

##### 控制消息协议 ICMP

Internet Control Message Protocol ICMP 是路由器监视 Internet 的协议，当路由器处理数据包的时候发生了以外，就可以用 ICMP 向数据包的源端报告有关的事件，所有的 ICMP 都被封装在一个 IP 数据包里.  分为差错报告 和询问报文两种.  差错报告有5种,  终点不可达,  源点抑制, 超时, 参数问题和重定向(改变路由).  ping使用了 ICMP回送请求和回答报文.  traceroute 使用了ICMP 时间超过报文.  

##### 地址解析协议 ARP

 以太网的网卡并不能理解 IP 地址，每一块 NIC 根据 48 位的以太网地址来发送和接收帧，ARP 协议的作用就是将 IP 地址映射成以太网的地址，优点在于简单，既可以算作网络层的协议，也可以算作数据链 路层的协议。 ARP 协议解决转换问题的方法是在主机的 ARP 高速缓存中存放一个 IP 地址到硬件地址的映射表，并进行动态的更新，每一台主机上都设有一个 SRP 高速缓存，里面有本局域网上的各台主机和路由器的 IP 到硬件地址的映射表。 当一台主机 A 要想本局域网上的主机 B 发送 IP 数据报的时候就会先在缓存中查看查出对应的硬件地址然后写入 MAC 帧中进行发送，否则需要进行一系列的复杂操作。 RARP就是reverse ARP

##### DHCP

dynamic host configuration protocol.  这是应用层协议, 基于UDP. 每个网络必须有一个 DHCP 服务器负责地址的配置，为发送请求的主机分配一个空闲的 IP 地址，并通过 DHCP 的 OFFER 包返回给主机。但是动态分配的 IP 地址只能持续一段时间，到期之前主机必须请求 DHCP 续订，否则时间到了之后主机的 IP 地址就会被取消。 正常情况是从小到大分配. 

##### 标签交换和 MPLS

多协议标签交换 (MPLS) 是指在每个数据包前面增加一个标签，路由器根据数据包标签进行转发，用 标签作为内部表的一个索引，快速查找出正确的输出路线。通用的 MPLS 有 4 个字节，包含 4 个字段，标签存放的是索引，QoS 表明服务类别，S 表示在层次网络中叠加多个标签的做法，TTL 字段指出该数据包 还可以被转发多少次，每经过一个路由器 TTL 减小 1，变成 0 的时候数据包就会被丢弃

#### 内部网关路由协议

##### 路由信息协议 RIP

Routing Information Protocol 是一种分布式的基于距离向量的路由选择协议，比较简单，规定每个路由器都要维护距离向量，而距离也称为跳数，规定从一个路由器到直接连接网络的跳数为 1， RIP 认为最佳路由就是通过的路由器的数目少，即 RIP 会优先选择跳数较少的路径，一条路径最多只能包含 15 个路由器( 这个要背诵 16就是infinite , 实际上现在是远远不够的. )，默认在每 30s 广播一次更新信息(这个不用背诵.  )，并且动态维护路由表。 相比于 OSPF，RIP 只和相邻的路由器交换信息，这个信息也就是路由表，并且有固定的时间间隔。

**split-horizon with poisoned reverse**

但是能收到哪怕是坏消息总是比收不到消息要好得多。我们可以用带毒性逆转的水平分割来实现这一点。

192.168.0.0这个网段的跳数却是16跳，也就是无穷大！所以无论怎样，R3都不会将这个条目置入自已的路由表内。也就保证了路由信息的可靠性。

##### 开放最短路径协议 OSPF

OSPF 的全称是开放最短路径协议 (Open Shortest Path First)，借鉴了 IS-IS(中间系统到中间系统) 协议，已经成为了ISO的标准，它具有以下特点： 

• 使用了分布式的链路状态协议和最短路径算法 

• 是一种动态的算法，支持多种距离度量 

• 实现了均衡负载，使用层次化的网络系统 

• 同时支持点到点的链路和广播网络 OSPF 将自治系统划分成了若干个 area，每一个都是一个单独的网络，每个自治系统有一个骨干区域 backbone。 路由器也分为区域边界路由器和内部路由器、自治系统边界路由器和骨干路由器等等，其中自治系统边界路由器可以把通往其他自治系统的外部路由注入到本区域中。 OSPF 的工作方式本质上是对一张图进行操作，将一组实际网络、路由器和线路抽象到一个有向图中，
路由器之间的连接可以用两条有向的弧来表示，OSPF 会记住最短的路径集合，并在报文转发阶段把流量 分摊到多条路径上面，实现负载均衡，这种方法称为等价成本多路径 (ECMP) 

OSPF 的消息类型有五种，在邻接的路由器之间进行传递，分别是：
• 问候分组，用来发现和维持邻居的可达性 • 数据库描述分组，给出自己的链路状态数据库中所有信息 • 链路状态请求分组，向对方请求阿松某些链路状态项目的详细信息 • 链路状态更新分组，用 flood 更新全网的链路状态 • 链路状态确认分组，对链路更新分组的确认

OSPF是 内部网关协议. 

DV  distance vector 协议 :  RIP   routing information 协议.  

LS  link state 协议 :    OSPF  open shortest path first . 

用带宽来判断路径的优劣弥补了RIP的缺陷（光凭带宽也不是很好），可以更好的控制管理和扩展网络。还有各种小特点比如DR、BDR机制，和适合不同网络类型机制，以及使用不同LSA传递各种信息，各种LSA的特性也不通。所有综合来讲OSPF是比较适合大众选择的一款路由协议。

#### 外部网关路由协议 BGP

 BGP 的全称是边界网关协议 Border Gateway Protocol，在一个自治系统的内部推荐使用 OSPF 和
ISIS，而在自治系统之间用 BGP 比较好，这是因为域内协议和域间协议的目标不同，域内协议所需要做的 只是尽可能有效地将数据包从源端发送到接收方，而域间的路由协议则必须要考虑大量的选择策略，比如是 否接收某个特定自治系统的消息等等。 

BGP 协议只能力求寻找到一条可以达到目的网络并且比较好的路由，采用了路径向量路由 选择协议 用于互联网（Internet）。它的地位是核心的（目前是最重要的，互联网上唯一使用的路由协议）它的目的是去中心化，以达到各个网络自治.BGP一般用于企业和企业之间，也就是运营商骨干网的通信，一般使用在AS内或者AS间通信（这里有个AS的概念），BGP注重的是数据传递的方式以及如何控制数据的走向，路由策略的实行，而对[收敛速度](https://www.zhihu.com/search?q=收敛速度&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"1690062194"})和最优路径没有太多的投入。一般使用BGP更多的是和运营商参与的MPLS专线结合使用，在大型企业网中实现的比较多。

 BGP 使用四种报文，分别是打开，更新，保活和通知

RIP、OSPF、BGP 三种协议的区别有：
• RIP 使用距离向量算法，传递 UDP 协议，选择跳数最少的路径 • OSPF 使用链路状态算法，传递 IP 协议，选择代价最低的路径 • BGP 使用路径向量算法，传递 TCP 协议，选择比较好的路径

inter AS :  RIP, OSPF    可以只关心performance

Inter AS routing : BGP  还要考虑别的因素.

AS（Autonomous system）：自治系统，指在一个（有时是多个）组织管辖下的所有IP网络和路由器的全体，它们对互联网执行共同的路由策略。也就是说，对于互联网来说，一个AS是一个独立的整体网络。而BGP实现的网络自治也是指各个AS自治。每个AS有自己唯一的编号。

IGP（Interior Gateway Protocol）：[内部网关协议](https://www.zhihu.com/search?q=内部网关协议&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"article"%2C"sourceId"%3A"25433049"})，在一个AS内部所使用的一种路由协议。一个AS内部也可以有多个路由器管理多个网络。各个路由器之间需要路由信息以知道子网络的可达信息。IGP就是用来管理这些路由。代表的实现有RIP和OSPF。

为啥需要BGP: https://zhuanlan.zhihu.com/p/25433049

BGP可以说是最复杂的路由协议。它是[应用层协议](https://www.zhihu.com/search?q=应用层协议&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"article"%2C"sourceId"%3A"25433049"})，其传输层使用TCP，默认端口号是179。因为是应用层协议，可以认为它的连接是可靠的，并且不用考虑底层的工作，例如fragment，确认，重传等等。BGP是唯一使用TCP作为传输层的路由协议，其他的路由协议可能都还到不了传输层。并且BGP适合大规模网络环境

#### IP 组播和移动 IP

IP 的组播 multicast一定只用在 UDP 协议上，普通的 IP 通信只发生在一个发送方和一个接收方之间，而 IP 用D 类 IP 地址来支持一对多的通信或者组播，每个 D 类地址标识了一组主机。IGMP 是internet  group management 协议 .(IGMP) 用来解决广播成员分布在不同网络上面的情况，在自治系统中主要使用协议独立组播协议 PIM. 值得注意的是，组播一次只发送一份数据。

  

## lec12  传输层

##### 作用

运输层向位于其上的应用层提供通信服务，是用户功能中的最底层，也是属于面向通信部分的最高层。 计算机通信的真正端点并不是主机，而是主机之中的进程，也就是说端到端的通信其实是两个应用进程之间 的通信。
运输层提供了进程之间的逻辑通信，而网络层则提供了主机之间的逻辑通信，基于这种功能，运输层最重要的功能是复用 (multiplexing) 和分用 (demultiplexing), 

• 复用：发送方不同的进程可以用同一个传输层的协议来传输数据 • 分用：接收方的运输层在处理完报文之后可以把数据交付给正确的接收方进程

packet  ip 路由

frame 差错校验, 纠错 

ELEMENTS OF TRANSPORT PROTOCOLS • Addressing • Connection Establishment • Connection Release • Error Control and Flow Control • Multiplexing • Crash Recovery

The differences between transport services and network  services. 

为什么有两个不同的层？  – 传输代码完全运行在用户机器上，但网络层主要运行在通常由运营商运营的路由器上。  – 网络层存在问题（丢失数据包、路由器崩溃……） – 传输层提高了网络层的 QoS。

–  The transport service is **more reliable** than the  network service. 

– Application programmers can write code according  to a standard set of transport service primitives and  have these programs work on a wide variety of  networks.

##### 传输层和link 层的区别

 – Addressing:  • Link: implicit • Transport: explicit 

– Connection establishment • Link: simple • Transport: complicated 

– Storage capacity:  • Link: no • Transport: yes => a network can delay a packet 

– Buffering • Link: allocate a fixed number of buffers to each line • Transport: a large number of connections and variations in the  bandwidth may require a dynamic and complicated approach.

##### addressing 

NSAP: Network service access point – IP (32 bits)  • TSAP: Transport service access point – Port (16 bits) 

• How a host knows a TSAP address at a server? – Some TSAP addresses are so famous that they are  fixed, e.g. HTTP=80 and others listed in /etc/services – A special process portmapper: service name ->  TSAP address 

• Many server processes will be used rarely and it  is wasteful to have them active – process server: e.g. inetd on UNIX

##### 重复了怎么办

discard 丢弃 , 但是 There are two problems which complicates the  scenario: – Possible wrap around of seqno – Client/Host or Server may crash

• Two assumptions that simplifies the problem – Assumption 1. Time for seqno wrap around 回包 (T1) is typically large if, e.g., seqno is 32 bits  long.  – Assumption 2. If pkt delays a relatively short  time (T2

保证时间够长后一定是新的packet.

如果见过, 时间很短, 可以确定是重复包.  如果见过, 时间很长.     记住存储空间很大?  可以记住没有收到的seqno,  甚至都不用记住seqno, 记住sequence no大小就可以了.

##### Restrict packet lifetime

可以使用以下技术之一将数据包生命周期限制为已知最大值

– Restricted subnet design.  – Putting a hop counter in each packet.  – Timestamping each packet (router synchronization  required)

use time-of-day clock to limit sending rate

The clocks at different hosts need not be  synchronized

##### 差错控制**Error control**

 is ensuring that the data is delivered with the desired level of reliability, usually that all of the data is delivered without any errors.
**Flow control** is keeping a fast transmitter from overrunning a slow receiver.
Solutions to these issues (same as data link layer): 

– A frame carries error detecting codes, e.g., CRC

 – ARQ: Automatic Repeat request

– Max send window size w: stop and wait (w=1), large w enables pipelining
– Sliding window protocol: combines the above features and supports bidirectional data transfer.

Differences: • Error detection: – The link layer checksum protects a frame while it crosses a single link.
– The transport layer checksum protects a segment while it crosses an entire network path. It is an end-to-end check, which is not the same as having a check on every link.
– End-to-end argument: transport check is essential for correctness while link layer check is not essential but valuable for performance.
• Sliding window protocol: – Link layer: stop and wait usually suffices, e.g., 802.11 

– Transport layer: use larger window size

##### 吞吐量

What’s the average throughput of TCP as a function of window size and RTT? – Ignore slow start
• Let W be the window size when loss occurs. • When window is W, throughput is W/RTT • Just after loss, window drops to W/2, throughput to W/2RTT.

flow 控制是根据receive 来控制, 网络不好那怎么调整发送呢?

## lec13 传输层

#### Crash Recovery

#### Congestion Control拥塞控制

Max-Min Fairness

公平和高效, 最慢的网络最大化

Convergence. 需求是不断变化的, 要快速响应, 收敛到决策的最优点. 

explicit : congestion 的情况有没有设备告诉sender.  TCP with ECN 和XCP协议可以. 其他的是靠delay变大和丢包率来判断. 

为什么要线性增加然后按比例增长? 

因为这样可以到最优点, 不会反复震荡.

不一定拥塞,  无线网络本身就可能丢包. 那怎么检测?

#### RPC

(Remote Procedure Call) allows programs to call  procedures located on remote hosts

可以模仿B/S架构的调用方式，在B服务暴露一个[Restful](https://www.jianshu.com/p/e3c4b2837961)接口，然后A服务通过调用这个Restful接口来间接调用CalculatorImpl的add方法。

很好，这已经很接近RPC了。不过这样每次调用时，都需要写一串发起http请求的代码，比如httpClient.sendRequest...之类的。能不能像本地调用一样，让使用者感知不到远程调用的过程呢.**RPC要解决的两个问题：**
1️⃣解决分布式系统中，服务之间的调用问题
2️⃣远程调用时，要能够像本地调用一样方便，让调用者感知不到远程调用的逻辑

底层也是用UDP实现.

工业界有一些rustful api,   RPC 在穿透的时候 性能有区别.  很多场景用rustful api. 

有的不幂等,  底层要用TCP

比如，既然是分布式了，那么一个服务可能有多个实例，在调用时，要如何获取这些实例的地址呢？

这时候就需要一个服务注册中心，比如在Dubbo里头，就可以使用Zookeeper作为注册中心。在调用时，从Zookeeper获取服务的实例列表，再从中选择一个进行调用

那么选哪个调用好呢？这时候就需要负载均衡了，于是又得考虑如何实现负载均衡，比如Dubbo就提供了好几种负载均衡策略。

这还没完，总不能每次调用时都去注册中心查询实例列表吧，这样效率多低呀，于是又有了缓存，有了缓存，就要考虑缓存的更新问题……

#### RTP

Real-time Transport Protocol 是一个 传输层协议, 但是实现起来像是在应用层. 用在Multimedia applications such as Internet radio, Internet  telephony, music-on-demand, videoconferencing. 不需要和TCP一样深入了解head.  RTP 是base on UDP的. buffer 让播放更流畅. 

#### TCP

TCP (Transmission Control Protocol) 通过不可靠的网络提供可靠的端到端字节流

分组, 然后放到数据包中传输.

service model 就是用socket 一些原语来描述.

##### port

 20数据传输,21控制 ftp , 22 ssh,  25 smtp, 80 http,   443 https. 110 pop3,  143IMAP , 23 telnet

全都在等太消耗资源了, 需要守护进程,  inetd or xinetd. 来一个请求来分配给具体的应用. 

为了提高利用率, 先写到buffer 等足够多再发, 你也可以用push flag 来强制立刻发送. 

Each segment, 包括TCP header, must fit in the  65515 (=65535-20) byte IP payload. (Total length in IP  pkt is 16 bits long) 实际上很少用到这么大的. 

Each network has a maximum transfer unit or MTU  (1500 for the Ethernet)

The TCP entities 滑动窗口协议

sequence number是对bytes编号 .不是对segment 编号. 确认是对报文段确认. 

TCP header length: how many 32-bit words are contained  in the TCP header.  注意这 个length不是bytes而是32 bits. 考试很多计算length .

RST bit: to reset a connection that has become confused due to a host  crash or some other reason.  

SYN bit: to used to establish connections. SYN for CONNECTION  REQUEST, SYN+ACK for CONNECTION ACCEPTED.   是用来建立连接的. 

FIN bit: used to release a connection.

例题:

In a network whose max segment is 128 bytes,  max segment lifetime is 30 sec, and has 8-bit  sequence numbers, what is the maximum data  rate per connection?

很大会在lifetime出现两个一样的sequence num.

30秒内不能从 0 -256再回来.  30sec  256bytes =256/30=8.533333 bytes/s

Sliding Window来实现flow control

收到2K 回复 ack =2048(注意不是1) win =2048

Nagle’s algorithm

延时变得很大.  运行效率低. 避免一个bytes 一个个发. 

##### Timer Management

Retransmission timer  要不要重传的timer.  SRTT (Smoothed Round-Trip Time) 

SRTT = α SRTT + (1- α) R 每次根据到达的ack 来调整SRTT.

RTO (Retransmission TimeOut) RTO = SRTT  + 4 RTTVAR

Persistence timer 问一问buffer 是不是0 ,  send probe to prevent the deadlock

Keepalive timer

滑动窗口太大, 会导致路由器变得拥挤, 主机可能丢失分组. 

##### Congestion Control

100万个PC 在链路上， 网络不行了， 所以需要拥塞控制。 流量控制是PC来不及接收了。 

TCP的拥塞控制采用了四种算法，即 **慢开始** 、 **拥塞避免** 、**快重传** 和 **快恢复**。

- **慢开始：** 初始值为1，每经过一个传播轮次，收到确认后cwnd加倍。
- **拥塞避免：**  > 慢开始门限后，用拥塞避免， 每经过一个往返时间RTT, 收到确认后发送方的cwnd加1.
- 快重传  连续收到三个重复的ack后， 直接重传。
- 快恢复， 连续收到三个重复的ack后， 把cwnd 设置为 slow start threash 的大小， 然后执行 拥塞避免

三次超时后cwnd为1 

1988年  ,To approximate an AIMD congestion window , To represent congestion signal by packet loss

The AIMD rule will take a very long time to reach a good  operating point on fast networks if the congestion window is  started from a small size. => slow start is not slow 

Slow start from an initial congestion window of 1 segment

cwnd 慢开始快速翻倍,  然后拥塞避免线性增长, 然后3次超时变成1 

实际发送速度比较慢, 所以叫slow

TCP Reno 3次重复ack就 fast recovery, 不要变成1 而是回到threshold. 

把packet loss 分成了两类, 收到3个duplicate acks, 就 cwnd 降半.  如果 timeout 那就认为是严重的阻塞, cwnd降低到1. 

send rate =  cwnd /RTT  round trip time

拥塞避免的时候,  cwnd = cwnd + MSS *(MSS/cwnd)  两次才能翻倍

Average throughout: 0.75 W/RTT

## lec14应用层

### DNS

why DNS?   记ip地址太麻烦. 

13个顶级域名root服务器, 国内一个都没有, 只有几个镜像. 

资源类型 

A    ipv4 地址 

MX     例如  3 top

TXT  都是ascii text

SOA   例如  star boss( 9527 ,xxx ) 



 根域名服务器 有13个

最高层次, 最重要, 

所有根域名服务器 都知道 所有的顶级域名服务器的ip地址. 

任何local 无法解析的时候都首先求助 root , 通常告诉local 下一步找哪个 top 

顶级域名服务器,管理二级域名. 

授权域名服务器, 把管辖的主机名转换为 该主机的ip地址. 每台主机必须在授权域名服务器 注册, 

本地域名服务器, 

最坏要问四次, 本地, 根.com,  顶级xyz.com, 权限 abc.xyz.com

### WWW

变化很快,每年都有变化. 

点下链接后发生了什么?

点下链接, 浏览器 问 DNS  ip地址, 

DNS 回复IP地址,  

 浏览器 产生 port80的tcp 连接, 发送request  请求html文件 

server 回复发送html文件

tcp 连接释放.

浏览器显示文字

浏览器fetches and display 图片. 

A URL points to one specific host ,  有时候不需要关注地点, URI  (uniform resource identifiers)是关注这个是什么东西.  

URL 包括三个部分, protocol 如http,  DNS name , 还有 file name 比如 index.html

Some URIs tell how to locate a resource. These are  the URLs.  

• Other URIs tell the name of a resource but not where  to find it. These URIs are called URNs (Uniform  Resource Names).

##### server 

1. Resolve the name of the Web page requested.  

2. Perform access control on the Web page. 
3.  Check the cache.  
4.  Fetch the requested page from disk or run a program to  build it.  
5. Determine the rest of the response (e.g., the MIME type to  send). 
6. Return the response to the client. 
7.  Make an entry in the server log

##### cookies

web 基本上是stateless的. 

track user 通过观察ip吗? 不能保证是同一个用户.   让浏览器保存cookie, 下一次来, 浏览器会发送cookie 给网站. server看到了之后就知道

token是服务器发给你的凭证.  cookie 让服务商可以定位每个用户

### 静态页面

##### HTML

css   cascading style sheets , 规定 h1 用什么字体, h2 用什么字体, 浏览器根据css 进行实际的渲染. 

### 动态页面

#### CGI

 (Common Gateway Interface): provides an interface  to allow Web servers to talk to back-end programs and  scripts (e.g. Python, Ruby, Perl) that can accept input (e.g.  from forms) and generate HTML pages in response. 

 – Server pages: to embed little scripts inside HTML pages  嵌在 html 内部的脚本 and have them be executed by the server itself to generate  the page.  • PHP: Hypertext Preprocessor • JSP: Java Server Pages • ASP.NET: Active Server Page

php 执行完了, 返回给用户一个页面. 

#### 服务端page

php, jsp, asp.net 三种 

PHP (Hypertext Preprocessor) 

• JSP (JavaServer Pages): the dynamic part is written in the Java programming language. Pages using this technique have the file extension .jsp. 

• ASP.NET (Active Server Pages .NET) is Microsoft’s version of PHP and JavaServer Pages. It uses programs written in Microsoft’s proprietary .NET networked application framework for generating the dynamic content. Pages using this technique have the extension .aspx.

#### 客户端脚本

上面的这几个有问题:  What none of them can do is respond to mouse movements or interact with users directly

Starting with HTML 4.0, these scripts are permitted using the tag 

在浏览器上渲染 , 会考这几个软件名字

JavaScript is very popular way to make Web pages highly interactive. 

• VBScript (based on Visual Basic) is an alternative on Windows platfroms. 

• Java applets runs on the JVM (Java Virtual Machine) 

• ActiveX Controls (which are programs compiled to x86 machine language and executed on the bare hardware) from Microsoft runs on Windows

##### AJAX

AJAX is a set of technologies that work together to enable  Web applications that are every bit as responsive and  powerful as traditional desktop applications. The  technologies are: 

1. HTML and CSS to present information as pages. 
2.  XML (eXtensible Markup Language) to let programs exchange  application data with the server. 
3. DOM (Document Object Model) to change parts of pages while  they are viewed. 
4. An asynchronous way for programs to send and retrieve XML  data. 
5. JavaScript as a language to bind all this functionality together.

操控dom 文件 document object model

dom tree :

##### XML

XML（可扩展标记 extensible markup language语言），是一种用于指定结构化内容的语言。
• HTML 将内容与格式混合在一起，因为它与信息的呈现有关。
• XML 允许构建 Web 内容以进行自动处理。
• 没有为 XML 定义的标签。 每个用户都可以定义自己的标签。

##### 异步请求

To provide a responsive interface in the browser while sending or  receiving data, it must be possible for scripts to perform asynchronous  I/O that does not block the display while awaiting the response to a  request.

Modern browsers have support for this model of communication

为了在发送或接收数据时在浏览器中提供响应式界面，脚本必须能够执行异步 I/O，在等待对请求的响应时不会阻塞显示。
• 例如，考虑可以在浏览器中滚动的地图。
当通知滚动动作时，如果地图的视图靠近数据的边缘，地图页面上的脚本可能会从服务器请求更多的地图数据。
• 获取这些数据时，接口不应冻结。
• 相反，滚动应该继续顺利进行。
• 当数据到达时，脚本会收到通知，以便它可以使用数据。
如果一切顺利，将在需要之前获取新的地图数据。
• 现代浏览器支持这种通信模型。

#### HTTP

HTTP 是一种应用层协议，因为它运行在 TCP 之上并且与 Web 密切相关。  会考
• 现在HTTP 变得更像是一种传输协议，它为进程提供一种跨越不同网络边界进行内容通信的方式。
这些进程不必是 Web 浏览器和 Web 服务器。
– 媒体播放器可以使用 HTTP 与服务器通信并请求专辑信息。
– 防病毒软件可以使用 HTTP 下载最新更新。

HTTP 1.0 with multiple connection

http1.1  with persistent connections  也就是长连接, 连接建立一次, 下次直接发请求就可以了.

HTTP是无状态协议

TCP 服务有  FTP, telnet, SMTP , HTTP, POP3   UDP 服务有 DNS, SNMP ,QQ

内置http reuest 方法: 

GET  要求读一个web page

HEAD  要求读个header.  不需要返回请求对象

PUT  要求 store 一个web page  

POST append 一个 named resource  POST方法用于将实体提交到指定的资源，通常导致在服务器上的状态变化或副作用。

DELETE remove web page

TRACE  echo 接下来的request

CONNECT方法建立一个到由目标资源标识的服务器的隧道。

#### The Mobile Web

 Difficulties for mobile phones browsing the web

1. Relatively small screens preclude large pages  and large images. 
2. Limited input capabilities make it tedious to enter  URLs or other lengthy input.
3.  Network bandwidth is limited over wireless links,  particularly on 3G networks 太贵了
4. Connectivity may be intermittent. 
5. Computing power is limited, for reasons of battery life, size, heat dissipation, and cost.

可以用3种方法:  cache, server replication, content delivery network来加快access web page的速度.  会考 

内容分发网络节点会在多个地点，多个不同的网络上摆放。这些节点之间会动态的互相传输内容，对用户的下载行为优化，并借此减少内容供应者所需要的带宽成本，改善用户的下载速度，提高系统的稳定性。

#### Email

Two kinds of Message Formats 

– RFC 5322 – The Internet Message format – Envelop fields vs message fields – ASCII message format 

– MIME (Multipurpose Internet Mail Extensions) message format

gmail 浏览器给邮件服务器发是http协议, 不同邮件服务器用 smtp 协议.

POP3 在传输层是明文传输密码的, 基于ascii码 

SMTP port25, ascii协议,TCP连接. 

##### MIME

非ascii码的数据, 要用mime协议转换. 

message类型 包括 http,rfc822  会考. 

audio类型 包括 basic, mpeg, mp4 

## chapter8 网络安全

#### Intrusion Detection and Prevention

IDS (Intrusion Detection System)

IPS (Intrusion Prevention System)

### 对称加密算法

#### DES 

#### AES 

The Advanced Encryption Standard

The algorithm must be a symmetric block cipher.

#### PUBLIC-KEY ALGORITHMS

How Alice and Bob establish a secure channel?  会考

– Both Alice's encryption key, EA, and Bob's encryption key, EB, are assumed to be in a publicly readable file. 

– Now Alice takes her first message, P, computes EB(P) 然后发送 

– Bob then decrypts it by applying his secret key DB [i.e. DB(EB(P) ) = P].  接收方用自己的私钥解密. 

– No one else can read the encrypted message EB(P), because the encryption system is assumed strong and because it is too difficult to derive DB from the publicly known EB. 

#### RSA algorithm

Factoring large numbers is very difficult. RSA 的保密体系都是建立在这个上面的. 

#### 数字签名

Digital Signatures

##### Symmetric-key signatures 

• BB (Big Brother): the central authority that knows everything and whom everyone trusts. 

Each user chooses a secret key and carries it by hand to BB’s office. Thus , only Alice and BB know Alice’s secret key, KA and, so on. 

• Alice sends a signed plaintext message P to Bob. – RA, a random number chosen by Alice. – t, timestamp to prevent replay attack.  时间戳可以防止replay attack . 过几个小时replay了就发现明显不对.   如果过几秒可能会伪造. 

但是需要KBB存在 

##### Public key signatures

if Alice discloses her secret key?   可能被伪造. 

– if Alice modifies her secret key? 

##### Message Digests

A message digest is a cryptographic hash function containing a string of digits created by a one-way hashing formula

计算MD5 , 错了一个bit, output完全不一样. 

##### The Birthday Attack

A 64-bit MD can probably be broken by generating about 2^32 messages and looking for two with the same message digest. 

#### 怎么获得public key 

• One solution: Bob puts his public key in the website for others to retrieve.

实际上, 是依靠证书,  certification authority  CA.  和 big brother不同. 他是certify public key 的.  浏览器也是用CA.

X.509 is the standard for managing the certificates



Authentication Protocols: Shared Secret Key

怎么证明你是A , 把一个随机数用共同的加密. 

Bob 收到了,  A发个随机数RA给bob ,然后 bob返回  Kab(ra) 

还有一个简化的版本. 

就是A发Ra和,  bob 返回  Kab(Ra ) 同时  Rb.   Alice 返回 Kab(Rb)

但是这两个都很容易被攻击!!

比如简化版本  攻击者Trudy 告诉bob我是alice,  发RT challenge bob. 然后bob回复.   Kab(Rt ) 同时发送随机数Rb challenge trudy. 

然后 Trudy 用另一个session 发送 A, **Rb**, 然后bob 回复加密后的  Kab(Rb ) 就把Kab(Rb) 告诉 trudy了. 

但是这个不能攻击 原版本.

  原版本 不会同时回复随机数和 Kab(Rb) , 不过 trudy 可以攻击 alice.  

基本原理就是 开两个session, 让对方把加密后的随机数发过来.

#### 密钥分发
