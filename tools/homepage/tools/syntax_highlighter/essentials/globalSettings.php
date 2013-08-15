<?php
error_reporting(0);
$currVersion = "3.9.1";

$fontSizeInPt = '2';
$MAXIMUM_CHARS_PER_LINE=100;
$ignoreMaxCharsForStrings = false;

$startCodeBlockInHtml = "[cpp_code]";
$startCodeBlockWithNoLineInHtml = "[cpp_code_no_line]";

$startLineHighlighter = "[cpp_code_line]";
$endLineHighlighter = "[/cpp_code_line]";
$startGetFormattedCodeFromExistingCode = "[cpp_code_existing]";
$endGetFormattedCodeFromExistingCode = "[/cpp_code_existing]";

$startCharacterForTitle=':';
$endCharacterForTitle=';';

/*for developer reference: 
if $startCharacterForTitle is ':' and $endCharacterForTitle is ';' then code with title would be
    [cpp_code]:this is sample and i love this title;<YOUR C++ CODE STARTS HERE>[/cpp_code]
\; in above example is not necessary, it is to demonstrate the way of adding semi-colon into your title
*/
$startCodeBlockInHtmlWithTitle = $startCodeBlockInHtml.$startCharacterForTitle;
$startCodeBlockWithNoLineInHtmlWithTitle = $startCodeBlockWithNoLineInHtml.$startCharacterForTitle;
$titleEscapeCharacter = '\\';
$endCodeBlockInHtml = "[/cpp_code]";
$escAlternator = "[__e__]";
?>
