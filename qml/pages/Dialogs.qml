import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: dialogsPage
    property alias dialogListAlias : dialogsList
    property alias dialogsListModelAlias : dialogsListModel
    property int offset
    property bool ready: false

    function updatePage() {
        offset = 0
        dialogsList.model.clear()
        ready = false
        vk.getDialogs(offset)
        console.log("dialogs page updated")
    }

    SilicaListView {
        id: dialogsList
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: "Exit"
                onClicked: {
                    pageStack.clear()
                    vk.dropAuthorization()
                    pageStack.push(Qt.resolvedUrl("Auth.qml"),{})
                }
            }
            MenuItem {
                text: "Report bug"
                onClicked: {
                    vk.assert0()
                }
            }
            MenuItem {
                text: "Update page"
                onClicked: {
                    vk.emitUpdatePages()
                }
            }
        }


        model: ListModel {
            id: dialogsListModel
        }
        spacing: Theme.paddingLarge
        header: PageHeader {
            id: pageHeader
            title: "Messanges"
        }
        footer: LoadingFooter {}

        delegate: DialogComponent{}
        onMovementEnded: {
            if (visibleArea.yPosition + visibleArea.heightRatio > 0.99) {
                console.log("getDialogs scroll");
                vk.getDialogs(offset)
            }
        }

        VerticalScrollDecorator {}
        Component.onCompleted: {
            vk.getDialogs(offset)
        }
        BusyIndicator {
            anchors.centerIn: dialogsList
            running: !ready
            size: BusyIndicatorSize.Large
        }
    }
}