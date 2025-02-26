#include "ProfileManager.h"

ProfileManager::ProfileManager() {
    profiles = new vector<Profile*>();
}

ProfileManager::~ProfileManager() {
    for (int i = 0; i < profiles->size(); ++i)
        delete profiles->at(i);
    delete profiles;
}

void ProfileManager::loadProfiles() {
    string path = "profiles";
    for(auto& p : fs::directory_iterator(path)) {
        addProfile(new Profile(p.path()));
    }
}

void ProfileManager::saveProfiles() {
    for(int i = 0; i < profiles->size(); ++i) {
        profiles->at(i)->saveProfileToFile();
        profiles->at(i)->saveDataToFile();
    }
}

bool ProfileManager::contains(string name) {
    for(int i = 0; i < profiles->size(); ++i) {
        if(profiles->at(i)->name == name)
            return true;
    }
    return false;
}

Profile* ProfileManager::getProfile(string name) {
    for(int i = 0; i < profiles->size(); ++i) {
        if(profiles->at(i)->name == name)
            return profiles->at(i);
    }
    return NULL;
}

void ProfileManager::addProfile(Profile* p) {
    profiles->push_back(p);
}

bool ProfileManager::deleteProfile(string name) {
    int i = getProfileIndex(name);
    Profile *p = profiles->at(i); // profile to delete
    if(i != -1) {
        string fileName = "profiles/" + name + ".txt";
        if(remove(fileName.c_str()) != 0) {
            cout << fileName << endl;
            cout << "ERROR: Could not delete file" << endl;
            return false;
        }
        delete p;
        profiles->erase(profiles->begin()+i);
    }
    return (i != -1);
}

void ProfileManager::printProfileList() {
    if(profiles->size() > 0) {
        for(int i = 0; i < profiles->size(); ++i) {
            profiles->at(i)->print(0);
        }
    } else {
        cout << "No profiles found; create a new profile to view." << endl;
    }
    cout << endl;
}

bool ProfileManager::isEmpty() {
    return (profiles->size() == 0);
}

// private methods

int ProfileManager::getProfileIndex(string name) {
    for(int i = 0; i < profiles->size(); ++i) {
        if(profiles->at(i)->name == name)
            return i;
    }
    return -1;
}
