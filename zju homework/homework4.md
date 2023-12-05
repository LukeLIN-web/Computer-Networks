# homework4

homework4

1. A group of N stations share a 56-kbps pure ALOHA channel. Each station outputs a 1000-bit frame on average once every 100 sec, even if the previous one has not yet been sent (e.g., the stations can buffer outgoing frames). What is the maximum value of N?

```
maximum flow capacity of the ALOHA channel = 18.4% = 0.184
Then, the stations N share 56 kbps
0.184 * 56kbps = 10.3kbps
Each station requires 10bps 
N = 10300/10 = 1030 stations
答案:  使用纯 ALOHA，可用带宽为 0.184 × 56 kbps = 10.3 kbps。 每个站需要10 bps，所以N=10300/10=1030站
```

1. Consider the delay of pure ALOHA versus slotted ALOHA at low load. Which one is less? Explain your answer.

with pure ALOHA, transmission can start instantly. At low load, no collisions are expected so the transmission is likely to be successful. With slotted ALOHA, it has to wait for the next slot. This introduces half a slot time of delay (on an average)

Thus, pure ALOHA has less delay.

答案: 使用纯 ALOHA，传输可以立即开始。 在低负载下，预计不会发生冲突，因此传输很可能成功。 使用时隙 ALOHA，它必须等待下一个时隙。 这引入了半个时隙的延迟。

1. Sixteen stations, numbered 1 through 16, are contending for the use of a shared channel by using the adaptive tree walk protocol. If all the stations whose addresses are prime numbers suddenly become ready at once, how many bit slots are needed to resolve the contention?

Multiple Access Protocols: Limited-Contention protocols 自适应树搜索协议,assign stations to slots dynamically

A 是root, 第二层B C 第三层 DEFG 第四层 HIJKLMNO

Stations 2, 3, 5, 7, 11, and 13 want to send. Viewing from node A, for slot #1: station 2, 3, 5, 7, 11, 13 will compete. Then, viewing from node B, for slot #2: station 2, 3, 5, 7 will compete. Then, viewing from node D, for slot #3: station 2, 3 will compete. Then, viewing from node H, for slot #4: station 2 will compete and obtain the slot. Then, viewing from node I, for slot #5: station 3 will compete and obtain the slot. Then, viewing from node E, for slot #6: station 5, 7 will compete. Then, viewing from node J, for slot #7: station 5 will compete and obtain the slot. Then, viewing from node K, for slot #8: station 7 will compete and obtain the slot. Then, viewing from node C, for slot #9: station 11, 13 will compete. Then, viewing from node F, for slot #10:station 11 will compete and obtain the slot. Then, viewing from node G, for slot #11:station 13 will compete and obtain the slot. Thus, 11 slots are needed

答案: 就是上面

4.Six stations, A through F, communicate using the MACA protocol. Is it possible for two transmissions to take place simultaneously? Explain your answer.

Yes, MACA (Multiple Access w/ Collision Avoidance) uses collision avoidance via RTS's (Request to send). Since they are in a straight line and that each station can reach only its nearest neighbours, A can send to B while E is sending to F. 答案: 是的。 假设它们在一条直线上，并且每个站点只能到达其最近的邻居。 然后 A 可以发送给 B，而 E 发送给 F。

1. Consider building a CSMA/CD network running at 1Gbps over a 1km cable with no repeaters. The signal speed in the cable is 200,000 km/sec. What is the minimum frame size?

one way propagation time = 1/200000 = 5 x 10-6 s = 5 µs

so for both ways it would be = 2 x 5 µsec = 10 µsec To make CSMA/CD work, it must be impossible to transmit an entire frame in this interval. At 1 Gbps, all frames shorter than 10,000 bits can be completely transmitted in under 10 µsec, so the minimum frame is 10,000 bits or 1250 bytes. 对的 , 就是答案

1. Please show the differences between (a) The Ethernet CSMA/CD protocol and the 802.11 CSMA/CA protocol (b) The MACA protocol and the 802.11 CSMA/CA protocol

