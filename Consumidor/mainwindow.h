#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
using namespace std;

//---------------------------------------------------------------//

#include <QThread>
#include <QCoreApplication>
#include <QThread>
#include <QSemaphore>
#include <QDebug>
#include <QVector>
#include <QRandomGenerator>
#include <QRandomGenerator64>


static QString abecedario = "abcdefghijklmnopqrstuvwxyz";
static QVector<QString> buffer;
static int producto = 0;
static int maximoproducto=20;

//static QSemaphore usedSemaphore(0);
//static QSemaphore freeSemaphore(maximoproducto);
static QRandomGenerator gen = QRandomGenerator();

class Productor: public QThread{
    Q_OBJECT

signals:
    void nuevoTexto();
    void actualizartiempoP(int,int);
    void agregarElemento();


public:
    int ident;
    int tiempoperdido = 0;
    bool pausa=false;
    void setestado(bool e){
        pausa = e;
    }
    Productor(int valor){
        ident = valor;
    }

    void run(){
        while(true){
            if(pausa){
                sleep(1);
            }
            else{
                if(producto<maximoproducto){
                    //freeSemaphore.acquire();
                    emit agregarElemento();
                    producto++;
                    //usedSemaphore.release();

                    emit nuevoTexto();
                    sleep(1);
                }
                else{
                    sleep(1);
                    tiempoperdido++;
                    emit actualizartiempoP(ident,tiempoperdido);
                }
            }
        }
    }
};

class Consumidor:public QThread{
    Q_OBJECT

signals:
    void nuevoTexto();
    void eliminarelementos();
    void actualizartiempoC(int, int);

public:
    int ident;
    int tiempoperdido = 0;
    bool pausa=false;
    void setestado(bool e){
        pausa = e;
    }
    Consumidor(int valor){
        ident = valor;
    }
    void run(){
        while(true){
            if(pausa){
                sleep(1);
            }
            else{
                if(producto>0){
                    //usedSemaphore.acquire();
                    emit eliminarelementos();
                    producto--;
                    emit nuevoTexto();
                    sleep(1);
                    //freeSemaphore.release();
                }
                else{
                    sleep(1);
                    tiempoperdido++;
                    actualizartiempoC(ident,tiempoperdido);
                }
            }
        }
    }
};

//---------------------------------------------------------------//

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{

    Q_OBJECT
private:
    Ui::MainWindow *ui;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void actualizartexto();
    //Productor
    void actualizartiempoproductor(int ident, int tiempo);
    void NuevoElemento();

    //Consumidor
    void actualizartiempoconsumidor(int ident, int tiempo);
    void extraerproducto();

private slots:
    void on_Iniciar_clicked();

    void on_PPlay_clicked();
    void on_PPause_clicked();
    void on_PKill_clicked();
    void on_PPlay_2_clicked();
    void on_PPause_2_clicked();
    void on_PKill_2_clicked();
    void on_PPlay_3_clicked();
    void on_PPause_3_clicked();
    void on_PKill_3_clicked();
    void on_PPlay_4_clicked();
    void on_PPause_4_clicked();
    void on_PKill_4_clicked();

    void on_CPlay_clicked();
    void on_CPause_clicked();
    void on_CKill_clicked();
    void on_CPlay_2_clicked();
    void on_CPause_2_clicked();
    void on_CKill_2_clicked();
    void on_CPlay_3_clicked();
    void on_CPause_3_clicked();
    void on_CKill_3_clicked();
    void on_CPlay_4_clicked();
    void on_CPause_4_clicked();
    void on_CKill_4_clicked();

};


#endif // MAINWINDOW_H
