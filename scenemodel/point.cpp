﻿//Project
#include "point.h"
#include "container.h"
#include "element.h"
#include "scenemodel.h"
#include "cgt/cgt.h"


//STL

//Qt

Point::Point(quintptr id_point, QObject *parent)
    : QObject(parent)
    , m_id(id_point)
    , m_cgt(parent->property("cgt").value<PCodeGenTools>())
    , m_model(parent->property("model").value<PSceneModel>())
{
    m_model->addPointToMap(this);
    collectingData();
}

Point::Point(const QJsonObject &object, QObject *parent)
    : QObject(parent)
    , m_model(parent->property("model").value<PSceneModel>())
{
    deserialize(object);
}

void Point::collectingData()
{
    m_type = m_cgt->ptGetType(m_id);
    m_dataType = m_cgt->ptGetDataType(m_id);
    m_index = m_cgt->ptGetIndex(m_id);
    m_name = QString::fromLocal8Bit(m_cgt->ptGetName(m_id));
    m_dpeName = QString::fromLocal8Bit(m_cgt->pt_dpeGetName(m_id));
    m_info = QString::fromLocal8Bit(m_cgt->ptGetInfo(m_id));
    m_linkPoint = m_cgt->ptGetLinkPoint(m_id);
    m_RLinkPoint = m_cgt->ptGetRLinkPoint(m_id);
}

QVariantMap Point::serialize()
{
    QVariantMap data;
    data.insert("id", m_id);
    data.insert("type", m_type);
    data.insert("dataType", m_dataType);
    data.insert("index", m_index);
    data.insert("name", m_name);
    data.insert("dpeName", m_dpeName);
    data.insert("info", m_info);
    data.insert("linkPoint", m_linkPoint);
    data.insert("RLinkPoint", m_RLinkPoint);

    return data;
}

void Point::deserialize(const QJsonObject &object)
{
    m_id = object["id"].toVariant().value<quintptr>();
    m_model->addPointToMap(this);

    m_type = PointType(object["type"].toInt());
    m_dataType = DataType(object["dataType"].toInt());
    m_index = object["index"].toVariant().toUInt();
    m_name = object["name"].toString();
    m_dpeName = object["dpeName"].toString();
    m_info = object["info"].toString();
    m_linkPoint = object["linkPoint"].toVariant().value<quintptr>();
    m_RLinkPoint = object["RLinkPoint"].toVariant().value<quintptr>();
}

quintptr Point::getId() const
{
    return m_id;
}

PElement Point::getParent() const
{
    return qobject_cast<PElement>(parent());
}

void Point::setType(PointType type)
{
    m_type = type;
}

PointType Point::getType() const
{
    return m_type;
}

void Point::setDataType(DataType dataType)
{
    m_dataType = dataType;
}

DataType Point::getDataType() const
{
    return m_dataType;
}

void Point::setIndex(uint index)
{
    m_index = index;
}

uint Point::getIndex() const
{
    return m_index;
}

void Point::setName(const QString &name)
{
    m_name = name;
}

QString Point::getName() const
{
    return m_name;
}

void Point::setDpeName(const QString &dpeName)
{
    m_dpeName = dpeName;
}

QString Point::getDpeName() const
{
    return m_dpeName;
}

void Point::setInfo(const QString &info)
{
    m_info = info;
}

QString Point::getInfo() const
{
    return m_info;
}

void Point::setLinkPoint(quintptr linkPoint)
{
    m_linkPoint = linkPoint;
}

quintptr Point::getLinkPoint() const
{
    return m_linkPoint;
}

void Point::setRLinkPoint(quintptr RLinkPoint)
{
    m_RLinkPoint = RLinkPoint;
}

quintptr Point::getRLinkPoint() const
{
    return m_RLinkPoint;
}

PCodeGenTools Point::getCgt()
{
    return m_cgt;
}

PSceneModel Point::getModel()
{
    return m_model;
}
