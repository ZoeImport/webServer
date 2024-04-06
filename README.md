# webServer
a webServer that besed on socket 
  基于socket套接字的多线程web服务器

# v0.1
 实现线程池库 
ThreadPool.h
实现基本的线程池库，使用参数拓展包，尾返回类型推导，以及基本的函数包装，STL容器使用
使用condition_variable 以及unique_lock


# v0.2
 实现基于套接字的基础网络echo服务(开放本地端口9001)
 实现单线程的基础echo通信
 实现accpet阻塞前的基础包装
 
# v0.3
  保持单线程设计
  实现accpet阻塞后的函数封装
  对于accpet_connect提供接口，该接口可以是Lambda表达式等一系列可调用对象，能够利用可调用对象进行数据处理，实现基础的echo
  
# v0.4
  引入spdlog库进行日志控制
  引入io多路复用设计(epoll)
  修改基础设计server库为TcpSocket库
  新增epoll设计库
  新增TcpSocket成员变量:buf buffersize 修改构造函数默认buffersize为1024
  修改server_func为ConnectCallback
  
