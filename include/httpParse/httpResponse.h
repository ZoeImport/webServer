#ifndef _HTTP_RESPONSE_
#define _HTTP_RESPONSE_

#include <string>
class HttpResponse {
private:
  static std::string space[2];
  std::string msg;
  std::string version;
  int statusCode;
  std::string line;
  std::string header;
  std::string body;

public:
  HttpResponse() = default;
  inline void setVersion(std::string version) { this->version = version; }
  inline void setStatusCode(int statusCode) { this->statusCode = statusCode; }
  inline void set(int statusCode) { this->statusCode = statusCode; }
  inline void setLine(std::string line) { this->line = line; }
  inline void setHeader(std::string header) { this->header = header; }
  inline void setBody(std::string body) { this->body = body; }
  std::string toString();
};

#endif