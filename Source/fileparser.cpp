#include "fileparser.h"

FileParser::FileParser()
{

}


StringVector FileParser::SplitString(const std::string &str, char delimiter)
{
    StringVector buffer;
    std::string word = "";

    for (auto x : str)
    {
        if (x == delimiter)
        {
            buffer.push_back(word);
            word="";
        }
        else {
            word += x;
        }
    }
    buffer.push_back(word);
    return buffer;
}

CIEVector FileParser::Read()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open a file");
    std::ifstream file(fileName.toStdString());
    CIEVector cieVector;

    if (file.is_open())
    {
        std::string line;
        if(!std::getline(file, line))
            return cieVector;

        while (std::getline(file, line))
        {
            auto strVec = SplitString(line, '\t');
            if(strVec.size()!=4) continue;
            CIE cieEntry;
            cieEntry.waveLength = stoi(strVec[0]);
            cieEntry.x = stof(strVec[1]);
            cieEntry.y = stof(strVec[2]);
            cieEntry.z = stof(strVec[3]);
            cieVector.push_back(cieEntry);
        }
        file.close();
    }

    return cieVector;
}