a)

CSMA/CD stands for **Carrier Sense Multiple Access / Collision Detection**. It is operated in the medium access control layer. It senses of the shared channel is busy for broadcasting and interrupts the broadcast until the channel is free. In CSMA/CD collision is detected by broadcast sensing from the other stations. Upon collision detection in CSMA/CD, the transmission is stopped and a jam signal is sent by the stations and then the station waits for a random time context before retransmission.

**CSMA/CA:** CSMA/CA stands for **Carrier Sense Multiple Access / Collision Avoidance** is a network protocol for carrier transmission. Like CSMA/CD it is also operated in the medium access control layer. Unlike CSMA/CD(that is effective after a collision) CSMA / CA is effective before a collision.

| S.NO | CSMA/CD                                                               | CSMA/CA                                                                         |
| ---- | --------------------------------------------------------------------- | ------------------------------------------------------------------------------- |
| 1.   | CSMA / CD is effective after a collision.                             | Whereas CSMA / CA is effective before a collision.                              |
| 2.   | CSMA / CD is used in wired networks.                                  | Whereas CSMA / CA is commonly used in wireless networks.                        |
| 3.   | It only reduces the recovery time.                                    | Whereas CSMA/ CA minimizes the possibility of collision.                        |
| 4.   | CSMA / CD resends the data frame whenever a conflict occurs.          | Whereas CSMA / CA will first transmit the intent to send for data transmission. |
| 5.   | CSMA / CD is used in 802.3 standard.                                  | While CSMA / CA is used in 802.11 standard.                                     |
| 6.   | It is more efficient than simple CSMA(Carrier Sense Multiple Access). | While it is similar to simple CSMA(Carrier Sense Multiple Access).              |

b)

The MACA (Multiple Access with Collision Avoidance) protocol. A sending an RTS to B, B responding with a CTS to A

CSMA/CA 工作过程 接收方和发送方 发送方发送一个RTS帧给接收方，从而发起发送请求。RTS帧包含整个通讯过程2需要的时间NAV 接收方接收到RTS帧，如果判断此时信道可以传输，则向发送方发送一个CTS帧进行确认。CTS同样包含发送方要发送的数据帧的长度。 接收方接收到CTS帧，开始发送数据。 接收方接收完数据帧后，向发送方返回一个ACK帧确认。

两个协议都可以解决隐蔽站问题，解决这个问题的关键在于离接收方近的站要保持安静。这个通过CTS就可以实现，只要接收到CTS的其他站保持安静就可以了。 而解决暴露站问题的关键在于，离发送方近的站点不需要保持安静，也就是说不需要对RTS做出任何反应，就像MACA所做的这样。而CSMA/CA中接收到RTS帧的站点也需要保持安静，这就导致了暴露站问题。 那么就到了下一个问题，为什么CSMA/CA要这样做呢.

最关键的区别在于，MACA是一个不可靠的协议，他只管发送，不管发送出去的东西有没有被正确接收。而CSMA/CA增加了一个ACK帧进行确认，是可靠的通讯协议。而在这段时间里面，发送方同样有可能接受数据->ACK帧。为了保证发送方能无冲突接收到ACK，所有离发送方近的站点同样需要保持安静。所以所有站点无论是接收到RTS还是CTS都需要保持安静一段时间。这也导致CSMA/CA的效率比较低。

答案:

a) CSMA CD 通过检测碰撞的发生来运行。 一旦检测到冲突，CSMA CD 立即终止传输，这样发射器就不必浪费大量时间继续传输。 最后的信息可以重传。 相比之下，CSMA CA 不处理碰撞后的恢复。 它的作用是检查介质是否在使用中。 如果它忙，则发射器等待直到它空闲才开始发射。 这有效地最大限度地减少了冲突的可能性，并更有效地利用了媒体。 Carrier Sense Multiple Access / Collision Avoidance

