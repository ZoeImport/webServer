# webServer

  基于socket套接字的多线程web服务器  

## v0.1

 实现线程池库
 ThreadPool.h  
 实现基本的线程池库，使用参数拓展包，尾返回类型推导，以及基本的函数包装，STL容器使用  
 使用condition_variable 以及unique_lock  

## v0.2

 实现基于套接字的基础网络echo服务(开放本地端口9001)  
 实现单线程的基础echo通信  
 实现accpet阻塞前的基础包装  

## v0.3

  保持单线程设计  
  实现accpet阻塞后的函数封装  
  对于accpet_connect提供接口，该接口可以是Lambda表达式等一系列可调用对象，能够利用可调用对象进行数据处理，实现基础的echo  
  
## v0.4

  引入spdlog库进行日志控制  
  引入io多路复用设计(epoll)  
  修改基础设计server库为TcpSocket库  
  新增epoll设计库  
  新增TcpSocket成员变量:buf buffersize 修改构造函数默认buffersize为1024  
  修改server_func为ConnectCallback  
  
## v0.45  
  
  修改项目目录结构，新增include目录，修改源文件层级关系  

## v0.5

  TheadPool库:  
    修改ThreadPool库enQueue函数,修改返回值为funture对象  
    增加packaged_task包装器进行包装  
  Epoll库:  
    结合ThreadPool实现io多路复用+线程池设计:为建立新连接和接收传递数据分别使用子线程  
    新增threadPoolAvtive变量控制Epoll对线程池使用的开关  
    新增智能指针(shared_ptr)控制Epoll私有线程池变量pool_ptr  
    <!-- 重载start函数以增加线程池的设计   -->
    新增epoll_recv wait epoll_deal私有方法实现Epoll创建后的模块分离  
  tools库:  
    新增wrap函数用于将函数转成一个可被使用的可调用对象  
  
## v0.55

  ThreadPool库:  
    修改enQueue函数使用decltype代替result_type  
  Epoll库:  
    重载start函数,代替startWithThreads使用  
    修改构造函数参数列表  
  宏增加:
    新增THREAD_POOL_ACTIVE宏,在预编译阶段进行代码压缩

## v0.60

  http请求解析以及http响应功能
  router增加路由解析实现路由GET,POST方法
  tool新增http request body模糊去除(模糊原因待发现)

## v0.7

  mariadb:新增数据库模块集成后端数据库连接(mariadb-connector-c++)
  
  