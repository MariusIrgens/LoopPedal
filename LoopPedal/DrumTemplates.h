// DrumTemplates.h

#ifndef _DRUMTEMPLATES_h
#define _DRUMTEMPLATES_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#pragma once
#include <vector>
#include <string>

class DrumTemplates {
public:
    struct Template {
        std::string name;
        int patternLength;
        int maxArraySize;
        std::vector<int> openHihatAlways;
        std::vector<int> openHihatVariable;
        std::vector<int> closedHihatAlways;
        std::vector<int> closedHihatVariable;
        std::vector<int> snareAlways;
        std::vector<int> snareVariable;
        std::vector<int> kickAlways;
        std::vector<int> kickVariable;
    };
    
    struct TomFill {
        std::vector<int> highTom;
        std::vector<int> lowTom;
    };

    DrumTemplates();

    const std::vector<Template>& getAllTemplates();
    const Template& getTemplateByIndex(size_t index);
    const TomFill& getTomFillByIndex(size_t index);
    int getMaxTemplateIndex();
    int getMaxTomFillIndex();

private:
    std::vector<Template> allTemplates;
    std::vector<TomFill> allTomFills;

};

#endif
