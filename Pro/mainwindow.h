#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ocultarTodo();

    void on_BotonLeeme_clicked();

    void on_BotonConfig_clicked();

    void on_BotonAcercaDe_clicked();

    void on_BotonOK_accepted();

    void on_BotonOK_rejected();

private:
    Ui::MainWindow *ui;
    int productores=1;
    int consumidores=1;
};



#endif // MAINWINDOW_H
