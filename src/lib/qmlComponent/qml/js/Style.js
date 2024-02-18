.pragma library

function getSystemNormalFont() {
    switch (Qt.platform.os) {
    case "windows":
        return "Microsoft Yahei"
    case "osx":
        return "PingFang SC"
    default:
        return ""
    }
}

function platformIsWindows() {
    var curOs = Qt.platform.os
    return curOs === "windows"
}

function getFilePrefix() {
    var curOs = Qt.platform.os
    if (curOs === "windows") {
        return "file:///"
    } else {
        return "file://"
    }
}

function getStyleValue(style, defaultStyle, strKey) {
    if (style === undefined || style[strKey] === undefined)
        return defaultStyle[strKey]
    else
        return style[strKey]
}

var FillDarkColor = "#101012"
var FillHightColor = "#1C1C1F"
var LayerSelectFillColor = "#232326"
var BorderColor = "#232326"
var BorderColorHight = "#8C8C8C"
var SplitlineColor = "#2E2E33"
// 大功能模块面板间的间隔
var SegmentationLineColor = "#050505"
var BlueText = "#4938FF"
var GrayHighlightText = "#8C8C8C"
var GrayText = "#595959"
var WhiteText = "#E6E6E6"
var BlackColor_1F1F21 = "#1F1F21"
var MaskColor =  Qt.rgba(5.0 / 255, 5.0 / 255, 5.0 / 255, 0.5)

//文本样式
var ComText_Style = {
    "color": "#E6E6E6",
    "textSize": 12,
    "font_family": getSystemNormalFont(),
    "font_weight": "Normal"
}

var ComText_Style_Bold = {
    "color": "#E6E6E6",
    "textSize": 12,
    "font_family": getSystemNormalFont(),
    "font_weight": "Bold"
}

var ComText_Style_Disable = {
    "color": "#595959",
    "textSize": 12,
    "font_family": getSystemNormalFont(),
    "font_weight": "Normal"
}

var ComText_Style_SubTitle = {
    "color": "#8C8C8C",
    "textSize": 12,
    "font_family": getSystemNormalFont(),
    "font_weight": "Normal"
}

var ComText_Style_11 = {
    "color": "#E6E6E6",
    "textSize": 11,
    "font_family": getSystemNormalFont()
}

var ComText_Style_SubTitle_11 = {
    "color": "#8C8C8C",
    "textSize": 11,
    "font_family": getSystemNormalFont(),
    "font_weight": "Normal"
}

var ComText_Style_Disable_11 = {
    "color": "#595959",
    "textSize": 11,
    "font_family": getSystemNormalFont()
}

var ComText_Style_14 = {
    "color": "#E6E6E6",
    "textSize": 14,
    "font_family": getSystemNormalFont()
}

var ComText_Style_Disable_14 = {
    "color": "#595959",
    "textSize": 14,
    "font_family": getSystemNormalFont()
}

var ComText_Style_14_Bold = {
    "color": "#E6E6E6",
    "textSize": 14,
    "font_family": getSystemNormalFont(),
    "font_weight": "Bold"
}

var ComText_Style_Disable_14_Bold = {
    "color": "#595959",
    "textSize": 14,
    "font_family": getSystemNormalFont(),
    "font_weight": "Bold"
}

var ComText_Style_24 = {
    "color": "#E6E6E6",
    "textSize": 24,
    "font_family": getSystemNormalFont()
}

var ComText_Style_24_BLACK = {
    "color": "#000000",
    "textSize": 24,
    "font_family": getSystemNormalFont()
}

// 提示失败
var ComText_Style_HintFail = {
    "color": "#FF385D",
    "textSize": 12,
    "font_family": getSystemNormalFont()
}

// 提示成功
var ComText_Style_HintSuccess = {
    "color": "#31D45C",
    "textSize": 12,
    "font_family": getSystemNormalFont()
}

//按钮样式 蓝色按钮
var ComButton_Style_Blue = {
    "width": 78,
    "height": 28,
    "color": "#4938FF",
    "pressColor": "#3F30D9",
    "hoverColor": "#5C4DFF",
    "disableColor": "#282080",
    "textColor": "#E6E6E6",
    "textPressColor": "#E6E6E6",
    "textHoverColor": "#E6E6E6",
    "textDisableColor": Qt.rgba(1, 1, 1, 0.2),
    "textSize": 12,
    "textFontWeight": "Normal"
}

var ComButton_Style_Blue_88 = {
    "width": 88,
    "height": 32,
    "color": "#4938FF",
    "pressColor": "#3F30D9",
    "hoverColor": "#5C4DFF",
    "disableColor": "#282080",
    "textColor": "#E6E6E6",
    "textPressColor": "#E6E6E6",
    "textHoverColor": "#E6E6E6",
    "textDisableColor": Qt.rgba(1, 1, 1, 0.2),
    "textSize": 14,
    "textFontWeight": "Normal"
}

var ComButton_Style_Blue_104 = {
    "width": 104,
    "height": 38,
    "color": "#4938FF",
    "pressColor": "#3F30D9",
    "hoverColor": "#5C4DFF",
    "disableColor": "#282080",
    "textColor": "#E6E6E6",
    "textPressColor": "#E6E6E6",
    "textHoverColor": "#E6E6E6",
    "textDisableColor": Qt.rgba(1, 1, 1, 0.2),
    "textSize": 16,
    "textFontWeight": "Bold"
}

// 灰色按钮
var ComButton_Style_Gray = {
    "width": 78,
    "height": 28,
    "color": "#2E2E33",
    "pressColor": "#232226",
    "hoverColor": "#45454D",
    "disableColor": "#232226",
    "textColor": "#E6E6E6",
    "textPressColor": "#E6E6E6",
    "textHoverColor": "#E6E6E6",
    "textDisableColor": "#595959",
    "textSize": 12,
    "textFontWeight": "Normal"
}

