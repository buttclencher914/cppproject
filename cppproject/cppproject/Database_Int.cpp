#include <string>
#include "DataRow.cpp"

using namespace std;
class Database_Int
{
private:
	const string dbpath = "db.db3";
	const string tablename = "db";
public:
	string getDBPath()
	{
		return dbpath;
	}
	string getTableName()
	{
		return tablename;
	}
	virtual bool Connect(string) = 0;
	virtual bool Disconnect() = 0;
	virtual bool AddData(DataRow) = 0; //add a new data
	virtual bool RemoveData(long) = 0; //remove data by id
};