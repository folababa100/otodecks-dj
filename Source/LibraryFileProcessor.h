#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Track.h"

class LibraryFileProcessor
{
public:

    LibraryFileProcessor();
    ~LibraryFileProcessor();

    // Create playlist file and appends the first track data to it
    void createPlaylistFile(std::string fileName);

    // Separate each line in the playlist file into tokens/parts based on the sent separator
    std::vector<Track> loadData(std::string filePath);

    // Append track title, length & file path to playlist file
    void appendData(String title, String length, String path);

    // Delete track title, length & file path from playlist file as indicated by the line number
    void deleteData(int lineNumber);

private:

    // Separate each line in the playlist file into tokens/parts
    static std::vector<std::string> tokenise(std::string line, char separator);

    // Convert vector of token strings to Track data structure
    static Track stringsToTrack(std::vector<std::string> tokens);

    std::ofstream mStream;
    std::string playlistFilePath;
};
