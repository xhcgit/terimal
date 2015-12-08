#ifndef FRMCONSOLE_H
#define FRMCONSOLE_H

#include"config.h"
#include "ui_frmconsole.h"
#include "mytool.h"

#include <QWidget>

namespace Ui {
class FrmConsole;
}

class FrmConsole : public QWidget
{
    Q_OBJECT

public:
    explicit FrmConsole(QWidget *parent = 0);
    ~FrmConsole();

    void clearMsg();
    void setUnlock();
    void setLock();
    void switchLock();
    void save();
    void browserSavedFile();
    void append(const QString &text);
    void setTitle(const QString &title);
    void setSavedFileName(QString fileName);

private slots:
    void append(const QByteArray &ba);
    void on_btnLock_clicked();
    void on_btnClear_clicked();
    void on_btnSave_clicked();
    void on_btnBrowser_clicked();

public slots:
    void appendAndSaveAsString(QByteArray ba, bool success);
    void appendAndSaveAsHex(QByteArray ba, bool success);

private:
    Ui::FrmConsole *ui;
    bool isLocked;
    QString fileName;
};

#endif // FRMCONSOLE_H
