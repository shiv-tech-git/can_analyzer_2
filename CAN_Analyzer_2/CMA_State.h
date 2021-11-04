#pragma once

#include <string>

class CMA_State {

public:
	static CMA_State& instance();

	void set_current_directory(std::wstring);
	void set_current_file_name(std::wstring);
	void set_current_file_absolute_path(std::wstring);
	std::wstring get_current_file_absolute_path();
	std::wstring get_current_file_name();
	std::wstring get_current_directory();

private:
	CMA_State();

	static CMA_State _instance;

	std::wstring currend_directory;
	std::wstring current_file_name;
	std::wstring current_file_absolute_path;
};
