#include "JsonObj.h"

JsonObj::JsonObj(QString str, QObject *parent)
    : QObject(parent),
      str(str)
{
    jsonObj(curObj, 1);
}

QJsonObject JsonObj::obj() const {
    return curObj;
}

int JsonObj::jsonArray(QJsonArray &arr, int s)
{
    /// **Набор переменных:**
    bool openE = false, /// \b * openE - стоит ли знак экранирования
         openQ = false; /// \b * openQ - открыты кавычки

    QString tmp;
    int i;
    char t = 'd', /// \b t for type: world(w), dital(d) or Json(j)
         q = '\0'; /// \b q for quited ' or "

    for (i = s; i < str.size() + 2; i++) {
        QChar c = str.at(i);
        if (!c.isDigit() & (c != '.') & (c != ',') & (c != ']') & !c.isSpace()) t = 'w';
        if ((c == '\\') & !openE) {
            openE = true;
            continue;
        } else openE = false;

//        if ((c == '"') & !openE) openQ = !openQ;
        if (!openE & (q == '\0' ? ((c == '\"') | (c == '\'')) : (c == q))) {
            q = c.toLatin1();
            t = 'w';
            openQ = !openQ;
            continue;
        }



/// **Если встречается Object или Array**
/// \code
/// // создается массив (Array):
        if (c == '[') {
            QJsonArray tmpArr;
            t = 'j';
            i = jsonArray(arr, i+1);
            arr.append(tmpArr);
            continue;
        }
/// // создается объект (Object:
        if (c == '{') {
            t = 'j';
            QJsonObject tmpObj;
            i = jsonObj(tmpObj, i+1);
            arr.append(tmpObj);
            continue;
        }
/// \endcode

/// **Завершаем заплнение массива**
/// \code
/// # ',', ']' - окончание пары или масива

        if (((c == ',') | (c == ']')) & !openQ  & !openE) {
            if (t == 'w') {
                tmp = tmp.trimmed();
                if (tmp.at(0) == '\'') arr.append(tmp.mid(1,tmp.size() - 2));
                else if (tmp.at(0) == '"') arr.append(tmp.mid(1,tmp.size() - 2));
                else arr.append(tmp);
            }
            else if (t == 'd') arr.append(tmp.trimmed().toDouble());
            tmp.clear();
            t = 'd';
        }

        else {
            tmp += c;
        }
        if ((c == ']') & !openQ  & !openE) {
            return i;
        }
/// \endcode
    }

    return i;
}

int JsonObj::jsonObj(QJsonObject &obj, int s)
{
    /// **Набор переменных:**
    bool openE = false, /// \b * openE - стоит ли знак экранирования
         openQ = false, /// \b * openQ - открыты кавычки
/* add */         first = true; /// \b * first
 /// \li true: определяет ключ(key)
 /// \li false: либо значение (value)

    char t = 'd', /// \b t for type: world(w), dital(d) or Json(j)
         q = '\0'; /// \b q for quited ' or "

    QString tmpKey, tmpValue; /*! QString \b tmpKey, \b tmpValue - переменные для QJsonObject
                                \li \b tmpKey соответствует ключу \b key
                                \li \b tmpValue соответствует значению переменной \b value
                                */


    int i;
    for (i = s; i < str.size(); i++) {
        QChar c = str.at(i);
        if (!c.isDigit() & (c != '.') & (c != ',') & (c != ']') & !c.isSpace()) t = 'w';
        if ((c == '\\') & !openE) {
            openE = true;
            continue;
        } else openE = false;
        if (!openE & (q == '\0' ? ((c == '\"') | (c == '\'')) : (c == q))) {
            q = c.toLatin1();
            t = 'w';
            openQ = !openQ;
            continue;
        }
/* add */
        if ((c == ':') & !openE) {
            first = false;
            q = '\0';
            t = 'd';
            continue;
        }
/**/
/// **Если встречается Object или Array**
/// \code
/// // создается массив (Array):
        if (c == '[') {
            QJsonArray arr; ///  arr
            t = 'j';
            i = jsonArray(arr, i+1);
            obj[tmpKey] = arr;
            tmpKey = "";
            continue;
        }
/// // создается объект (Object:
        if (c == '{') {
            t = 'j';
            QJsonObject tmpObj;
            i = jsonObj(tmpObj, i+1);
            obj[tmpKey] = tmpObj;
            continue;
        }
/// \endcode

/// **Завершаем заплнение объекта**
/// \code
/// # ',', '}' - окончание пары или масива

        if (((c == ',') | (c == '}')) & !openQ  & !openE) {
            if (t == 'j') {
                first = true;
                continue;
            }
            first = true;
            q = '\0';

            QString key;

            if (tmpKey.at(0) == '"') t = 'q';
            else {
                 for (int j = 0; j < tmpKey.size() + 1; j++) {
                     if (!tmpValue.at(j).isNumber()) {
                         t = 'w';
                         break;
                     }
                 }
            }

/// # заполняем массив
            key = tmpKey.trimmed();
            switch (t) {
                case 'd': obj[key] = tmpValue.trimmed().toDouble(); break;
                case 'w': obj[key] = tmpValue.trimmed(); break;
                default: obj[key.mid(1,key.size() - 2)] = tmpValue.trimmed();
            }
            tmpValue = tmpKey = "";
        }
        else {
            if (first) tmpKey += c;
            else tmpValue += c;
        }
        if ((c == '}') & !openQ  & !openE) {
            return i;
        }
        /// \endcode
/**/
    }

    return i;

}
