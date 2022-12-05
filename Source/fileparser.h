#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <string>
#include <vector>
#include <QFileDialog>
#include <iostream>
#include <fstream>

#include "cie.h"

typedef std::vector<std::string> StringVector;
typedef std::vector<CIE> CIEVector;


class FileParser
{
public:
    FileParser();
    CIEVector Read();

private:
    StringVector SplitString(const std::string &str, char delimiter);

};

#endif // FILEPARSER_H