CSMA CD 和 CSMA CA 之间的另一个区别是它们通常使用的地方: CSMA CD 主要用于有线安装，因为它可以检测是否发生了碰撞。 对于无线安装，发射器不可能检测是否发生了碰撞。 这就是为什么无线安装经常使用 CSMA CA 而不是 CSMACD。

(b) 802.11 中的 RTS/CTS 对暴露终端问题没有帮助。 因此，考虑到图 4-11(b) 中的情况，MACA 协议将允许同时进行通信，B 到 A 和 C 到 D，但 802.11 一次只允许进行这些通信中的一个。

1. An unscrupulous host, A, connected to an 802.3 (Ethernet) network biases their implementation of the binary exponential backoff algorithm so they always choose from {0,1} after a collision, in any situation. Another host, B, is trying to send a frame at the same time as A. Assuming A and B collide exactly three times before one of their transmissions succeeds, what are the odds that B sends its frame before A(as opposed to A sending before B)?

3 次, B可以从 0-7 的时间间隔选择一个.

A = 0 , B = 0 collision, B >0 都是 A先发送.

A= 1 , B = 1 collision , B >1 都是 A先发送.

16个情况, 2个 collisions , B 只有一种就是 A为1B为0 ,

1/14

上面是对的

1. Consider the following wireless network, where the circles are showing transmission ranges, and the presence of a host (letter) in a particular circle indicates it can hear that transmitter. If hosts A and C are both trying to send to host B will they encounter the hidden or exposed station problems? Does the MACA protocol help in this situation?

Host C can hear both A and B, but A cannot hear C. Thus A transmitting to B will encounter C as a hidden station: A may listen, hear nothing and attempt to send to B while C is already sending to B.

MACA does help. In MACA, A and C would first send RTS packets to B to initiate their data transmissions. C can hear A’s transmission and would know to stay quiet if A sends first. If C sends first, while A cannot hear C, A can hear B’s CTS response to C and knows not to attempt sending until that has time to complete. This prevents A from interrupting a C ->B transmission. A先发, C可以知道.就quiet. C先发, A可以听到B的CTS就quiet.

不过 collisions can still occur—e.g., via simultaneous RTS packets.

答案: 主机 C 可以听到 A 和 B，但 A 听不到 C。因此，向 B 发送的 A 将遇到 C 作为隐藏站：A 可能会听，什么也听不到并尝试发送给 B，而 C 已经在向 B 发送。MACA 确实有帮助。 在 MACA 中，A 和 C 将首先向 B 发送 RTS 数据包以启动它们的数据传输。 C 可以听到 A 的传输，如果 A 先发送，C 会知道保持安静。 如果 C 先发送，而 A 听不到 C，A 可以听到 B 对 C 的 sCTS 响应，并且知道在有时间完成之前不要尝试发送。这可以防止 A 中断 C->B 传输。

1. Consider the extended LAN connected using bridges B1 and B2in Fig. 4-41(b). Suppose the hash tables in the two bridges are empty. List all ports on which a packet will be forwarded for the following sequence of data transmissions: (a) A sends a packet to C. (b) E sends a packet to F. (c) F sends a packet to E. (d) G sends a packet to E. (e) D sends a packet to A. (f) B sends a packet to F.

(a) B1 will forward this packet on ports 2, 3, and 4. B2 will forward it on 1, 2 and 3. (b) B2 will forward this packet on ports 1, 3, and 4. B1 will forward it on 1, 2 and 3. (c) B2 will not forward this packet on any of its ports, and B1 will not see it. 因为已经记录了. E ->F (d) B2 will forward this packet on port 2. B1 will not see it. 知道 F 在port2 (e) B2 will forward this packet on port 4 and B1 will forward it on port 1. 知道A在port4, B1也知道在port1 因为a)的时候发了, (f) B1 will forward this packet on ports 1, 3 and 4. B2 will forward it on port 2. B1不知道 F在哪里, 只知道 E在port4.

答案: 就是上面
