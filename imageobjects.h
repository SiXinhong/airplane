#ifndef IMAGEOBJECTS_H
#define IMAGEOBJECTS_H
#include<vector>
#include<QString>
#include"objectitem.h"
#include<QJsonDocument>
#include<QVariantMap>

using namespace std;
class ImageObjects
{
public:
    ImageObjects();
    QString filename;
    vector<ObjectItem> om;
    void LoadJson(QString json);

};

#endif // IMAGEOBJECTS_H
