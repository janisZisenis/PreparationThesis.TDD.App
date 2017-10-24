#ifndef IRMB_FILEFINDER_H
#define IRMB_FILEFINDER_H

#include <memory>
#include <string>

class FileFinder;
typedef std::shared_ptr<FileFinder> FileFinderPtr;

class FileFinder {
public:
    virtual ~FileFinder() {};
protected:
    FileFinder() {};

public:
    virtual bool findFile() = 0;
    virtual std::string getFileName() = 0;
};

#endif //IRMB_FILEFINDER_H
