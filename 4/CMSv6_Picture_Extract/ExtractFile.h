#ifndef EXTRACTFILE_H
#define EXTRACTFILE_H
#include <string>
#include <vector>
#include "IndexFileStructure.h"
#include "SystemFunctions.h"
using namespace std;

class ExtractFile
{
public:
    // Reads index file and extract the JPGs using that info
    void CheckForExtractFile(const string fileP);
    // Searches for index files that are not finished yet
    void GetNewFilenames();
    // returns a vector of index files
    vector<string> GetVectors();

private:
    // Takes the info from index file and creates individual JPGs
    void SaveJpgs(const string fileP);
    // Different file paths
    vector<string> indexfiles;
    string jpgfilename;
    // vector of the index blocks
    vector<StoreFileIndex> IndexBlockVector;
    // object of StoreFileIndex
    StoreFileIndex IndexBlock;
    SystemFunctions Sys;
    // For searching for new files
    int PosIndex, FileNameDatePos;
    string ext, NewFile;
    // Used for counting index blocks
    long counter;
    // Where to start reading in picfile
    long picfile_offset;

};

#endif // EXTRACTFILE_H
