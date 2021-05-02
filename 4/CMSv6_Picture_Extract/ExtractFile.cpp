#include "stdafx.h"
#include <string>
#include "dirent.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <tchar.h>
#include "ExtractFile.h"
#include "SystemFunctions.h"

using namespace std;

//--------------------------------------------------------------------------------------------------//
//--------------------------------CREATE A VECTOR OF INDEX FILES------------------------------------//
//--------------------------------**Programmer: C.A Torino**----------------------------------------//
//--------------------------------------------------------------------------------------------------//

void ExtractFile::GetNewFilenames()
{
    ofstream log;
    log.open("CMSv6_Picture_Extract_LOGS\\logs" + Sys.currentDateTime() + ".txt", ios::app);
    if (log.fail())
    {
        log << Sys.current_time() << "Failed to open log file. Aborting!" << endl;
        exit(1);
    }
    log << Sys.current_time() << "**------------------------**" << endl;
    log << Sys.current_time() << "**START OF PROGRAM v1.0.12**" << endl;
	log << Sys.current_time() << "**Modified for use with Visual Studio 2019**" << endl;
	log << Sys.current_time() << "**Programmer: C.A Torino**" << endl;
    cout << Sys.current_time() << "**START OF PROGRAM v1.0.12**" << endl;
	cout << Sys.current_time() << "**Modified for use with Visual Studio 2019**" << endl;
	cout << Sys.current_time() << "**Programmer: C.A Torino**" << endl;
    log << Sys.current_time() << "Beginning to search for more files:" << endl;
    cout << Sys.current_time() << "Beginning to search for more files:" << endl;

    // Needs dirent.h --> For searching through the dir
    DIR *dir;
    struct dirent *ent;

    // Clear the vector of index files
    indexfiles.clear();

    if ((dir = opendir (Sys.picfiledir().c_str())) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            NewFile = ent->d_name;
            // Get the extension (picfile or index)
            PosIndex = NewFile.find_last_of('.');
            ext = NewFile.substr(PosIndex, -1);

            if (ext == ".index")
            {
                int completed = Sys.get_completed(NewFile);
                if (completed == 0)
                {
                    cout << Sys.current_time() << NewFile << endl;
                    log << Sys.current_time() << NewFile << endl;
                    // Get just the date part of the filename
                    int filedatepos = NewFile.find_first_of('.');
                    string filedate = NewFile.substr(0, filedatepos);
                    indexfiles.push_back(filedate);
                    Sys.set_lastfile(NewFile);
                }
            }
        }
    }
    else
    {
        log << Sys.current_time() << "Could not open directory picfiles. Aborting!" << endl;
        log << Sys.picfiledir() << endl;
        exit(1);
    }

    delete ent;

    closedir (dir);


    log.close();
}

//--------------------------------------------------------------------------------------------------//
//------------------------------------READ THE INDEX FILE-------------------------------------------//
//--------------------------------------------------------------------------------------------------//

void ExtractFile::CheckForExtractFile(const string fileP)
{
    ifstream infile;
    ofstream log;

    log.open("CMSv6_Picture_Extract_LOGS\\logs" + Sys.currentDateTime() + ".txt", ios::app);
    if (log.fail())
    {
        log << Sys.current_time() << "Failed to open log file. Aborting!" << endl;
        exit(1);
    }

    string fullfilename = Sys.picfiledir() + fileP + ".picfile.index";
    cout << Sys.current_time() << "Reading " << fileP << ".picfile.index" << endl;
    log << Sys.current_time() << "Reading " << fileP << ".picfile.index" << endl;

    infile.open(fullfilename.c_str(), ios::binary | ios::in);

    if (infile.fail())
    {
        log << Sys.current_time() << "Failed to open " << fileP << ".picfile.index. Aborting!" << endl;
		log << Sys.current_time() << "Failed to open " << fullfilename << fileP << ".picfile.index. Aborting!" << endl;
		log << Sys.current_time() << "Did you forget to add the \\ at the end of the .ini path?" << endl;
		cout << Sys.current_time() << "Did you forget to add the \\ at the end of the .ini path?" << endl;
		cout << Sys.current_time() << "Failed to open " << fileP << ".picfile.index. Aborting!" << endl;
		cout << Sys.current_time() << "Failed to open " << fullfilename << fileP << ".picfile.index. Aborting!" << endl;
		Sleep(10000);
        exit(1);
    }
    log << Sys.current_time() << "Opened " << fileP << ".picfile.index" << endl;

    long offVal = Sys.get_counter(fileP + ".picfile.index");
    counter = 0;
    IndexBlockVector.clear();
    // This while loop reads from the last index block to the end of the file
    while (!infile.eof())
    {
        infile.read((char*)&IndexBlock, sizeof(IndexBlock));

        if (counter >= offVal)
        {
            // Create memory space for newly created object in the vector
            IndexBlockVector.push_back(IndexBlock);
        }
        counter++;
    }
    if (offVal > counter)
    {
        cout << Sys.current_time() << fileP + ".picfile.index file count specified is out of range. Aborting!" << endl;
        log << Sys.current_time() << fileP + ".picfile.index file count specified is out of range. Aborting!" << endl;
        exit(1);
    }
    log << Sys.current_time() << "Index vector size: " << counter << endl;
    cout << Sys.current_time() << "Index vector size: " << counter << endl;
    infile.close();
    cout << Sys.current_time() << "Closing " << fileP << ".picfile.index" << endl;
    log << Sys.current_time() << "Closing " << fileP << ".picfile.index" << endl;
    if (counter == offVal)
    {
        log << Sys.current_time() << "This is the end of the file" << endl;
        cout << Sys.current_time() << "This is the end of the file" << endl;

        // Set file to done in ini file (all except last file)
        if ((fileP + ".picfile.index") != Sys.get_lastfile())
            Sys.set_completed(1, fileP + ".picfile.index");
    }
    else
    {
        picfile_offset = IndexBlockVector.at(0).get_fileoffset();

        // The file has been appended to, therefore it is not completed
        Sys.set_completed(0, fileP + ".picfile.index");

        // Start exporting Jpg's using the offset and filelen
        // specified in index file
        SaveJpgs(fileP);
    }

    log.close();
}

