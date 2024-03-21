#include <iostream>
#include <string>
#include <vector>
#include "MenuData.h"

MenuData::MenuData()
: mCommands(), mCommandActionMap(), mCommandDescriptionMap() {

}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {
    mCommands.push_back(name);
    mCommandActionMap[name] = func;
    mCommandDescriptionMap[name] = description;
}

const std::vector<std::string>& MenuData::getNames() const {
    return mCommands;
}

ActionFunctionType MenuData::getFunction(const std::string& name) {
    if ( mCommandActionMap.find(name) != mCommandActionMap.end() ) {
        return mCommandActionMap[name];
    }
    return 0;
}

const std::string& MenuData::getDescription(const std::string& name) {
    if ( mCommandDescriptionMap.find(name) != mCommandDescriptionMap.end() ) {
        return mCommandDescriptionMap[name];
    }
    static std::string string_ = "";
    return string_;
}
