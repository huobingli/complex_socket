#include <mysql/mysql.h>
#include <iostream>
using namespace std;

int main () {
  MYSQL *mysql;
  mysql = mysql_init(NULL);
  bool a = mysql_real_connect(mysql, "localhost", "root", "123456", "ssm", 3306, NULL, 0);
  if(a == true) {
    cout<<"yes"<<endl;
  }
  
  char *sql = "insert into administrator(id, name, password) values(1, 'huobingli', '123456')";
  mysql_query(mysql, sql);
  mysql_close(mysql);

  return 0;
}
