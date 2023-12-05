# homework3

1. The following character encoding is used in a data link protocol: A: 01000111 B: 11100011 FLAG: 01111110 ESC: 11100000 Show the bit sequence transmitted(in binary) for the four-character frame A B ESC FLAG when each of the following framing methods is used:

(a) Byte count.

00000100 01000111 11100011 11100000 01111110(4 A B ESC FLAG) 有4个字节就写4

(b) Flag bytes with byte stuffing.

Flag bytes with byte stuffing：让每个帧以特殊字节开始和结束。两个连续的标记字节flag byte表示一个帧的结束和下一个帧的开始。因此，如果接收器失去同步，它可以搜索两个标记字节来找到当前帧的结束和下一帧的开始。 当这个标记字节出现在帧中，用一个转义字符escape byte (ESC) 插入到标记字节前。接收者收到后，又将这个转义字符去掉，这个过程叫byte stuffing字节填充

01111110 01000111 11100011 11100000 11100000 11100000 01111110 01111110(FLAG A B ESC ESC ESC FLAG FLAG)

(c) Starting and ending flag bytes with bit stuffing.

01111110   01000111  110100011  111000000  0111110(零比特填充)10  01111110 FLAG A B ESC FLAG FLAG

答案: (a) 00000101 01000111 11100011 11100000 01111110

(b) 01111110 01000111 11100011 11100000 11100000 11100000 01111110 01111110

(c) 01111110 01000111 110100011 111000000 011111010 01111110

1. Hamming code is an effective way for error correcting. Show that the # of check bits(i.e. r) in the Hamming codes described in the textbook(e.g., Fig.3-6) (almost) achieves the low bound of Eq (3-1).

 m:信息位      r:检验位    m+r+1<=2^r

m+r =11

12<= 2^r r= 4

答案: 假设校验比特数为r。根据汉明码，数据比特数m在2^(r-1)+1-r比特和2^r-r-1比特之间。所以2^(r- 1)+2\<r+m+1<2^r 。 汉明码中校验位的数量（几乎）达到了Eq(3-1)的下界。在图3.6中，4+7+1<2^4，所以4位就足够了。

1. Suppose you have the following 12-bit message: 010100111111 (a) Numbering bits from right to left (i.e. least-significant bit on the right), insert check bits according to to Hamming’s 1-bit error correction system. Indicate which bits are check bits and which are message bits. (b) Hamming’s scheme only corrects 1-bit errors. Since it’ s a distance 3 code, it could also be used to detect 2-bit errors. Describe a 3-bit error (3 \*1-bit errors) in the above codeword affecting only message bits (not check bits) that would be undetected (and of course uncorrected). Be sure to describe how and why the algorithm fails.

a) check bits will be insert in the 1 2 4 8 16. message bits are 3 5 6 7 9 10 11 12 13 14 15 17.  这是对的

b)to detect 3-bit error,the hamming distance need to be 4.to correct 3-bit error，the hamming distance need to be 2\*3+1 = 7. So the algorithm fails.

答案: 首先，我们需要多少个校验位：为了满足 m+r+1<=2^r ，当 m=12 时，我们需要 r=5 个校验位.

（b）In order for the error to be undetected the check bits must remain valid。 因此，翻转的 3 位必须使它们的bit pisition (mod-2) 之和为 0。有许多这样的三元组； 例如，翻转第 3、5 和 6 位

1. Consider an original frame 110111011011. The generator polynomial x4+x+1, show the converted frame after appending the CRC.

G(x) = 10011

位宽为4 , 就是 多项式对应的二进制数的位数减1,填上4个0 就是 110111011011 0000

异或运算, 得到 1101110110110101

答案:先在原帧上加4个零，然后我们得到1101110110110000

Generator是10011，用模2减法得到的答案是110110110110101

1. A 3000-km-long T1 trunk (with data rate 1.536Mbps) is used to transmit 64-byte frames. How many bits should the sequence numbers be for protocol 5 and protocol 6 respectively? The propagation speed is 6usec/km.

transmit 64-byte frames need 64bytes/ 1.536Mbps = 0.3ms. 

propagation time 3000\*6 = 18000us = 18ms. 

Start ->Arrive：18+0.3=18.3ms  

Ack： 18ms  总时间 18+18.3=36.3ms 

36.3/0.3=121 frames 可以填满

 7-bit sequence numbers are needed.

答案: 高效运行，序列空间（实际上，发送方的窗口大小）必须足够大，以允许发送方继续发送，直到收到第一个 ack。 传播是18ms。 在 T1 速度下，即 1.536Mbps（不包括 1 个头位），一个 64 字节的帧需要 0.300 毫秒。 因此，第一帧在传输开始后 18.3ms 完全到达。 ack 还需要 18 毫秒才能返回，再加上一小段时间（可以忽略不计）让 ack 完全到达。 总的来说，这个时间是 36.3 毫秒。 一帧需要0.3ms，所以需要121帧来填充管道。对于协议5，需要7位序列号。对于协议6，需要8位序列号。

1. Frames of 1000 bits are sent over a 1-Mbps channel using a geostationary satellite whose propagation time from the earth is 270 msec. Acknowledgements are always piggybacked onto data frames. The headers are very short. Three-bit sequence numbers are used. What is the maximum achievable channel utilization for (a) Stop-and-wait? (b) Protocol 5? (c) Protocol 6?

发送 1000\*1mbps=1s. 

start : t=0ms 

the first frame has been fully transmitted : t = 1 ms, the first frame has fully arrived : t = 271 ms 

the first frame's acknowledgement has been fully sent : t = 272 ms

acknowledgement has fully arrived : t = 542 ms So the cycle is 542 ms.   

(a) k = 1, efficiency = 1/542 = 0.18%. 

(b) Send Window Size <= MAX\_SEQ (0…N) maxseq = 2^3 -1 = 7

 k = 7, efficiency = 7/542 = 1.29%.

 (c) Send Window Size <= (MAX\_SEQ+1)/2

 k = 4, efficiency = 4/542 = 0.74%

答案:

让 t = 0 表示传输的开始。 在 t = 1 毫秒时，第一帧已经完全传输。 在 t = 271 毫秒时，第一帧已经完全到达。 在 t = 272 毫秒时，确认第一个帧的帧已完全发送。 在 t = 542 毫秒时，确认承载帧已经完全到达。 因此，周期为 542 毫秒。 在 542 毫秒内总共发送 k 帧，效率为 k/542。 因此，对于（a）k = 1，效率 = 1/542 = 0.18%。（b）k = 7，效率 = 7/542 = 1.29%。（c）k = 4，效率 = 4/542 = 0.74% .

7.Compute the fraction of the useful data bandwidth for protocol 6 on a heavily loaded 50kbps

satellite channel with data frames consisting of 40 header and 3960 data bits. Assume that the

signal propagation time from the earth to the satellite is 270 msec. ACK frames never occur.

NAK frames are 40 bits. The error rate for data frames is 1%, and the error rate for NAK frames

is negligible. The sequence numbers are 3 bits.

Solution:

The sequence number are 3 bits, then the windows size is 4

4000 bits frame takes 80ms and 40 bits NAK takes 0.8ms.

The utilization is 4_80/(270_2+80+0.8)=51.5%

The number of retransmissions per frame is about 0.01. Each good frame wastes 40 header bits, plus 1% of 4000 bits (retransmission), plus a 40bit Nak once every 100 frames. The total overhead is 80.4 bits per 3960 data bits, so the wasted on

overhead is 80.4/(3960+80.4=1.99%

So the fraction of the useful data bandwidth is 51.5%\*(1-1.99%)=50.5%
