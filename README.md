# webServer

  基于socket套接字的多线程web服务器  

## 线程池

 实现基本的线程池库，使用参数拓展包，尾返回类型推导，以及基本的函数包装，STL容器使用  
  
## 日志控制  

  引入spdlog库进行日志控制  
  引入io多路复用设计(epoll)  

##   http

  http请求解析以及http响应功能
  router路由解析实现路由GET,POST方法

## 数据库

  mariadb:新增数据库模块集成后端数据库连接(mariadb-connector-c++)
    对数据库连接进行封装,新增Update Insert Select Delete,Describe对基础操作进行封装(增删改查)
    对查询结果进行封装Result，title(),result()可对结果进行格式化输出
    
  
