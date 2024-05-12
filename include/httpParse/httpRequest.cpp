#include "httpRequest.h"
#include "../tools/tool.h"
#include "httpResponse.h"
#include <algorithm>
#include <boost/test/unit_test_suite.hpp>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>

HttpRequest::HttpRequest(const std::string &requestStr) {

  // save origin request message
  _msg = requestStr;
  // get header position 
  int header_pos = requestStr.find_first_of("\r\n");
  std::string line = requestStr.substr(0, header_pos);

  // locate Request body position 
  std::string body_string =requestStr.substr(0,requestStr.find_last_of("\r\n")-3);
  int body_pos = body_string.find_last_of("\r\n");
  // std::cout<<"body_pos: "<<body_pos<<" req size:"<<requestStr.size()<<std::endl;
  _body = requestStr.substr(body_pos, requestStr.size() - body_pos);

  // substr for header by Request header position
  std::string header = requestStr.substr(header_pos, body_pos - header_pos);

  // by stringStream to get method path version
  std::stringstream line_ss(line);
  line_ss >>_method >> _path >> _version;
  // std::cout<<"method:"<<_method<<" path:"<<_path<<" version:"<<_version<<std::endl;

  
  std::string header_line;
  std::stringstream header_ss(header);
  
  while (getline(header_ss, header_line, '\n')) {
    // cout<<header_line<<endl;
    int split = header_line.find(":");

    // avoid blank line 
    if (split<0) {
      continue;
    }

    _header_table[header_line.substr(0,split)]=header_line.substr(split+2,header_line.size()-split-3);
    // cout << split << "::"  << len << endl;
  }

  // for (auto &kv :_header_table) {
  //   std::cout<<"header line :: "<<kv.first<<"="<<kv.second<<std::endl;
  // }
  
  // cout << "line:" <<endl <<line << endl;
  // cout << "header:" << endl<<header << endl;
  // std::cout<<"body: "<<std::endl<<_body<<std::endl;
}
std::string HttpRequest::url_prefix = "../resource";

// std::string httpResponse = "HTTP/1.1 200 OK\r\n"
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
// std::string  httpHandle(HttpRequest &req) {
//   std::string url;
//   if (req.getMethod() == "GET") {

//     url = HttpRequest::getUrlPrefix() + req.getPath();
//     //test
//     url += "index.html";
//     auto pagestream=readFileToString(url);
//     HttpResponse reponse(pagestream);
//     reponse.setVersion("HTTP/1.1");
//     reponse.setStatusCode(200);
//     reponse.setMsg("ok");
//     auto res = reponse.toString();
//     return res;
//   }
//   return NULL;
// }
