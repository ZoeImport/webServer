#define BOOST_TEST_MODULE TEST_CPP
#include "include/database/connector.h"
#include "include/webserver/webserver.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <iostream>

using namespace db;
using namespace std;
using namespace tool;

// void printMap(const std::map<std::string, int> &m) {
//   for (const auto &[key, value] : m) {
//     std::cout << key << ": " << value << std::endl;
//   }
// }
// BOOST_AUTO_TEST_CASE(map_move) {
//   std::map<std::string, int> originalMap = {
//       {"Alice", 30}, {"Bob", 25}, {"Carol", 28}};

//   std::cout << "Original Map:" << std::endl;
//   printMap(originalMap);

//   // 使用std::move将originalMap转换为右值并移动资源到movedMap
//   std::map<std::string, int> movedMap = std::move(originalMap);

//   std::cout << "Moved Map:" << std::endl;
//   printMap(movedMap);

//   std::cout << "Original Map after move:" << std::endl;
//   printMap(originalMap); // originalMap现在应该为空
// }

BOOST_AUTO_TEST_CASE(update_db) {
  string url{"jdbc:mariadb://localhost:3306/Cpp"};

  Connector conn(url, "zoe", "123456");

  Statement state(conn);

  // state.Update("user",{{"account","Jack"}},"id=001");
  // state.Delete("user",{{"account","'nod'"},{"id","'2'"}},"||");

  // auto descirbe{state.Describe("user", "Field", "Type", "Null", "Key",
  //                              "Default", "Extra")};
  // for (auto &mem : descirbe.get_list_result_map()) {
  //   for (auto &x : mem) {
  //     cout << std::setw(14) << std::left << x.second;
  //   }
  //   cout << endl;
  // }

  cout << endl;
  auto res{state.Select("user", "id", "account", "password", "create_date")};
  res.title().result();
  // res.std_format_result(15);
}

// BOOST_AUTO_TEST_CASE(tool_1){
//   for (auto &s :strs_to_lists("hello","nihao","back")) {
//     cout<<s<<" ";
//   }
//   cout<<endl;

// }

// template <typename... Args> string addString(char sepeerator, Args... args) {
//   // if ((std::is_same_v<string, Args> && ...)) {
//   string res;
//   vector<string> arr{args...};
//   for (auto &x : arr) {
//     res += (x + sepeerator);
//   }
//   if (res.back() == sepeerator) {
//     res.pop_back();
//     return res;
//   } else {
//     throw exception{};
//   }
//   // }
// }

// BOOST_AUTO_TEST_CASE(insertTEST) {
//   sql::SQLString url{"jdbc:mariadb://localhost:3306/Cpp"};

//   Connector conn(url, "zoe", "123456");

//   Statement state(conn);

//   cout<<state.insert("user",{{"id","008"},{"account","JJ"},{"password","666"},{"create_date","01-01-11"}});
//   cout<<state.insert("user",{{"id","007"},{"account","JJ"},{"password","666"},{"create_date","01-01-11"}});
//   cout<<endl;

// }

// TODO:select with where
// TODO:update with where
// TODO:delete with where

// BOOST_AUTO_TEST_CASE(selectTEST) {

//   string url{"jdbc:mariadb://localhost:3306/Cpp"};

//   Connector conn(url, "zoe", "123456");

//   Statement state(conn);

// }

// template<typename  ...Args>
// auto captureArgs(Args ... args){
//   return (args + ...);

// // }
// //
// // template <typename ... Ts>
// // auto sum(Ts ... ts)
// // {
// //     return (ts + ...);
// // }

// template <typename ... Ts>
// std::string sum(Ts ... ts)
// {
//     std::stringstream ss;
//     (ss << ... << ts);
//     return ss.str();
// }

// // template <typename ... Ts>
// // auto stringAdd(Ts ... ts)
// // {
// //     vectorTs> vec;
// //     return (ts + ... );
// // }
// #include <iostream>
// #include <string>

// // 递归终止条件
// std::string concatenate() {
//     return "";
// }

// // 递归调用，将第一个参数转换为字符串，然后与其他参数连接
// template<typename T, typename... Args>
// std::string concatenate(const T& first, const Args&... args) {
//     return first + concatenate(args...);
// }

// // 递归调用，处理字符串类型的参数
// std::string concatenate(const std::string& first) {
//     return first;
// }

// // // 主函数
// // template<typename... Args>
// // std::string joinStrings(const Args&... args) {
// //     return concatenate(args...);
// // }

// template<typename T>
// string to_string(const T&t){
//   if constexpr (std::is_convertible_v<T,string>){
//     return t;
//   }else {
//     return std::to_string(t);
//   }
// }

