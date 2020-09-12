#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

#include "json.h"

#include "JsonObj.h"

#include <QJsonDocument>
#include <iostream>

int main()
{
    QString str2 = "{arr: ['1,2', '5', 3, {d: d}],ss: 333,'ss2': dd,o: 13,'1': 333,'2': t2,obj: {d: d}}";
    QJsonObject obj2;
    qInfo() << "test line:" << str2;
    jsonObj(obj2,str2);

    QJsonDocument doc(obj2);
    std::cout << doc.toJson(QJsonDocument::Compact).toStdString() << std::endl;

    // ex1.
    JsonObj o(str2);
    qInfo() << o.obj()["1"].toString();

    // ex2.
    qInfo() << JsonObj(str2).obj()["ss2"].toString();


    return 0;
}
