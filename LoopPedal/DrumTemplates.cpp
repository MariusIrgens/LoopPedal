#include "DrumTemplates.h"

DrumTemplates::DrumTemplates() {

    // BEAT TEMPLATES
    // copy-paste and replace inside with HTML output

    // Construct and add basicBeat
    Template beat =
    {
        .name = "basicBeat",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {},
        .openHihatVariable = {3,3,3,11,11,11},
        .closedHihatAlways = {1,5,9,13},
        .closedHihatVariable = {3,3,3,4,7,7,7,8,11,11,11,12,15,15,15,16},
        .snareAlways = {5,13},
        .snareVariable = {4,4,16,16},
        .kickAlways = {1},
        .kickVariable = {3,3,7,7,9,9,9,11,11,11,15,15},
    };
    allTemplates.push_back(beat);

    // Construct and add fiveFourBeat
    beat =
    {
        .name = "fiveFourBeat",
        .patternLength = 20,
        .maxArraySize = 60,
        .openHihatAlways = {},
        .openHihatVariable = {3,3,3,7,7,7,11,11,11,15,15,15,19,19,19},
        .closedHihatAlways = {1,5,9,13,17},
        .closedHihatVariable = {3,3,3,7,7,7,11,11,11,15,15,15,19,19,19},
        .snareAlways = {7,17},
        .snareVariable = {3,3,11,11,15,15},
        .kickAlways = {1,13},
        .kickVariable = {3,3,5,7,7,9,11,11,15,15,17,19,19},
    };
    allTemplates.push_back(beat);



    // TOM FILLS
    // Always 2 beats long, for simplicity (8 steps)
    TomFill fill = 
    {
        .highTom = {1, 2, 4},
        .lowTom = {5, 7}
    };
    allTomFills.push_back(fill);

    fill =
    {
        .highTom = {1, 4},
        .lowTom = {5, 7}
    };
    allTomFills.push_back(fill);

    fill =
    {
        .highTom = {1, 2, 3, 4},
        .lowTom = {5, 6, 7, 8}
    };
    allTomFills.push_back(fill);

    fill =
    {
        .highTom = {2, 4},
        .lowTom = {5, 7, 8}
    };
    allTomFills.push_back(fill);

    fill =
    {
        .highTom = {3, 4},
        .lowTom = {7, 8}
    };
    allTomFills.push_back(fill);

    fill =
    {
        .highTom = {1, 3},
        .lowTom = {2, 4, 6}
    };
    allTomFills.push_back(fill);

    fill =
    {
        .highTom = {1, 2},
        .lowTom = {4, 5}
    };
    allTomFills.push_back(fill);
}

const std::vector<DrumTemplates::Template>& DrumTemplates::getAllTemplates() {
    return allTemplates;
}

const DrumTemplates::Template& DrumTemplates::getTemplateByIndex(size_t index) {
    if (index >= allTemplates.size())
    {
        index = 0;
    }
    return allTemplates[index];
}

const DrumTemplates::TomFill& DrumTemplates::getTomFillByIndex(size_t index) {
    if (index >= allTomFills.size())
    {
        index = 0;
    }
    return allTomFills[index];
}

int DrumTemplates::getMaxTemplateIndex()
{
    return allTemplates.size() - 1;
}

int DrumTemplates::getMaxTomFillIndex()
{
    return allTomFills.size() - 1;
}