// template<typename ...Args>
// auto joinStrings(const Args ...args){
//   string result;
//   (result+=...+=to_string(args));
//   return result;
// }

// template<typename... Args>
// std::vector<std::any> storeArgsInVector(const Args&... args) {
//     return {std::any(args)...}; // 使用参数包展开来初始化容器
// }
// // std::string concate(std::string ...args) {
// //     std::string result;
// //     (result += ... += args);
// //     return result;
// // }
// template<typename  T>
// auto vi=[](const T&t){
//   cout<<t<<",";
// };
// BOOST_AUTO_TEST_CASE(args){
// }

// BOOST_AUTO_TEST_CASE(db_test) {

//   // sql::Driver *driver = sql::mariadb::get_driver_instance();

//   // sql::Properties properties{{"user", "zoe"}, {"password", "123456"}};
//   // unique_ptr<sql::Connection> conn{driver->connect(url, properties)};
//   sql::SQLString url{"jdbc:mariadb://localhost:3306/Cpp"};

//   Connector conn(url, "zoe", "password");

//   shared_ptr<sql::Statement> stmnt{conn.getConnectPtr()->createStatement()};

//   Statement state(conn);
//   // state.selectAll("user","name","type","len");

//   // unique_ptr<sql::ResultSet> res{stmnt->executeQuery("describe user")};

//   // while (res->next()) {
//   //   cout<<""<<res->getString("Field")<<":"<<res->getString("Type")<<endl;
//   // }

//   // sql::ResultSetMetaData *metaData = res->getMetaData();
//   // auto count = metaData->getColumnCount();
//   // cout << count;

//   // for (auto index = 0; index < count; ++index) {
//   //   cout << metaData->getColumnType(index) << endl;
//   // }

//   // metaData->getColumnCount()
// }

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

// string request("GET / HTTP/1.1\r\nHost: 127.0.0.1:8080\r\nUser-Agent: "
//                "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:125.0) "
//                "Gecko/20100101 Firefox/125.l0\r\nAccept: "
//                "text/html,application/xhtml+xml,application/xml;q=0.9,image/"
//                "avif,image/webp,*/*;q=0.8\r\nAccept-Language: "
//                "zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0."
//                "2\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: "
//                "keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nSec-Fetch-Dest:
//                " "document\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-Site: "
//                "none\r\nSec-Fetch-User: ?1\r\n\r\n");

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
// void HandleHome(int clientSocket) {
//   std::string response =
//       "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHome Page";
//   send(clientSocket, response.c_str(), response.size(), 0);
// }

// void HandleAbout(int clientSocket) {
//   std::string response = "HTTP/1.1 200 OK\r\n"
//                          "Content-Type: text/html; charset=UTF-8\r\n"
//                          "\r\n"
//                          "<!DOCTYPE html>\n"
//                          "<html>\n"
//                          "<head>\n"
//                          "<title>HTML Response</title>\n"
//                          "</head>\n"
//                          "<body>\n"
//                          "<h1>Hello, this is a simple HTML response!</h1>\n"
//                          "</body>\n"
//                          "</html>\n";
//   send(clientSocket, response.c_str(), response.size(), 0);
// }

// BOOST_AUTO_TEST_CASE(netFrameTest) {
//   Router router;
//   router.Get("/home", []() {
//     std::string response = "HTTP/1.1 200 OK\r\n"
//                            "Content-Type: text/html; charset=UTF-8\r\n"
//                            "\r\n"
//                            "<!DOCTYPE html>\n"
//                            "<html>\n"
//                            "<head>\n"
//                            "<title>HTML Response</title>\n"
//                            "</head>\n"
//                            "<body>\n"
//                            "<h1>Hello, this is a simple HTML
//                            response!</h1>\n"
//                            "</body>\n"
//                            "</html>\n";
//     return response;
//     // send(clientSocket, response.c_str(), response.size(), 0);
//   });
//   router.Get("/about", []() {
//     std::string response =
//         "HTTP/1.1 200 OK\r\nContent-Type: text/plain; "
//         "charset=UTF-8\r\nContent-Length: 13\r\n\r\nHome Page";
//     return response;
//     // send(clientSocket, response.c_str(), response.size(), 0);
//   });

//   Webserver server(8082, router);
// }

// BOOST_AUTO_TEST_CASE(HTTPRESPONSE) {
//   Router router;
//   router.Get("/home", []() -> HttpResponse {
//     HttpResponse resp("text_html", "index.html");
//     return resp;
//   });
//   router.Post("/login", []() -> HttpResponse {
//     HttpResponse resp("text_html", "login.html");
//     return resp;
//   });

