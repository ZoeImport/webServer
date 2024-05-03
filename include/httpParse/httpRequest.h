#ifndef _HTTP_REQUEST_
#define _HTTP_REQUEST_
#include <sstream>
#include <string>
#include <vector>

class HttpRequest {
private:
  std::string msg;
  std::string method;
  std::string path;
  std::string version;
  std::vector<std::pair<std::string, std::string>> headers;
  std::string body;

  static std::string url_prefix;

public:
  HttpRequest(const std::string &requestStr);

  inline std::string getMethod() const { return method; }

  inline std::string getMsg() const { return msg; }

  inline std::string getPath() const { return path; }

  inline std::string getVersion() const { return version; }

  inline std::vector<std::pair<std::string, std::string>> getHeaders() const {
    return headers;
  }

  inline std::string getBody() const { return body; }
  inline static std::string getUrlPrefix() {
    return HttpRequest::url_prefix;
  }
};

// void httpHandle(HttpRequest &req);
std::string httpHandle(HttpRequest &req);
#endif