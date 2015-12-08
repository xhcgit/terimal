#include "Configuration.h"
#include "ui_Configuration.h"
#include <QDebug>

#define SYMBOL1 ','
#define SYMBOL2 '*'
#define CR 0x0D
#define LF 0x0A

Configuration::Configuration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Configuration)
{
    ui->setupUi(this);

    connect(ui->lstWidgetSettingItem, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

Configuration::~Configuration()
{
    delete ui;
}

void Configuration::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->lblCurSelectedItem->setText(current->text());
    ui->stackedSettingPages->setCurrentIndex(ui->lstWidgetSettingItem->row(current));
}

void Configuration::on_buttonBox_accepted()
{
    QByteArray cmd;
    QByteArray temp;
    cmd.append("$CC");    //插入固定头部CC
    //判断消息类型
    int selectedIndex = ui->stackedSettingPages->currentIndex();
    switch (selectedIndex)
    {
    case 0:
        cmd.append("CAS");
        temp = CAS();
        break;
    case 1:
        cmd.append("SIR");
        temp = SIR();
    default:
        //TODO
        break;
    }
    cmd.append(SYMBOL1);
    cmd.append(temp);
    //计算校验和并插入cmd中
    QString endOfMessage = check_code(cmd);
    cmd.append(endOfMessage);
    //插入结尾
    cmd.append(CR);
    cmd.append(LF);
    emit sendCmdViaCom(cmd);
}

void Configuration::on_buttonBox_rejected()
{
    close();
}

QString Configuration::check_code(QByteArray message)
{
    int messageLen = message.length();
    int i;
    int messageCopyLen;
    int checkSum;
    QByteArray messageTemp;
    for(i = 0; i < messageLen ; i++)
    {
        if ((message.at(i) == '$') || (message.at(i) == ',') || (message.at(i) == '*'))
            continue;
        else
            messageTemp.append(message.at(i));
    }
    checkSum = messageTemp.at(0);
    messageCopyLen = messageTemp.length();

    for(i = 1; i < messageCopyLen; i++)
    {
        checkSum ^= messageTemp.at(i);
    }
    QString strcheckSum = QString::number(checkSum, 16);
    if(checkSum <= 16)    //小于f时，高位补零
    {
        strcheckSum.insert(0, '0');
    }
    return strcheckSum;
}


QByteArray Configuration::CAS()    //CAS信息处理
{
    int baud_index;
    QByteArray CAS;
    //判断串口号
    if(ui->rBtnCom1->isChecked())
        CAS.append("1");
    else if(ui->rBtnCom2->isChecked())
        CAS.append("2");
    CAS.append(SYMBOL1);
    //判断波特率
    baud_index = ui->cbxBuadrate->currentIndex();
    QString temp = QString::number(baud_index + 1, 10);
    CAS.append(temp);
    CAS.append(SYMBOL2);
    return CAS;
}

QByteArray Configuration::SIR()    //CAS信息处理
{
    QByteArray SIR;
    int workingMode;
    int bootMode;
    QString temp;
    //工作模式选择
    if(ui->rBtnGps->isChecked())
        workingMode = 1;
    else if(ui->rBtnBds->isChecked())
        workingMode = 2;
    else if(ui->rBtnBdsGps->isChecked())
        workingMode = 3;
    else
        //保留项，目前无意义
        workingMode = 4;
    //启动模式选择
    if(ui->rBtnNone->isChecked())
        bootMode = 0;
    else if(ui->rBtnCode->isChecked())
        bootMode = 1;
    else if(ui->rBtnWarn->isChecked())
        bootMode = 2;
    else if(ui->rBtnHot->isChecked())
        bootMode = 3;
    else
        //保留项，目前无意义
        bootMode = 4;
    temp = QString::number(workingMode, 10);
    SIR.append(temp);
    SIR.append(SYMBOL1);
    temp = QString::number(bootMode, 10);
    SIR.append(temp);
    SIR.append(SYMBOL2);
    return SIR;
}
