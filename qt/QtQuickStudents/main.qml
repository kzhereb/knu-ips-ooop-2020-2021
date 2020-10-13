import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        spacing: 5

        RowLayout {
            spacing: 5
            Text {
                text: qsTr("Surname: ")
            }

            TextField {
                id: surname

            }
        }

        RowLayout {
            spacing: 5
            Text {
                text: qsTr("Name: ")
            }

            TextField {
                id: name
            }
        }

        RowLayout {
            spacing: 5
            Text {
                text: qsTr("Group: ")
            }

            ComboBox {
                id: group
                model: ["K-28", "K-29"]
            }
        }

        RowLayout {
            spacing: 5
            Text {
                text: qsTr("AvgGrade: ")
            }

            SpinBox {
                id: avgGrade
                from: 0
                value: 75 * 100
                to: 100 * 100
                stepSize: 100
                editable: true
                //anchors.centerIn: parent

                property int decimals: 2
                property real realValue: value / 100

                validator: DoubleValidator {
                    bottom: Math.min(avgGrade.from, avgGrade.to)
                    top:  Math.max(avgGrade.from, avgGrade.to)
                }

                textFromValue: function(value, locale) {
                    return Number(value / 100).toLocaleString(locale, 'f', avgGrade.decimals)
                }

                valueFromText: function(text, locale) {
                    return Number.fromLocaleString(locale, text) * 100
                }
            }
        }

        Button {
            text: "Save"
            onClicked: backend.save(surname.text,
                                    name.text,
                                    group.currentText,
                                    avgGrade.realValue)
        }
    }
}
