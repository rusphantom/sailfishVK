#include "vkcontainerwall.h"

VKContainerWall::VKContainerWall(QObject *parent) :
    VKAbstractContainer(parent)
{
}

VKContainerWall *VKContainerWall::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(obj);
    Q_UNUSED(users);
    Q_UNUSED(userIds);

    auto wall = new VKContainerWall;

    return wall;
}
