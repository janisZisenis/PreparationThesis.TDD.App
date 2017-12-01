#ifndef QTIRMB_QTGRIDGENERATOR_H
#define QTIRMB_QTGRIDGENERATOR_H

#include <QtViews/QWidgetBased/QtCentral/QtCentral.h>
#include <vtkSmartPointer.h>
#include <QObject>

class QPushButton;
class QVTKWidget;
class vtkUnstructuredGrid;
class vtkPolyData;
class vtkPoints;
class vtkDoubleArray;
class vtkRenderer;

class CNAcceptor;

class GridGenerator;
class Grid;

class QtGridGenerator;
typedef std::shared_ptr<QtGridGenerator> QtGridGeneratorPtr;

class QtGridGenerator : public QObject, public QtCentral, public std::enable_shared_from_this<QtGridGenerator> {
public:
    Q_OBJECT
public:
    static QtGridGeneratorPtr getNewInstance(std::shared_ptr<GridGenerator> gridGenerator);
    virtual ~QtGridGenerator();

protected:
    QtGridGenerator(std::shared_ptr<GridGenerator> gridGenerator);

public:
    QWidget *getQWidget() override;
    std::string getTitle() override;

    virtual void accept(CNVisitorPtr visitor) override;
private:
    virtual void initialize();
    virtual void initializeView();
    virtual void connectToView();
    virtual void update();
    virtual void visualize();
    virtual void visualizeGrid();
    virtual void thresholdGrid();
    virtual int getUpperThresholdBoundary();
    virtual int getLowerThresholdBoundary();
    virtual void readPoints();
    virtual vtkSmartPointer<vtkPolyData> getThresholdedPoints();
    virtual QtGridGeneratorPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    QWidget* view;
    QPushButton* solidButton;
    QPushButton* fluidButton;
    QVTKWidget* widget;
    std::shared_ptr<GridGenerator> gridGenerator;
    Grid* grid;
    vtkSmartPointer<vtkPoints> points;
    vtkSmartPointer<vtkDoubleArray> types;
    vtkSmartPointer<vtkUnstructuredGrid> thresholdedGrid;
    vtkSmartPointer<vtkRenderer> renderer;

    bool showSolidNodes = true;
    bool showFluidNodes = true;
private slots:
    virtual void onSolidButtonToggled();
    virtual void onFluidButtonToggled();

    void initializePoints();
};

#endif //QTIRMB_QTGRIDGENERATOR_H