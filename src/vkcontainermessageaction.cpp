#include "vkcontainermessageaction.h"
#include "vkhandlerusers.h"

VKContainerMessageAction::VKContainerMessageAction(QObject *parent) :
    VKAbstractContainer(parent)
{
    setType(ACTION_INVALID);
    m_actionMid = 0;
    m_type = eVKContainerMessageAction;
}

QSharedPointer<VKContainerMessageAction> VKContainerMessageAction::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> &userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(users);

    auto action = new VKContainerMessageAction;

    auto act = obj.value("action").toString();
    if (act == "") {
        action->setType( ACTION_INVALID );
    } else if (act == "chat_photo_update") {
        //todo
        action->setType( ACTION_PHOTO_UPDATED );
    } else if (act == "chat_photo_remove") {
        //todo
        action->setType( ACTION_PHOTO_REMOVED );
    } else if (act == "chat_create") {
        action->setType( ACTION_CHAT_CREATE );
        action->setText(obj.value("action_text").toString());
    } else if (act == "chat_title_update") {
        action->setType( ACTION_TITLE_UPDATED );
        qDebug()<<"title updated";
        action->setText(obj.value("action_text").toString());
    } else if (act == "chat_invite_user") {
        action->setType( ACTION_INVITE_USER );
        int userId = 0;
        if (obj.value("action_mid").isString()) {
            userId = obj.value("action_mid").toString().toInt();
        } else {
            userId = obj.value("action_mid").toInt();
        }
        if (userId < 0) {
            action->setText(obj.value("action_email").toString());
        } else {
            qDebug()<<"adding"<<userId;
            userIds.append(userId);
            action->setUserId(userId);
        }
    } else if (act == "chat_kick_user") {
        action->setType( ACTION_KICK_USER );
        int userId = 0;
        if (obj.value("action_mid").isString()) {
            userId = obj.value("action_mid").toString().toInt();
        } else {
            userId = obj.value("action_mid").toInt();
        }
        if (userId < 0) {
            action->setText(obj.value("action_email").toString());
        } else {
            qDebug()<<"adding"<<userId;
            userIds.append(userId);
            action->setUserId(userId);
        }
    } else {
        qDebug()<<"unknown action"<<act;
        Q_ASSERT(0);
    }

    return QSharedPointer<VKContainerMessageAction>(action);
}

void VKContainerMessageAction::complete(VKAbstractHandler *_h) {
    auto users = dynamic_cast<VKHandlerUsers*>(_h);

    if (users) {
        for (int i=0;i<users->count();i++) {
            auto el = users->get(i);
            if (userId() == el->id()) {
                setText(el->firstName() + " " + el->lastName());
                qDebug()<<"Message action with type"<<type()<<"completed with user id"<<el->id();
                return;
            }
        }
    }
}

void VKContainerMessageAction::setType(int id) {
    SET_ARG(m_actionType, id);
}

void VKContainerMessageAction::setUserId(int id) {
    SET_ARG(m_actionMid, id);
}

void VKContainerMessageAction::setText(QString text) {
    SET_ARG(m_actionText, text);
}
