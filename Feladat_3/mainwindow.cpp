#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QMessageBox>

QuoteWindow::QuoteWindow(QWidget *parent)
    : QWidget(parent), lastQuoteIndex(-1) {

    quoteLabel = new QLabel("Idézet betöltése...", this);
    quoteLabel->setWordWrap(true);
    quoteLabel->setAlignment(Qt::AlignCenter);
    quoteLabel->setObjectName("quoteText");

    authorLabel = new QLabel("", this);
    authorLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    authorLabel->setObjectName("authorText");

    newQuoteButton = new QPushButton("Another one!", this);
    newQuoteButton->setCursor(Qt::PointingHandCursor);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(quoteLabel);
    layout->addWidget(authorLabel);
    layout->addSpacing(30);
    layout->addWidget(newQuoteButton, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(newQuoteButton, &QPushButton::clicked, this, &QuoteWindow::showRandomQuote);

    setWindowTitle("Daily motivation");
    resize(600, 400);
    applyStyles();
    loadQuotes();
    showRandomQuote();
}

QuoteWindow::~QuoteWindow() {}

void QuoteWindow::loadQuotes() {
    QFile file("quotes.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot fiind quotes.txt");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        int tildeIndex = line.lastIndexOf('~');
        if (tildeIndex != -1) {
            QString quote = line.left(tildeIndex).trimmed();
            QString author = line.mid(tildeIndex + 1).trimmed();
            quotes.push_back(qMakePair(quote, author));
        } else {
            quotes.push_back(qMakePair(line, QString("Unknown")));
        }
    }
    file.close();
}

void QuoteWindow::showRandomQuote() {
    if (quotes.empty()) {
        quoteLabel->setText("No awalaible quotes.");
        return;
    }

    int newIndex;
    do {
        newIndex = QRandomGenerator::global()->bounded(static_cast<int>(quotes.size()));
    } while (newIndex == lastQuoteIndex && quotes.size() > 1);

    lastQuoteIndex = newIndex;

    quoteLabel->setText("\"" + quotes[newIndex].first + "\"");
    authorLabel->setText("— " + quotes[newIndex].second);
}

void QuoteWindow::applyStyles() {
    QString style = R"(
        QWidget {
            background-color: #2c3e50;
            color: #ecf0f1;
            font-family: 'Segoe UI', Arial, sans-serif;
        }
        QLabel#quoteText {
            font-size: 26px;
            font-style: italic;
            padding: 20px;
        }
        QLabel#authorText {
            font-size: 18px;
            font-weight: bold;
            color: #e74c3c;
            padding-right: 40px;
        }
        QPushButton {
            background-color: #e74c3c;
            color: white;
            border-radius: 20px;
            padding: 10px 30px;
            font-size: 16px;
            font-weight: bold;
            border: none;
        }
        QPushButton:hover {
            background-color: #c0392b;
        }
        QPushButton:pressed {
            background-color: #a93226;
        }
    )";
    this->setStyleSheet(style);
}