#include "Database_Int.cpp"
#include "sqlite3.h"


class Database : public Database_Int
{
private:
	sqlite3* db;
public:
	bool Connect(string dbpath) override
	{
		const char* c = dbpath.c_str();
		int rc = sqlite3_open(c, &db);
		if (rc)
		{
			Disconnect();
			return false;
		}
		else
		{
			return true;
		}
	}
	bool Disconnect() override
	{
		sqlite3_close(db);
		return true;
	}
	bool AddData(DataRow dr) override
	{
		sqlite3_stmt* stmt = 0;
		
		string statement = "INSERT INTO " + getTableName() + "(SOURCE, ARTICLE_ID, ARTICLE, CONTENT_ID, CONTENT) VALUES('" + dr.getSource()
			+ "','" + dr.getArticleID() + "','" + dr.getArticle() + "','" + dr.getContentID() + "','" + dr.getContent() + "');";
		//int rc = sqlite3_prepare_v2(db, statement.c_str(), -1, &stmt, 0);
		int rc = sqlite3_exec(db, statement.c_str(), 0, 0, 0);
		//rc = sqlite3_step(stmt);
		if (rc)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool RemoveData(long id) override
	{
		sqlite3_stmt* stmt = 0;

		string statement = "DELETE FROM " + getTableName() + " WHERE ID = " + to_string(id) + ";";
		//int rc = sqlite3_prepare_v2(db, statement.c_str(), -1, &stmt, 0);
		int rc = sqlite3_exec(db, statement.c_str(), 0, 0, 0);
		//rc = sqlite3_step(stmt);
		if (rc)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	sqlite3* getDbObject()
	{
		return db;
	}
};