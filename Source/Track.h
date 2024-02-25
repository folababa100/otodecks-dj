#pragma once

#include <JuceHeader.h>

// ==============================================================================
/*
*/
#pragma once

#include "JuceHeader.h"
#include <string>

class Track
{
public:

    Track(String _title,
          String _length,
          String _path);

    String title;
    String length;
    String path;
};
