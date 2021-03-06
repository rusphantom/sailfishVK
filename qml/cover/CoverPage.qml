/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    id:coverId
    //property alias unreadLabel : coverMessagesCount.text

    /*Row {
        anchors.centerIn: parent
        spacing: 20

        Image {
            anchors.verticalCenter: coverMessagesCount.verticalCenter
            width: Theme.iconSizeSmall
            height: Theme.iconSizeSmall
            source: "image://theme/icon-cover-message"
        }

        Label {
            id: coverMessagesCount
            text: "0"
            font.bold: true
            font.pixelSize: Theme.fontSizeHuge
        }
    }*/

    Column {
        anchors.fill: parent
        anchors.margins: Theme.paddingLarge
        spacing: Theme.paddingMedium

        ConversationComponent {
            id: label1
            width: Theme.coverSizeLarge.width - 2*Theme.paddingLarge
        }
        ConversationComponent {
            id: label2
            width: Theme.coverSizeLarge.width - 2*Theme.paddingLarge
        }
        ConversationComponent {
            id: label3
            width: Theme.coverSizeLarge.width - 2*Theme.paddingLarge
        }

    }

    function getLabel(idx) {
        var obj
        if (idx === 1) {
            obj = label1
        } else if (idx === 2) {
            obj = label2
        } else if (idx === 3) {
            obj = label3
        } else {
            console.log("cannot get label with index",idx)
        }

        return obj
    }

    function store(idx) {
        var obj = getLabel(idx)
        return {dialog: obj.dialogName, message: obj.messageText, read: obj.isRead}
    }

    function load(idx, t) {
        var obj = getLabel(idx)
        obj.dialogName = t.dialog
        obj.messageText = t.message
        obj.isRead = t.read
    }

    function swap(idx1, idx2) {
        var t = store(idx1)
        load(idx1, store(idx2))
        load(idx2, t)

    }

    function insertFirst(t) {
        var t

        //2 => 3
        t = store(2)
        load(3, t)

        //1 => 2
        t = store(1)
        load(2, t)

        update(1, t)
    }

    function update(idx, t) {
        var obj = getLabel(idx)
        if (obj) {
            if ( t.dialog ) {
                obj.dialogName = t.dialog
            }
            if ( t.message ) {
                obj.messageText = t.message
            }
            if ( t.read ) {
                obj.isRead = t.read
            }
        }
    }
}


