import QtQuick 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

Dialog {
    title: "Add Task"
    width: 300
    height: 94

    function get_clear_entry_button()
    {
        return clear_entry
    }

    function clearEntry()
    {
        taskEdit.text = "Task_"
        progress.currentIndex = 0
        calendar.text = ""
    }

    contentItem: Rectangle {
        antialiasing: true
        ColumnLayout {
            anchors.margins: 1
            spacing: 1

            RowLayout {
                anchors.margins: 1
                spacing: 1

                Label {
                   Layout.preferredWidth:  30
                   text: qsTr("Task")
                   horizontalAlignment: Qt.AlignRight
                }

                TextField {
                    id: taskEdit
                    width: 230
                    Layout.preferredWidth:  270
                    Layout.preferredHeight: 30
                    selectByMouse: true
                }
            }

            RowLayout {
                anchors.margins: 1
                spacing: 1

                Label {
                    Layout.preferredWidth:  30
                    text: qsTr("Date")
                    horizontalAlignment: Qt.AlignRight
                }

                TextField {
                    id: calendar
                    Layout.preferredWidth:  110
                    Layout.preferredHeight: 30
                    selectByMouse: true
                }

                Label {
                    Layout.preferredWidth:  45
                    text: qsTr("Progress")
                    horizontalAlignment: Qt.AlignRight
                }

                ComboBox {
                    id: progress
                    Layout.preferredWidth:  100
                    model: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                    Layout.preferredHeight: 30
                    background:
                Rectangle { color: "white" }
                }
            }

            RowLayout {
                anchors.margins: 1
                spacing: 1
                Layout.alignment: Qt.AlignBottom
                Layout.fillWidth: true

                Button {
                    id: add_entry
                    Layout.preferredHeight: 30
                    Layout.fillWidth: true
                    text: qsTr("Add")
                    onClicked: {
                         if(taskEdit.text.trim().length === 0)
                        {
                            console.error("Try to add empty task")
                            error_msgbox.text = "Task is empty.Input task!"
                            error_msgbox.open();
                        }
                         else if (!tableModel.checkDate(calendar.text.trim()))
                               {
                                   console.error("Try to use incorrect date")
                                   error_msgbox.text = "Incorrect date. Input correct date (dd.MM.yyyy)!"
                                   error_msgbox.open();
                               }
                        else
                        {
                            tableModel.onAdd(taskEdit.text.trim(), calendar.text.trim(), progress.currentText);
                            add_entry_dialog.close();
                            mainWindow.title = getTitle()
                        }
                    }
                }

                Button {
                    id: clear_entry
                    Layout.preferredHeight: 30
                    Layout.fillWidth: true
                    text: qsTr("Clear")
                    onClicked: { clearEntry() }
                }
            }
        }
    }
}
