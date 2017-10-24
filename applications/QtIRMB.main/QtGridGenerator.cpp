#include "QtGridGenerator.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#include <CrossNative/CNVisitor/CNVisitor.h>
#include <QtViews/QWidgetBased/QtCentral/QtCentralVisitor.h>

#include "IRMB/GridGenerator/GridGenerator.h"
#include <QWidget>
#include "QVTKWidget.h"
#include "GridGenerator/grid/kernel/Grid.h"

#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkVertex.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDoubleArray.h>
#include <vtkProperty.h>

QtGridGeneratorPtr QtGridGenerator::getNewInstance(GridGeneratorPtr gridGenerator) {
    return QtGridGeneratorPtr(new QtGridGenerator(gridGenerator));
}

QtGridGenerator::~QtGridGenerator() {
    delete widget;
}

QtGridGenerator::QtGridGenerator(GridGeneratorPtr gridGenerator)
        : acceptor(CNAcceptorImp<QtCentralVisitor, QtCentral>::getNewInstance()),
          widget(new QVTKWidget()),
          gridGenerator(gridGenerator) {
    widget->setWindowTitle(QString::fromStdString(gridGenerator->getName()));

    Grid* grid = gridGenerator->generateGrid();

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkVertex> vertex = vtkSmartPointer<vtkVertex>::New();

    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkDoubleArray> types = vtkSmartPointer<vtkDoubleArray>::New();

    int x, y, z;

    for(int i = 0; i < grid->size; i++) {
        grid->transIndexToCoords(i, x, y, z);
        points->InsertNextPoint(x, y, z);
        unstructuredGrid->SetPoints(points);
        vertex->GetPointIds()->SetId(0, i);
        unstructuredGrid->InsertNextCell(vertex->GetCellType(), vertex->GetPointIds());
        types->InsertNextValue((int)grid->field[i]);
    }
    unstructuredGrid->GetPointData()->SetScalars(types);

    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(unstructuredGrid);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetPointSize(3);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(222./255, 222./255, 222./255);

    widget->GetRenderWindow()->AddRenderer(renderer);
}

QWidget *QtGridGenerator::getQWidget() {
    return widget;
}

std::string QtGridGenerator::getTitle() {
    return widget->windowTitle().toStdString();
}

void QtGridGenerator::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

QtGridGeneratorPtr QtGridGenerator::me() {
    return this->shared_from_this();
}
