#include "CMyList.h"

int main()
{
	CMyList<int> list;	

	list.PushFront(3);

	list.begin()--;
}