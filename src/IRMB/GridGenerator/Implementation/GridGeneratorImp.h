#ifndef IRMB_GRIDGENERATORIMP_H
#define IRMB_GRIDGENERATORIMP_H

#include <vector>

#include "IRMB/GridGenerator/GridGenerator.h"

class CNAcceptor;

class STLFile;
class GridKernelCPU;

class GridGeneratorImp;
typedef std::shared_ptr<GridGeneratorImp> GridGeneratorImpPtr;

class GridGeneratorImp : public GridGenerator, public std::enable_shared_from_this<GridGeneratorImp> {
public:
    static GridGeneratorImpPtr getNewInstance(std::string name, double length, double width, double height, double delta, std::string distribution);
    virtual ~GridGeneratorImp();
protected:
    GridGeneratorImp(std::string name, double length, double width, double height, double delta, std::string distribution);

public:
    virtual std::string getName() override;

    virtual void addSTLFile(std::shared_ptr<STLFile> stlFile) override;
    virtual void removeSTLFile(std::shared_ptr<STLFile> stlFile) override;

    virtual void accept(CNVisitorPtr visitor) override;

    virtual double getLength() override;
    virtual double getWidth() override;
    virtual double getHeight() override;
    virtual double getDelta() override;
    virtual std::string getDistribution() override;
    virtual Grid* generateGrid() override;
private:
    GridGeneratorImpPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    std::vector< std::shared_ptr<STLFile> > stlFiles;
    std::string name;
    double length;
    double width;
    double height;
    double delta;
    std::shared_ptr<GridKernelCPU> gridKernel;
    std::string distribution;
};

#endif //IRMB_GRIDGENERATORIMP_H
