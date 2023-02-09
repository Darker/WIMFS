#include "MainWindow.h"
#include "./ui_mainwindow.h"
#include "ui/model/ItemInstanceModel.h"

#include <core/DatabaseAccess.h>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , database(new DatabaseAccess(this))
{
  ui->setupUi(this);  
  database->initDB("data.sqlite");

  ui->itemInstanceView->setModel(new ItemInstanceModel(this));
}

MainWindow::~MainWindow()
{
  delete ui;
  delete database;
}

