#include <JuceHeader.h>
#include "LibraryComponent.h"
#include "Initiallise.h"

//==============================================================================
LibraryComponent::LibraryComponent(AudioFormatManager& _formatManager,
    DeckGUI* deckGUI1,
    DeckGUI* deckGUI2)
    : formatManager(_formatManager),
    leftDeck(deckGUI1),
    rightDeck(deckGUI2)
{
    if (playlistFileExists())
    {
        std::string playlistFilePath = getPlaylistFilePath();
        tracksToDisplay = fileProcessor.loadData(playlistFilePath);
        allTracks = fileProcessor.loadData(playlistFilePath);
        tableComponent.updateContent();
    }

    // Image button
    auto insertImage = ImageCache::getFromMemory(BinaryData::folder_png, BinaryData::folder_pngSize);
    insertButton.setImages(true, true, true, insertImage, 1, Colours::transparentWhite, Image(nullptr), 1, Colours::transparentWhite, Image(nullptr), 1, Colours::transparentBlack);
    Initiallise::buttonOptions(this, &insertButton, this, false, "Insert track to library", 0.75f);

    // Label
    Initiallise::labelOptions(this, &label, "Playlist", dontSendNotification, Justification::horizontallyCentred, 14.0f, label.textColourId, Colours::violet);
    label.toBack();

    // Table component
    tableComponent.getHeader().addColumn("L", 1, 50, TableHeaderComponent::defaultFlags);
    tableComponent.getHeader().addColumn("R", 2, 50, TableHeaderComponent::defaultFlags);
    tableComponent.getHeader().addColumn("Track title", 3, 300, TableHeaderComponent::defaultFlags);
    tableComponent.getHeader().addColumn("Duration", 4, 70, TableHeaderComponent::defaultFlags);
    tableComponent.getHeader().addColumn("Delete", 5, 50, TableHeaderComponent::defaultFlags);
    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);

    insertButton.addListener(this);

    // Search Bar
    addAndMakeVisible(searchBar);
    searchBar.addListener(this);
    searchBar.setTextToShowWhenEmpty("Search Your Added Tracks Here...", Colour::fromRGBA(201, 0, 255, 255));
}

LibraryComponent::~LibraryComponent()
{
}

void LibraryComponent::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGBA(33, 0, 75, 255));
}

void LibraryComponent::resized()
{
    double rowH = getHeight() / 8;
    double colW = getWidth() / 14;
    tableComponent.setBounds(0, rowH, getWidth(), getHeight());
    tableComponent.setColour(ListBox::backgroundColourId, Colour::fromRGBA(33, 0, 75, 255));
    tableComponent.setColour(ListBox::outlineColourId, Colour::fromRGBA(33, 0, 0, 255));
    label.setBounds(colW * 5, rowH * 0.2, colW * 4, rowH * 0.6);
    searchBar.setBounds(rowH * 0.1, rowH * 0.1, colW * 6, rowH * 0.9);
    searchBar.setColour(TextEditor::backgroundColourId, Colour::fromRGBA(33, 0, 75, 255));
    insertButton.setBounds(colW * 13, rowH * 0.2, colW, rowH * 0.6);
}

int LibraryComponent::getNumRows()
{
    return tracksToDisplay.size();
}

void LibraryComponent::paintRowBackground(Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    // Highlight selected row
    if (rowIsSelected)
    {
        g.fillAll(Colour::fromRGBA(102, 94, 199, 255));
    }
    else if (rowNumber % 2)
    {
        g.fillAll(Colour::fromRGBA(103, 0, 232, 255));
    }
}

