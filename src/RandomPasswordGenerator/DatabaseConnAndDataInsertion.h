#pragma once

#include <mysql.h>
#include <iostream>

void insertDataInDatabase(TCHAR buff1[], TCHAR buff2[], TCHAR buff3[]) {

	int qstate;

	std::string query = "INSERT INTO userinfo (appname, email, password) VALUES(";

	std::wstring wstr1(&buff1[0]);
	std::string str1(wstr1.begin(), wstr1.end());
	std::string v1 = "'" + str1 + "'";
	query += v1;

	std::wstring wstr2(&buff2[0]);
	std::string str2(wstr2.begin(), wstr2.end());
	std::string v2 = ", '" + str2 + "'";
	query += v2;

	std::wstring wstr3(&buff3[0]);
	std::string str3(wstr3.begin(), wstr3.end());
	std::string v3 = ", '" + str3 + "');";
	query += v3;

	std::cout << query << std::endl;

	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "Localhost", "root", "benimyenisifrem", "passwordmanagerdbs", 3306, NULL, 0);

	if (conn) {


		const char* q = query.c_str();
		qstate = mysql_query(conn, q);


	}
}
