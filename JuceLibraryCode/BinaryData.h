/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   dj_9_png;
    const int            dj_9_pngSize = 53131;

    extern const char*   dj_png;
    const int            dj_pngSize = 471715;

    extern const char*   folder_png;
    const int            folder_pngSize = 3404;

    extern const char*   info_png;
    const int            info_pngSize = 15493;

    extern const char*   pause_png;
    const int            pause_pngSize = 1270;

    extern const char*   play_png;
    const int            play_pngSize = 4671;

    extern const char*   save_jpg;
    const int            save_jpgSize = 4521;

    extern const char*   stop_png;
    const int            stop_pngSize = 8948;

    extern const char*   load_png;
    const int            load_pngSize = 8222;

    extern const char*   playlist_txt;
    const int            playlist_txtSize = 424;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 10;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
