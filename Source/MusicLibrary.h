#pragma once

#include <JuceHeader.h>
#include "Track.h"
#include "DeckGUI.h"
#include "LibraryFileProcessor.h"
#include <vector>
#include <string>

//==============================================================================
/*
*/
class MusicLibrary : public Component,
                         public TableListBoxModel,
                         public Button::Listener,
                         public TextEditor::Listener,
                         public FileDragAndDropTarget
{
    public:

        MusicLibrary(AudioFormatManager & _formatManager, DeckGUI * deckGUI1, DeckGUI * deckGUI2);
        ~MusicLibrary() override;

        void paint(Graphics& g) override;
        void resized() override;

        // Number of rows
        int getNumRows() override;

        // Table background
        void paintRowBackground(Graphics& g,
                                int rowNumber,
                                int width,
                                int height,
                                bool rowIsSelected) override;
        // Table cells
        void paintCell(Graphics& g,
                       int rowNumber,
                       int columnId,
                       int width,
                       int height,
                       bool rowIsSelected) override;

        // Create, update custom component into cell.
        Component* refreshComponentForCell(int rowNumber,
                                           int columnId,
                                           bool isRowSelected,
                                           Component* existingComponentToUpdate) override;
        // Implement Button::Listener,pointer to the button that is clicked.
        void buttonClicked(Button* button) override;

        // When user search
        void textEditorTextChanged(TextEditor& editor);

        bool isInterestedInFileDrag(const StringArray& files) override;
        void filesDropped(const StringArray& files, int x, int y) override;

    private:
        // Check if there is already an existing music library database
        static bool playlistFileExists();

        // Get file path from the music library database
        static std::string getPlaylistFilePath();

        // Check song title against all titles in the music library prevent duplicate, inputing title as a juce string.
        bool songIsDuplicate(String songTitle);

        Label label;
        ImageButton insertButton;
        TextEditor searchBar { "Search", 0 };
        std::vector<Track> tracksToDisplay;
        std::vector<Track> allTracks;

        TableListBox tableComponent;
        AudioFormatManager& formatManager;

        DJAudioPlayer* player;
        DeckGUI* leftDeck;
        DeckGUI* rightDeck;
        LibraryFileProcessor fileProcessor;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MusicLibrary)
};
