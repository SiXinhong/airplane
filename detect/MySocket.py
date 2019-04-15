# -*- coding:utf-8 -*-
import socket
from MyDetection import *
t = MyDetection()
def setDetection():
    t.setDetection()
    return "Detection"
def detectionImage(imageName):
    ret = t.detectionImage(imageName)
    return ret
ip_port = ('127.0.0.1', 9999)
sk = socket.socket()            # 创建套接字
sk.bind(ip_port)                # 绑定服务地址
sk.listen(5)                    # 监听连接请求
print('启动socket服务，等待客户端连接...')
conn, address = sk.accept()     # 等待连接，此处自动阻塞
while True:
    client_data = conn.recv(1024).decode()      # 接收信息
    print(client_data)
    data = ""
    if client_data == "exit":       # 判断是否退出连接
        exit("通信结束")
    elif client_data == "setDetection":
        data = setDetection()
    elif client_data.startswith("setDetection"):
        data = setDetection()
        idx = client_data.find(".jpg")
        data = detectionImage(client_data[12:idx+4])
    else :
        idx = client_data.find(".jpg")
        data = detectionImage(client_data[:idx+4])
    conn.send(data.encode())    # 回馈信息给客户端
conn.close()    # 关闭连接