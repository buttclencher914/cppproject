#include <string>

using namespace std;
class DataRow
{
private:
	long ID; //used to get id of row ID of database
	string source; //eg. facebook, reddit, twitter
	string article_id; //string to identify the post
	string article; //eg. news article, post
	string content_id;
	string content; //all text strings of comments in a article
public:
	long getID()
	{
		return ID;
	}
	void setID(long id)
	{
		ID = id;
	}
	string getSource()
	{
		return source;
	}
	void setSource(string src)
	{
		source = src;
	}
	string getArticleID()
	{
		return article_id;
	}
	void setArticleID(string id)
	{
		article_id = id;
	}
	string getArticle()
	{
		return article;
	}
	void setArticle(string art)
	{
		article = art;
	}
	string getContentID()
	{
		return content_id;
	}
	void setContentID(string conID)
	{
		content_id = conID;
	}
	string getContent()
	{
		return content;
	}
	void setContent(string con)
	{
		content = con;
	}
};