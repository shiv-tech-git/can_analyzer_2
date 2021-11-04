#include "CMA_State.h"
#include "CMA_Utils.h"

CMA_State CMA_State::_instance;

CMA_State::CMA_State() {}

CMA_State& CMA_State::instance() {
	return _instance;
}

void CMA_State::set_current_directory(std::wstring dir) {
	currend_directory = dir;
}

void CMA_State::set_current_file_absolute_path(std::wstring abs_path) {
	current_file_absolute_path = abs_path;
}

void CMA_State::set_current_file_name(std::wstring f_name) {
	current_file_name = f_name;
}

std::wstring CMA_State::get_current_file_absolute_path() {
	if (current_file_absolute_path != L"")
		return current_file_absolute_path;

	if (currend_directory != L"" && current_file_name != L"")
		return currend_directory + L"\\" + current_file_name;

	return L"";
}

std::wstring CMA_State::get_current_file_name() {
	if (current_file_name != L"")
		return current_file_name;
	if (current_file_absolute_path != L"") {
		return get_file_name_from_absolute_path(current_file_absolute_path);
	}
	return L"";
}

std::wstring CMA_State::get_current_directory() {
	return currend_directory;
}