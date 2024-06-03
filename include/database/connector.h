#pragma once

#include "../tools/tool.h"
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <mariadb/conncpp/Statement.hpp>
#include <mariadb/conncpp/jdbccompat.hpp>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
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
  std::unique_ptr<sql::ResultSet> _uptr_res;
  std::vector<std::string> _mete_coloum;

public:
  Result() = default;

  Result(Result &&moved_result)
      : _uptr_res(std::move(moved_result._uptr_res)),
        _list_result_map(std::move(moved_result._list_result_map)),
        _mete_coloum(std::move(moved_result._mete_coloum)) {}
  Result &operator=(Result &&moved_result) {
    if (this != &moved_result) {
      _uptr_res = std::move(moved_result._uptr_res);
      _list_result_map = std::move(moved_result._list_result_map);
      _mete_coloum = std::move(moved_result._mete_coloum);
    }
    return *this;
  }

  template <typename... Args> Result(sql::ResultSet *result, Args... args) {
    _uptr_res.reset(result);
    _mete_coloum = tool::strs_to_lists(args...);
    std::reverse(_mete_coloum.begin(), _mete_coloum.end());
    while (_uptr_res->next()) {
      std::unordered_map<std::string, std::string> row;
      for (auto &param : _mete_coloum) {
        row[param] = result->getString(param);
      }
      _list_result_map.push_back(row);
    }
  }
  Result(const Result &) = delete;
  Result &operator=(const Result &) = delete;

  Result inline result(int width = 15) {
    if (this->_list_result_map.empty()) {
      return Result();
    }

    for (auto &mem : this->_list_result_map) {
      for (auto &x : mem) {
        std::cout << std::setw(width) << std::left << x.second;
      }
      std::cout << std::endl;
    }
    return Result(std::move(*this));
  }

  Result inline title(int width = 15) {
    if (this->_mete_coloum.empty()) {
      return Result();
    }
    for (auto &col_name : this->_mete_coloum) {
      std::cout << std::setw(width) << std::left << col_name;
    }
    std::cout << std::endl;
    return Result(std::move(*this));
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
  auto Select(const sql::SQLString &&tableName, const Args &...args) {
    auto coloums = tool::add_string(',', args...);
    sql::SQLString selectSql{"select " + coloums + " from " + tableName};
    Result res(_stmnt->executeQuery(selectSql), args...);
    return res;
  }
  template <typename... Args>
  Result Describe(const std::string &tableName, const Args &...args) {
    std::string sql{"describe " + tableName};
    Result res{_stmnt->executeQuery(sql), args...};
    return res;
  }

  int Insert(const std::string &tableName,
             const std::map<std::string, std::string> &coloumToValueMap);

  int Update(const std::string &tableName,
             const std::map<std::string, std::string> &coloumToValueMap,
             std::string condition = "true");

  int Delete(const std::string &tableName, const std::string &condition);

  int Delete(const std::string &tableName,
             const std::map<std::string, std::string> &conditionMap,
             const std::string &separate);
};

} // namespace db