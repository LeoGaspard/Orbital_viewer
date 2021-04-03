#include "hdr/mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>

#include <fstream>

#include "hdr/hydrogenoidorbital.hpp"
#include "hdr/C3Vec.hpp"
#include "hdr/grid.hpp"
#include "hdr/marchingcube.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_reload_pushbutton_clicked()
{
   int n = this->ui->N_spinbox->value();
   int l = this->ui->L_spinbox->value();
   int m = this->ui->M_spinbox->value();
   unsigned int divX = static_cast<unsigned int>(this->ui->xdiv_spinbox->value());
   unsigned int divY = static_cast<unsigned int>(this->ui->ydiv_spinbox->value());
   unsigned int divZ = static_cast<unsigned int>(this->ui->zdiv_spinbox->value());
   double xMin = this->ui->xmin_spinbox->value();
   double xMax = this->ui->xmax_spinbox->value();
   double yMin = this->ui->ymin_spinbox->value();
   double yMax = this->ui->ymax_spinbox->value();
   double zMin = this->ui->zmin_spinbox->value();
   double zMax = this->ui->zmax_spinbox->value();
   double isovalue = this->ui->isovalue_spinbox->value();

   bool draw = true;

   if(l >= n)
   {
       QMessageBox messageBox;
       messageBox.critical(nullptr, "Bad input","l must be inferior to n");
       messageBox.setFixedSize(500,200);
       draw = false;
   }
   if(std::abs(m) > l)
   {
       QMessageBox messageBox;
       messageBox.critical(nullptr, "Bad input","m must be between -l and l");
       messageBox.setFixedSize(500,200);
       draw = false;
   }
   if(draw)
   {
       qDebug() << n << " " << l << " " << m;
       qDebug() << divX << " " << divY << " " << divZ;
       qDebug() << xMin << " " << xMax;
       qDebug() << yMin << " " << yMax;
       qDebug() << zMin << " " << zMax;
       qDebug() << isovalue;

       HydrogenoidOrbital orb(n,l,m);
       Grid Positive_Grid(divX, divY, divZ, xMin,xMax, yMin, yMax, zMin, zMax);
       Grid Negative_Grid(divX, divY, divZ, xMin,xMax, yMin, yMax, zMin, zMax);

       double MaxVal(0.0);

       for(unsigned int i=0; i<divX; i++)
       {
           for(unsigned int j=0; j<divY; j++)
           {
               for(unsigned int k=0; k<divZ; k++)
               {
                   C3Vec pos = Positive_Grid.getVerticePosition(i,j,k);
                   double dValue = orb(pos.GetX(), pos.GetY(), pos.GetZ());
                   double dValue2 = dValue*dValue;
                   if(dValue <= 0)
                   {
                       Negative_Grid.setValue(i,j,k,dValue2);
                   }
                   else
                   {
                       Positive_Grid.setValue(i,j,k,dValue2);
                   }
                   MaxVal = (dValue2>MaxVal) ? dValue2 : MaxVal;
               }
           }
       }
       std::vector<Surface>			s;

       std::vector<C3Vec> 			Vertices;
       std::vector<C3Vec> 			Normals;
       std::vector<unsigned int>	Triangles;

       MarchingCube(Positive_Grid, isovalue*MaxVal, Vertices, Triangles, Normals);
       s.push_back(Surface(Vertices, Normals, Triangles, C3Vec(0.0,0.0,1.0)));
       MarchingCube(Negative_Grid, isovalue*MaxVal, Vertices, Triangles, Normals);
       s.push_back(Surface(Vertices, Normals, Triangles, C3Vec(1.0,0.0,0.0)));

       qDebug() << "Computed the surfaces";

       this->ui->openGLWidget->draw_surfaces(s);
   }
}

