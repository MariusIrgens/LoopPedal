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

// ... (previous code)

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

    DrumTemplates();

    const std::vector<Template>& getAllTemplates();
    const Template& getTemplateByIndex(size_t index);

private:
    std::vector<Template> allTemplates; // This will store all the templates for the instance
};

// ... (remaining code)


#endif
