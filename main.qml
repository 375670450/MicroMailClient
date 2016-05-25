import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import Material 0.2
import Material.ListItems 0.1 as ListItem
import QtWebEngine 1.2


ApplicationWindow {
    id : mainWindow

    title: "MicroMailClient"

    visible: true

    property bool isLargeWindow: width > Screen.desktopAvailableWidth/2

    property int selectedIndex: 0

    property string globalBackgroundColor: "whitesmoke"

    property double iconScale: 0.8

    theme {
        primaryColor: "blue"
        accentColor: "red"
        primaryDarkColor: "gray"
        tabHighlightColor: "Zwhite"
    }

    MouseArea{
        anchors.fill: parent
        property variant previousPosition
        onPressed: {
            previousPosition = Qt.point(mouseX, mouseY)
        }
        onPositionChanged: {
            if( pressedButtons == Qt.LeftButton ){
                mainWindow.x += mouseX - previousPosition.x
                mainWindow.y += mouseY - previousPosition.y
            }
        }
       onClicked: menuSidebar.expanded = false
    }



    Sidebar{
        id: menuSidebar  // 完整的侧边栏
        backgroundColor: Theme.backgroundColor
        expanded: true

        ColumnLayout{
            anchors.fill: parent
            spacing: Units.dp(2)

            width: parent.width

            Button{
                width: height * 1.2
                Image {
                    source: "/icons/menu"
                    scale: iconScale
                }
                onClicked:  menuSidebar.expanded = !menuSidebar.expanded
            }

            MyButton{
                Layout.fillWidth: true
                source: "/icons/add"
                label:  "New Mail"

            }

            MyButton{
                Layout.fillWidth: true
                source: "/icons/person"
                label: "Accounts"

            }

            MyButton{
                Layout.fillWidth: true
                source: "/icons/person_add"
                label: "Add Account"
            }



        }

    }

    Rectangle{

        id: thinMenuSidebar             // 小的侧边栏

        width: menuSidebar.expanded ? 0 : Units.dp(35)

        color: Theme.backgroundColor

        anchors.left: menuSidebar.right

        border.color: "black"

        Column {
            spacing: Units.dp(10)

            anchors.fill : parent

            Button{

                width: parent.width
                height: width
                Image{
//                    scale: iconScale
                    anchors.fill: parent
                    source: "/icons/menu"
                }
                onClicked: {
                    menuSidebar.expanded = !menuSidebar.expanded
                }
            }
        }

    }



    Rectangle{

        id: mailListColumn

        anchors.left: thinMenuSidebar.right

        anchors.leftMargin: 4

        width: isLargeWindow ? 400 : parent.width - thinMenuSidebar.width

        height: parent.height

        ListView{

            id:mailListView

            anchors.fill: parent

            width: parent.width

            delegate:mailListDelegate

            model: mailListModel

            header : Rectangle{
                id: mailListHeader
                height: 35
                width: mailListView.width

                Rectangle{
                    id : searchTextRectangle
                    height: mailListHeader.height
                    width: parent.width - mailListHeaderButtonRectangle.width
                    color: globalBackgroundColor
                    border.color: searchTextField.activeFocus ? "lightgray" : color


                    TextField{

                        id: searchTextField
                        text: "search"
                        height: mailListHeader.height
                        anchors.right: searchButton.left
                        width: parent.width - searchButton.width
                        font.pointSize: 12
                        font.bold: false
                        font.family: "微软雅黑"

                    }

                    Button{
                        id : searchButton
                        anchors.right: parent.right
                        width: 40

                        Image{
                            scale: iconScale
                            id : searchButtonImage
                            anchors.fill: parent
                            anchors.margins: 4
                            source: "/icons/search"
                        }
                    }

                }


                Rectangle{
                    id: mailListHeaderButtonRectangle
                    anchors.left: searchTextRectangle.right
                    height: mailListHeader.height
                    width: 80

                    color: globalBackgroundColor

                    Button{
                        id: refreshButton
                        width: parent.width/2
                        Image{
                            scale: iconScale
                            anchors.fill: parent
                            anchors.margins: 4
                            source: "/icons/refresh"
                        }
                    }
                    Button{
                        anchors.left: refreshButton.right
                        id: selectButton
                        width: parent.width/2
                        Image{
                            scale: iconScale
                            anchors.fill: parent
                            anchors.margins: 4
                            source: "/icons/select"
                        }
                    }
                }
            }
            section.property: "mail_subject"        // should be datetime
            section.criteria: ViewSection.FullString
            section.delegate: mailListSectionDelegate
        }


/*
    Invisible Components of mailListColumn
*/
        Component{
            id: mailListSectionDelegate
            ListItem.Subheader{
                backgroundColor: Theme.backgroundColor
                height: 40
                Label{
                    anchors.verticalCenter: parent.verticalCenter
                    text: section
                    font.pixelSize: 14
                }
                ThinDivider{
                    anchors {
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                    }
                    visible: true
                }

            }


        }

        Component{
            id: mailListDelegate

            ListItem.Standard{
                id: mailListItem

                width: mailListColumn.width
                height: 100

                backgroundColor: selectedIndex == index ? "silver" : globalBackgroundColor

                onClicked: {
                    model.mail_isread = true;           // update isread
                    selectedIndex = index;
                    console.log(mailListModel.get(index).subject);
                    mailWebView.loadHtml(mailListModel.get(index).subject);
                }

               Rectangle{
                   id: isreadRectangle
                   height: parent.height

                   width: 5
                   color: model.mail_isread ? mailListItem.backgroundColor : "green"
               }

                Label{
                    id: mailTitle
                    anchors.left: isreadRectangle.right
                    anchors.margins: 5
                    text: model.mail_subject
                    font.bold: true
                    font.pixelSize: 20
                }

                Label{
                    anchors.top: mailTitle.bottom
                    anchors.left: mailTitle.left
                    anchors.margins: 5

                    id: mailContent
                    text:model.mail_content
                }

                ThinDivider{
                    anchors {
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                    }
                    visible: true
                }

            }
        }

    }

    Rectangle{
        id: mailView

        anchors.left: mailListColumn.right

        height: parent.height

        width: parent.width - mailListColumn.x - mailListColumn.width       // How to simplify?

        color: Theme.backgroundColor

        ColumnLayout{
            spacing: 8

            anchors.fill: parent
            anchors.margins: 10
            anchors.topMargin: 0

            RowLayout{
                id : mailViewToolBar

                height: 60

                spacing: 0

                anchors.top : parent.top

                anchors.right: parent.right

                Layout.fillWidth : true

//                layoutDirection: Qt.RightToLeft

                MyButton{
                    id : markAsUnreadButton
                    label : "Mark As Unread"
                    source: "/icons/mail_unread"
                    Layout.preferredWidth: label.length*8 + 60
                }

                MyButton{
                    id : replyButton
                    label: "Reply"
                    source: "/icons/reply"
                    Layout.preferredWidth: label.length*8 + 60

                }

                MyButton{
                    id : replyAllButton
                    label: "Reply All"
                    source: "/icons/reply_all"
                    Layout.preferredWidth: label.length*8 + 60
                }

            }

            RowLayout{
                id: mailHeaderView

                height: mailViewToolBar.height

                spacing: 10

                Rectangle{
                    height: parent.height / 2
                    width: height
                    radius: height/2
                    color: theme.accentColor
                    Label{
                        anchors.centerIn: parent
                        text: "C"
                    }
                }

                ColumnLayout{
                    spacing: 2
                    Label  {
                        id : mailHeaderSender
                        text : "CodinGame"
                        font.bold: true
                        font.pixelSize: 20
                    }

                    Label {
                        id : mailHeaderDatetime
                        text : "5/23/2016 22:55"
                        font.pixelSize: 13
                    }
                }

            }

            Label {
                text : "Learn new algorithms & tricks"
            }

            Label{
                text : "To: pb375670450@gmail.com"
            }

            WebEngineView{

                id: mailWebView

                Layout.fillHeight: true
                Layout.fillWidth: true
                url: "https://www.baidu.com/"
                onLoadProgressChanged: console.log(mailWebView.loadProgress)

            }
        }


    }


}


/* 测试单个Mail访问
        ListView{
            width: 100
            height: 100
            anchors.right: parent.right
            anchors.top: parent.top
            model: mailListModel.get(0)

            delegate :Component{
                ListItem.Standard{
                    width: 100
                    height: 100

                    backgroundColor: "red"
                    Label{
                        text: "subject" + model.subject
                    }
                }

            }
        }
*/
