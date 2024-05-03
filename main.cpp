#define BOOST_TEST_MODULE MyTest
#include <cstring>
#include <spdlog/common.h>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include "include/webserver/webserver.h"


using namespace std;

// THREAD_POOL_ACTIVE

// ThreadPool thread;
// // Epoll server(9002, true,ThreadPool()); // 设置端口复用
// Epoll server(9002, true, true); // 设置端口复用
// std::string httpResponse =
//     "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
// httpResponse += "Hello, this is a simple HTTP response!\r\n";

// spdlog::info("service begin in port 9002");
// server.startWithThreads([httpResponse](char *buf) -> char * {
//   char *resp;
//   return httpResponse.c_str();
// });
// char *response;
// strcpy(response, httpResponse.c_str());

// BOOST_AUTO_TEST_CASE(commonTest1) {
//   ifstream resource_read("../resource/index.html");
//   string line;
//   string msg;

//   if (resource_read.is_open()) {
//     while (getline(resource_read, line)) {
//       msg += (line + "\n");
//     }
//     resource_read.close();
//   } else {
//     cout << "failed to open file" << endl;
//   }
//   cout << msg << endl;
// }

// BOOST_AUTO_TEST_CASE(httpParse1) {
//   stringstream ss("hello world ! ");
//   string str1, str2, str3;
//   ss >> str1 >> str2 >> str3;
//   cout << "1:" << str1 << "2:" << str2 << "3:" << str3 << endl;
//   string line;
//   stringstream ss2("age:200");
//   string name, value;
//   getline(ss2, name, ':');
//   getline(ss2, value);
//   cout << "key:" << name << " v:" << value << endl;
// }

// BOOST_AUTO_TEST_CASE(httpParse2) {
//   // TcpSocket tcp = TcpSocket(8080, true);
//   // tcp.httpHandle();
//
//   HttpRequest req(request);
//   cout << req.getMethod() << endl;
//   cout << req.getPath() << endl;
//   cout << req.getVersion() << endl;
//   for (auto &line : req.getHeaders()) {
//     cout << line.first << ":" << line.second << endl;
//   }
//   cout << req.getBody() << endl;
// }

string request("GET / HTTP/1.1\r\nHost: 127.0.0.1:8080\r\nUser-Agent: "
               "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:125.0) "
               "Gecko/20100101 Firefox/125.l0\r\nAccept: "
               "text/html,application/xhtml+xml,application/xml;q=0.9,image/"
               "avif,image/webp,*/*;q=0.8\r\nAccept-Language: "
               "zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0."
               "2\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: "
               "keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nSec-Fetch-Dest: "
               "document\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-Site: "
               "none\r\nSec-Fetch-User: ?1\r\n\r\n");

// BOOST_AUTO_TEST_CASE(httphandle) {
//   HttpRequest req(request);
//   httpHandle(req);
//   // TcpSocket app(8080, true);
//   // app.httpHandleTest();
// }

// BOOST_AUTO_TEST_CASE(fileread) {
//   auto res = readFileToString("../resource/index.html");
//   cout << res << endl;
// }

// BOOST_AUTO_TEST_CASE(stringCopy) {
//   char buf[10] = "123456789";
//   string res(buf);
//   cout<<res<<endl;
// }

// BOOST_AUTO_TEST_CASE(listen_http) {
//   TcpSocket socket(8080, true);
//   socket.httpHandle();
// }

// BOOST_AUTO_TEST_CASE(netFrameTest) {
//   netFrame::Net net(8081);
// }
void HandleHome(int clientSocket) {
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHome Page";
    send(clientSocket, response.c_str(), response.size(), 0);
}

void HandleAbout(int clientSocket) {
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 14\r\n\r\nAbout Page";
    send(clientSocket, response.c_str(), response.size(), 0);
}

BOOST_AUTO_TEST_CASE(netFrameTest) {
  Router router;
  router.Get("/home", [](int clientSocket) {
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHome Page";
    send(clientSocket, response.c_str(), response.size(), 0);
  });
  router.Get("/index",HandleHome);

  WebServer server(8081);
  server.Start(router);
}
