#ifndef JSONOBJ_H
#define JSONOBJ_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

///
/// \brief The JsonObj class для перевода строки в QJsonObject
///
/// На основе строки будет создан объект для последующей работы с ним
///
class JsonObj : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief JsonObj - создает объект на основе строки
    /// \param str - строка на основе которой создается объект
    /// \param parent - объект при удаление которого удаляется текущий
    ///
    explicit JsonObj(QString str, QObject *parent = nullptr);
    /// \brief возращает полученный объект
    QJsonObject obj() const;

private:
    ///
    /// \brief jsonArray переводит текущюю строку в массив
    /// \param arr - массив, который заполняется
    /// \param s - позиция с которой надо начинать обработку
    /// \return позицию последнего символа массива
    ///
    int jsonArray(QJsonArray &arr, int s);

    ///
    /// \brief jsonObj переводит текущюю строку в объект
    /// \param obj - объект для заполнения
    /// \param s - позиция с которой надо начинать обработку
    /// \return позицию последнего символа объекта
    ///
    int jsonObj(QJsonObject &obj, int s);

    QJsonObject curObj;

    QString str;

signals:

};

#endif // JSONOBJ_H
