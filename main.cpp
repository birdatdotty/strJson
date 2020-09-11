#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

#include "json.h"

#include <QJsonDocument>
#include <iostream>

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

    QString str2 = "{arr: ['1,2', '5', 3, {d: d}],ss: 333,'ss2': dd,o: 13,'1': 333,'2': t2,obj: {d: d}}";
    QJsonObject obj2;
    qInfo() << str2;
    jsonObj(obj2,str2);

    QJsonDocument doc(obj2);
    std::cout << doc.toJson(QJsonDocument::Compact).toStdString() << std::endl;
}
