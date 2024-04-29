#include "httpResponse.h"
std::string HttpResponse::space[2] = {"\r\n", " " };

std::string HttpResponse::toString() {
  std::string response;
  response += this->version+space[2]+
}