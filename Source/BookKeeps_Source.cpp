#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <io.h>

/*供_findfirst,_findnext等函数使用*/
const char Search[] = "*.bmdat";

class Book
{
	public:
		unsigned int m_Num;
		char m_BookTittle[50];
		char m_BookSubTittle[50];
		char m_WriterName[50];
		char m_PressName[40];
		unsigned int m_PagesNum;
		double m_Price;
		unsigned int m_Star;
		char m_Criticize[50];
		char m_ISBN[11];

		void PrintIndex(void);
		void Enter(void);
		void Print(void);
		void Star(void);
		void Write(void);
		void Read(char*);
};

Book *MarkedBooks;

inline void Menu(void);
int BooksFind(void);
int IndexFilling(void);
int FindMarkedBooksIndex(int);

int main(void)
{
	int Choice,Index;
	int len;
	int Tmp;
	Lee:

	Menu();
	
	//填充MarkedBooks数组信息. 
	len = BooksFind();
	//如果工作目录中存在文件:
	if(len)
	{
    		len--;
		MarkedBooks = new Book[len];
		IndexFilling();
	}
	
	std::cin >> Choice;
	switch(Choice)
	{ 
		case 1:
		{
			std::cout << "请问要载入多少本书?" << std::endl;
			std::cin >> len;
			if(len > 0)
			{
				Book *mybook = new Book[len];
				std::cout << "记录中:" << std::endl;
				for(Tmp = 0;Tmp < len;Tmp++)
				{
					mybook[Tmp].Enter();
					mybook[Tmp].Write();
					/*为了保存文件.*/
				}
				delete [] mybook;
				mybook = NULL;
				delete [] MarkedBooks;
				MarkedBooks = NULL; 
			}
			else
			{
				std::cout << "真心不懂，逻辑错误!" << std::endl;
			}
			break;
		}
		case 2:
		{
			std::cout << "\n图书目录:" << std::endl; 
			for(Tmp = 0;Tmp < len;Tmp++)
			{
				MarkedBooks[Tmp].PrintIndex();
			}
			system("cls");
			for(Tmp = 0;Tmp < len;Tmp++)
			{
				MarkedBooks[Tmp].PrintIndex();
			}
			goto Lee;
			break; 
		}
		case 3:
		{ 
			char DelFileName[20];
			
			std::cout << "\n图书目录:" << std::endl; 
			for(Tmp = 0;Tmp < len;Tmp++)
			{
				MarkedBooks[Tmp].PrintIndex();
			}
			
			std::cout << "请输入您要删除的书籍序列:" << std::endl;
			std::cin >> Index;
			sprintf(DelFileName,"%d.bmdat",Index);
			remove(DelFileName);
			system("cls");
			goto Lee;
			break;
		}
		case 4:
		{
			char DelFileName[20];
			int NowChioce;
			int thisNum;
			
			std::cout << "\n图书目录:" << std::endl; 
			for(Tmp = 0;Tmp < len;Tmp++)
			{
				MarkedBooks[Tmp].PrintIndex();
			}
			
			std::cout << "这是第几本书?" <<std::endl;
			std::cin >> thisNum;
			Tmp = FindMarkedBooksIndex(thisNum);
			if(Tmp == -1)
			{
				std::cout << "\n不存在该图书信息!!" <<std::endl;
				goto Lee;
				break;
			}
			Book TmpBook = MarkedBooks[Tmp];
			std::cout << "\n选择更改项目:" <<std::endl;
			std::cout << "1.图书序列." <<std::endl;
			std::cout << "2.图书标题." <<std::endl;
			std::cout << "3.图书副标题." <<std::endl;
			std::cout << "4.图书短评价." <<std::endl;
			std::cout << "5.图书出版社." <<std::endl;
			std::cout << "6.图书页码数." <<std::endl;
			std::cout << "7.图书价格." <<std::endl;
			std::cout << "8.图书星级." <<std::endl;
			std::cout << "9.作者姓名." <<std::endl;
			std::cout << "10.图书ISBN." <<std::endl;
			ChangeYes:
			std::cin >> NowChioce;
			switch(NowChioce)
			{
				case 1:std::cin >> TmpBook.m_Num;break;
				case 2:std::cin >> TmpBook.m_BookTittle;break;
				case 3:std::cin >> TmpBook.m_BookSubTittle;break;
				case 4:std::cin >> TmpBook.m_Criticize;break;
				case 5:std::cin >> TmpBook.m_PressName;break;
				case 6:std::cin >> TmpBook.m_PagesNum;break;
				case 7:std::cin >> TmpBook.m_Price;break;
				case 8:std::cin >> TmpBook.m_Star;break;
				case 9:std::cin >> TmpBook.m_WriterName;break;
				case 10:std::cin >> TmpBook.m_ISBN;break;
				default:goto Lee;
			}
			std::cout << "\n继续更改项目？(Yes[1]\\No[2])" <<std::endl;
			std::cin >> NowChioce;
			if(NowChioce == 1)
			{
				goto ChangeYes;
			}
			sprintf(DelFileName,"%d.bmdat",TmpBook.m_Num);
			remove(DelFileName);
			TmpBook.Write();
			goto Lee;
			break;
		}
		case 5:
		{
			int Num;
			
			std::cout << "\n图书目录:" << std::endl; 
			for(Tmp = 0;Tmp < len;Tmp++)
			{
				MarkedBooks[Tmp].PrintIndex();
			}
			
			std::cout << "请输入图书序列(第*本书)\n";
			std::cin >> Num;
			Tmp = FindMarkedBooksIndex(Num);
			std::cout << std::endl;
			MarkedBooks[Tmp].Print();
			goto Lee;
			break;
		}
		case 6:
		{
			break;
		}
		default:goto Lee;break;
	}
	delete [] MarkedBooks;
	MarkedBooks = NULL; 
	return 0;
}

