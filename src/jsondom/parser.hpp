#pragma once

#include <vector>

#include <utki/span.hpp>

namespace jsondom{

class parser{
	unsigned line = 0;

	enum class state{
		idle,
		object,
		array
	};

	std::vector<state> state_stack{state::idle};

	void parse_idle(utki::span<char>::const_iterator& i, utki::span<char>::const_iterator& e);
	void parse_object(utki::span<char>::const_iterator& i, utki::span<char>::const_iterator& e);
	void parse_array(utki::span<char>::const_iterator& i, utki::span<char>::const_iterator& e);

	std::vector<char> buf;
public:
	virtual ~parser()noexcept{}

	virtual void on_object_start() = 0;
	virtual void on_object_end() = 0;
	virtual void on_array_start() = 0;
	virtual void on_array_end() = 0;
	virtual void on_name_parsed(utki::span<const char> str) = 0;
	virtual void on_string_parsed(utki::span<const char> str) = 0;
	virtual void on_number_parsed(utki::span<const char> str) = 0;
	virtual void on_boolean_parsed(bool b) = 0;
	virtual void on_null_parsed() = 0;

	/**
	 * @brief feed UTF-8 data to parser.
	 * @param data - data to be fed to parser.
	 */
	void feed(utki::span<const char> data);
	
	/**
	 * @brief feed UTF-8 data to parser.
	 * @param data - data to be fed to parser.
	 */
	void feed(const utki::span<uint8_t> data){
		this->feed(utki::make_span(reinterpret_cast<const char*>(data.data()), data.size()));
	}
	
	/**
	 * @brief Parse the string.
	 * @param str - string to parse.
	 */
	void feed(const std::string& str){
		this->feed(utki::make_span(str.c_str(), str.length()));
	}
};

}
