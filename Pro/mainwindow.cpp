#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ocultarTodo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ocultarTodo(){
    ui->TextoLeeme->setHidden(true);
    ui->TextoAcercaDe->setHidden(true);
    ui->CajaConfig->setHidden(true);
};

void MainWindow::on_BotonLeeme_clicked(){
    ocultarTodo();
    ui->TextoLeeme->setHidden(false);
}

void MainWindow::on_BotonConfig_clicked(){
   ocultarTodo();
   ui->CajaConfig->setHidden(false);
   ui->DatoProd->setText(QString::number(productores));
   ui->DatoCons->setText(QString::number(consumidores));
}

void MainWindow::on_BotonAcercaDe_clicked(){
    ocultarTodo();
    ui->TextoAcercaDe->setHidden(false);
}


void MainWindow::on_BotonOK_accepted(){
    QString aux = ui->DatoProd->text();
    productores = aux.toInt();
    aux = ui->DatoCons->text();
    consumidores = aux.toInt();
    ocultarTodo();
}

void MainWindow::on_BotonOK_rejected(){
    ocultarTodo();

}






