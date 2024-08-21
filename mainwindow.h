#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QRegularExpression>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStatusBar>
#include <QMenuBar>
#include <QTextEdit>
#include <QLineEdit>
#include <QAction>
#include <QLabel>
#include <QDebug>
#include "stream_enum.h" // Include the Streams enum

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QNetworkAccessManager *manager; // Declare as a pointer
    void jsonParser(const QByteArray &responseData, bool Search, bool Stream);

    // Enum definition
    enum Stations {
        band,
        callletters,
        city,
        dartUrl,
        description,
        frequency,
        id,
        logo,
        name,
        newlogo,
        rank,
        score,
        shareLink,
        state,
        StationCount // Keep track of the number of enum values
    };
    // List to hold the station mappings
    QMap<Stations, QString> stationValues;
    QList<QMap<Stations, QString>> allStations;
    QString outputText, searchText, errorText;
    bool Search, Stream;

private slots:
    //Private functions
    void SearchTriggered();
    void StreamTriggered();
    void onFinished(QNetworkReply* reply);
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError code);
    void slotSslErrors(const QList<QSslError> &errors);
    void populateStationsFromJson(const QJsonObject &jsonObjects);

private:
    Ui::MainWindow *ui;
    QUrl url;
    QUrlQuery query;
    QNetworkRequest request;
    QNetworkReply *reply;

};

#endif // MAINWINDOW_H
