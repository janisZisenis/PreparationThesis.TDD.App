#include "QtFileFinder.h"
#include <QFileDialog>

QtFileFinderPtr QtFileFinder::getNewInstance() {
    return QtFileFinderPtr(new QtFileFinder());
}

QtFileFinder::~QtFileFinder() {

}

QtFileFinder::QtFileFinder() {

}

bool QtFileFinder::findFile() {
    bool success = false;
    QString file = QFileDialog::getOpenFileName(nullptr, "Select STL File", "/Users/Janis/Desktop/STL", "STL Files (*.stl)");


    if(!file.isEmpty() && !file.isNull()) {
        foundFile = file.toStdString();
        success = true;
    }

    return success;
}

std::string QtFileFinder::getFileName() {
    std::string temp = foundFile;
    foundFile = "";
    return temp;
}
