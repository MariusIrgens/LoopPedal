#include "DrumTemplates.h"

DrumTemplates::DrumTemplates() {

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

    // copy-paste and replace inside with HTML output
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


}

const std::vector<DrumTemplates::Template>& DrumTemplates::getAllTemplates() {
    return allTemplates;
}

const DrumTemplates::Template& DrumTemplates::getTemplateByIndex(size_t index) {
    if (index >= allTemplates.size())
    {
        // Handle the error appropriately, maybe throw an exception or return a default value
    }
    return allTemplates[index];
}