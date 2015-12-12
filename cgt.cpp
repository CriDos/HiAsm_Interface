﻿//Project
#include "cgt.h"
#include "proxycgt.h"
#include "global.h"

//STL

//Qt
#include <QDebug>
#include <QFlags>

namespace fcgt
{
    bool isSelect(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_SELECT;
    }

    bool isParent(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_PARENT;
    }

    bool isCore(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_CORE;
    }

    bool isNoDelete(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_NODELETE;
    }

    bool isMulti(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_MULTI;
    }

    bool isEdit(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_EDIT;
    }

    bool isLink(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_LINK;
    }


    bool isEditMultiEx(const ElementClass &eClass)
    {
        return eClass == CI_EditMultiEx;
    }

    bool isPolyMulti(const ElementClass &eClass)
    {
        return eClass == CI_PolyMulti;
    }
}


namespace cgt
{
    //!~~~~~~~~~~~~~~~~~~~~~ служебные функции ~~~~~~~~~~~~~~~~~~~~~~~
    static TBuildProcessRec *m_buildProcess;
    static PCodeGenTools m_origCgt{};
    static PCodeGenTools m_cgt{};
    static id_sdk m_sdk{};

    //ru Инициализация параметров
    void init(TBuildProcessRec &params)
    {
        m_buildProcess = &params;
        m_origCgt = params.cgt;
        m_cgt = params.cgt;
        m_sdk = params.sdk;
    }

    void setProxyCgt(PCodeGenTools proxyCgt)
    {
        m_cgt = proxyCgt;
        m_buildProcess->cgt = proxyCgt;
    }

