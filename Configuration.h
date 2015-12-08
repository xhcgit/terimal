#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QListWidget>
#include <QWidget>

namespace Ui {
class Configuration;
}

class Configuration : public QWidget
{
    Q_OBJECT

public:
    explicit Configuration(QWidget *parent = 0);
    ~Configuration();
    QString check_code(QByteArray);
    QByteArray CAS();
    QByteArray SIR();

signals:
    void sendCmdViaCom(QByteArray ba);

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Configuration *ui;
};

#endif // CONFIGURATION_H
