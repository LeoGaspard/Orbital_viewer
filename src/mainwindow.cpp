#include "hdr/mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QShortcut>

#include <fstream>

#include "hdr/hydrogenoidorbital.hpp"
#include "hdr/C3Vec.hpp"
#include "hdr/grid.hpp"
#include "hdr/marchingcube.hpp"
#include "hdr/utils.hpp"

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
   double probability = this->ui->probSlider->value()/100.0;
   double isovalue(0.0);

   // Magic number
   double xMax = 3*n*n;
   double yMax = xMax;
   double zMax = xMax;
   double xMin = -xMax;
   double yMin = -yMax;
   double zMin = -zMax;

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
       HydrogenoidOrbital orb(n,l,m);
       Grid Positive_Grid(divX, divY, divZ, xMin,xMax, yMin, yMax, zMin, zMax);
       Grid Negative_Grid(divX, divY, divZ, xMin,xMax, yMin, yMax, zMin, zMax);

       double integral(0.0);
       double dX((xMax-xMin)/divX), dY((yMax-yMin)/divY), dZ((zMax-zMin)/divZ);

       std::vector<std::vector<double>> dVals;

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
                   double R = std::sqrt(pos.GetX()*pos.GetX() + pos.GetY()*pos.GetY() + pos.GetZ()*pos.GetZ());
                   dVals.push_back(std::vector<double>{R, dValue2});
               }
           }
       }

       std::sort(dVals.begin(), dVals.end(),sortcol);
       for(unsigned int i=0; i<dVals.size() && integral < probability; i++)
       {
           integral += dVals[i][1]*dX*dY*dZ;
           isovalue = dVals[i][1];
       }
       std::vector<Surface>			s;

       std::vector<C3Vec> 			Vertices;
       std::vector<C3Vec> 			Normals;
       std::vector<unsigned int>	Triangles;

       MarchingCube(Positive_Grid, isovalue, Vertices, Triangles, Normals);
       s.push_back(Surface(Vertices, Normals, Triangles, C3Vec(0.0,0.0,1.0)));
       MarchingCube(Negative_Grid, isovalue, Vertices, Triangles, Normals);
       s.push_back(Surface(Vertices, Normals, Triangles, C3Vec(1.0,0.0,0.0)));
       this->ui->openGLWidget->draw_surfaces(s);
   }
}


void MainWindow::on_probSlider_valueChanged(int value)
{
   this->ui->probLabel->setText(QString::number(value)+"%");
}
