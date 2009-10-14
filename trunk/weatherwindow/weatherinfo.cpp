#include "weatherinfo.h"
#include <QDebug>

WeatherInfo::WeatherInfo()
{
    connect(&http,SIGNAL(finished(QNetworkReply*)),this,SLOT(finishedReply(QNetworkReply*)));
}

void WeatherInfo::update(QString cityName, QString queryLanguage)
{
    QString url="http://www.google.com/ig/api?weather=%1&hl=%2";
    url=url.arg(cityName,queryLanguage);//TODO: later check whether the city name or query language is empty
    http.get(QNetworkRequest(QUrl(url)));
    city=cityName;
    language=queryLanguage;
}

void WeatherInfo::finishedReply(QNetworkReply* reply)
{
    QDomDocument doc;
    doc.setContent(reply->readAll());
    //analysis the xml reply and digest the data into member variables
    //the following code are highly dependent to the google api result,
    //so it might be subject to change according to google's changes
    QDomNode e=doc.elementsByTagName("forecast_information").at(0);
    location=e.firstChildElement("city").attribute("data");
    unit=e.firstChildElement("unit_system").attribute("data");
    QChar dUnit;
    if(unit=="US")
        dUnit=QChar(0x2109);
    else
        dUnit=QChar(0x2103);
    e=doc.elementsByTagName("current_conditions").at(0);
    curCondition=e.firstChildElement("condition").attribute("data");
    //TODO: check unit settings here
    if(unit=="US")
        curTemp=e.firstChildElement("temp_f").attribute("data")+dUnit;
    else
        curTemp=e.firstChildElement("temp_c").attribute("data")+dUnit;
    curHumidity=e.firstChildElement("humidity").attribute("data");
    curIcon=e.firstChildElement("icon").attribute("data");
    curIcon=curIcon.mid(curIcon.lastIndexOf("/")+1).replace(".gif",".png");
    curWind=e.firstChildElement("wind_condition").attribute("data");
    qDebug()<<location<<unit<<curCondition<<curTemp<<curHumidity<<curIcon<<curWind;

    QDomNodeList list=doc.elementsByTagName("forecast_conditions");
    for(int i=0;i<list.count();i++)
    {
        e=list.at(i);
        day[i]=e.firstChildElement("day_of_week").attribute("data");
        low[i]=e.firstChildElement("low").attribute("data")+dUnit;
        high[i]=e.firstChildElement("high").attribute("data")+dUnit;
        icon[i]=e.firstChildElement("icon").attribute("data");
        icon[i]=icon[i].mid(icon[i].lastIndexOf("/")+1).replace(".gif",".png");
        condition[i]=e.firstChildElement("condition").attribute("data");
        qDebug()<<day[i]<<low[i]<<high[i]<<icon[i]<<condition[i];
    }
    emit updateComplete();
}
