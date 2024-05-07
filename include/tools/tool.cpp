#include <fstream>
#include <spdlog/spdlog.h>
#include <string>

std::string readFileToString(std::string path) {
  std::fstream read(path);
  std::string result;
  if (read.is_open()) {
    std::string line;
    while (std::getline(read, line)) {
      result += (line + "\n");
    }
  } else {
    spdlog::error("cannot open file!");
    return std::string("_ERROR_PATH");
  }
  return result;
}
