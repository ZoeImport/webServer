#include "connector.h"
#include <iostream>
#include <iterator>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <memory>
#include <ostream>
#include <string>

namespace db {
Connector::Connector(sql::SQLString url, sql::SQLString account,
                     sql::SQLString password) {
  try {
    _driver = sql::mariadb::get_driver_instance();
    _url = url;
    _properties["user"] = account;
    _properties["password"] = password;
    std::unique_ptr<sql::Connection> conn(_driver->connect(_url, _properties));
    _connection.swap(conn);
  } catch (sql::SQLException &e) {
    std::cerr << "sql excetpion : " << e.what() << std::endl;
  }
}

sql::Connection *Connector::getConnectPtr() { return _connection.release(); }

Statement::Statement(Connector connector) {
  _conn = std::unique_ptr<sql::Connection>(connector.getConnectPtr());
}

} // namespace db