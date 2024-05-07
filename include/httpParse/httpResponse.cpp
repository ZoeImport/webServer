#include "httpResponse.h"
#include "../tools/tool.h"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>

const std::unordered_map<std::string, std::string> HttpResponse::CONTENT_MAP{
    {"text_html", "text/html"},
    {"text_plain", "text/plain"},
    {"application_json", "application/json"},
    {"text_xml ", "text/xml "},
};

const std::unordered_map<int, std::string> HttpResponse::STATUS_CODE{
    {200, "OK"},
    {404, "Bad Request"},
};

HttpResponse::HttpResponse(std::string content_type, std::string body,
                           std::string version) {
  if (!CONTENT_MAP.count(content_type)) {
    std::cerr << "invalid content-type" << std::endl;
    return;
  }
  if (body.empty()) {
    std::cerr << "invalid response body" << std::endl;
    return;
  }
  _version = version;
  _headers_map["Content-Type"] = CONTENT_MAP.at(content_type);
  _body = body;
}

bool HttpResponse::put_headers(std::pair<std::string, std::string> _pair) {
  if (_pair.first.empty() || _pair.second.empty()) {
    std::cerr << "invalid headers args " << std::endl;
  }
  _headers_map[_pair.first] = _pair.second;
  return true;
}

std::string HttpResponse::to_string() {

  // create line

  setLine(_status_code);

  // create header

  for (auto &pair : _headers_map) {
    _header += pair.first + ": " + pair.second + "\r\n";
  }

  // creat body
  std::string _content_type = _headers_map["Content-Type"];
  if (_content_type == "text/html") {
    return_html(_body);
  } else if (_content_type == "text/plain") {
    return_plain(_body);
  } else if (_content_type == "application/json") {
    return_json(_body);
  }

  _response = _line + _header + "\r\n" + _body;
  return _response;
}

void HttpResponse::setLine(int statusCode) {
  if (!STATUS_CODE.count(statusCode)) {
    std::cerr << "invalid status code" << std::endl;
    return;
  }
  _line = _version + " " + std::to_string(statusCode) + " " +
          STATUS_CODE.at(statusCode) + "\r\n";
}

void HttpResponse::return_html(std::string body) {
  _prefix="../resource/";
  auto html_body = readFileToString(_prefix+body);
  if (html_body.empty()) {
    std::cerr << "Blank Page" << std::endl;
    _body = "<h3>Blank Page<h3>";
  }
  if (html_body == "_ERROR_PATH") {
    _status_code = 404;
  }
  _body = html_body;
}
void HttpResponse::return_plain(std::string body) { _body = body; }
void HttpResponse::return_json(std::string body) { _body = body; }