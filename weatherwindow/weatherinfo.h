#ifndef WEATHERINFO_H
#define WEATHERINFO_H
#include <QDomDocument>
#include <QDomElement>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>


class WeatherInfo: public QObject
{
    Q_OBJECT
public:
    WeatherInfo();
    QString city, location, unit, language;
    QString curCondition, curTemp, curHumidity, curIcon, curWind;
    QString day[4], low[4], high[4], icon[4], condition[4];
    void update(QString cityName, QString queryLanguage);
private slots:
    void finishedReply(QNetworkReply * reply);
private:
    QNetworkAccessManager http;
signals:
    void updateComplete();
};

#endif // WEATHERINFO_H
