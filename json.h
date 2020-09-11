#ifndef JSON_H
#define JSON_H

/** @file */

/**
 * A mathematical set
 */

#include <QJsonObject>
#include <QJsonArray>

int jsonObj(QJsonObject &obj, QString &str, int s = 1);
int jsonArray(QJsonArray &arr, QString &str, int s = 1);

#endif // JSON_H
