#include "connector.h"
#include <iostream>
#include <map>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <mariadb/conncpp/Statement.hpp>
#include <memory>
#include <ostream>
#include <string>

namespace db {
// Connector
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

// Statement

Statement::Statement(Connector &connector) {
  _conn = std::unique_ptr<sql::Connection>{connector.getConnectPtr()};
  _stmnt = std::shared_ptr<sql::Statement>{_conn->createStatement()};
  _prepare_stmnt = std::shared_ptr<sql::PreparedStatement>();
}

int Statement::Insert(
    const std::string &tableName,
    const std::map<std::string, std::string> &coloumToValueMap) {
  std::string insertSql{"insert into "};
  insertSql += tableName;
  std::string colounms{"("};
  std::string values{" values("};
  auto len = coloumToValueMap.size();
  auto index = 0;
  for (auto &kv : coloumToValueMap) {
    if (index == len - 1) {
      colounms += (kv.first + ") ");
      values += ("?)");
      break;
    }
    colounms += (kv.first + ",");
    values += ("?,");
    ++index;
  }
  insertSql += colounms + values;

  std::shared_ptr<sql::PreparedStatement> temp{
      _conn->prepareStatement(insertSql)};
  _prepare_stmnt.swap(temp);

  index = 1;
  for (auto &kv : coloumToValueMap) {
    _prepare_stmnt->setString(index++, kv.second);
  }

  return _prepare_stmnt->executeUpdate();
}

int Statement::Update(
    const std::string &tableName,
    const std::map<std::string, std::string> &coloumToValueMap,
    std::string condition) {
  std::string updateSql{"update " + tableName + " set "};

  for (auto it = coloumToValueMap.begin(); it != coloumToValueMap.end(); ++it) {
    if (it != coloumToValueMap.begin()) {
      updateSql += ",";
    }
    updateSql += (it->first + " = ? ");
  }
  updateSql += ("where " + condition);

  std::shared_ptr<sql::PreparedStatement> temp{
      _conn->prepareStatement(updateSql)};
  _prepare_stmnt.swap(temp);
  auto index = 1;
  for (auto &kv : coloumToValueMap) {
    _prepare_stmnt->setString(index++, kv.second);
  }

  return _prepare_stmnt->executeUpdate();
}

int Statement::Delete(const std::string &tableName,
                      const std::string &condition) {

  std::string deleteSql = ("delete from " + tableName + " where " + condition);

  return _stmnt->executeUpdate(deleteSql);
}

int Statement::Delete(const std::string &tableName,
                      const std::map<std::string, std::string> &conditionMap,
                      const std::string &separate) {

  std::string deleteSql = ("delete from " + tableName + " where ");
  int index = 1;
  int len = conditionMap.size();
  for (auto &kv : conditionMap) {
    deleteSql += (kv.first + "=" + kv.second);
    if (index != len) {
      ++index;
      deleteSql += (" " + separate + " ");
    }
  }
  return _stmnt->executeUpdate(deleteSql);
}
  

} // namespace db