#include "Database_Int.cpp"
#include "sqlite3.h"
#include <iostream>


class Database : public Database_Int
{
private:
	sqlite3* db;
public:
	bool Connect(string dbpath)
	{
		char* c = const_cast<char*>(dbpath.c_str());
		int rc = sqlite3_open(c, &db);
		if (rc)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool Disconnect()
	{
		return false;
	}
	bool AddData(DataRow dr)
	{
		return false;
	}
	bool RemoveData(long id)
	{
		return false;
	}

};