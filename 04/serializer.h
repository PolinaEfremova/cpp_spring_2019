#pragma once
#include<iostream>
#include<string>

enum class Error
{
	NoError,
	CorruptedArchive
};

class Serializer
{
public:
	explicit Serializer(std::ostream& out)
		: out_(out){}
	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}
	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}

private:
	static constexpr char Separator = ' ';
	std::ostream& out_;
	template <class T, class... ArgsT>
	Error process(T&& value, ArgsT&&... args)
	{
		if (process(std::forward<T>(value)) == Error::CorruptedArchive) {
			return Error::CorruptedArchive;
		}
		return process(std::forward<ArgsT>(args)...);
	}
	Error process(uint64_t value)
	{
		out_ << value << Separator;
		return Error::NoError;
	}
	Error process(bool value)
	{
		out_ << (value ? "true" : "false") << Separator;
		return Error::NoError;
	}
};

class Deserializer
{
public:
	explicit Deserializer(std::istream& in)
		: in_(in){}
	template <class T>
	Error load(T& object)
	{
		return object.serialize(*this);
	}
	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}
private:
	std::istream& in_;
	template <class T, class ...ArgsT>
	Error process(T&& value, ArgsT&&... args)
	{
		if (process(std::forward<T>(value)) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		else return process(std::forward<ArgsT>(args)...);
	}
	Error process(bool& value)
	{
		std::string text;
		in_ >> text;
		if (text == "true")
			value = true;
		else if (text == "false")
			value = false;
		else {
			return Error::CorruptedArchive;
		}
		return Error::NoError;
	}
	Error process(uint64_t& value)
	{
		std::string text;
		in_ >> text;
		value = 0;
		for (size_t i = 0; i < text.size(); i++)
			if (isdigit(text[i]))
				value = value * 10 + text[i] - '0';
			else 
				return Error::CorruptedArchive;
		return Error::NoError;
	}
};
