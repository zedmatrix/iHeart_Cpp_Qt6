#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsonParser.cpp"
#include "populate_stations.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    // Setup the Ui:: MainWindow
    ui->setupUi(this);

    this->setWindowTitle("Network Access Test");

    searchText = ui->searchTerm->text();
    qDebug() << searchText;
    // connect the buttons to routines
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionSearch, &QAction::triggered, this, &MainWindow::SearchTriggered);
    connect(ui->actionGet_Stream, &QAction::triggered, this, &MainWindow::StreamTriggered);

    manager = new QNetworkAccessManager(this); // Instantiate the pointer
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onFinished);

    // Setup url for reuest
    QUrl url("http://api2.iheart.com/api/v1/catalog/searchAll");
    //QUrlQuery query;

    // Add query parameters
    query.addQueryItem("keywords", searchText);

    // Set the query on the URL
    url.setQuery(query);

    // Create the request with the URL
    QNetworkRequest request(url);

    // Set the raw header (e.g., User-Agent)
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    // Send the request using QNetworkAccessManager
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QIODevice::readyRead, this, &MainWindow::slotReadyRead);
    connect(reply, &QNetworkReply::errorOccurred, this, &MainWindow::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &MainWindow::slotSslErrors);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFinished(QNetworkReply* reply)
{
    // Handle onFinished signal here
    if (reply->error() == QNetworkReply::NoError) {
        ui->rawText->setText("No Error");
        QUrl requestUrl = reply->request().url();

        if (requestUrl.path().contains("/searchAll")) {
            QByteArray responseData = reply->readAll();     //get reply from server
            jsonParser(responseData, true, false);          // Set Search = true, Stream = false
        } else if (requestUrl.path().contains("/liveStations")) {
            // Get the status code from the reply
            QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            // Check if the status code is 200
            if (statusCode.isValid() && statusCode.toInt() == 200) {
                qDebug() << "Request successful, status code:" << statusCode.toInt();
                QByteArray responseData = reply->readAll(); // Optionally read the data
                Stream = true;
                Search = false;
                jsonParser(responseData, false, true);      // Set Search = false, Stream = true
                qDebug() << "Response data:" << responseData;
            } else {
                qDebug() << "Request failed, status code:" << statusCode.toInt();
            }
        } else {
            // Handle unexpected or unrecognized paths
            qDebug() << "Received response for an unexpected path:" << requestUrl.path();
            // Handle the unexpected data or log an error
        }
    } else {
        errorText = reply->errorString();
        ui->rawText->setText("Error " + errorText);
    }
    reply->deleteLater();
}

void MainWindow::slotReadyRead()
{
    // Handle readyRead signal here
}

void MainWindow::slotError(QNetworkReply::NetworkError code)
{
    // Handle errorOccurred signal here
}

void MainWindow::slotSslErrors(const QList<QSslError> &errors)
{
    // Handle sslErrors signal here
}

void MainWindow::SearchTriggered() {
    // Code to execute when the action is triggered
    ui->rawText->setText("Search has been Triggered");
    QString x = ui->searchTerm->text();
    if (x != searchText) {
        searchText = ui->searchTerm->text();
        query.clear();

        // setup for new query item
        query.addQueryItem("keywords", searchText);
        QUrl url("http://api2.iheart.com/api/v1/catalog/searchAll");
        url.setQuery(query);
        request.setUrl(url);

        // Debug the URL and query
        qDebug() << "Full URL:" << url.toString();
        qDebug() << "Query:" << query.toString();
        QNetworkRequest request(url);
        reply = manager->get(request);
    } else {
        qDebug() << "Error: Search Text is not different";
    }
}

void MainWindow::StreamTriggered() {
    // Code to execute when the action is triggered
    ui->rawText->setText("Get Stream has been Triggered");

    QString y = ui->searchTerm->text();
    QRegularExpression regex("^\\d{4}$");
    // Check if the input matches the 4-digit pattern
    if (regex.match(y).hasMatch()) {
        QUrl url("https://api.iheart.com/api/v2/content/liveStations/");
        url.setPath(url.path() + y);
        qDebug() << "Full URL:" << url.toString();
        QNetworkRequest request(url);
        reply = manager->get(request);
    } else {
        qDebug() << "Invalid 4-digit value for Stream Get.";
    }

}
