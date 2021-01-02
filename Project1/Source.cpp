#include <iostream>
#include <assert.h>
#include <Windows.h>
#include<string>

template <class T>
class Word
{
	T* key;
	T* value;

public:
	Word() :key(nullptr), value(nullptr) {}
	Word(const T& key, const T& value)
	{
		setKey(key);
		setValue(value);
	}
	//Setter
	void setKey(const T& key)
	{
		assert(!key.empty() && "Key is blank!");
		this->key = new T(key);
	}
	void setValue(const T& value)
	{
		this->value = new T(value);
	}
	//Getter
	T getKey() const
	{
		return *this->key;
	}
	T* getValue() const
	{
		return this->value;
	}
	//
	friend std::ostream& operator<<(std::ostream& out, const  Word& word);
};

std::ostream& operator<<(std::ostream& out, const  Word<std::string>& word)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	out << "English: ";
	SetConsoleTextAttribute(hConsole, 10);
	out << word.getKey() << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	out << "Azerbaijani: ";
	SetConsoleTextAttribute(hConsole, 10);
	out << *word.getValue();
	SetConsoleTextAttribute(hConsole, 15);
	return out;
}

template<class T>
class Container
{
	size_t Word_count;
	Word<T>** Words;

public:
	Container() :Word_count(0), Words(nullptr) {}
	Container(size_t Word_count, Word<T>** Words)
	{
		setWordCount(Word_count);
		setWords(Words);
	}
	//Setter
	void setWordCount(size_t Word_count)
	{
		assert(Word_count && "Word count must be greater than zero");
		this->Word_count = Word_count;
	}
	void setWords(Word<T>** Words)
	{
		size_t Word_count = getWordCount();

		this->Words = new Word<T> *[Word_count];

		if (this->Words)
		{
			for (size_t i = 0; i < Word_count; i++)
			{
				this->Words[i] = new Word<T>(*Words[i]);
			}
		}
	}
	//Getter
	size_t getWordCount() const
	{
		return this->Word_count;
	}
	Word<T>** getWords()const
	{
		return this->Words;
	}
	//
	T* operator[](T& key)
	{
		for (size_t i = 0; i < this->Word_count; i++)
		{
			if (key == this->Words[i]->getKey())
			{
				return this->Words[i]->getValue();
			}
		}
		addWord(key);
		return this->Words[this->Word_count - 1]->getValue();
	}

	void addWord(T& key)
	{
		auto temp = new Word<T> *[getWordCount()+1];
		for (size_t i = 0; i < getWordCount(); i++)
		{
			temp[i] = new Word<T>(*Words[i]);
		}
		temp[getWordCount()] = new Word<T>;
		temp[getWordCount()]->setKey(key);
		temp[getWordCount()]->setValue("");

		this->Words = temp;
		setWordCount(getWordCount()+1);
	}
	~Container()
	{
		for (size_t i = 0; i < this->Word_count; i++)
		{
			delete this->Words[i];
		}
		delete[] this->Words;
	}
};



void main()
{



	Word<std::string>* w1 = new Word<std::string>("apple", "alma");
	Word<std::string>* w2 = new Word<std::string>("ball", "top");
	Word<std::string>* w3 = new Word<std::string>("task", "tapshiriq");
	Word<std::string>** Words = new Word<std::string> * [3]{w1, w2, w3 };
	std::cout << *w1 << std::endl;
	Container<std::string> container(3, Words);
	std::string key = "pear";
	*container[key]="armud" ;
	std::cout << "Pear: ";
	std::cout << *container[key] << std::endl;

	
}

