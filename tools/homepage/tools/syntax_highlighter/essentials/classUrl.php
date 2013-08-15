<?php 
require_once "globalSettings.php";

function getNokiaQtClassUrl($className){
    return "http://doc.qt.nokia.com/latest/$className.html";
}

function getGtkPlusClassUrl($className){
    return "http://developer.gnome.org/gtk/$gtkVersion/$className.html";
}
function getWxWidgetsClassUrl($className){
    $lowercaseClassName=strtolower($className);
    return "http://docs.wxwidgets.org/stable/wx_".$lowercaseClassName.".html";
}
?>
