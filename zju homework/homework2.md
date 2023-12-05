# homework2

1111111111111111200\. Fast” Ethernet operates 10x faster (100Mbps) than regular ethernet. Explain why the following changes were made. (a) Encoding changed to 4B/5B. (b) CAT-5 cable has more twists.

4B/5B编码其实就是用5bit的二进制码来代表4bit二进制码。此编码的效率是80%，比Manchester码高。目的就是让码流产生足够多的跳变。

最新的网络网线由紧密双绞的铜线制成 - 每根网线4-10对。通过这些电线传输数据，但网线长度和干扰可能妨碍数据传输。更紧密编织的线对可以解决这两个问题，或至少提高可靠性，因此旧版和新版网线版本之间的最大差异之一通常归结为布线。

答案:(a) 曼彻斯特编码的效率仅为 50%，每比特需要 2 次信号变化。4B/5B 的效率为 80%，从而实现更好的线路利用率 (c) 这减少了电缆上的干扰（噪声），增加了电缆的有效带宽

1. If a binary signal is sent over a 3-kHz channel whose signal-to noise radio is 20dB, what is the maximum achievable data rate?

香浓定理, 知道 带宽, 信噪比, 就可以得到最大信息传输速率.

20 = 10 log10(S/N) => S/N = 100

X = H Log2 (1 + S/N) bps = 3000 Log2 (1 + 100) bps =19974.63bps

没有考虑 最高传输速度!

答案:

20 dB 的信噪比意味着 S/N=100。 由于 log 2 101 约为 6.658，因此香农极限约为 19.975 kbps。 奈奎斯特限制为 6 kbps。 因此，瓶颈是奈奎斯特极限，最大信道容量为 6 kbps。

对于一个带宽为W（Hz）的无噪声低通信道，最高的码元传输速率Bmax: 2W(Baud)，即每赫兹带宽的理想低通信道的最高码元传输速率是每秒2个码元。

1. What are the advantages of fiber optics over copper as a transmission medium? Is there any downside of using fiber optics over copper?

带宽大Fiber optic cables provide more bandwidth for carrying more data than copper cables of the same diameter. A number of fiber cables can be made cheaper than copper wire.

损失小 Due to less signal degradation, the loss of signals in fiber is less compared to copper wires. The loss of signals in copper is more than fiber optic.

光更快 Copper uses electrons for data transmission, while fiber uses photons. Light is faster than electrical pulses, so fiber can transmit more bits of data per second and offer higher bandwidth.

缺点

功率低, 光纤更脆弱. Low Power—Light emitting sources are limited to low power. Although high power emitters are available to improve power supply, it would add extra cost. Fragility—Optical fiber is rather fragile and more vulnerable to damage compared to copper wires. You’d better not to twist or bend fiber optic cables.

光纤与铜线相比具有许多优势。 它可以处理比铜线高得多的带宽。 不受电涌、电磁干扰、停电或空气中腐蚀性化学物质的影响。 它不会漏光，而且很难敲击。最后，它又薄又轻，从而大大降低了安装成本。 使用光纤而不是铜有一些缺点。 首先，它很容易因过度弯曲而损坏。 其次，光通信是单向的，因此双向通信需要两根光纤或一根光纤上的两个频段。 最后，光纤接口比电接口成本更高。

1. Is the Nyquist theorem true for high-quality single-mode optical fiber or only for copper wire?

都成立 **Nyquist** **theorem** is **valid** for both **fibre** **optics** and **copper** **wires** this is because the **Niquist** **theorem** is purely depend upon the mathematic function and has not any concern with the transmission media for communication.

答案: 奈奎斯特定理是数学的属性，与技术无关。 它表示，如果您有一个函数，其傅立叶频谱不包含任何高于 f 的正弦或余弦，则通过以 2f 的频率对该函数进行采样，您可以捕获所有信息。 因此，奈奎斯特定理适用于所有媒体。

1. What is the minimum bandwidth needed to achieve a data rate of B bits/sec if the signal is transmitted using NRZ and Manchester encoding? Explain your answer.

采用NRZ双极性不归零码，第一零点带宽等于码元速率，带宽 = B

Manchester encoding has worst-case two transitions per bit-time (under the same assumption as NRZ). 2个 symbols represent 1 bit. data rate = ½ \* symbol rate 所以 最小带宽为 2B

答案: NRZ，数据速率=信号速率，所以信号速率为B bps。 所以，最小带宽需要达到 B bits/sec 数据速率是 B/2 Hz。在曼彻斯特编码中，数据速率=1/2 \* 信号速率，所以信号速率是 2B bps。所以，最小带宽需要达到 B 位/秒数据速率为 B Hz。 data rate 不是带宽

最小带宽 是 信号速率的一半.

1. Is an oil pipeline a simplex system, a half-duplex system, a fullduplex system, or none of the above? What about a river or a walkie-talkie-style communication?

石油管道是 half-duplex 半双工, 同时只有一边.

河流从高往低是单工 simplex 或者有的河流可能改变流向那就是半双工.

对讲机是全双工. fullduplex

答案: 石油管道是一个半双工系统，因为石油可以向任一方向流动，但不能同时向两个方向流动。 河流是单工系统，而对讲机式通信是半双工系统。

1. A modem constellation diagram similar to Fig. 2-23 has data points at the following coordinates: (1,1), (1,-1), (-1,1), (-1,-1). How many bps can a modem with these parameters achieve at 1200 symbols/sec?

QPSK encodes 2 bits/symbol.

比特率=1200\*log2 (4） = 2400 bps

答案: 每个符号有 4 个合法值，因此比特率是符号率的两倍（log2 (4)）。在 1200 个符号时，数据率为 2400 bps。

1. What is the difference, if any, between the demodulator part of a modem and the coder part of codec? (After all, both convert analog signals to digital ones.

有，编码器接受任意的相位模拟信号，并从它产生数字信号。而解调器只接受调制了的正弦波，产生数字信号。

答案: 调制解调器的解调器部分接受调制的正弦波并生成数字信号，而编解码器的编码器部分接受任意模拟信号并从中生成数字信号。

1. What is the available user bandwidth in an OC-12c connection?

OC-12C 有`12*90 = 1080列，其中12*3=36列`用作线路和其他部分开销。剩下1044，其中SPE列用于通道开销，剩下1043列给用户数据，每列有9bytes

有`1043*9*8bits =75096`用户数据位，帧速率为8000frame/sec ，所以用户速率为8000\*75096=600.768Mbps。

答案: STS-12c 帧有十二个 STS-1 帧，每个 STS-1 帧有 3 列开销。 因此，STS-12c 有效载荷 = 90 \* 12 \* 9 –3 \* 12 \* 9 = 9396 字节。 我们减去 1 列 POH，所以最后我们有： 9396 –1\*9 = 每 125 μs 发送 9387 个字节。 这转化为用户带宽：600.768 Mbps

1. Suppose that A, B, and C are simultaneously transmitting 0 bits, using a CDMA system with the chip sequences of Fig. 2-28(a). What is the resulting chip sequence?

**S= A非+B非+C非 = （+3 +1 +1 -1 -3 -1 -1 +1）**

发送0是发送补码.

答案: 就是上面.
