<?php
function writelog($level, $msg) {
   exec("./log-wrapper/wrapper ". $level . " '" . $msg . "'");
}
function logInfo($msg) {
   writeLog("INFO", $msg);
}
function logWarning($msg) {
   writeLog("WARNING", $msg);
}
function logDebug($msg) {
   writeLog("DEBUG", $msg);
}
function logError($msg) {
   writeLog("ERROR", $msg);
}
?>
