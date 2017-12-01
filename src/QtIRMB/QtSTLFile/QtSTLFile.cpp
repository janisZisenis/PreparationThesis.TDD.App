#include "QtSTLFile.h"
#include <Hierarchies/CNAcceptor/CNAcceptorImp.h>
#include <QtViews/QWidgetBased/QtCentral/QtCentralVisitor.h>
#include <IRMB/STLFile/STLFile.h>
#include <QWidget>
#include "QVTKWidget.h"
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSTLWriter.h>

QtSTLFilePtr QtSTLFile::getNewInstance(STLFilePtr stlFile) {
    return QtSTLFilePtr(new QtSTLFile(stlFile));
}

QtSTLFile::~QtSTLFile() {
    delete widget;
}

QtSTLFile::QtSTLFile(STLFilePtr stlFile)
        : acceptor(CNAcceptorImp<QtCentralVisitor, QtSTLFile>::getNewInstance()),
          widget(new QVTKWidget()),
          stlFile(stlFile) {
    initialize();
    visualize();
}

QWidget *QtSTLFile::getQWidget() {
    return widget;
}

std::string QtSTLFile::getTitle() {
    return widget->windowTitle().toStdString();
}

void QtSTLFile::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

QtSTLFilePtr QtSTLFile::me() {
    return this->shared_from_this();
}

void QtSTLFile::initialize() {
    this->widget->setWindowTitle(QString::fromStdString(stlFile->getName()));
}

void QtSTLFile::visualize() {
    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(stlFile->getPath().c_str());
    reader->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(222./255, 222./255, 222./255);
    renderer->AddActor(actor);

    widget->GetRenderWindow()->AddRenderer(renderer);
//    vtkSmartPointer<vtkSTLWriter> writer = vtkSmartPointer<vtkSTLWriter>::New();
//    writer->SetFileTypeToBinary();
//    writer->SetInputData(reader->GetOutput());
//    writer->SetFileName("/Users/Janis/STLFiles/binaryOutput.stl");
//    writer->Write();
}
