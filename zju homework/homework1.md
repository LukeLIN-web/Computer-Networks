homework1 

1. Imagine that you have trained your St. Bernard, Bernie, to carry a box of three 8-mm tapes instead of a flask of brandy. (When your disk fills up, you consider that an emergency.) These tapes each contain 7 gigabytes. The dog can travel to your side, wherever you may be, at 18 km/hour. For what range of distances does Bernie have a higher data rate than a transmission line whose data rate (excluding overhead) is 150 Mbps? How does your answer change if (i) Bernie’s speed is doubled; (ii) each tape capacity is doubled; (iii) the data rate of the transmission line is doubled.

   each types 7*10^9 bytes 

   3 types  = >  2.1*10^10 bytes 

   1Mbps=1,000,000bps = 125，000B/s

   transmission line data rate : 150*10^6/8=18.75 *10^6 bytes/s

   dog speed: 18km/h = 5m/s

   So transmission line need 1120s to transmit these data.

   In 1120s, the dog can travel 5600m. 

   Thus, in the range of 5600 meters, the dog transmits data faster than the transmission line.

   i) Bernie’s speed is doubled , range  = 5600*2= 11200m

   ii) each tape capacity is doubled, range = 5600*2 = 11200m

   iii)the data rate of the transmission line is doubled. range = 2800m


答案是 按1024的三次方算的



1. What are two reasons for using layered protocols? What is one possible disadvantage of using layered protocols?

This architecture offers an abstract framework to exchange the information among hosts by a simple way. Different hosts could use different implementations.

It divides the complex tasks into simple tasks.

However, using layered protocols has one possible disadvantage. The higher level layers  can't know what in a connection a problem is, or exactly what the problem is.

答案:  在使用分层协议的其他原因中，使用它们会导致将设计问题分解为更小、更易于管理的部分，而分层意味着可以更改协议而不影响更高或更低的协议。 一个可能的缺点是分层系统的性能可能比单体系统的性能更差，尽管实现和管理单体系统极其困难。


3. In some networks, the data link layer handles transmission errors by requesting that damaged frames be retransmitted. If the probability of a frame’s being damaged is p, what is the mean number of transmissions required to send a frame? Assume that acknowledgements are never lost.

fail : p    ,  success: 1-p  The probability of failing k-1 times :  p ^(k-1)

```
the mean number of transmissions  =   E(x) = 1*(1-p) + 2*(1-p)*p + 3 *(1-p) *p^2 + .... = 1/(1-p)
```

对的

4. What is the main difference between TCP and UDP?

TCP is connection-oriented. UDP is connectionless. 这是最重要的. 之所以说UDP是无连接的，因为使用UDP协议的发送者和接受者之间不必存在任何长期的关系。 它们没有建立连接过程，整个消息传输过程简单来说就是“发送即结束

UDP is much faster than TCP. It has a much more effective protocol because it is simpler and faster.

TCP allows retransmission of data packets (lost ones)- something that the UDP doesn’t offer. 

UDP does not work on end-to-end communications. Conversely, TCP delivers data in the intended order to the server from the user. In fact, UDP also does not check a receiver’s readiness. 

5. How long was a bit in the original 802.3 standard in meters? Use a transmission speed of 10 Mbps and assume the propagation speed in coax is 2/3 the speed of light in vacuum.

```
The speed of light in coax: 200000 km/sec (200 meter/μsec).
At 10Mbps, it takes 0.1  μsec to transmit a bit.
0.1 * 200 = 20 meters.
Hence, a bit is 20 meters long here.  对的
```

6. List one advantage and one disadvantage of having international standards for network protocols.

disadvantage: It is difficult to modify some parts of the standards.
advantage: people from different countries could communicate with each other easily. 

一个优点是，如果每个人都使用标准，那么每个人都可以与每个人交谈。 另一个优势是，任何标准的广泛使用都将带来规模经济，就像 VLSI 芯片一样。 缺点是实现标准化所需的政治妥协经常导致标准差。 另一个缺点是，一旦标准被广泛采用，即使发现了新的更好的技术或方法，也很难改变。 此外，当它被接受时，它可能已经过时了。

7. Which layers are common in the OSI model and TCP/IP model?

application , session, presentation -> **application**

transportation - > transportation

network -> network

datalink- > datalink

physical - > physical 

If four layer TCP/IP, Physical layer and data link layer merged into one network interface layer.

答案: Application layer , transport layer, network(internet) layer

