#include "STLFileImp.h"
#include "IRMB/STLFile/STLFileVisitor.h"
#include <Hierarchies/CNAcceptor/CNAcceptorImp.h>

#include <boost/filesystem.hpp>
#include "GridGenerator/utilities/io/STLReaderWriter.h"
#include "GridGenerator/utilities/Transformator.h"

STLFileImpPtr STLFileImp::getNewInstance(std::string path) {
    return STLFileImpPtr(new STLFileImp(path));
}

STLFileImp::~STLFileImp() {}

STLFileImp::STLFileImp(std::string path)
        : acceptor(CNAcceptorImp<STLFileVisitor, STLFile>::getNewInstance()),
          path(path) {
    static int i;

    boost::filesystem::path p(path);
    this->name = p.stem().string() + " (" + std::to_string(i++) + ")";

    Transformator trans;
    triangles = STLReaderWriter::readSTL(getPath(), trans);

    BoundingBox b;
    initializeBoundingBox();
}

void STLFileImp::initializeBoundingBox() {
    boundingBox.minX = (int)(*min_element(triangles.begin(), triangles.end(), [](const Triangle& t1, const Triangle& t2) {
        return std::min(t1.v1.x, std::min(t1.v2.x, t1.v3.x)) < std::min(t2.v1.x, std::min(t2.v2.x, t2.v3.x));
    })).v1.x;

    boundingBox.minY = (int)(*min_element(triangles.begin(), triangles.end(), [](const Triangle& t1, const Triangle& t2) {
        return std::min(t1.v1.y, std::min(t1.v2.y, t1.v3.y)) < std::min(t2.v1.y, std::min(t2.v2.y, t2.v3.y));
    })).v1.y;

    boundingBox.minZ = (int)(*min_element(triangles.begin(), triangles.end(), [](const Triangle& t1, const Triangle& t2) {
        return std::min(t1.v1.z, std::min(t1.v2.z, t1.v3.z)) < std::min(t2.v1.z, std::min(t2.v2.z, t2.v3.z));
    })).v1.z;

    boundingBox.maxX = (int)(*max_element(triangles.begin(), triangles.end(), [](const Triangle& t1, const Triangle& t2) {
        return std::max(t1.v1.x, std::max(t1.v2.x, t1.v3.x)) < std::max(t2.v1.x, std::max(t2.v2.x, t2.v3.x));
    })).v1.x;

    boundingBox.maxY = (int)(*max_element(triangles.begin(), triangles.end(), [](const Triangle& t1, const Triangle& t2) {
        return std::max(t1.v1.y, std::max(t1.v2.y, t1.v3.y)) < std::max(t2.v1.y, std::max(t2.v2.y, t2.v3.y));
    })).v1.y;

    boundingBox.maxZ = (int)(*max_element(triangles.begin(), triangles.end(), [](const Triangle& t1, const Triangle& t2) {
        return std::max(t1.v1.z, std::max(t1.v2.z, t1.v3.z)) < std::max(t2.v1.z, std::max(t2.v2.z, t2.v3.z));
    })).v1.z;
}

std::string STLFileImp::getName() {
    return name;
}
std::string STLFileImp::getPath() {
    return path;
}

void STLFileImp::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

std::vector<Triangle> STLFileImp::getTriangles() {
    return triangles;
}

STLFileImpPtr STLFileImp::me() {
    return this->shared_from_this();
}

int STLFileImp::getNumberOfTriangles() {
    return (int) triangles.size();
}

BoundingBox STLFileImp::getBoundingBox() {
    return boundingBox;
}


