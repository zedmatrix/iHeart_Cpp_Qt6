#include "mainwindow.h"

void MainWindow::populateStationsFromJson(const QJsonObject &jsonObjects) {
    // Lambda function to populate the map for a single station
    auto populateStations = [](const QJsonObject &newObj) {
        QMap<Stations, QString> stationValues;
        foreach (const QString &key, newObj.keys()) {
            QJsonValue value = newObj.value(key);
            if (key == "band") {
                stationValues[band] = value.toString();
            } else if (key == "callletters") {
                stationValues[callletters] = value.toString();
            } else if (key == "city") {
                stationValues[city] = value.toString();
            } else if (key == "dartUrl") {
                stationValues[dartUrl] = value.toString();
            } else if (key == "description") {
                stationValues[description] = value.toString();
            } else if (key == "frequency") {
                stationValues[frequency] = value.toString();
            } else if (key == "id") {
                stationValues[id] = QString::number(value.toInt());
            } else if (key == "logo") {
                stationValues[logo] = value.toString();
            } else if (key == "name") {
                stationValues[name] = value.toString();
            } else if (key == "newlogo") {
                stationValues[newlogo] = value.toString();
            } else if (key == "rank") {
                stationValues[rank] = value.toString();
            } else if (key == "score") {
                stationValues[score] = QString::number(value.toDouble());
            } else if (key == "shareLink") {
                stationValues[shareLink] = value.toString();
            } else if (key == "state") {
                stationValues[state] = value.toString();
            }
        }
        return stationValues;
    };

    // Now populate the stations in the MainWindow class
    QJsonValue stationsValue = jsonObjects.value("stations");
    if (!stationsValue.isArray()) {
        qDebug() << "Error: Expected an array for 'stations' key";
        return;
    }
    QJsonArray stationsArray = stationsValue.toArray();
    // Clear the current list of stations before populating
    allStations.clear();

    // Iterate over the stations array
    foreach (const QJsonValue &value, stationsArray) {
        if (value.isObject()) {
            QJsonObject stationObj = value.toObject();
             allStations.append(populateStations(stationObj));
        }

    }

    // Optional: You might want to update the UI or do further processing here
    qDebug() << "Stations populated. Total count:" << allStations.size();
    for (const QMap<Stations, QString> &station : allStations) {
    // Access the values for 'id' and 'name' from each station
        outputText += QString("%1 - %2, %3\n")
            .arg(station[id])
            .arg(station[name])
            .arg(station[description]);
    }
    ui->outputText->setPlainText(outputText);
}
