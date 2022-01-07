Homework 1. Can a machine with a single DNS name have multiple IP  addresses? How could this occur? 

可以的。 如果一台机器有两个以太网卡，它可以在两个不同的网络上，如果是这样，它需要两个 IP 地址。 DNS 不 知道并且实际上无法区分多个 IP 地址是否用于不同的机器。 

2 A binary file is 4560 bytes long. How long will it be if  encoded using base64 encoding , with a CR+LF pair inserted  after every 110 bytes sent and at the end? 

base 64 编码会将消息分成 1024 个单元，每个单元 3 个字节。 每一个都将被编码为 4 个字节，总共 4096 个字节。 如果然后将它们分解为 80 个字节的行，将需要 52 个这样的行，添加 52 个 CR 和 52 个 LF。 总长度将为 4200 字节。

3 When Web pages are sent out, they are prefixed by MIME  headers. Why? 

 The browser has to be able to know whether the page is text, audio, video, or something else

**媒体类型**（通常称为 **Multipurpose Internet Mail Extensions** 或 **MIME** 类型 ）是一种标准，用来表示文档、文件或字节流的性质和格式。浏览器通常使用MIME类型（而不是文件扩展名）来确定如何处理URL，因此Web服务器在响应头中添加正确的MIME类型非常重要。如果配置不正确，浏览器可能会曲解文件内容，网站将无法正常工作，并且下载的文件也会被错误处理。

4 How do you make an image clickable in HTML? Give an  example.

` <img> 标签以及带有 href 属性的 <a> 标签。  <img> 标签用于在网页中使用图像，<a> 标签用于添加链接。 在图像标签 src 属性下，添加图像的 URL。 还要添加高度和宽度。`

```html
<!DOCTYPE html>
<html>
   <head>
      <title>HTML Image as link</title>
   </head>
   <body>
      The following image works as a link:<br>
      <a href="https://www.qries.com/">
         <img alt="Qries" src="https://www.qries.com/images/banner_logo.png"
         width=150" height="70">
      </a>
   </body>
</html>
```
