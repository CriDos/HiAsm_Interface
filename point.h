#pragma once

//Project
#include "CGTShare.h"

//STL
#include <memory>
#include <vector>

//Qt
#include <QDebug>

class Point;
typedef std::shared_ptr<Point> PPoint;
typedef std::vector<PPoint> ArrayPPoints;

class Point
{
private:
    const id_point m_ptId {};

    //ru Данные точки
    DataTypes m_dataType{};
    int m_index{};
    QString m_info{};
    id_point m_linkPoint{};
    QString m_name{};
    id_element m_parent{};
    id_point m_RLinkPoint{};
    PointTypes m_type{};
    QString m_dpeName{};

public:
    explicit Point(id_point pt);
    ~Point();

private:
    void getPointData();
};