void LibraryComponent::paintCell(Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    g.setColour(getLookAndFeel().findColour(ListBox::textColourId));
    g.setFont(14.0f);

    if (rowNumber < getNumRows())
    {
        if (columnId == 3)
        {
            g.drawText(tracksToDisplay[rowNumber].title,
                5, 0,
                width - 4, height,
                Justification::centredLeft,
                true);
        }
        if (columnId == 4)
        {
            g.drawText(tracksToDisplay[rowNumber].length,
                5, 0,
                width - 4, height,
                Justification::centredLeft,
                true);
        }
    }
    g.setColour(getLookAndFeel().findColour(ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

Component* LibraryComponent::refreshComponentForCell(int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate)
{
    if (columnId == 1)
    {
        TextButton* loadLBtn = (TextButton*)existingComponentToUpdate;

        if (loadLBtn == 0)
        {
            loadLBtn = new TextButton();
        }

        String id{ rowNumber };
        loadLBtn->setComponentID(id);
        loadLBtn->setButtonText("<");
        loadLBtn->setMouseCursor(MouseCursor::PointingHandCursor);
        loadLBtn->setColour(TextButton::ColourIds::buttonColourId, Colours::cyan);
        loadLBtn->setColour(TextButton::ColourIds::textColourOffId, Colours::fuchsia);
        loadLBtn->addListener(this);

        return loadLBtn;
    }

    if (columnId == 2)
    {
        TextButton* loadRBtn = (TextButton*)existingComponentToUpdate;

        if (loadRBtn == 0)
        {
            loadRBtn = new TextButton();
        }

        String id{ "0." + std::to_string(rowNumber) };
        loadRBtn->setComponentID(id);
        loadRBtn->setButtonText(">");
        loadRBtn->setMouseCursor(MouseCursor::PointingHandCursor);
        loadRBtn->setColour(TextButton::ColourIds::buttonColourId, Colours::fuchsia);
        loadRBtn->setColour(TextButton::ColourIds::textColourOffId, Colours::cyan);
        loadRBtn->addListener(this);

        return loadRBtn;
    }

    if (columnId == 5)
    {
        TextButton* deleteTrackBtn = (TextButton*)existingComponentToUpdate;

        if (deleteTrackBtn == 0)
        {
            deleteTrackBtn = new TextButton();
        }

        String id{ "X" + std::to_string(rowNumber) };
        deleteTrackBtn->setComponentID(id);
        deleteTrackBtn->setButtonText("X");
        deleteTrackBtn->setMouseCursor(MouseCursor::PointingHandCursor);
        deleteTrackBtn->setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        deleteTrackBtn->setColour(TextButton::ColourIds::textColourOffId, Colours::red);
        deleteTrackBtn->addListener(this);

        return deleteTrackBtn;
    }
    else
    {
        return 0;
    }
}

void LibraryComponent::buttonClicked(Button* button)
{
    if (button == &insertButton)
    {
        FileChooser chooser{ "Add a music file..." };
        if (chooser.browseForMultipleFilesToOpen())
        {
            for (const auto& result : chooser.getResults())
            {
                File songFile{ result };
                String songTitle = leftDeck->getSongTitle(songFile);
                String songLength = rightDeck->getSongDuration(songFile);
                String songPath = URL{ songFile }.toString(false);

                if (playlistFileExists())
                {
                    // Append track data to playlist file & created track to tracksToDisplay vector
                    if (songIsDuplicate(songTitle) == false)
                    {
                        Track trackToAdd{ songTitle, songLength, songPath };
                        fileProcessor.appendData(songTitle, songLength, songPath);
                        tracksToDisplay.push_back(trackToAdd);
                        allTracks.push_back(trackToAdd);
                    }
                }
                else
                {
                    // Create file to store tracksToDisplay
                    fileProcessor.createPlaylistFile("playlist.txt");

                    // Append track data to playlist file & created track to tracksToDisplay vector
                    Track trackToAdd{ songTitle, songLength, songPath };
                    fileProcessor.appendData(songTitle, songLength, songPath);
                    tracksToDisplay.push_back(trackToAdd);
                    allTracks.push_back(trackToAdd);
                }

                tableComponent.updateContent();
            }
        }
    }
    else
    {
        std::string componentID = button->getComponentID().toStdString();

        if (componentID.find('.') != std::string::npos) // since not = no pos, found
        {
            int start = componentID.find_first_of('.', 0);
            int rightBtnId = std::stoi(componentID.substr(start + 1));
            URL pathURL{ tracksToDisplay[rightBtnId].path };
            rightDeck->loadTrack(tracksToDisplay[rightBtnId].title,
                tracksToDisplay[rightBtnId].length,
                pathURL);
        }
        if (componentID.find('X') != std::string::npos)
        {
            int start = componentID.find_first_of('X', 0);
            int deleteTrackBtnId = std::stoi(componentID.substr(start + 1));
            tracksToDisplay.erase(tracksToDisplay.begin() + deleteTrackBtnId);
            allTracks.erase(allTracks.begin() + deleteTrackBtnId);
            fileProcessor.deleteData(deleteTrackBtnId);
            tableComponent.updateContent();
        }
        else if (componentID.find('.') == std::string::npos &&
            componentID.find('X') == std::string::npos)
        {
            int leftBtnId = std::stoi(componentID);
            URL pathURL{ tracksToDisplay[leftBtnId].path };
            leftDeck->loadTrack(tracksToDisplay[leftBtnId].title,
                tracksToDisplay[leftBtnId].length,
                pathURL);
        }
    }
}

void LibraryComponent::textEditorTextChanged(TextEditor& editor)
{
    if (editor.isEmpty() == false)
    {
        std::vector<Track> results;
        String keyword = editor.getText();

        for (unsigned int i = 0; i < allTracks.size(); ++i)
        {
            String songTitle{ allTracks[i].title };
            songTitle = songTitle.toLowerCase();
            keyword = keyword.toLowerCase();

            if (songTitle.startsWith(keyword))
            {
                results.push_back(allTracks[i]);
            }
        }

        tracksToDisplay = results;
        tableComponent.updateContent();
    }
    else
    {
        tracksToDisplay = allTracks;
        tableComponent.updateContent();
    }
}

bool LibraryComponent::isInterestedInFileDrag(const StringArray& files)
{
    return true;
}

void LibraryComponent::filesDropped(const StringArray& files, int x, int y)
{
    for (const auto& file : files)
    {
        File songFile{ file };
        String songTitle = leftDeck->getSongTitle(songFile);
        String songLength = rightDeck->getSongDuration(songFile);
        String songPath = URL{ songFile }.toString(false);

        if (playlistFileExists())
        {
            // Append track data to playlist file & created track to tracksToDisplay vector
            unsigned int songID = allTracks.size();

            if (songIsDuplicate(songTitle) == false)
            {
                Track trackToAdd{ songTitle, songLength, songPath };
                fileProcessor.appendData(songTitle, songLength, songPath);
                tracksToDisplay.push_back(trackToAdd);
                allTracks.push_back(trackToAdd);
            }
        }
        else
        {
            // Create file to store tracksToDisplay
            fileProcessor.createPlaylistFile("playlist.txt");

            // Append track data to playlist file & created track to tracksToDisplay vector
            unsigned int songID = allTracks.size();
            Track trackToAdd{ songTitle, songLength, songPath };
            fileProcessor.appendData(songTitle, songLength, songPath);
            tracksToDisplay.push_back(trackToAdd);
            allTracks.push_back(trackToAdd);
        }

        tableComponent.updateContent();
    }
}

bool LibraryComponent::playlistFileExists()
{
    auto dir = File::getCurrentWorkingDirectory();

    int numTries = 0;

    while (!dir.getChildFile("Resources").exists() && numTries++ < 15)
    {
        dir = dir.getParentDirectory();
    }

    auto tableFile = dir.getChildFile("Resources").getChildFile("playlist.txt");

    if (tableFile.exists())
    {
        return true;
    }

    return false;
}

std::string LibraryComponent::getPlaylistFilePath()
{
    auto dir = File::getCurrentWorkingDirectory();
    int numTries = 0;

    while (!dir.getChildFile("Resources").exists() && numTries++ < 15)
    {
        dir = dir.getParentDirectory();
    }

    std::string resourcesDir = (dir.getChildFile("Resources").getFullPathName()).toStdString();
    std::string filePath = resourcesDir + "/playlist.txt";

    return filePath;
}

bool LibraryComponent::songIsDuplicate(String songTitle)
{
    for (const auto& song : allTracks)
    {
        if (song.title == songTitle)
        {
            return true;
        }
    }

    return false;
}
