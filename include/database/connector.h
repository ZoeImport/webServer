#pragma once

#include "../tools/tool.h"
#include <algorithm>
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <mariadb/conncpp/Statement.hpp>
#include <mariadb/conncpp/jdbccompat.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace db {

class Connector {
private:
  sql::Driver *_driver;
  sql::SQLString _url;
  sql::Properties _properties;
  std::unique_ptr<sql::Connection> _connection;

public:
  Connector(sql::SQLString url, sql::SQLString account,
            sql::SQLString password);
  sql::Connection *getConnectPtr();
};

class Result {
private:
  std::vector<std::unordered_map<std::string, std::string>> _list_result_map;

public:
  template <typename... Args> Result(sql::ResultSet *result, Args... args) {
    auto vec = tool::strs_to_lists(args...);
    std::reverse(vec.begin(),vec.end());
    while (result->next()) {
      std::unordered_map<std::string, std::string> row;
      for (auto &param : vec) {
        row[param] = result->getString(param);
      }
      _list_result_map.push_back(row);
    }
  }

  inline auto &get_list_result_map() const { return _list_result_map; }

};

class Statement {
private:
  std::unique_ptr<sql::Connection> _conn;
  std::shared_ptr<sql::Statement> _stmnt;
  std::shared_ptr<sql::PreparedStatement> _prepare_stmnt;
  std::unique_ptr<sql::ResultSet> _result;

public:
  Statement(Connector &connector);
  template <typename... Args>
  auto select(const sql::SQLString &&tableName, const Args &...args) {
    auto coloums = tool::add_string(',', args...);
    sql::SQLString selectSql{"select " + coloums + " from " + tableName};
    Result res(_stmnt->executeQuery(selectSql), args...);
    return res;
  }

  int insert(const std::string &tableName,
             const std::map<std::string, std::string> &coloumToValueMap);
};

} // namespace db