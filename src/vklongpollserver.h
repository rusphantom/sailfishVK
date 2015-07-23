#ifndef VKLONGPOLLSERVER_H
#define VKLONGPOLLSERVER_H

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QSet>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QPair>
#include "vkabstracthandler.h"
#include "vklpeventtype.h"
#include "vklpabstract.h"

#include "vklpmessagedelete.h"
#include "vklpmessageflagschange.h"
#include "vklpmessageflagsreset.h"
#include "vklpmessageflagsset.h"
#include "vklpmessagenew.h"
#include "vklpmessagemarkincoming.h"
#include "vklpmessagemarkoutcoming.h"
#include "vklpuseroffline.h"
#include "vklpuseronline.h"
#include "vklpchatupdated.h"
#include "vklpusertyping.h"
#include "vklpchatusertyping.h"
#include "vklpcounterupdate.h"

#define MAX_USER_ID 2000000000
//Long Poll server
//Have his own parser, network manager and so on

/*
class E_VKUPDATE : public QObject
{
    Q_OBJECT
public:
    E_VKUPDATE(QObject *parent = 0) : QObject(parent) {}


};*/


class VKStorage;
class VK;
class VKHandlerLongPollUpdateData;
class VKLongPollServer : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKLongPollServer(VKStorage *storage, QObject *parent = 0);
    void                                init(VK* vk, VKStorage* storage, QString key, QString server, int ts, int pts);
    bool                                initilized() {return key() != "" && ts() != 0;}

    virtual QString                     name() {return "longPollServer";}
    virtual const QNetworkRequest       processRequest() {qCritical("never called"); return QNetworkRequest();}
    virtual void                        processReply(QJsonValue*) {qCritical("never called");}

    Q_INVOKABLE int                     count();
    Q_INVOKABLE VKLPAbstract*           at(int idx);
    Q_INVOKABLE void                    clean();

private:
    QString                             key() const                         {return m_key;}
    void                                setKey(const QString &key)          {m_key = key;}
    QString                             server() const                      {return m_server;}
    void                                setServer(const QString &server)    {m_server = server;}
    int                                 ts() const                          {return m_ts;}
    void                                setTs(int ts)                       {m_ts = ts;}
    int                                 pts() const                         {return m_pts;}
    void                                setPts(int pts)                     {m_pts = pts;}
    VKStorage*                          storage() const                     {return m_storage;}
    void                                setStorage(VKStorage *storage)      {m_storage = storage;}
    QNetworkAccessManager&              manager()                           {return m_manager;}
    void                                setVK(VK *vk)                       {m_vk = vk;}
    VK*                                 vk()                                {return m_vk;}
    void                                request();
    void                                processUpdate(QJsonArray &update, QList<QString> &userIds, QList<QString> &messageIds, QList<QString> &chatIds, QList<QString> &checkMessages, QList<QString> &removed);
    void                                sendUpdateDataRequest(QList<QString> &userIds, QList<QString> &messageIds, QList<QString> &chatIds, QList<QString> &checkMessages, QList<QString> &removed);
    QString                             type2string(VKLPEventType::E_VKUPDATE type);
    void                                updateReadyEvents();


signals:

public slots:
    void networkDataReady(QNetworkReply* reply);
    void updateDataReady(VKAbstractHandler* handler);
    void additionalInformationAboutUsersReady(VKAbstractHandler* handler);
private:
    QNetworkAccessManager m_manager;
    QString m_key;
    QString m_server;
    int m_ts;
    int m_pts;
    VKStorage* m_storage;
    VK* m_vk;

    QMap<int, QVector<VKLPAbstract*>> m_cachedEvents;
    QVector<VKLPAbstract*> m_readyEvents;

    QVector<VKContainerDialog*> m_updateDialogs;
    QVector<VKContainerMessage*> m_updateMessages;
    QVector<VKContainerUser*> m_updateUsers;
    QMap<int, QVector<QPair<int, int> > > m_longPollData;           //remove
};

#endif // VKLONGPOLLSERVER_H
