#pragma once
#ifndef STRING_H
#define STRING_H
#include<cstring>
#include<cstdlib>
namespace My {

	class String {
	private:

		char* body_;
		int size_ = 0;

		char* copy_(char* second)
		{
			char* c = new char[(strlen(second) * sizeof(char))];
			for (int i = 0; i < strlen(second); i++)
			{
				c[i] = second[i];
			}
			c[strlen(second)] = '\0';
			return c;
		}
	public:
		String() = default;
		String(const String& str) :body_(copy_(str.body_)), size_(str.size_) {};
		String(char* str) :body_(copy_(str)), size_(strlen(str)) {};
		String(const char* str) :body_(copy_((char*)str)), size_(strlen(str)) {};
		String(char c) { append(c); };

		void operator=(const String& str);
		String operator+(const String& str);
		void operator+=(const String& str);

		bool operator==(const String& str);
		bool operator!=(const String& str) { return !(operator==(str)); };
		bool operator<(const String& str);
		bool operator>(const String& str);

		char operator[](int indx)const { return body_[indx]; };
		char& operator[](int indx) { return body_[indx]; };

		int findStr(const String& substr, int indx);

		void append(char c);

		int size()const { return size_; };
		int size() { return size_; }
		bool empty() { return size_ == 0; };
		void resize(int newsize, char c = ' ');
		void clear() { size_ = 0; body_ = (char*)realloc(body_, sizeof(char)); body_[0] = '\0'; };

		auto getCharArr()->char* { return body_; };

	};

}
#endif