#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Buffer->setHidden(true);

    ui->CajaCons->setHidden(true);
    ui->CajaCons_2->setHidden(true);
    ui->CajaCons_3->setHidden(true);
    ui->CajaCons_4->setHidden(true);


    ui->CajaProd->setHidden(true);
    ui->CajaProd_2->setHidden(true);
    ui->CajaProd_3->setHidden(true);
    ui->CajaProd_4->setHidden(true);
}

MainWindow::~MainWindow(){
    delete ui;
}

static int losproductores=0;
static int losconsumidores=0;


void MainWindow::actualizartexto(){
    QString aux;
    for(int i = 0; i<buffer.size();i++){
        auto x = buffer[i];
        aux.append(x);
        aux.append(" ");
        if((i+1)%10==0){
            aux.append("\n");
        }
    }
    ui->Buffer->setText(aux) ;
}


void MainWindow::NuevoElemento(){
    buffer.push_back(abecedario.at(gen.bounded(26)));
}

void MainWindow::actualizartiempoproductor(int ident, int tiempo){
    switch (ident) {
    case 1:
        ui->CantProd->setText(QString::number(tiempo));
        break;
    case 2:
        ui->CantProd_2->setText(QString::number(tiempo));
        break;
    case 3:
        ui->CantProd_3->setText(QString::number(tiempo));
        break;
    case 4:
        ui->CantProd_4->setText(QString::number(tiempo));
        break;
    }
}

void::MainWindow::extraerproducto(){
    buffer.remove(0);
}

void MainWindow::actualizartiempoconsumidor(int ident, int tiempo){
    switch (ident) {
    case 1:
        ui->CantCons->setText(QString::number(tiempo));
        break;
    case 2:
        ui->CantCons_2->setText(QString::number(tiempo));
        break;
    case 3:
        ui->CantCons_3->setText(QString::number(tiempo));
        break;
    case 4:
        ui->CantCons_4->setText(QString::number(tiempo));
        break;
    }
}


static Productor *Productor1 = new Productor(1);
static Productor *Productor2 = new Productor(2);
static Productor *Productor3 = new Productor(3);
static Productor *Productor4 = new Productor(4);

static Consumidor *Consumidor1 = new Consumidor(1);
static Consumidor *Consumidor2 = new Consumidor(2);
static Consumidor *Consumidor3 = new Consumidor(3);
static Consumidor *Consumidor4 = new Consumidor(4);

void MainWindow::on_Iniciar_clicked(){
    //Guardar Datos
    losproductores = ui->NumProd->value();
    losconsumidores = ui->NumCons->value();
    ui->Buffer->setHidden(false);
    ui->Cajainicio->setHidden(true);

    //Conexiones
    connect(Productor1,SIGNAL(nuevoTexto()),SLOT(actualizartexto()));
    connect(Productor1,SIGNAL(agregarElemento()),SLOT(NuevoElemento()));
    connect(Productor1,SIGNAL(actualizartiempoP(int,int)),SLOT(actualizartiempoproductor(int,int)));

    connect(Productor2,SIGNAL(nuevoTexto()),SLOT(actualizartexto()));
    connect(Productor2,SIGNAL(agregarElemento()),SLOT(NuevoElemento()));
    connect(Productor2,SIGNAL(actualizartiempoP(int,int)),SLOT(actualizartiempoproductor(int,int)));

    connect(Productor3,SIGNAL(nuevoTexto()),SLOT(actualizartexto()));
    connect(Productor3,SIGNAL(agregarElemento()),SLOT(NuevoElemento()));
    connect(Productor3,SIGNAL(actualizartiempoP(int,int)),SLOT(actualizartiempoproductor(int,int)));

    connect(Productor4,SIGNAL(nuevoTexto()),SLOT(actualizartexto()));
    connect(Productor4,SIGNAL(agregarElemento()),SLOT(NuevoElemento()));
    connect(Productor4,SIGNAL(actualizartiempoP(int,int)),SLOT(actualizartiempoproductor(int,int)));


    connect(Consumidor1,SIGNAL(nuevoTexto()),SLOT(actualizartexto()));
    connect(Consumidor1,SIGNAL(eliminarelementos()),SLOT(extraerproducto()));
    connect(Consumidor1,SIGNAL(actualizartiempoC(int,int)),SLOT(actualizartiempoconsumidor(int,int)));

    connect(Consumidor2,SIGNAL(nuevoTexto()),SLOT(actualizartexto()));
    connect(Consumidor2,SIGNAL(eliminarelementos()),SLOT(extraerproducto()));
    connect(Consumidor2,SIGNAL(actualizartiempoC(int,int)),SLOT(actualizartiempoconsumidor(int,int)));

    connect(Consumidor3,SIGNAL(nuevoTexto()),SLOT(actualizartexto()));
    connect(Consumidor3,SIGNAL(eliminarelementos()),SLOT(extraerproducto()));
    connect(Consumidor3,SIGNAL(actualizartiempoC(int,int)),SLOT(actualizartiempoconsumidor(int,int)));

    connect(Consumidor4,SIGNAL(nuevoTexto()),SLOT(actualizartexto()));
    connect(Consumidor4,SIGNAL(eliminarelementos()),SLOT(extraerproducto()));
    connect(Consumidor4,SIGNAL(actualizartiempoC(int,int)),SLOT(actualizartiempoconsumidor(int,int)));


    if(losproductores>=1){
        ui->CajaProd->setHidden(false);
        Productor1->start();
    }
    if(losproductores>=2){
        ui->CajaProd_2->setHidden(false);
        Productor2->start();
    }
    if(losproductores>=3){
        ui->CajaProd_3->setHidden(false);
        Productor3->start();
    }
    if(losproductores==4){
        ui->CajaProd_4->setHidden(false);
        Productor4->start();
    }


    if(losconsumidores>=1){
        ui->CajaCons->setHidden(false);
        Consumidor1->start();
    }
    if(losconsumidores>=2){
        ui->CajaCons_2->setHidden(false);
        Consumidor2->start();
    }
    if(losconsumidores>=3){
        ui->CajaCons_3->setHidden(false);
        Consumidor3->start();
    }
    if(losconsumidores==4){
        ui->CajaCons_4->setHidden(false);
        Consumidor4->start();
    }
}