var ComButton_Style_Gray_88 = {
    "width": 88,
    "height": 32,
    "color": "#2E2E33",
    "pressColor": "#232226",
    "hoverColor": "#45454D",
    "disableColor": "#232226",
    "textColor": "#E6E6E6",
    "textPressColor": "#E6E6E6",
    "textHoverColor": "#E6E6E6",
    "textDisableColor": "#595959",
    "textSize": 14,
    "textFontWeight": "Normal"
}

var ComButton_Style_Gray_104 = {
    "width": 104,
    "height": 38,
    "color": "#2E2E33",
    "pressColor": "#232226",
    "hoverColor": "#45454D",
    "disableColor": "#232226",
    "textColor": "#E6E6E6",
    "textPressColor": "#E6E6E6",
    "textHoverColor": "#E6E6E6",
    "textDisableColor": "#595959",
    "textSize": 16,
    "textFontWeight": "Bold"
}

// 黑色按钮带边框
var ComButton_Style_Black = {
    "width": 78,
    "height": 28,
    "color": "transparent",
    "pressColor": "transparent",
    "hoverColor": "transparent",
    "disableColor": "transparent",
    "textColor": "#E6E6E6",
    "textPressColor": "#E6E6E6",
    "textHoverColor": "#E6E6E6",
    "textDisableColor": "#595959",
    "borderWidth": 1,
    "borderColor": "#8C8C8C",
    "borderPressColor": "#595959",
    "borderHoverColor": "#E6E6E6",
    "borderDisableColor": "#595959",
    "textSize": 12,
    "textFontWeight": "Normal"
}

var ComButton_Style_Black_88 = {
    "width": 88,
    "height": 32,
    "color": "transparent",
    "pressColor": "transparent",
    "hoverColor": "transparent",
    "disableColor": "transparent",
    "textColor": "#E6E6E6",
    "textPressColor": "#E6E6E6",
    "textHoverColor": "#E6E6E6",
    "textDisableColor": "#595959",
    "borderWidth": 1,
    "borderColor": "#8C8C8C",
    "borderPressColor": "#595959",
    "borderHoverColor": "#E6E6E6",
    "borderDisableColor": "#595959",
    "textSize": 14,
    "textFontWeight": "Normal"
}

var ComButton_Style_Black_104 = {
    "width": 104,
    "height": 38,
    "color": "transparent",
    "pressColor": "transparent",
    "hoverColor": "transparent",
    "disableColor": "transparent",
    "textColor": "#E6E6E6",
    "textPressColor": "#E6E6E6",
    "textHoverColor": "#E6E6E6",
    "textDisableColor": "#595959",
    "borderWidth": 1,
    "borderColor": "#8C8C8C",
    "borderPressColor": "#595959",
    "borderHoverColor": "#E6E6E6",
    "borderDisableColor": "#595959",
    "textSize": 16,
    "textFontWeight": "Bold"
}
//输入框样式，普通输入框
var Com_Plain_Input_Style = {
    "hoverBorderColor": "#2E2E33",
    "focusBorderColor": "#8C8C8C",
    "textColor": "#E6E6E6",
    "selectionColor": "#E2E2E2",
    "selectedTextColor": "#060606",
    "textDisableColor": "#4F4F4F",
    "charLengthColor": "#8C8C8C",
    "charSizeOverMaxColor" : "#FF385D",
    "backgroundColor": "#1C1C1F",
}

//数组输入框
var Com_Number_Input_Style = {
    "hoverBorderColor": "#2E2E33",
    "focusBorderColor": "#8C8C8C",
    "textColor": "#E6E6E6",
    "selectionColor": "#E2E2E2",
    "selectedTextColor": "#060606",
    "textDisableColor": "#4F4F4F",
    "charLengthColor": "#8C8C8C",
    "charSizeOverMaxColor" : "#FF385D",
    "backgroundColor": "#1C1C1F",
}

//百分百输入框
var Com_Percent_Input_Style = {
    "borderColor": "#2E2E33",
    "backgroundColor": "#1C1C1F",
    "textSize": 12
}

//组合输入框
var Com_Group_Input_Style = {
    "hoverBorderColor": "#2E2E33",
    "focusBorderColor": "#8C8C8C",
    "textColor": "#E6E6E6",
    "selectionColor": "#E2E2E2",
    "selectedTextColor": "#060606",
    "textDisableColor": "#4F4F4F",
    "backgroundColor": "#1C1C1F",
}

//前后缀输入框
var Com_Suffix_Input_Style = {
    "hoverBorderColor": "#2E2E33",
    "focusBorderColor": "#8C8C8C",
    "textColor": "#E6E6E6",
    "selectionColor": "#E2E2E2",
    "selectedTextColor": "#060606",
    "textDisableColor": "#4F4F4F",
    "prefixTextColor": "#595959",
    "suffixTextColor": "#8C8C8C"
}

//多行输入框
var Com_Mutiple_Input_Style = {
    "hoverBorderColor": "#2E2E33",
    "focusBorderColor": "#8C8C8C",
    "textColor": "#E6E6E6",
    "selectionColor": "#E2E2E2",
    "selectedTextColor": "#060606",
    "textDisableColor": "#4F4F4F",
    "prefixTextColor": "#595959",
    "suffixTextColor": "#8C8C8C",
    "charSizeOverMaxColor" : "#FF385D",
    "backgroundColor": "#1C1C1F"
}

var ComScrollBar_Style = {
    "implicitWidth": 6,
    "implicitHeight": 6,
    "radius": 2,
    "color": "#4F4F4F",
    "pressedColor": "#4F4F4F",
    "hoveredColor": "#4F4F4F"
}
