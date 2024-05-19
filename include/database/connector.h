#pragma once

#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <mariadb/conncpp/jdbccompat.hpp>
#include <memory>

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

public:
  Statement(Connector connector);
  
};
} // namespace db