    id_sdk getMainSDK()
    {
        return m_sdk;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в контейнере.

    int sdkGetCount(id_sdk SDK)
    {
        return m_cgt->sdkGetCount(SDK);
    }

    //ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
    id_element sdkGetElement(id_sdk SDK, int Index)
    {
        return m_cgt->sdkGetElement(SDK, Index);
    }

    //ru Возвращает ID элемента по имени элемента.
    id_element sdkGetElementName(id_sdk SDK, char *Name)
    {
        return m_cgt->sdkGetElementName(SDK, Name);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает флаги элемента.
    ElementFlags elGetFlag(id_element e)
    {
        return m_cgt->elGetFlag(e);
    }

    //ru Возвращает количество свойств элемента.
    int elGetPropCount(id_element e)
    {
        return m_cgt->elGetPropCount(e);
    }

    //ru Возвращает свойство элемента по индексу, с порядковым номером из INI.
    id_prop elGetProperty(id_element e, int Index)
    {
        return m_cgt->elGetProperty(e, Index);
    }

    //ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
    bool elIsDefProp(id_element e, int Index)
    {
        return m_cgt->elIsDefProp(e, Index);
    }

    //ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
    id_element elSetCodeName(id_element e, const char *Name)
    {
        return m_cgt->elSetCodeName(e, Name);
    }

    //ru Возвращает уникальное имя элемента
    const char *elGetCodeName(id_element e)
    {
        return m_cgt->elGetCodeName(e);
    }

    //ru Возвращает имя класса элемента.
    const char *elGetClassName(id_element e)
    {
        return m_cgt->elGetClassName(e);
    }

    //ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
    const char *elGetInfSub(id_element e)
    {
        return m_cgt->elGetInfSub(e);
    }

    //ru Возвращает общее количество видимых точек у элемента.
    int elGetPtCount(id_element e)
    {
        return m_cgt->elGetPtCount(e);
    }

    //ru Возвращает ID точки по её индексу.
    id_point elGetPt(id_element e, int i)
    {
        return m_cgt->elGetPt(e, i);
    }

    //ru Возвращает ID точки по её имени.
    //[deprecated]
    id_point elGetPtName(id_element e, const char *Name)
    {
        return m_cgt->elGetPtName(e, Name);
    }

    //ru Возвращает индекс класса элемента.
    ElementClass elGetClassIndex(id_element e)
    {
        return m_cgt->elGetClassIndex(e);
    }

    //ru Возвращает ID внутренней схемы для контейнеров,
    //ru или ID родителя id_element для редактора контейнера (ELEMENT_FLG_IS_EDIT).
    id_sdk elGetSDK(id_element e)
    {
        return m_cgt->elGetSDK(e);
    }

    //ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
    bool elLinkIs(id_element e)
    {
        return m_cgt->elLinkIs(e);
    }

    //ru Возвращает ID главного элемента(тот, на который ссылаются другие).
    id_element elLinkMain(id_element e)
    {
        return m_cgt->elLinkMain(e);
    }

    //ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
    void elGetPos(id_element e, int &X, int &Y)
    {
        m_cgt->elGetPos(e, X, Y);
    }

    //ru Помещает в переменные "W" и "H", размеры элемента.
    void elGetSize(id_element e, int &W, int &H)
    {
        m_cgt->elGetSize(e, W, H);
    }

    //ru Возвращает внутренний ID элемента (отличается от внешнего).
    //[deprecated]
    int elGetEID(id_element e)
    {
        return m_cgt->elGetEID(e);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID точки, с которой соединена указанная.
    //TODO [deprecated?], в CodeGen.dpr не используется.
    id_point ptGetLinkPoint(id_point p)
    {
        return m_cgt->ptGetLinkPoint(p);
    }

    //ru Возвращает ID точки, с которой соединена указанная точка,
    //ru без учета точек разрыва и хабов.
    id_point ptGetRLinkPoint(id_point p)
    {
        return m_cgt->ptGetRLinkPoint(p);
    }

    //ru Возвращает тип точек(константы PointTypes).
    PointTypes ptGetType(id_point p)
    {
        return m_cgt->ptGetType(p);
    }

    //ru Возвращает имя точки.
    const char *ptGetName(id_point p)
    {
        return m_cgt->ptGetName(p);
    }

    //ru Возвращает ID элемента, которому принадлежит точка.
    id_element ptGetParent(id_point p)
    {
        return m_cgt->ptGetParent(p);
    }

    //ru Возвращает тип точки (PointTypes).
    PointTypes ptGetIndex(id_point p)
    {
        return m_cgt->ptGetIndex(p);
    }

    //ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
    const char *pt_dpeGetName(id_point p)
    {
        return m_cgt->pt_dpeGetName(p);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип свойства.
    DataTypes propGetType(id_prop prop)
    {
        return m_cgt->propGetType(prop);
    }

    //ru Возвращает имя свойства.
    const char *propGetName(id_prop prop)
    {
        return m_cgt->propGetName(prop);
    }

    //ru Возвращает значение свойства в виде указателя на данные.
    quintptr propGetValue(id_prop prop)
    {
        return m_cgt->propGetValue(prop);
    }

    //ru Возвращает значение свойства в формате uchar.
    uchar propToByte(id_prop prop)
    {
        return m_cgt->propToByte(prop);
    }

    //ru Возвращает значение свойства в формате int.
    int propToInteger(id_prop prop)
    {
        return m_cgt->propToInteger(prop);
    }

    //ru Возвращает значение свойства в формате float.
    float propToReal(id_prop prop)
    {
        return m_cgt->propToReal(prop);
    }

    //ru Возвращает значение свойства в виде C строки.
    const char *propToString(id_prop prop)
    {
        return m_cgt->propToString(prop);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~

    //ru Добавляет имя файла в общий список временных файлов
    //ru для последующего удаления файла.
    int resAddFile(const char *Name)
    {
        return m_cgt->resAddFile(Name);
    }

    //ru Добавляет иконку в ресурсы и в список временных файлов,
    //ru и возвращают имя временного файла.
    //TODO p - является свойством, которое содержит иконку?
    const char *resAddIcon(id_prop p)
    {
        return m_cgt->resAddIcon(p);
    }

    //ru Добавляет строку в ресурсы и в список временных файлов.
    //TODO Что возвращает?
    const char *resAddStr(const char *p)
    {
        return m_cgt->resAddStr(p);
    }

    //ru Добавляет поток (данные) в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    const char *resAddStream(id_prop p)
    {
        return m_cgt->resAddStream(p);
    }

    //ru Добавляет звук в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    const char *resAddWave(id_prop p)
    {
        return m_cgt->resAddWave(p);
    }

    //ru Добавляет картинку в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    const char *resAddBitmap(id_prop p)
    {
        return m_cgt->resAddBitmap(p);
    }

    //ru Добавляет меню в ресурсы и в список временных файлов.
    //[deprecated]
    const char *resAddMenu(id_prop p)
    {
        return m_cgt->resAddMenu(p);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Выводит строку Text в окно Отладка цветом Color
    //ru Всего возвращает 0.
    int _Debug(const char *Text, int Color)
    {
        return m_cgt->_Debug(Text, Color);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает значение параметра среды по его индексу
    int GetParam(CgtParams index, void *value)
    {
        return m_cgt->GetParam(index, value);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в массиве.
    int arrCount(id_array a)
    {
        return m_cgt->arrCount(a);
    }

    //ru Возвращает тип элементов в массиве.
    DataTypes arrType(id_array a)
    {
        return m_cgt->arrType(a);
    }

    //ru Возвращает имя элемента с индексом Index.
    const char *arrItemName(id_array a, int Index)
    {
        return m_cgt->arrItemName(a, Index);
    }

    //ru Возвращает значение элемента с индексом Index
    quintptr arrItemData(id_array a, int Index)
    {
        return m_cgt->arrItemData(a, Index);
    }

    //ru Получаем элемент массива в виде свойства,
    //ru для дальнейшей работы с ним prop* функциями.
    id_data arrGetItem(id_array a, int Index)
    {
        return m_cgt->arrGetItem(a, Index);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает >0, если запускаем cборку и запуск схемы в режиме отладки,
    //ru иначе 0.
    int isDebug(id_sdk e)
    {
        return m_cgt->isDebug(e);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~

    //ru Возвращает тип данных.
    DataTypes dtType(id_data d)
    {
        return m_cgt->dtType(d);
    }

    //ru Возвращает данные в формате: строка в стиле C.
    const char *dtStr(id_data d)
    {
        return m_cgt->dtStr(d);
    }

    //ru Возвращает данные в формате: целое число.
    int dtInt(id_data d)
    {
        return m_cgt->dtInt(d);
    }

    //ru Возвращает данные в формате: число с плавающей запятой.
    double dtReal(id_data d)
    {
        return m_cgt->dtReal(d);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает название шрифта.
    const char *fntName(id_font f)
    {
        return m_cgt->fntName(f);
    }
    //ru Возвращает размер шрифта.
    int fntSize(id_font f)
    {
        return m_cgt->fntSize(f);
    }
    //ru Возвращает стиль шрифта.
    uchar fntStyle(id_font f)
    {
        return m_cgt->fntStyle(f);
    }
    //ru Возвращает цвет шрифта.
    uint fntColor(id_font f)
    {
        return m_cgt->fntColor(f);
    }
    //ru Возвращает кодировку шрифта.
    uchar fntCharSet(id_font f)
    {
        return m_cgt->fntCharSet(f);
    }

    //!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
    //!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.

    //ru Возвращает пользовательские данные элемента.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
    quintptr elGetData(id_element e)
    {
        return m_cgt->elGetData(e);
    }

    //ru Устанавливает пользовательские данные элементу.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
    void elSetData(id_element e, const quintptr data)
    {
        m_cgt->elSetData(e, data);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных точки.
    DataTypes ptGetDataType(id_point p)
    {
        return m_cgt->ptGetDataType(p);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID родительского контейнера элемента.
    id_sdk elGetParent(id_element e)
    {
        return m_cgt->elGetParent(e);
    }

    //ru Возвращает количество свойств в списке свойств(из панели свойств).
    //ru В RTCG используется аналогичная функция - elGetPropCount.
    //[deprecated]
    int elGetPropertyListCount(id_element e)
    {
        return m_cgt->elGetPropertyListCount(e);
    }

    //ru Возвращает свойство из списка свойств (PropertyList).
    //[deprecated]
    id_proplist elGetPropertyListItem(id_element e, int i)
    {
        return m_cgt->elGetPropertyListItem(e, i);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает имя свойства.
    const char *plGetName(id_prop p)
    {
        return m_cgt->plGetName(p);
    }

    //ru Возвращает описание свойства.
    const char *plGetInfo(id_prop p)
    {
        return m_cgt->plGetInfo(p);
    }

    //ru Возвращает группу свойсва.
    const char *plGetGroup(id_prop p)
    {
        return m_cgt->plGetGroup(p);
    }

    //ru Возвращает указатель на данные свойства.
    quintptr plGetProperty(id_prop p)
    {
        return m_cgt->plGetProperty(p);
    }

    //ru Возвращает ID родительского элемента указанного свойства.
    id_element plGetOwner(id_prop p)
    {
        return m_cgt->plGetOwner(p);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает описание точки.
    const char *ptGetInfo(id_point p)
    {
        return m_cgt->ptGetInfo(p);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID элемента, прилинкованного к указанному свойству.
    id_element propGetLinkedElement(id_element e, const char *propName)
    {
        return m_cgt->propGetLinkedElement(e, propName);
    }

    //ru Возвращает 1, если свойство помечено на перевод.
    int propIsTranslate(id_element e, id_prop p)
    {
        return m_cgt->propIsTranslate(e, p);
    }

    //ru Предназначение данной функции так и небыло найдено.
    //ru Всегда возвращает 0.
    //[deprecated]
    id_element propGetLinkedElementInfo(id_element e, id_prop prop, char *_int)
    {
        return m_cgt->propGetLinkedElementInfo(e, prop, _int);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает SDK контейнера по его индексу.
    id_sdk elGetSDKByIndex(id_element e, int index)
    {
        return m_cgt->elGetSDKByIndex(e, index);
    }

    //ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
    int elGetSDKCount(id_element e)
    {
        return m_cgt->elGetSDKCount(e);
    }

    //ru Возвращает имя контейнера по индексу.
    const char *elGetSDKName(id_element e, int index)
    {
        return m_cgt->elGetSDKName(e, index);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает элемент родитель для данного SDK.
    //ru Возвращает 0, если контейнер не имеет родителя.
    id_element sdkGetParent(id_sdk SDK)
    {
        return m_cgt->sdkGetParent(SDK);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает интерфейсы, предоставляемые элементом.
    //ru Содержимое поля Interfaces= из конфигурации элемента.
    const char *elGetInterface(id_element e)
    {
        return m_cgt->elGetInterface(e);
    }

    //ru Возвращает список классов, от которых наследуется элемент
    //ru Содержимое поля Inherit= из конфигурации элемента.
    const char *elGetInherit(id_element e)
    {
        return m_cgt->elGetInherit(e);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
    int resEmpty()
    {
        return m_cgt->resEmpty();
    }

    //ru Устанавливает префикс для имен ресурсов.
    int resSetPref(const char *pref)
    {
        return m_cgt->resSetPref(pref);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет информацию в информационную панель
    int _Error(int line, id_element e, const char *text)
    {
        return m_cgt->_Error(line, e, text);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
    //[deprecated]
    int elGetGroup(id_element e)
    {
        return m_cgt->elGetGroup(e);
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Сохраняет данные свойства в файл.
    //[deprecated]
    int propSaveToFile(id_prop p, const char *fileName)
    {
        return m_cgt->propSaveToFile(p, fileName);
    }





}
