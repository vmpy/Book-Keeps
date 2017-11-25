#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
class Book
{
	private:
		unsigned int m_Num;
		std::string m_BookTittle;
		std::string m_BookSubTittle;
		std::string m_WriterName;
		std::string m_PressName;
		unsigned int m_PagesNum;
		double m_Price;
		unsigned int m_Star;
		std::string m_Criticize;
		std::string m_ISBN;
	public:
		Book(void){};
		~Book(void){};
		void Enter(void);
		void Print(void);
		void Star(void);
		void Write(void);
};
int main(void)
{
	Book mybook = Book();
	mybook.Enter();
	mybook.Print();
	mybook.Write();
	return 0;
}

void Book::Write(void)
{
	char FileName[10];
	sprintf(FileName,"%u.dat",m_Num);
	std::ifstream fin(FileName);
	if(!fin)
	{
		std::fstream infile;
		infile.open(FileName,std::ios::out|std::ios::binary);
		infile.write((char*)this,sizeof(Book));
		infile.close();
	}
	else
	{
		std::cout << "书籍序列重复!" << std::endl; 
	}
}

void Book::Print(void)
{
	std::cout << "您的该书籍序列:" << std::endl;
	std::cout << m_Num << std::endl;
	std::cout << "书籍标题:" << std::endl;
	std::cout << m_BookTittle << std::endl;
	std::cout << "书籍副标题:" << std::endl;
	std::cout << m_BookSubTittle << std::endl;
	std::cout << "书籍作者:" << std::endl;
	std::cout << m_WriterName << std::endl;
	std::cout << "书籍出版社:" << std::endl;
	std::cout << m_PressName << std::endl;
	std::cout << "书籍页数:" << std::endl;
	std::cout << m_PagesNum << std::endl;
	std::cout << "书籍价格（元）:" << std::endl;
	std::cout << m_Price << std::endl;
	std::cout << "书籍分数(星):" << std::endl;
	this->Star();
	std::cout << "您的书籍一句话短评:" << std::endl;
	std::cout << m_Criticize << std::endl;
	std::cout << "书籍ISBN:" << std::endl;
	std::cout << m_ISBN << std::endl;
	
}

void Book::Star(void)
{
	int Tmp = this->m_Star;
	while(Tmp > 0)
	{
		std::cout << "★"; 
		Tmp--;
	}
	std::cout << std::endl;
}

void Book::Enter(void)
{
	std::cout << "这是您看过的第几部书:" << std::endl;
	std::cin >> m_Num;
	std::cin.get();
	std::cout << "请输入书籍标题:" << std::endl;
	std::getline(std::cin,m_BookTittle);
	std::cout << "请输入书籍副标题:" << std::endl;
	std::getline(std::cin,m_BookSubTittle);
	std::cout << "请输入书籍作者:" << std::endl;
	std::getline(std::cin,m_WriterName);
	std::cout << "请输入书籍出版社:" << std::endl;
	std::getline(std::cin,m_PressName);
	std::cout << "请输入书籍页数:" << std::endl;
	std::cin >> m_PagesNum;
	std::cin.get();
	std::cout << "请输入书籍价格（元）:" << std::endl;
	std::cin >> m_Price;
	std::cin.get();
	std::cout << "您觉得这部书分数几星?" << std::endl;
	std::cin >> m_Star;
	std::cin.get();
	std::cout << "您的一句话短评:" << std::endl;
	std::getline(std::cin,m_Criticize);
	std::cout << "这部书的ISBN:" << std::endl;
	std::getline(std::cin,m_ISBN);
}
