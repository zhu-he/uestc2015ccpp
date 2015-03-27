#include <iostream>
#include <cassert>

template <class T>
class LinkedList
{
private:
	struct Node
	{
		T value;
		Node* next;
	};

	int _size;
	Node* headNode;
	Node* rearNode;
public:
	LinkedList<T>()
	{
		_size = 0;
		headNode = new Node();
		headNode->next = NULL;
		rearNode = headNode;
	}

	void resize(const int size)
	{
		if (_size < size)
		{
			Node* p = headNode;
			for (int i = 0; i < size - _size; ++i)
			{
				Node* newNode = new Node();
				p->next = newNode;
				p = newNode;
			}
		}
		_size = size;
	}

	T& operator [] (const int index)
	{
		return this->at(index);
	}

	void operator = (const T* array)
	{
		Node* p = headNode;
		for (int i = 0; i < _size; ++i)
		{
			p = p->next;
			p->value = array[i];
		}
		rearNode = p;
	}

	friend std::ostream& operator << (std::ostream& out, LinkedList<T>& linkedList)
	{
		out << '[';
		Node* p = linkedList.begin();
		for (int i = 0; i < linkedList.size(); ++i)
		{
			p = p->next;
			if (i)
			{
				out << ", ";
			}
			out << p->value;
		}
		out << ']';
		return out;
	}

	friend std::istream& operator >> (std::istream& in, LinkedList<T>& linkedList)
	{
		T t;
		in >> t;
		linkedList.push_back(t);
		return in;
	}

	int size()
	{
		return _size;
	}

	void push_back(const T t)
	{
		Node* newNode = new Node();
		newNode->value = t;
		newNode->next = NULL;
		rearNode->next = newNode;
		rearNode = newNode;
		_size++;
	}

	void insert(const int index, const T t)
	{
		if (index == _size)
		{
			push_back(t);
			return;
		}
		assert(index >= 0 && index < _size);
		Node* p = headNode;
		for (int i = 0; i < index; ++i)
		{
			p = p->next;
		}
		Node* newNode = new Node();
		newNode->value = t;
		newNode->next = p->next;
		p->next = newNode;
		_size++;
	}

	T& at(const int index)
	{
		assert(index >= 0 && index < _size);
		Node* p = headNode;
		for (int i = 0; i < index + 1; ++i)
		{
			p = p->next;
		}
		return p->value;
	}

	int find(const T t)
	{
		Node* p = headNode;
		for (int i = 0; i < _size; ++i)
		{
			p = p->next;
			if (p->value == t)
			{
				return i;
			}
		}
		return -1;
	}

	void erase(const int index)
	{
		assert(index >= 0 && index < _size);
		Node* p = headNode;
		for (int i = 0; i < index; ++i)
		{
			p = p->next;
		}
		p->next = p->next->next;
		if (index == _size - 1)
		{
			rearNode = p;
		}
		_size--;
	}

	bool empty()
	{
		return _size == 0 || headNode == rearNode;
	}

	Node* begin()
	{
		return headNode;
	}

	Node* end()
	{
		return rearNode;
	}
};

int main()
{
	LinkedList<int> a;
	a.resize(4);
	int b[] = {1, 4, 3, 2};
	a = b;
	a.erase(2);
	a.push_back(123);
	std::cout << a << '\n';
	return 0;
}