//Productores
void MainWindow::on_PPlay_clicked(){
    Productor1->setestado(false);
}
void MainWindow::on_PPause_clicked(){
    Productor1->setestado(true);
}
void MainWindow::on_PKill_clicked(){
    Productor1->terminate();
    ui->PPlay->setHidden(true);
    ui->PPause->setHidden(true);
    ui->PKill->setHidden(true);
}

void MainWindow::on_PPlay_2_clicked(){
    Productor2->setestado(false);
}
void MainWindow::on_PPause_2_clicked(){
    Productor2->setestado(true);
}
void MainWindow::on_PKill_2_clicked(){
    Productor2->terminate();
    ui->PPlay_2->setHidden(true);
    ui->PPause_2->setHidden(true);
    ui->PKill_2->setHidden(true);
}

void MainWindow::on_PPlay_3_clicked(){
    Productor3->setestado(false);
}
void MainWindow::on_PPause_3_clicked(){
    Productor3->setestado(true);
}
void MainWindow::on_PKill_3_clicked(){
    Productor3->terminate();
    ui->PPlay_3->setHidden(true);
    ui->PPause_3->setHidden(true);
    ui->PKill_3->setHidden(true);
}

void MainWindow::on_PPlay_4_clicked(){
    Productor4->setestado(false);
}
void MainWindow::on_PPause_4_clicked(){
    Productor4->setestado(true);
}
void MainWindow::on_PKill_4_clicked(){
    Productor4->terminate();
    ui->PPlay_4->setHidden(true);
    ui->PPause_4->setHidden(true);
    ui->PKill_4->setHidden(true);
}


//Consumidor
void MainWindow::on_CPlay_clicked(){
    Consumidor1->setestado(false);
}
void MainWindow::on_CPause_clicked(){
    Consumidor1->setestado(true);
}
void MainWindow::on_CKill_clicked(){
    Consumidor1->terminate();
    ui->CPlay->setHidden(true);
    ui->CPause->setHidden(true);
    ui->CKill->setHidden(true);
}

void MainWindow::on_CPlay_2_clicked(){
    Consumidor2->setestado(false);
}
void MainWindow::on_CPause_2_clicked(){
    Consumidor2->setestado(true);
}
void MainWindow::on_CKill_2_clicked(){
    Consumidor2->terminate();
    ui->CPlay_2->setHidden(true);
    ui->CPause_2->setHidden(true);
    ui->CKill_2->setHidden(true);
}

void MainWindow::on_CPlay_3_clicked(){
    Consumidor3->setestado(false);
}
void MainWindow::on_CPause_3_clicked(){
    Consumidor3->setestado(true);
}
void MainWindow::on_CKill_3_clicked(){
    Consumidor3->terminate();
    ui->CPlay_3->setHidden(true);
    ui->CPause_3->setHidden(true);
    ui->CKill_3->setHidden(true);
}

void MainWindow::on_CPlay_4_clicked(){
    Consumidor4->setestado(false);
}
void MainWindow::on_CPause_4_clicked(){
    Consumidor4->setestado(true);
}
void MainWindow::on_CKill_4_clicked(){
    Consumidor4->terminate();
    ui->CPlay_4->setHidden(true);
    ui->CPause_4->setHidden(true);
    ui->CKill_4->setHidden(true);
}
