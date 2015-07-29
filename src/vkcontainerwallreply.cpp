#include "vkcontainerwallreply.h"

VKContainerWallReply::VKContainerWallReply(QObject *parent) :
    VKAbstractContainer(parent)
{
}

VKContainerWallReply *VKContainerWallReply::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(obj);
    Q_UNUSED(users);
    Q_UNUSED(userIds);

    auto wallReply = new VKContainerWallReply;

    return wallReply;
}

