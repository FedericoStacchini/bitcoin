#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QJsonObject sendRequest() {

    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("https://www.bitstamp.net/api/v2/ticker/btceur/") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();

        //parse json
        //qDebug() << "Response:" << strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObj = jsonResponse.object();

        delete reply;
        return jsonObj;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return sendRequest();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QJsonObject jsonObj = sendRequest();
    ui->label->setText("Time:" + QDateTime::fromTime_t(jsonObj["timestamp"].toString().toULongLong()).toString("hh:mm:ss"));
    ui->label_2->setText("Volume:" + jsonObj["volume"].toString());
    ui->label_3->setText("High:" + jsonObj["high"].toString());
    ui->label_4->setText("Low:" + jsonObj["low"].toString());
    ui->label_5->setText("Open:" + jsonObj["open"].toString());
    ui->label_6->setText("Last:" + jsonObj["last"].toString());
    ui->label_7->setText("Ask:" + jsonObj["ask"].toString());
    ui->label_8->setText("Bid:"+ jsonObj["bid"].toString());
    ui->label_9->setText("Vwap:" + jsonObj["vwap"].toString());

    ui->statusBar->showMessage(QDate::currentDate().toString("dd/MM/yyyy") + " " + QTime::currentTime().toString("hh:mm:ss"));
}