//   Webserver server(8081, router);
// }

// BOOST_AUTO_TEST_CASE(httpRequest) {

//  std::string request =
//     "POST /login HTTP/1.1\r\n"
//     "Host: 127.0.0.1:8081\r\n"
//     "Connection: keep-alive\r\n"
//     "Content-Length: 37\r\n"
//     "sec-ch-ua: \"Chromium\";v=\"124\", \"Google Chrome\";v=\"124\",
//     \"Not-A.Brand\";v=\"99\"\r\n" "Accept: application/json, text/plain,
//     */*\r\n" "Content-Type: application/json\r\n" "sec-ch-ua-mobile: ?0\r\n"
//     "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36
//     (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36\r\n"
//     "sec-ch-ua-platform: \"Windows\"\r\n"
//     "Origin: http://127.0.0.1:8081\r\n"
//     "Sec-Fetch-Site: same-origin\r\n"
//     "Sec-Fetch-Mode: cors\r\n"
//     "Sec-Fetch-Dest: empty\r\n"
//     "Referer: http://127.0.0.1:8081/login\r\n"
//     "Accept-Encoding: gzip, deflate, br, zstd\r\n"
//     "Accept-Language: zh-CN,zh;q=0.9\r\n"
//     "\r\n"
//     "{\"username\":\"aaaaa\",\"password\":\"ccc\"}";

// ;
//   int header_pos = request.find_first_of("\r\n");
//   string line = request.substr(0, header_pos);

//   int body_pos = request.find_last_of("\r\n");
//   string body = request.substr(body_pos, request.size() - body_pos);

//   string header = request.substr(header_pos, body_pos - header_pos);

//   string method;
//   string path;
//   string version;
//   stringstream line_ss(line);
//   line_ss >> method >> path >> version;
//   cout<<"method:"<<method<<" path:"<<path<<" version:"<<version<<endl;

//   unordered_map<string,string> header_table;
//   string header_line;
//   stringstream header_ss(header);

//   while (getline(header_ss, header_line, '\n')) {
//     // cout<<header_line<<endl;
//     int split = header_line.find(":");
//     if (split<0) {
//       continue;
//     }
//     int len=header_line.size();
//     header_table[header_line.substr(0,split)]=header_line.substr(split+2,header_line.size()-split-3);
//     // cout << split << "::"  << len << endl;
//   }

//   for (auto &kv :header_table) {
//     cout<<kv.first<<"="<<kv.second<<endl;
//   }

//   // cout << "line:" <<endl <<line << endl;
//   // cout << "header:" << endl<<header << endl;
//   cout << "body:" <<endl<< body << endl;
// }

/**
         application/json：用于指示实体主体是 JSON 格式的数据。
         application/xml：用于指示实体主体是 XML 格式的数据。
         text/plain：用于指示实体主体是纯文本格式的数据。
         text/html：用于指示实体主体是 HTML 格式的数据。
         multipart/form-data：用于指示实体主体包含多部分数据，常用于文件上传。
         application/x-www-form-urlencoded：用于指示实体主体是经过 URL
   编码的表单数据，常用于 HTTP POST 请求中发送表单数据。
         image/jpeg、image/png、image/gif 等：用于指示实体主体是图片格式的数据。
         application/pdf：用于指示实体主体是 PDF 格式的数据。
         application/octet-stream：用于指示实体主体是二进制数据流，没有指定具体的内容类型。
*/

// BOOST_AUTO_TEST_CASE(HTTPRESPONSE) {
//   Router router;
//   router.Get("/home", [](HttpRequest) -> HttpResponse {
//     HttpResponse resp("text_html", "index.html");
//     return resp;
//   });
//   router.Get("/login", [](HttpRequest) -> HttpResponse {
//     HttpResponse resp("text_html", "login.html");
//     return resp;
//   });
//   router.Get("/login", [](HttpRequest) -> HttpResponse {
//     HttpResponse resp("text_html", "login.html");
//     return resp;
//   });
//   router.Post("/login", [](HttpRequest req) -> HttpResponse {
//     cout << req.getBody() << endl;
//     cout<<req.getHeaders()["Content-Type"]<<endl;
//     HttpResponse resp("application_json", R"({"message":"success"})");

//     cout << "this post handle was played" << endl;
//     return resp;
//   });

//   Webserver server(8081, router);
// }

// BOOST_AUTO_TEST_CASE(mariadbSql) {
//   sql::Driver *driver = sql::mariadb::get_driver_instance();
//   sql::SQLString url{"jdbc:mariadb://localhost:3306/Cpp"};
//   sql::Properties properties{{"user", "zoe"}, {"password", "123456"}};
//   std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

// }
