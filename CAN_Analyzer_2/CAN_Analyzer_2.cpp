#include <string>
#include <iostream>

#include "FileReader.h"

int test(int i); //declaration

int test(int i) { //definition
    return i;
}
int i;

int main()
{
    std::string file_path = "E:\\learning\\C++\\CAN_Analyzer\\test.bin";
    FileReader* fr = new FileReader();
    FILE_DATA file_data = fr->parse_log_file(file_path);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
