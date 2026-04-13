#pragma once
#include <QtAwesome.h>

class Awesome {
public:
    static fa::QtAwesome *instance() {
        static fa::QtAwesome *awesome = nullptr;
        if (!awesome) {
            awesome = new fa::QtAwesome();
            awesome->initFontAwesome();
        }
        return awesome;
    }
};
