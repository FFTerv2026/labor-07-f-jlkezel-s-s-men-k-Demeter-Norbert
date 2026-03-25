#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QPair>
#include <vector>

class QuoteWindow : public QWidget {
    Q_OBJECT

public:
    QuoteWindow(QWidget *parent = nullptr);
    ~QuoteWindow();

private slots:
    void showRandomQuote();

private:
    void loadQuotes();
    void applyStyles();

    QLabel *quoteLabel;
    QLabel *authorLabel;
    QPushButton *newQuoteButton;

    std::vector<QPair<QString, QString>> quotes;
    int lastQuoteIndex;
};