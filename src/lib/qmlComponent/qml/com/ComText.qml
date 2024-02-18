import QtQuick 2.12
import "../js/Style.js" as JsStyle

Text {
    property var style: ({})
    property var defaultStyle: JsStyle.ComText_Style
    property int textSize: JsStyle.getStyleValue(style, defaultStyle,
                                                 "textSize")
    font.pixelSize: textSize
    elide: Text.ElideRight
    color: JsStyle.getStyleValue(style, defaultStyle, "color")
    font.family: JsStyle.getStyleValue(style, defaultStyle, "font_family")
    font.weight: JsStyle.getStyleValue(style, defaultStyle, "font_weight")

    function setText(newText) {
        text = newText
    }

    function getText() {
        return text
    }
}
