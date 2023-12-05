homework 5 network

• 1. Give two example computer applications for which  connection-oriented service is appropriate. Now give two examples for which connectionless service is best. 

connection orient :  file transfer, remote login. A path from the source router to the destination router  must be established before any data packets can be sent.

connectionless:  远程数据库访问, 电子转账是connectionless.  No advance setup is needed

答案：文件传输、远程登录、视频点播需要面向连接的服务。 另一方面，信用卡验证和其他销售点终端、电子资金转账和多种形式的远程数据库访问本质上是无连接的，查询以一种方式进行，回复以另一种方式返回。

• 2. Consider the network of Fig. 5-12(a). Distance vector routing  is used, and the following vectors have just come in to router C:  from B: (5, 0, 8, 12, 6, 2); from D: (16, 12, 6, 0, 9, 10); and from  E: (7, 6, 3, 9, 0, 4). The cost of the links from C to B, D, and E,  are 6, 3, and 5, respectively. What is C’s new routing table? Give  both the outgoing line to use and the cost. 

距离矢量路由算法  DV 算法

cost 可以知道 d.BC = 6   d.CD  = 3 , d.CE = 5 

 d.AB+d.BC = 5 + 6 = 11 

d.AD + d.DC   =16 +3 = 19

d.AE + d.EC = 7 +5 = 12

所以取最小 得到d.AC = 11  

s.AC =  B  

d.BC = 6   s.BC = C

| destination | delay | next station |
| ----------- | ----- | ------------ |
| A           | 11    | B            |
| B           | 6     | C            |
| C           | 0     | -            |
| D           | 3     | C            |
| E           | 5     | C            |
| F           | 8     | B            |

Solution: 

a) Going via B gives (11, 6, 14, 18, 12, 8).

b) Going via D gives (19, 15, 9, 3, 9, 10).

c) Going via E gives (12, 11, 8, 14, 5, 9).

d)Taking the minimum for each destination except C gives (11, 6, 0,3, 5, 8).

e) The outgoing lines are (B, B,- , D, E, B).



• 3. Please give an example in which the poisoned reverse  technique cannot prevent the count-to-infinity problem and  explain why. 

count-to-infinity 原因是  ABC  B 不知道  A 到C 经过B , 所以C挂了的时候B 会认为到C 的距离为 1+ 2 =3.

Poison Reverse的理念是当Router A发现Network X的中断後, 在下次做routing update时不会忽略X, 反而会把X包含到routing update当中, 但将其跳跃数Hop count变更为Maximum+1(RIP为15+1), 因为Hop count超过了Maximum, 所以Router B收到更新时会立刻知道Network X为Inaccessible, 而无需等待180秒, 这样便会大大地加快网络收敛的速度。

![image-20211124195010143](C:\Users\12638\AppData\Roaming\Typora\typora-user-images\image-20211124195010143.png)

t1的时候, xy距离从4变成60,  Y就更新为到x为无穷大.  

t2的时候, w接收到y的消息, w 到x的距离变成无穷大. 

t3的时候 z 接收到w的消息,  z到 x 的距离变成无穷大, 

t4的时候  y接收到z的消息, y到x的距离变成无穷大.

然后不断循环.

• 4. A router has just received the following new IP addresses:  57.6.96.0/21, 57.6.104.0/21, 57.6.112.0/21, and  57.6.120.0/21. If all of them use the same outgoing line, can  they be aggregated? If so, to what? If not, why not? 

可以进行路由聚合。4个地址的前16位都相同，点分十进制的第三部分对应的2进制分别为：01100000，01101000，01110000，01111000，最长前缀为前三位 011，即 96，因此可以被聚合为 57.6.96.0/19  对的

• 5. The set of IP addresses from 29.18.0.0 to 29.18.128.255  has been aggregated to 29.18.0.0/17. However, there is a  gap of 1024 unassigned addresses from 29.18.60.0 to  29.18.63.255 that are now suddenly assigned to a host using  a different outgoing line. Is it now necessary to split up the  aggregate address into its constituent blocks, add the new  block to the table, and then see if any reaggregation is  possible? If not, what can be done instead? 

Classless Inter-Domain Routing，CIDR可以将路由集中起来，在路由表中更灵活地定义地址。它不区分 A 类、B 类、C 类地址，而是使用 CIDR 前缀的值指定地址中作为网络 ID 的位数。 最长地址匹配

答：不需要分块重新聚合。路由表里只需要添加一个新的表项：29.18.60.0/22。如果收到的 IP 包在查表选路时同时匹配 29.18.0.0/17 和 29.18.60.0./22，则采用最长地址匹配，转发到地址前缀最长的子网，即 29.18.60.0/22。

• 6. A router has the following (CIDR) entries in its routing table: Address/mask Next hop 135.46.56.0/22 Interface 0 135.46.60.0/22 Interface 1 192.53.40.0/23 Router 1 default Router 2 For each of the following IP addresses, what does the router do if a packet with that address arrives?(a) 135.46.63.10 (b) 135.46.57.14 (c) 135.46.52.2 (d) 192.53.40.7 (e) 192.53.56.7 

利用子网掩码获得目的网络地址，查路由表确定如何转发

下面就是答案

答：（a）将地址分别与22位掩码相与得到：135.46.60.0，存在表项，则a将转发到接口1；
（b）将地址分别与22位掩码相与得到：135.46.56.0，存在表项，则b将转发到接口0；
（c）将地址分别与22位掩码相与得到：135.46.52.0，不存在这样的表项，则c将执行默认路由表，转发到路由器2；
（d）将地址分别与23位掩码相与得到：192.53.40.0，存在表项，则d将转发到路由器1；
（e）将地址分别与23位掩码相与得到：192.53.56.0，不存在这样的表项，则c将执行默认路由表，转发到路由器2。

引入IPv6协议后，ARP协议是不是必须要改？ 如果是，这些变化是概念性的还是技术性的？

解决方案：概念上没有变化。 从技术上讲，现在请求的 IP 地址更大，因此需要更大的字段

• 8. Consider the user of differentiated services with expedited forwarding. Is there a guarantee that expedited packets experience a shorter delay than regular packets?  Why or why not? 

No guarantee.If too many packets are expedited, their channel may have even worse performance that the regular channel.如果加速的数据包太多，他们的通道可能会比常规的性能更差. 

• 9. A token bucket scheme is used for traffic shaping. A new  token is put into the bucket every 5 μsec. Each token is  good for one short packet, which contains 48 bytes of data.  What is the maximum sustainable data rate?

With a token every 5 μsec, 200,000 cells/sec can be sent. Each cell holds 48 data bytes or 384 bits.

200000*48/1000000=9.6MB/s   对的