//--------------------------------------------------------------------------------------------------//
//---------------------------------------SAVE THE JPGS!---------------------------------------------//
//---Take the offset and file lengths from the index file and use it to create a separate jpg file--//
//--------------------------------------------------------------------------------------------------//

void ExtractFile::SaveJpgs(const string fileP)
{
    ifstream picfile;
    ofstream jpg_file;
    ofstream log;
    log.open("CMSv6_Picture_Extract_LOGS\\logs" + Sys.currentDateTime() + ".txt", ios::app);
    if (log.fail())
    {
        log << Sys.current_time() << "Failed to open log file. Aborting!" << endl;
        exit(1);
    }

    string fullfilename = Sys.picfiledir() + fileP + ".picfile";
    cout << Sys.current_time() << "Reading " << fileP << ".picfile" << endl;
    log << Sys.current_time() << "Reading " << fileP << ".picfile" << endl;

    // Get the previous turns file count
    int oldfilecount = Sys.get_counter(fileP + ".picfile.index");
    log << Sys.current_time() << "Initial JPG: #" << oldfilecount << endl;
    cout << Sys.current_time() << "Initial JPG: #" << oldfilecount << endl;

    // using details from the index file we now open the picfile
    picfile.open(fullfilename.c_str(), ios::binary | ios::out);
    if (picfile.fail())
    {
        log << Sys.current_time() << "Failed to open " << fileP << ".picfile! Aborting!" << endl;
        exit(1);
    }

    // Proceed to the picfile's offset
    picfile.seekg(picfile_offset, ios::beg);
    unsigned int i=0;

    while (i < IndexBlockVector.size())
    {
        // Now read a block of the picfile using the filelen specified in index file
        char * memblock = new char [IndexBlockVector.at(i).get_filelen()];
        picfile.read(memblock, IndexBlockVector.at(i).get_filelen());

        // Create a JPG file to write to
        IndexBlockVector.at(i).create_jpgfile(jpgfilename);
        // Open JPG file
        jpg_file.open(jpgfilename.c_str(), ios::binary | ios::out);
        if (jpg_file.fail())
        {
            log << Sys.current_time() << "Failed to create " << jpgfilename << "! Aborting!" << endl;
            exit(1);
        }

        // Write memblock to newly created JPG file
        jpg_file.write(memblock, IndexBlockVector.at(i).get_filelen());
        if (! jpg_file.write(memblock, IndexBlockVector.at(i).get_filelen()))
        {
            log << Sys.current_time() << "Cannot write to " << jpgfilename << ". Aborting!" << endl;
            exit(1);
        }

        jpg_file.close();
        // Every 100 records update the ini file
        if (i % 100 == 0)
        {
            Sys.set_counter(oldfilecount + i, fileP + ".picfile.index");
        }
        i++;
        cout << '\r' << oldfilecount+i;

        delete [] memblock;
    }
    Sys.set_counter(oldfilecount + i, fileP + ".picfile.index");
    cout << endl;
    log << Sys.current_time() << "End JPG: #" << oldfilecount+i << endl;
    cout << Sys.current_time() << "End JPG: #" << oldfilecount+i << endl;
    cout << Sys.current_time() << "Closing " << fileP << ".picfile" << endl;
    log << Sys.current_time() << "Closing " << fileP << ".picfile" << endl;
    log.close();
    picfile.close();
}

//--------------------------------------------------------------------------------------------------//
//------------------------------RETURN THE VECTOR OF INDEX FILES------------------------------------//
//--------------------------------------------------------------------------------------------------//

vector<string> ExtractFile::GetVectors()
{
    return indexfiles;
}


