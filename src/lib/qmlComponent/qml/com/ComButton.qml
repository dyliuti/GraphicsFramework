import QtQuick 2.12
import QtQuick.Controls 2.12
import "../com"
import "../js/Style.js" as JsStyle

Rectangle {
    id: comButton
    width: style.width
    height: style.height
    color: getBackgroundColor(bPressed, bHovered, bEnable)
    radius: 4
    border.width: style.borderWidth === undefined ? 0 : style.borderWidth
    border.color: getBorderColor(bPressed, bHovered, bEnable)
    property var style: JsStyle.ComButton_Style_Black
    property var defaultStyle: JsStyle.ComButton_Style_Blue
    property bool bHovered: false
    property bool bPressed: false
    property bool bEnable: true
    property string text: ""
    property string textColor: getTextColor(bPressed, bHovered, bEnable)
    property string textSize: style.textSize === undefined ? defaultStyle.textSize : style.textSize
    property string textFontWidght: style.textFontWeight === undefined ? defaultStyle.textFontWeight : style.textFontWeight
    signal sigClicked

    ComText {
        id: btnText
        anchors.centerIn: parent
        text: comButton.text
        font.pixelSize: textSize
        font.weight: textFontWidght
        color: textColor
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            comButton.bHovered = true
        }
        onExited: {
            comButton.bHovered = false
        }

        onClicked: {
            if (!comButton.bEnable)
                return
            comButton.sigClicked()
        }
        onPressed: {
            comButton.bPressed = true
        }
        onReleased: {
            comButton.bPressed = false
        }
    }

    function getBackgroundColor(pressed, hovered, enable){
        if(enable === false){
            return style.disableColor === undefined ? defaultStyle.disableColor : style.disableColor
        }else if(pressed === true){
            return style.pressColor === undefined ? defaultStyle.pressColor : style.pressColor
        }else if(hovered === true){
            return style.hoverColor === undefined ? defaultStyle.hoverColor : style.hoverColor
        }

        return style.color === undefined ? defaultStyle.color : style.color
    }

    function getTextColor(pressed, hovered, enable){
        if(enable === false){
            return style.textDisableColor === undefined ? defaultStyle.textDisableColor : style.textDisableColor
        }else if(pressed === true){
            return style.textPressColor === undefined ? defaultStyle.textPressColor : style.textPressColor
        }else if(hovered === true){
            return style.textHoverColor === undefined ? defaultStyle.textHoverColor : style.textHoverColor
        }

        return style.textColor === undefined ? defaultStyle.textColor : style.textColor
    }

    function getBorderColor(pressed, hovered, enable){
        if(enable === false){
            return style.borderDisableColor === undefined ? "transparent" : style.borderDisableColor
        }else if(pressed === true){
            return style.borderPressColor === undefined ?"transparent" : style.borderPressColor
        }else if(hovered === true){
            return style.borderHoverColor === undefined ? "transparent" : style.borderHoverColor
        }

        return style.borderColor === undefined ? "transparent" : style.borderColor
    }
}
