#ifndef IRMB_GRIDGENERATOR_H
#define IRMB_GRIDGENERATOR_H

#include <CrossNative/CNVisitable/CNVisitable.h>
#include <string>

class STLFile;
struct Grid;

class GridGenerator;
typedef std::shared_ptr<GridGenerator> GridGeneratorPtr;

class GridGenerator : public virtual CNVisitable {
public:
    virtual ~GridGenerator() {};
protected:
    GridGenerator() {};

public:
    virtual std::string getName() = 0;

    virtual void addSTLFile(std::shared_ptr<STLFile> stlFile) = 0;
    virtual void removeSTLFile(std::shared_ptr<STLFile> stlFile) = 0;

    virtual double getLength() = 0;
    virtual double getWidth() = 0;
    virtual double getHeight() = 0;
    virtual double getDelta() = 0;
    virtual std::string getDistribution() = 0;
    virtual Grid* generateGrid() = 0;
};

#endif //IRMB_GRIDGENERATOR_H
