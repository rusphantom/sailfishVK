#ifndef VKDIALOGCONTAINER_H
#define VKDIALOGCONTAINER_H

#include <QObject>
#include <QVariantList>
#include <QVariant>
#include <QVector>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include "vkabstractcontainer.h"
#include "vkcontainerattachments.h"

class VKContainerUser;
class VKContainerMessage;
class VKStorage;
class VKHandlerUsers;
class VKContainerMessageAction;
class VKContainerMessage : public VKAbstractContainer
{
    Q_OBJECT

public:
    explicit VKContainerMessage(QObject *parent = 0);
             ~VKContainerMessage();

    static QSharedPointer<VKContainerMessage> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users, QVector<int> &userIds);
    virtual void complete(VKAbstractHandler* _h);

    Q_INVOKABLE int id() const                                      { return m_id; }
    Q_INVOKABLE QDateTime date() const                              { return m_date; }
    Q_INVOKABLE bool isIncoming() const                             { return m_isIncoming; }
    Q_INVOKABLE VKContainerUser* userPtr() const                    { return m_user.data(); }
    Q_INVOKABLE bool readState() const                              { return m_readState; }
    Q_INVOKABLE QString body() const                                { return m_body; }
    Q_INVOKABLE bool isChat() const                                 { return m_isChat; }
    Q_INVOKABLE int chatId() const                                  { return m_chatId; }
    Q_INVOKABLE VKContainerAttachments* attachmentsPtr() const      { return m_attachments.data(); }
    Q_INVOKABLE VKContainerMessageAction* actionPtr() const         { return m_action.data(); }

    Q_INVOKABLE bool isValid();
    Q_INVOKABLE int countFwd();
    Q_INVOKABLE VKContainerMessage* getFwdPtr(int i) const;


    QSharedPointer<VKContainerUser> user() const                 { return m_user; }
    QSharedPointer<VKContainerAttachments> attachments() const   { return m_attachments; }
    QSharedPointer<VKContainerMessageAction> action() const      { return m_action; }
    QSharedPointer<VKContainerMessage> getFwd(int i) const;

    void setId(int arg);
    void setDate(QDateTime arg);
    void setIsIncoming(bool arg);
    void setBody(QString arg);
    void setIsChat(bool arg);
    void setChatId(int arg);
    void setUser(QSharedPointer<VKContainerUser> arg);
    void addFwdMsg(QSharedPointer<VKContainerMessage> arg);
    void setAttachments(QSharedPointer<VKContainerAttachments> attachments);
    void setAction(QSharedPointer<VKContainerMessageAction> action);
    void setReadState(bool arg);

    static void processEmoji(QString &s);

private:
    int                                         m_id;
    QDateTime                                   m_date;
    bool                                        m_isIncoming;       //optimaze bool flags
    bool                                        m_readState;
    bool                                        m_isChat;
    QSharedPointer<VKContainerUser>             m_user;
    QString                                     m_body;
    int                                         m_chatId;
    QVector<QSharedPointer<VKContainerMessage>> m_fwd;
    QSharedPointer<VKContainerAttachments>      m_attachments;
    bool                                        m_valid;
    QSharedPointer<VKContainerMessageAction>    m_action;

};


#endif // VKDIALOGCONTAINER_H
