#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
string getFileContents (std::ifstream&);            //Gets file contents
class Readfile
{
private:
    vector<string> filename;
public:
    Readfile();
    string getFileContents (std::ifstream& File);
    void printFile(int idx);
    void addFileName(string);
    void deleteFile(int idx);
};
#endif // READFILE_H