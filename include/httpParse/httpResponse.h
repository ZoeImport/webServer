#ifndef _HTTP_RESPONSE_
#define _HTTP_RESPONSE_

#include <string>
#include <unordered_map>
#include <utility>
class HttpResponse {
private:
  std::string _version;
  std::string _line;
  std::string _header;
  std::unordered_map<std::string, std::string> _headers_map;
  std::string _body;
  std::string _response;
  int _status_code;
  std::string _prefix;

  const std::unordered_map<std::string, std::string> _split_character{
      {"Space", " "},
      {"Return", "/r/n"},
  };

public:
  HttpResponse(std::string content_type, std::string body, std::string version="HTTP/1.1");

  const static std::unordered_map<std::string, std::string> CONTENT_MAP;
  const static std::unordered_map<int, std::string> STATUS_CODE;

  inline void set_status_code(int statusCode) { _status_code = statusCode; }

  bool put_headers(std::pair<std::string, std::string>);

  void setLine(int statusCode);

  void return_html(std::string body);
  void return_plain(std::string body);
  void return_json(std::string body);
  std::string to_string();
};

#endif