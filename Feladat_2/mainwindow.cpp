#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    // 1. Táblázat létrehozása és beállítása
    tableWidget = new QTableWidget(this);

    // A táblázat ne legyen módosítható (Read-Only)
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // A táblázat beállítása a főablak központi elemeként
    setCentralWidget(tableWidget);

    // 2. Menüsáv, menü és menüpont létrehozása
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *openAction = new QAction("Open File...", this);
    fileMenu->addAction(openAction);

    // Eseménykezelés: a menüpont megnyomása meghívja az openFile függvényt
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    setWindowTitle("CSV Olvasó");
    resize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::openFile() {
    // Fájlmegnyitó dialógus, szűrve csak .csv kiterjesztésre
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open CSV File",
                                                    "",
                                                    "CSV Files (*.csv)");

    // Ha a felhasználó bezárta a dialógust választás nélkül
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Hiba", "Nem sikerült megnyitni a fájlt!");
        return;
    }

    QTextStream in(&file);

    // Előző betöltés adatainak törlése (ha már volt nyitva fájl)
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(0);

    // 3. Első sor beolvasása (Oszlopok beállítása)
    if (!in.atEnd()) {
        QString headerLine = in.readLine();
        // A CSV értékeket vesszők mentén választjuk szét
        QStringList headers = headerLine.split(',');

        tableWidget->setColumnCount(headers.size());
        tableWidget->setHorizontalHeaderLabels(headers);
    }

    // 4. További adatsorok beolvasása
    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.trimmed().isEmpty()) continue;

        QStringList fields = line.split(',');
        tableWidget->insertRow(row);

        for (int col = 0; col < fields.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(fields[col]);
            tableWidget->setItem(row, col, item);
        }
        row++;
    }

    file.close();

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}