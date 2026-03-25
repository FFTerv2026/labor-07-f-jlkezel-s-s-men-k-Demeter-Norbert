#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QProgressDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"Fájlnév", "Méret (KB)"});

    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::browse);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::search);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browse()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Könyvtár kiválasztása");
    if (!dir.isEmpty())
        ui->dirLineEdit->setText(dir);
}

void MainWindow::search()
{
    ui->tableWidget->setRowCount(0);

    searchFiles(ui->dirLineEdit->text(), ui->searchLineEdit->text());
}

void MainWindow::searchFiles(const QString &dirPath, const QString &text)
{
    QDirIterator it(dirPath, QDir::Files, QDirIterator::Subdirectories);

    QStringList files;
    while (it.hasNext())
        files << it.next();

    QProgressDialog progress("Keresés...", "Mégse", 0, files.size(), this);

    int i = 0;
    for (const QString &filePath : files)
    {
        progress.setValue(i++);
        if (progress.wasCanceled()) break;

        QFileInfo info(filePath);
        bool match = text.isEmpty();

        if (!match)
        {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                while (!in.atEnd())
                {
                    if (in.readLine().contains(text, Qt::CaseInsensitive))
                    {
                        match = true;
                        break;
                    }
                }
            }
        }

        if (match)
        {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            ui->tableWidget->setItem(row, 0,
                                     new QTableWidgetItem(info.fileName()));

            ui->tableWidget->setItem(row, 1,
                                     new QTableWidgetItem(QString::number(info.size()/1024) + " KB"));
        }
    }

    progress.setValue(files.size());
}
