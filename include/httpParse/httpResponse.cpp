#include "httpResponse.h"
#include <string>
std::string HttpResponse::space[2] = {"\r\n", " " };

std::string HttpResponse::toString() {
  std::string response;
  
  this->header="Content-Type: text/html; charset=UTF-8\r\n";
  response += this->version + space[1] + std::to_string(this->statusCode) +
              space[1] + this->msg + space[0] + this->header + space[0]+this->body;
  return response;
}