#include "Readfile.h"
Readfile::Readfile() {}
string Readfile::getFileContents (std::ifstream& File) {
    std::string Lines = "";        //All lines
    
    if (File)                      //Check if everything is good
    {
	while (File.good ())
	{
	    std::string TempLine;                  //Temp line
	    std::getline (File , TempLine);        //Get temp line
	    TempLine += "\n";                      //Add newline character
	    
	    Lines += TempLine;                     //Add newline
	}
	return Lines;
    }
    else                           //Return error
    {
	//return "ERROR File does not exist.";
    return " ";
    }
}

void Readfile::printFile(int idx) {
    string filepath = "Image/" + filename[idx];
    std::ifstream Reader (filepath);             //Open file

    std::string Art = getFileContents (Reader);       //Get file
    
    std::cout << Art << std::endl;               //Print it to the screen

    Reader.close ();                           //Close file

}

void Readfile::addFileName(string newfilename) {
    filename.push_back(newfilename);
}

void Readfile::deleteFile(int idx){
    filename.erase(filename.begin() + idx);
}