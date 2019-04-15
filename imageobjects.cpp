#include "imageobjects.h"

ImageObjects::ImageObjects()
{

}

void ImageObjects::LoadJson(QString json)
{
    QJsonParseError error;
    QJsonDocument jd = QJsonDocument::fromJson(json.toUtf8(),&error);
    if(error.error == QJsonParseError::NoError){
        if(jd.isObject()){
            QVariantMap qvm = jd.toVariant().toMap();
            this->filename = qvm["filename"].toString();
            QVariantList list = qvm["data"].toList();
            foreach (QVariant items, list) {
                QVariantMap item = items.toMap();
                QString name = item["name"].toString();
                QVariantList l = item["box_points"].toList();
                int p0 = l.at(0).toInt();
                int p1 = l.at(1).toInt();
                int p2 = l.at(2).toInt();
                int p3 = l.at(3).toInt();
                QPoint pointstart(p0,p1);
                QPoint pointend(p2,p3);
                ObjectItem it;
                it.name=name;
                it.startPoint= pointstart;
                it.endPoint = pointend;
                om.push_back(it);
//                    int p1 = item['']
            }
         }

    }
}
