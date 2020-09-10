#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

int jsonObj(QJsonObject &obj, QString &str, int s = 1) ;

int jsonArray(QJsonArray &arr, QString &str, int s = 1)  {
    bool openE = false,
         openQ = false;

    QString tmp;
    int i;
    char t = 'd', // type: world(w), dital(d) or Json(j)
         q = '\0'; // for quited ' or "

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



/// for Json Array and Object
        if (c == '[') {
            QJsonArray tmpArr;
            t = 'j';
            i = jsonArray(arr, str, i+1);
            arr.append(tmpArr);
            continue;
        }
        if (c == '{') {
            t = 'j';
            qInfo() << "{" << str.mid(i);
            QJsonObject tmpObj;
            i = jsonObj(tmpObj, str, i+1);
            arr.append(tmpObj);
            continue;
        }
/// -for Json Array and Object

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

    }

    return i;
}

int jsonObj(QJsonObject &obj, QString &str, int s)  {
    bool openE = false,
         openQ = false,
/* add */         first = true;

    char t = 'd', // type: world(w), dital(d) or Json(j)
         q = '\0'; // for quited ' or "

    QString tmpKey, tmpValue;

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
/// for Json Array and Object
        if (c == '[') {
            QJsonArray arr;
            t = 'j';
            i = jsonArray(arr, str, i+1);
            obj[tmpKey] = arr;
            continue;
        }
        if (c == '{') {
            t = 'j';
            qInfo() << "{" << str.mid(i);
            QJsonObject tmpObj;
            i = jsonObj(tmpObj, str, i+1);
            obj[tmpKey] = tmpObj;
            continue;
        }
/// -for Json Array and Object
/* replace */
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
/**/
    }

    return i;
}

int main(int argc, char *argv[])
{
    QString str2 = "{arr:['1,2',\"5\", 3, {d:d}],ss:'3\\\"33','ss2':\"d\\d\",o:13,1:333,2:t2,obj:{d:d}}";
    QJsonObject obj2;
    qInfo() << str2;
    qInfo() << jsonObj(obj2,str2) << "|" << obj2;
}