/**
*寻找 MarkedBooks数组空间中与指定的书籍序列的元素.
*@param Index:书籍序列.
*@return:存在返回该元素下标;不存在则返回-1. 
*/
int FindMarkedBooksIndex(int Index)
{
	int Tmp;
	for(Tmp = 0;;Tmp++)
	{
		if(MarkedBooks[Tmp].m_Num == Index)
		{
			return Tmp;
		}
	}
	return -1;
}
/**
*将MarkedBooks对象指针所分配的空间用文件信息填充. 
*/
int IndexFilling(void)
{
	long Handle;
	int Tmp;
	int count = 0;
	struct _finddata_t BooksFile;
	Tmp = Handle = _findfirst(Search,&BooksFile);
	while(Tmp != -1)
	{
		MarkedBooks[count].Read(BooksFile.name);
		Tmp = _findnext(Handle,&BooksFile);
		count++;
	}
	_findclose(Handle);
	return 0;
}

/**
*返回存在的文件数目. 
*/
int BooksFind(void)
{
	long Handle;
	int Tmp,Count;
	struct _finddata_t BooksFile;
	Tmp = Handle = _findfirst(Search,&BooksFile);
	if(Tmp != -1)
	{
		Count = 1;
	}
	else
	{
		Count = 0;
	}
	while(Tmp != -1)
	{
		Tmp = _findnext(Handle,&BooksFile);
		Count++;
	}
	_findclose(Handle); 
	return Count;
}

inline void Menu(void)
{
	std::cout << "*******************************************\n\n";
	std::cout << "                1.记录图书信息.\n"; 
	std::cout << "                2.获得图书目录.\n";
	std::cout << "                3.删除图书信息.\n";
	std::cout << "                4.更改图书信息.\n"; 
	std::cout << "                5.查看图书信息.\n";
	std::cout << "                6.退出程序.\n";
}

/**
*打印本书籍的序列和标题. 
*/
void Book::PrintIndex(void)
{
	std::cout << "            第" << m_Num << "本书:" << m_BookTittle << std::endl; 
}

/**
*将本书籍写入文件(.bmdat).
*/
void Book::Write(void)
{
	char FileName[10];
	A:
	sprintf(FileName,"%u.bmdat",m_Num);
	std::ifstream fin(FileName);
	if(!fin)
	{
		std::fstream infile;
		infile.open(FileName,std::ios::out | std::ios::binary);
		infile.write((char*)this,sizeof(Book));
		infile.close();
	}
	else
	{
		std::cout << "书籍序列重复!" << std::endl;
		std::cout << "或者你可以更改书籍序列(您的第几本书):" << std::endl;
		std::cin >> m_Num;
		goto A;
	}
}
/**
*将此对象用文件信息填充(.bmdat).
*@param FileName:文件名称. 
*/
void Book::Read(char* FileName)
{
	std::ifstream fin(FileName);
	if(fin)
	{
		std::fstream infile;
		infile.open(FileName,std::ios::in|std::ios::binary);
		infile.read((char*)this,sizeof(Book));
		infile.close();
	}
}
/**
*打印书籍详细信息. 
*/
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
/**
*用星星符号的形式打印星级. 
*/
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

/**
*从用户输入获得图书详细信息. 
*/
void Book::Enter(void)
{
	std::cout << "这是您看过的第几部书:" << std::endl;
	std::cin >> m_Num;
	std::cin.get();
	std::cout << "请输入书籍标题:" << std::endl;
	std::cin.getline(m_BookTittle,25);
	std::cout << "请输入书籍副标题:" << std::endl;
	std::cin.getline(m_BookSubTittle,25);
	std::cout << "请输入书籍作者:" << std::endl;
	std::cin.getline(m_WriterName,25);
	std::cout << "请输入书籍出版社:" << std::endl;
	std::cin.getline(m_PressName,25);
	std::cout << "请输入书籍页数:" << std::endl;
	std::cin >> m_PagesNum;
	std::cin.get();
	std::cout << "请输入书籍价格（元）:" << std::endl;
	std::cin >> m_Price;
	std::cin.get();
	std::cout << "您觉得这部书分数几星?" << std::endl;
	std::cin >> m_Star;
	std::cin.get();
	std::cout << "您的一句话短评(最长25个字):" << std::endl;
	std::cin.getline(m_Criticize,50);
	std::cout << "这部书的ISBN:" << std::endl;
	std::cin.getline(m_ISBN,11);
}
