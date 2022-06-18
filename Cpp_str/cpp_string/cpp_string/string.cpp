#pragma once
#include "str.h"

void My::String::operator=(const String& str)
{
	body_ = (char*)realloc(body_, str.size() * sizeof(char));
	for (int i = 0; i < str.size(); i++)
	{
		body_[i] = str[i];
	}
	body_[str.size()] = '\0';
	size_ = str.size_;
}

My::String My::String::operator+(const String& str)
{
	auto body = new char[(size() + str.size()) * sizeof(char)];
	for (int i = 0; i < size(); i++)
	{
		body[i] = body_[i];
	}
	for (int i = size(); i < size() + str.size(); i++)
	{
		body[i] = str[i - size()];
	}
	body[size() + str.size()] = '\0';
	String ans;
	ans.body_ = body;
	ans.size_ = strlen(body);
	return ans;
}

void My::String::operator+=(const String& str)
{
	*this = *this + str;
}

bool My::String::operator==(const String& str)
{
	if (str.size() == size()) {
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] != body_[i])return false;
		}
		return true;
	}
	return false;
}

bool My::String::operator<(const String& str)
{
	if (str.size() == size()) {
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] > body_[i])return false;
		}
		return true;
	}

	if (size() < str.size())
		return true;
	return false;
}

bool My::String::operator>(const String& str)
{
	if (!operator<(str) && !operator==(str))
		return true;
	return false;
}

int My::String::findStr(const String& substr, int indx)
{
	for (int i = indx; i < size() - substr.size() + 1; i++)
	{
		bool f = true;
		for (int j = 0; j < substr.size(); j++)
		{
			if (body_[i] != substr[j])
			{
				f = false;
				break;
			}
		}
		if (f)
		{
			return i;
		}
	}
	return -1;
}

void My::String::append(char c)
{
	size_++;
	body_ = (char*)realloc(body_, size_ * sizeof(char));

	body_[size() - 1] = c;
	body_[size()] = '\0';
}

void My::String::resize(int newsize, char c)
{
	body_ = (char*)realloc(body_, newsize * sizeof(char));
	for (int i = size(); i < newsize; i++)
	{
		body_[i] = c;
	}
	body_[newsize] = '\0';
	size_ = newsize;
}
