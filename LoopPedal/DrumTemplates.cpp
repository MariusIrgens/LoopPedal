#include "DrumTemplates.h"

DrumTemplates::DrumTemplates() {

    // BEAT TEMPLATES
    // copy-paste and replace inside with HTML output

    // 4/4

    // 0
    Template beat =
    {
        .name = "pop1",
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

    // 1
    beat =
    {
        .name = "pop2",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {},
        .openHihatVariable = {3,3,3,7,7,7,11,11,11,15,15,15},
        .closedHihatAlways = {1,5,9,13},
        .closedHihatVariable = {3,3,3,4,7,7,7,8,11,11,11,12,15,15,15,16},
        .snareAlways = {5,13},
        .snareVariable = {4,4,7,7,7,11,11,11,16,16},
        .kickAlways = {1},
        .kickVariable = {3,3,7,7,9,9,9,11,11,11,15,15},
    };
    allTemplates.push_back(beat);

    // 2
    beat =
    {
        .name = "bossanova",
        .patternLength = 32,
        .maxArraySize = 96,
        .openHihatAlways = {1,9,17,25},
        .openHihatVariable = {3,5,5,5,7,11,13,13,13,15,19,21,21,21,23,27,29,29,29,31},
        .closedHihatAlways = {},
        .closedHihatVariable = {1,1,2,2,3,3,3,4,4,5,5,6,6,7,7,7,8,8,9,9,10,10,11,11,11,12,12,13,13,14,14,15,15,15,16,16,17,17,18,18,19,19,19,20,20,21,21,22,22,23,23,23,24,24,25,25,26,26,27,27,27,28,28,29,29,30,30,31,31,31,32,32},
        .snareAlways = {7,13,21,27},
        .snareVariable = {1,1,1,5,5,11,11,19,19,31,31},
        .kickAlways = {1,9,17,25},
        .kickVariable = {7,7,7,13,15,15,15,23,23,23,31,31,31},
        .closedHihatBusyness = 0.90,
        .maxBPM = 150,
        .minBPM = 120,
    };
    allTemplates.push_back(beat);

    // 3
    beat =
    {
        .name = "world",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {},
        .openHihatVariable = {1,1,1,5,5,5,7,7,7,9,9,9,13,13,13,15,15,15},
        .closedHihatAlways = {},
        .closedHihatVariable = {1,1,1,2,3,3,3,4,5,5,5,6,7,7,7,8,9,9,9,10,11,11,11,12,13,13,13,14,15,15,15,16},
        .snareAlways = {4,7},
        .snareVariable = {3,11,12,12,12,13,13,13,15,15,15},
        .kickAlways = {1,9},
        .kickVariable = {4,5,5,5,8,12,13,13,13,16},
        .closedHihatBusyness = 0.90,
        .maxBPM = 130,
        .minBPM = 90,
    };
    allTemplates.push_back(beat);

    // 4
    beat =
    {
        .name = "cascara",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {},
        .openHihatVariable = {1,1,1,3,3,3,5,5,5,7,7,7,9,9,9,11,11,11,13,13,13,15,15,15},
        .closedHihatAlways = {},
        .closedHihatVariable = {1,1,1,2,3,3,3,4,5,5,5,6,7,7,7,8,9,9,9,10,11,11,11,12,13,13,13,14,15,15,15,16},
        .snareAlways = {3,9,12},
        .snareVariable = {5,5,5,15,15,15},
        .kickAlways = {4,7,12,15},
        .kickVariable = {1,8,10,10,10},
        .closedHihatBusyness = 0.90,
        .maxBPM = 130,
        .minBPM = 90,
    };
    allTemplates.push_back(beat);

    // 5
    beat =
    {
        .name = "chacha",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {1},
        .openHihatVariable = {11},
        .closedHihatAlways = {5,9,13},
        .closedHihatVariable = {7,7,7,8,11,11,11,12,15,15,15,16},
        .snareAlways = {5},
        .snareVariable = {},
        .kickAlways = {7,9,13},
        .kickVariable = {},
        .closedHihatBusyness = 0.70,
        .maxBPM = 130,
        .minBPM = 90,

    };
    allTemplates.push_back(beat);

    // 6
    beat =
    {
        .name = "songo",
        .patternLength = 32,
        .maxArraySize = 96,
        .openHihatAlways = {1,17},
        .openHihatVariable = {5,5,5,9,9,9,13,13,13,21,21,21,25,25,25,29,29,29},
        .closedHihatAlways = {5,9,13,21,25,29},
        .closedHihatVariable = {2,3,3,3,4,6,7,7,7,8,10,11,11,11,12,14,15,15,15,16,18,19,19,19,20,22,23,23,23,24,26,27,27,27,28,30,31,31,31,32},
        .snareAlways = {5,15,27,31},
        .snareVariable = {11,11,11,19,19,19,21,21,21},
        .kickAlways = {7,13,23,29},
        .kickVariable = {15,15,15,16,31,31,31,32},
        .closedHihatBusyness = 0.80,
        .maxBPM = 140,
        .minBPM = 100,
    };
    allTemplates.push_back(beat);

    // 7
    beat =
    {
        .name = "bolero",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {},
        .openHihatVariable = {1,1,1,5,5,5,9,9,9,13,13,13},
        .closedHihatAlways = {1,5,9,13},
        .closedHihatVariable = {2,3,3,3,4,6,7,7,7,8,10,11,11,11,12,14,15,15,15,16},
        .snareAlways = {},
        .snareVariable = {},
        .kickAlways = {7,9,13},
        .kickVariable = {},
        .closedHihatBusyness = 0.70,
        .maxBPM = 120,
        .minBPM = 90,
    };
    allTemplates.push_back(beat);

    // 8
    beat =
    {
        .name = "samba",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {},
        .openHihatVariable = {1,1,1,4,5,5,5,8,9,9,9,12,13,13,13,16},
        .closedHihatAlways = {},
        .closedHihatVariable = {1,1,1,2,3,3,4,5,5,5,6,6,7,7,8,9,9,9,10,11,11,12,13,13,13,14,15,15,16},
        .snareAlways = {3,6,10,13,15},
        .snareVariable = {1,1,1,8,8,8},
        .kickAlways = {1,5,9,13},
        .kickVariable = {4,4,4,8,8,8,12,12,12,16,16,16},
        .openHihatBusyness = 0.8,
        .closedHihatBusyness = 0.8,
        .snareBusyness = 0.2,
        .kickBusyness = 0.4,
        .maxBPM = 110,
        .minBPM = 70,

    };
    allTemplates.push_back(beat);

    // 9
    beat =
    {
        .name = "calypso",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {4,7,12,15},
        .openHihatVariable = {},
        .closedHihatAlways = {1,5,9,13},
        .closedHihatVariable = {2,2,2,3,3,3,4,4,4,6,6,6,7,7,7,8,8,8,10,10,10,11,11,11,12,12,12,14,14,14,15,15,15,16,16,16},
        .snareAlways = {},
        .snareVariable = {15},
        .kickAlways = {1,5,9,13},
        .kickVariable = {4,4,12,12},
        .openHihatBusyness = 0.8,
        .closedHihatBusyness = 0.8,
        .snareBusyness = 0.1,
        .kickBusyness = 0.2,
        .maxBPM = 120,
        .minBPM = 70,
    };
    allTemplates.push_back(beat);

    // 10
    beat =
    {
        .name = "ska",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {1},
        .openHihatVariable = {3,3,3,7,7,7,11,11,11,15,15,15},
        .closedHihatAlways = {1,5,9,13},
        .closedHihatVariable = {2,3,3,3,4,6,7,7,7,8,10,11,11,11,12,14,15,15,15,16},
        .snareAlways = {9},
        .snareVariable = {15},
        .kickAlways = {1,5,9,13},
        .kickVariable = {},
        .closedHihatBusyness = 0.6,
        .snareBusyness = 0.1,
        .maxBPM = 150,
        .minBPM = 115,
    };
    allTemplates.push_back(beat);

    // 11
    beat =
    {
        .name = "reggae one drop",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {},
        .openHihatVariable = {3,3,3,7,7,7,11,11,11,15,15,15},
        .closedHihatAlways = {1,5,9,13},
        .closedHihatVariable = {4,4,4,8,8,8,16,16,16},
        .snareAlways = {9},
        .snareVariable = {15,15},
        .kickAlways = {9},
        .kickVariable = {},
        .closedHihatBusyness = 0.5,
        .snareBusyness = 0.1,
        .maxBPM = 150,
        .minBPM = 120,
    };
    allTemplates.push_back(beat);

    // 12
    beat =
    {
        .name = "techno",
        .patternLength = 16,
        .maxArraySize = 48,
        .openHihatAlways = {},
        .openHihatVariable = {3,3,3,7,7,7,11,11,11,15,15,15},
        .closedHihatAlways = {1,5,9,13},
        .closedHihatVariable = {2,3,3,3,4,6,7,7,7,8,10,11,11,11,12,14,15,15,15,16},
        .snareAlways = {5,13},
        .snareVariable = {8,15,15,15,16},
        .kickAlways = {1,5,9,13},
        .kickVariable = {},
        .closedHihatBusyness = 0.5,
        .snareBusyness = 0.1,
        .maxBPM = 140,
        .minBPM = 115,
    };
    allTemplates.push_back(beat);


    // 3/4

    beat =
    {
        .name = "country waltz",
        .patternLength = 24,
        .maxArraySize = 72,
        .openHihatAlways = {},
        .openHihatVariable = {1,1,1,3,3,3,5,5,5,7,7,7,9,9,9,11,11,11,13,13,13,15,15,15,17,17,17,19,19,19,21,21,21,23,23,23},
        .closedHihatAlways = {1,5,8,9,13,17,20,21},
        .closedHihatVariable = {2,3,3,3,4,6,7,7,7,10,11,11,11,12,14,15,15,15,16,18,19,19,19,22,23,23,23,24},
        .snareAlways = {13},
        .snareVariable = {},
        .kickAlways = {1},
        .kickVariable = {7,7,7,15,15,15,19,19,19,23,23,23},
        .closedHihatBusyness = 0.6,
        .kickBusyness = 0.3,
        .maxBPM = 150,
        .minBPM = 115,
    };
    allTemplates.push_back(beat);

    beat =
    {
        .name = "bikutsi",
        .patternLength = 12,
        .maxArraySize = 36,
        .openHihatAlways = {},
        .openHihatVariable = {1,1,1,5,5,5,7,7,7,9,9,9},
        .closedHihatAlways = {},
        .closedHihatVariable = {1,1,1,2,3,3,3,4,5,5,5,6,7,7,7,8,9,9,9,10,11,11,11,12},
        .snareAlways = {9},
        .snareVariable = {1,5,5,5},
        .kickAlways = {1,10},
        .kickVariable = {3,4,4,4,7,7,7,12},
        .closedHihatBusyness = 0.90,
        .snareBusyness = 0.2,
        .kickBusyness = 0.3,
        .maxBPM = 140,
        .minBPM = 100,
    };
    allTemplates.push_back(beat);

    // 5/4
    beat =
    {
        .name = "fivefour1",
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