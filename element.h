#pragma once

//Project
#include "CGTShare.h"
#include "point.h"
#include "property.h"
#include "cgt.h"
#include "global.h"

//STL

//Qt
#include <QString>

class Element
{
private:
    //ru Данные элемента
    const id_element m_id;
    id_element m_linkMain{};

    //Указатели и ссылки
    PContainer m_parent{};
    PElement m_linkMainPtr{};

    QString m_className{};
    ElementClass m_classIndex{};
    ElementFlgs m_flags{};
    QString m_inherit{};
    int m_group{};
    QString m_interface{};
    QString m_infSub{};
    bool m_linkIs{};
    int m_propCount{};
    int m_ptCount{};

    int m_posX{};
    int m_posY{};
    int m_sizeW{};
    int m_sizeH{};

    //Массивы
    Containers m_containers;
    Points m_points;
    Properties m_properties;

public:
    explicit Element(id_element eId, PContainer parent);
    ~Element();

private:
    void collectingData();

public:
    //ru Добавляем контейнер в список контейнеров элемента
    void addContainer(PContainer container);

    ElementClass getClassIndex() const
    {
        return m_classIndex;
    }
    ElementFlgs getFlags() const
    {
        return m_flags;
    }

    uint getCountContainers() const
    {
        return m_containers.count();
    }
    id_element getId() const
    {
        return m_id;
    }
    Containers &getContainers()
    {
        return m_containers;
    }
    Points &getPoints()
    {
        return m_points;
    }
    Properties &getProperties()
    {
        return m_properties;
    }

};
