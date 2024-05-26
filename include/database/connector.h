#pragma once

#include "../tools/tool.h"
#include <iostream>
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

class Statement {
private:
  std::unique_ptr<sql::Connection> _conn;
  std::shared_ptr<sql::Statement> _stmnt;
  std::shared_ptr<sql::PreparedStatement> _prepare_stmnt;
  std::unique_ptr<sql::ResultSet> _result;

public:
  Statement(Connector &connector);
  template <typename... Args>
  sql::ResultSet* select(const sql::SQLString &&tableName,
                            const Args &...args) {
    auto coloums = tool::addString(',', args...);
    sql::SQLString selectSql{"select " + coloums + " from " + tableName};
    return _stmnt->executeQuery(selectSql);
  }

  int insert(const std::string &tableName,const std::map<std::string,std::string> &coloumToValueMap);
};
} // namespace db