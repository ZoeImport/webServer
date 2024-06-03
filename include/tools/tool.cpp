#include <fstream>
#include <iostream>
#include <string>
#include "tool.h"

std::string readFileToString(std::string path) {
  std::fstream read(path);
  std::string result;
  if (read.is_open()) {
    std::string line;
    while (std::getline(read, line)) {
      result += (line + "\n");
    }
  } else {
    std::cerr<<"cannot open file!";
    return std::string("_ERROR_PATH");
  }
  return result;
}
// std::string eraseBlur(const std::string &content_type,const std::string &body=" "){
//   if (content_type=="application/json") {
    
//   }
// }


