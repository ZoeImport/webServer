#ifndef _HTTP_RESPONSE_
#define _HTTP_RESPONSE_

#include <string>
class HttpResponse {
private:
  static std::string space[2];
  std::string msg;
  std::string version;
  int statusCode;
  std::string header;
  std::string body;

public:
  HttpResponse() = default;
  HttpResponse(std::string body) {
    this->body=body;
  }
  inline void setVersion(std::string version) { this->version = version; }
  inline void setStatusCode(int statusCode) { this->statusCode = statusCode; }
  inline void setMsg(std::string msg) { this->msg = msg; }
  inline void setHeader(std::string header) { this->header = header; }
  inline void setBody(std::string body) { this->body = body; }
  std::string toString();
};

#endif