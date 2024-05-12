#ifndef _HTTP_REQUEST_
#define _HTTP_REQUEST_
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class HttpRequest {
private:
  std::string _msg;
  std::string _method;
  std::string _path;
  std::string _version;
  std::unordered_map<std::string,std::string> _header_table;
  std::string _body;
  static std::string url_prefix;

public:
  HttpRequest(const std::string &requestStr);

  inline std::string getMethod() const { return _method; }

  inline std::string getMsg() const { return _msg; }

  inline std::string getPath() const { return _path; }

  inline std::string getVersion() const { return _version; }

  inline std::unordered_map<std::string,std::string>  getHeaders() const {
    return _header_table;
  }

  inline std::string getBody() const { return _body; }
  inline static std::string getUrlPrefix() {
    return HttpRequest::url_prefix;
  }
};

// void httpHandle(HttpRequest &req);
std::string httpHandle(HttpRequest &req);
#endif