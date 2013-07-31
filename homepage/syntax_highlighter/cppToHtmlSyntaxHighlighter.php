<?php
include_once "essentials/style.css";            //Contains style related to C++ syntax
include_once "essentials/utils.js";            //Contains utility javascript functions for certain functionalities
include_once "essentials/stringFunctions.php";        //contains basic string checking functions, e.g, is number etc.
include_once "essentials/globalSettings.php";        //contains global settings used in highlighting
include_once "essentials/classUrl.php";            //contains functions that connect custom library classes to their documentation
include_once "essentials/cppKeywordsStandard.php";    //contains array of standard C++ keywords
include_once "essentials/cppKeywordsNokiaQt.php";    //contains array of Qt classes
include_once "essentials/cppKeywordsGtkPlus.php";    //contains array of GTK+ widgets
include_once "essentials/cppKeywordsWxWidgets.php";    //contains array of wxWidgets classes
include_once "essentials/braceTraceKeys.php";        //contains functions to support brace trace functionality
include_once "essentials/braceTrace.php";        //contains functions to support brace trace functionality
include_once "essentials/braceTraceJs.js";        //contains Javascript functions to support brace trace functionality

/**
 * You may use this class in your code to access specific lines, lines' markup or part of code. This class contains essential functions
 */
class CppCode{
    public $code;
    public $formattedCode;
    public $title;

    //array that contains simple C++ lines
    public $lines;
    //array that contains all formatted C++ lines
    public $formattedLines;

    public function getLineCount(){
        if (isset($this->formattedLines))
            return count($this->formattedLines);
        else
            return "[no_count]";
    }

    function __construct($code="",$title="") {
        $this->code = $code;
        $this->title=$title;
    }
    /*
     * this function returns a mark up that will highlight the line in the code
     */
    public function getLineHighlighter($lineNumber,$endLineNumber=0){
        $lineCode = substr(md5($this->title),0,4)."-line".$lineNumber;
        $displayText = 'line ' . $lineNumber;
        $singleLine = true;
        if (($endLineNumber != 0 ) && ($endLineNumber > $lineNumber)){
            if ($endLineNumber > $this->getLineCount())
                $endLineNumber = $this->getLineCount();//to prevent extra memory to be used
            $singleLine=false;
            $displayText .= '-'. $endLineNumber;
            $endLineCode = substr(md5($this->title),0,4)."-line".$endLineNumber;
        }
        if ($singleLine)
            return "<span class='AccessibleLineNumber'><a class='AccessibleLineNumber' href='#".$lineCode."' onmouseover=\"javascript:highlightLine('".$lineCode."');\" onmouseout=\"javascript:normalizeLine('".$lineCode."');\">$displayText</a></span>";
        else
            return "<span class='AccessibleLineNumber'><a class='AccessibleLineNumber' href='#".$lineCode."' onmouseover=\"javascript:highlightMultipleLines('".$lineCode."','".$endLineCode."');\" onmouseout=\"javascript:normalizeMultipleLines('".$lineCode."','".$endLineCode."');\">$displayText</a></span>";
    }
    /*
     * this function gets non-formatted C++ code lines (plain text)
     */
    public function getFormattedLines($start,$end=0){
        global $fontSizeInPt;
        if ($end==0){ 
            $end = $start; 
        }
        elseif ($end > $this->getLineCount()) { 
            $end = $this->getLineCount(); 
        }

        $end++;

        if (isset($this->formattedLines)){
            $linesBuilder="<pre class='Code'><table><tr><td><table border=0>";
            for ($i=($start-1);$i<$end-1;$i++){
                if ((($start-1) > count($this->formattedLines)) || (($end-1) > count($this->formattedLines)))
                    throw new Exception("Invalid index in formatted lines - formattedLines [count: ".count($this->formattedLines)."] are 1-index");
                else
                    $linesBuilder.=$this->formattedLines[$i];
            }
            $linesBuilder.="</table></td></tr></table></pre>";
            return $linesBuilder;
        }
        else{
            return "";
        }
    }
    /*
     * this function gets non-formatted C++ code lines (plain text)
     */
    public function getLines($start,$count=1){
        if (isset($this->lines)){
            $linesBuilder="";

            for ($i = ($start-1) ; $i < (($start + $count)-1) ; $i++){

                if ((($start-1) > count($this->lines)) || ((($start + $count)-1) > count($this->lines)))
                    throw new Exception("Invalid index in code lines - lines [count: ".count($this->lines)."] are 1-index");
                else
                    $linesBuilder.=$this->lines[$i];
            }

            return $linesBuilder;
        }
        else{
            return "";
        }
    }
}


class Highlighter{

    public $showLineNumber=true;
    public $supportNokiaQtClasses=true;
    public $supportGtkPlusClasses=true;
    public $supportWxWidgetsClasses=true;
    public $supportBraceTrace=true;
    public $buildLines=true;
    public $buildFormattedLines=true;

    //array of CppCode that is generated in findCppCodeInHtmlBlock()
    //NOTE: CppCode is identified by title. if 2 CppCodes have no title, they will be treated same when being accessed
    private $cppCodesInHtmlBlock;
    public function getCppCodesInHtmlBlock($oneIndex){
        $properZeroIndex=0;
        if (count($this->cppCodesInHtmlBlock) < $oneIndex)
            $properZeroIndex = count($this->cppCodesInHtmlBlock);
        elseif ($oneIndex < 1)
            $properZeroIndex=1;
        else
            $properZeroIndex=$oneIndex;
        $properZeroIndex-=1;//make it actual zero index
        return $this->cppCodesInHtmlBlock[$properZeroIndex];
    }
    /*
     * function: highlightCode
     * parameters:
     *        cppCodeString: actual C++ code that needs to be highlighted
     * returns CppCode object
     */
    public function highlightCode($cppCodeString,$title=""){

        $braceTracer = new BraceTrace();
        $cppCode = new CppCode($cppCodeString,$title);
        if ($this->buildLines){
            $cppCode->lines=array();
        }
        if ($this->buildFormattedLines){
            $cppCode->formattedLines=array();
        }


        // Following variables are declared in settings.php file

        global $fontSizeInPt;
        global $MAXIMUM_CHARS_PER_LINE;
        global $cppKeywords;        //refers to C++ standard keywordr
        global $nokiaQtClasses;        //refers to Nokia Qt classes
        global $gtkPlusClasses;        //refers to GTK+ classes
        global $wxWidgetsClasses;    //refers to wxWidgets classes
        global $braceTraceStart;
        global $braceTraceEnd;
        global $ignoreMaxCharsForStrings;

        $showLineNumber=$this->showLineNumber;
        $supportNokiaQtClasses=$this->supportNokiaQtClasses;
        $supportGtkPlusClasses=$this->supportGtkPlusClasses;
        $supportWxWidgetsClasses=$this->supportWxWidgetsClasses;
        $supportBraceTrace=$this->supportBraceTrace;


        $in_char_block = false;                //identifies if current character is inside single quote block
        $in_comment_block = false;            //identifies if current character is inside /**/  block
        $in_single_line_comment = false;        //identifies if current character is inside //  block
        $in_string_block = false;            //identifies if current character is inside double quote block

        $output="<pre class='Code'>";//initialize output
        if ($cppCode->title != "")
            $output.="<center><table class='Title'><tr><td align=center>$cppCode->title</td></tr></table></center>";
        $output.="<table><tr><td><table border=0>";

        $lines=explode("\n",$cppCodeString);    //break cppCodeString by lines
        $currLine=1;
        foreach ($lines as &$thisLine) {
            //you may use buildLines to not push $thisLine to $cppCode->lines in order to save memory if you like
            if ($this->buildLines){
                array_push($cppCode->lines,$thisLine);
            }
            $spaceAdded=false;
            $currFormattedLine="<tr id='".substr(md5($title),0,4)."-line$currLine-c'>";
            if ($showLineNumber) { 
                $currFormattedLine.="<td class='Line-TD' align='right'><span class='Line'><font size=$fontSizeInPt><a name='".substr(md5($title),0,4)."-line$currLine'>".$currLine."</a></font></span></td>";
                //Add an extra space for better code reading
                $currFormattedLine .= "<td>&nbsp;</td>";
            }
            $currFormattedLine.="<td align='left'><font size=$fontSizeInPt>";
            if (!$showLineNumber){
                 $currFormattedLine.="<a name='".substr(md5($title),0,4)."-line$currLine'>";
            }
            if (trim($thisLine) == "")
                $currFormattedLine.="&nbsp;";

            if ($in_comment_block)
                $currFormattedLine.="<span class='Comment'>";

            $i=0;
            $n=0;
            $nCol=0;
            for ($i=0;$i<strlen($thisLine);$i++) {
                  if (($nCol > $MAXIMUM_CHARS_PER_LINE)) {
                    if (($in_string_block || $in_char_block) && $ignoreMaxCharsForStrings) {
                        //we are in string block and ignoring condition because of ignoreMaxCharsForStrings flag
                    }
                    else {
                        //break line if maximum characters reached
                        $currFormattedLine.='<br/>';
                        $nCol = 0;
                    }
                }
                //checks each character in line and transform every character accordingly
                switch ($thisLine[$i]) {
                case ' ':
                    $currFormattedLine.="&nbsp;";        //converts each <space> with &nbsp;
                    $nCol++;                //next column
                    break;
                case '<':
                    $currFormattedLine.="&lt;";        //converts < to &lt;
                    $nCol++;            //next column
                    break;
                case '>':
                    $currFormattedLine.= "&gt;";    //converts > to &gt;
                    $nCol++;            //next column
                    break;
                case '&':
                    $currFormattedLine.= "&amp;";    //converts & to &amp;
                    $nCol++;            //next column
                    break;
                case '\t':
                    $n = 4;        //converts \t to 4 &nbsp;
                    $nCol += $n;            //4 columns added
                    for (; $n > 0; $n--)
                        $currFormattedLine.="&nbsp;";
                    break;
                case '\\':
                    if (($i > 0) && ($thisLine[$i - 1] == '\\'))
                        $thisLine[$i] = " ";
                    $currFormattedLine.="\\";
                    $nCol++;
                    break;
                case '/':
                /*this is complex case. we have mulitple conditions.
                    1. /*
                    2. //
                    3. "something/with/slash/in/quotes"
                    4. '/'
                */

                    if (!$in_comment_block && !$in_string_block && !$in_single_line_comment && !$in_char_block){
                        //if none of above condition is not true then check next character, if it is "/" then it is single line comment
                        if ($thisLine[$i+1]=='/'){
                            $in_single_line_comment=true;
                            $currFormattedLine.="<span class='Comment'>";
                        }
                        //if next character is "*" then it is multi-line comment
                        else if($thisLine[$i+1]=='*'){
                            $currFormattedLine.="<span class='Comment'>";
                            $in_comment_block=true;
                        }
                    }
                    else if($in_comment_block){
                        //if it was in comment block i.e, /* then ignore everything until we found *
                        if (($i>0) && ($thisLine[$i-1]=='*')){
                            //close comment block because we are in / switch case
                            $currFormattedLine.="/</span>";
                            $nCol++;
                            $in_comment_block=false;


                            break;
                        }
                    }

                    //add / to output
                    $currFormattedLine.="/";

                    //next column
                    $nCol++;


                    break;

                case '\'':
                    if (!$in_string_block && !$in_comment_block && !$in_single_line_comment){
                        //if above flags are not set then check to see if previous character was \ if yes then simply add single quote to output
                        //example:        'test comment \' and this '
                        //in above example \' has to be inside quotes and should not break highlighting
                        if (($i>0)&&($thisLine[$i-1]=='\\')){
                            $currFormattedLine.="&#39;";
                        }
                        else{
                            //reverse it, because it means end the quote
                            $in_char_block = !$in_char_block;

                            //if now character block has started add "span" for string
                            if ($in_char_block){
                                $currFormattedLine.="<span class='String'>&#39;";    //notice &#39; that means add ' inside span
                            }
                            else{    //otherwise end span, notice &#39; just before </span>
                                $currFormattedLine.="&#39;</span>";

                            }
                        }
                    }
                    else{
                        //if it's in string block " or comment block /* or single line comment // then simply add single quote
                        $currFormattedLine.="&#39;";
                    }
                    $nCol++;    //next column
                    break;
                case "\"":
                    if (!$in_char_block && !$in_comment_block && !$in_single_line_comment){
                        //if its not in character block ' not in comment block /* or not in single line comment //
                        //then do the same thing as above, check the previous character.
                        //example, "test\"this"
                        //in above example, it will print "test\"this" as is
                        if (($i>0)&&($thisLine[$i-1]=='\\')){
                            $currFormattedLine.="&quot;";
                        }
                        else {
                            //reverse the flag
                            $in_string_block = !$in_string_block;
                            if ($in_string_block){
                                //if after reverse, its in its in string block, then add <span>
                                $currFormattedLine.="<span class='String'>&quot;";
                            }
                            else{
                                //otherwise end the span
                                $currFormattedLine.="&quot;</span>";

                            }
                        }
                    }
                    else{
                        $currFormattedLine.="&quot;";    //if its in char block or comment block or single line block then simply add quote
                    }
                    $nCol++;


                    break;
                default:
                    //for all other cases there are posibilities:
                    //next chracter is digit
                    //next chracter or letter is special class
                    //next character or letter is special keywords (C++ keyword)

                    if (!$in_char_block && !$in_comment_block && !$in_single_line_comment && !$in_string_block){
                        if ($supportBraceTrace){

                            if (in_array($thisLine[$i],$braceTraceStart)){
                                $nCol++;
                                $currFormattedLine.= $braceTracer->getStartMarkup(substr(md5($title),0,4),$currLine,$nCol,$thisLine[$i]);
                                break;
                            }
                            if (in_array($thisLine[$i],$braceTraceEnd)){
                                $nCol++;
                                $currFormattedLine.= $braceTracer->getEndMarkup($thisLine[$i]);
                                break;
                            }
                        }
                        if (StringType::isdigit($thisLine[$i])){
                            //if it's digit
                            $word_arr=array();
                            for ($j=0;StringType::isalnum($thisLine[$i+$j]) || ($thisLine[$i+$j]=='.');$j++)
                                $word_arr[$j]=$thisLine[$i+$j];
                            $i+=$j-1;
                            $nCol+=$j;
                            $wd=implode("",$word_arr);
                            $currFormattedLine.="<span class='Number'>$wd</span>";
                            break;
                        }

                        if (StringType::isalpha($thisLine[$i]) || ($thisLine[$i] == '#') || ($thisLine[$i] == '_')){
                            $word_arr=array();
                            for ($j=0; StringType::isalnum($thisLine[$i+$j]) || ($thisLine[$i+$j]=='#') || ($thisLine[$i+$j]=='_') ;$j++){
                                $word_arr[$j]=$thisLine[$i+$j];
                            }
                            $i+=$j-1;
                            $nCol+=$j;
                            $wd=implode("",$word_arr);
                            //if word is one of $keywords array
                            if (in_array($wd, $cppKeywords)){
                                $currFormattedLine.="<span class='Keyword'>".htmlentities($wd)."</span>";
                            }
                            else{
                                //if word is one of $nokiaQtClasses array
                                if (in_array($wd,$nokiaQtClasses)){
                                    if ($supportNokiaQtClasses){
                                        $currFormattedLine.="<span class='SpecialClass'><a href='".getNokiaQtClassUrl($wd)."' class='SpecialClass'>".htmlentities($wd)."</a></span>";
                                    }
                                    else{
                                        $currFormattedLine.= htmlentities("$wd");
                                    }
                                }
                                //if word is one of $gtkPlusClasses array
                                else if (in_array($wd,$gtkPlusClasses)){
                                    if ($supportGtkPlusClasses)
                                    {
                                        $currFormattedLine.="<span class='SpecialClass'><a href='".getGtkPlusClassUrl($wd)."' class='SpecialClass'>".htmlentities($wd)."</a></span>";
                                    }
                                    else
                                    {
                                        $currFormattedLine.= htmlentities("$wd");
                                    }
                                }
                                //if word is one of $wxWidgetsClasses array
                                else if (in_array($wd,$wxWidgetsClasses)){
                                    if ($supportWxWidgetsClasses){
                                        $currFormattedLine.="<span class='SpecialClass'><a href='".getWxWidgetsClassUrl($wd)."' class='SpecialClass'>".htmlentities($wd)."</a></span>";
                                    }
                                    else{

                                        $currFormattedLine.= htmlentities("$wd");
                                    }
                                }
                                else {

                                    $currFormattedLine.= htmlentities("$wd");
                                }


                            }

                            break;
                        }

                    }
                    $currFormattedLine.=htmlentities($thisLine[$i]);
                    $nCol++;
                    break;

                }
            }

            if($in_single_line_comment){
                //if single line comment and because this is end of line, so end single line comment and end flag
                $currFormattedLine.="</span>";
                $in_single_line_comment=false;
            }
            if ($this->buildFormattedLines){
                //push current formatted line ($currFormattedLine) to formattedLines array
                //but note: this is what's used later in getLines($start,$end) function.
                array_push($cppCode->formattedLines,$currFormattedLine);
            }
            if (!$showLineNumber){
                $currFormattedLine.="</a>";
            }
        $currFormattedLine.="</font>";
            $output.=$currFormattedLine;

            $currLine++;        //next line

        }
        if ($in_char_block || $in_string_block){
            //if it is in char block or string block then end this before string/char block after parsing finished
            $currFormattedLine.="</span>";
            if ($this->buildFormattedLines){
                //append ending </span> to current line in formattedLines array
                $cppCode->formattedLines[$currLines-1]=$cppCode->formattedLines[$currLines-1].$currFormattedLine;
            }
            $output.=$currFormattedLine;
        }
        if ($in_comment_block){
            //if it is in comment block end this block after parsing finished
            $currFormattedLine.="</span>";
            if ($this->buildFormattedLines){
                //append ending </span> to current line in formattedLines array
                $cppCode->formattedLines[$currLines-1]=$cppCode->formattedLines[$currLines-1].$currFormattedLine;
            }
            $output.=$currFormattedLine;
        }
        $output.="</font></td></tr></table></td></tr></table></pre>";    //final output
        $cppCode->formattedCode = $output;
        return $cppCode;
    }
    public static function changeToCppCode($HTMLcodeBlock){
        $htm = array("&quot;", "&lt;", "&gt;","&#39;","<br>");
        $cpp   = array("\"", "<", ">","'","\n");
        $cpp_code=str_replace($htm,$cpp,$HTMLcodeBlock);
        return $cpp_code;
    }
    private function getTitle($line,&$i) {
      global $titleEscapeCharacter;
      global $endCharacterForTitle;
      global $escAlternator; 
      $line = str_replace($titleEscapeCharacter.$endCharacterForTitle,$escAlternator,$line);
      $title = substr($line,0,strpos($line,$endCharacterForTitle));
      $escapeCharacterCount = 0;
      $idx = 0;
      while (strpos($title,$escAlternator,$idx) != false) {
         $escapeCharacterCount++;
         $idx+=strpos($title,$escAlternator,$idx)+1;
      }
      $title = str_replace($escAlternator,$endCharacterForTitle,$title);
      $i += $escapeCharacterCount;
      return $title;
    }
    /*
     * this is used when [cpp_code] or [cpp_code_no_line] block needs to be highlighted
     */
    public function findCppCodeInCppBlock($cppCodeBlock){
        global $startCodeBlockInHtml;
        global $startCodeBlockWithNoLineInHtml;
        global $endCodeBlockInHtml;

        global $startCharacterForTitle;
        global $endCharacterForTitle;
        global $startCodeBlockInHtmlWithTitle;
        global $startCodeBlockWithNoLineInHtmlWithTitle;

        $title="";
        $lines=explode('\n',$cppCodeBlock);

        $cppCode=null;
        $codes=array();
        $thisCode="";
        $insideCode=false;
        $codeNumber=0;
        $htmlWithCppCode="";
        $thisColorCode="";
        foreach ($lines as &$thisLine){
            for ($i=0;$i<strlen($thisLine);$i++){
                if ($thisLine[$i]==substr($startCodeBlockInHtml,0,1)){
                   //NOTE: order of these if statements are very important since $startCodeBlockInHtmlWithTitle 
                   //and $startCodeBlockWithNoLineInHtmlWithTitle have same starting string as those with no title
                    if ((substr($thisLine,$i,strlen($startCodeBlockInHtmlWithTitle)))==$startCodeBlockInHtmlWithTitle){
                        $insideCode=true;
                        $codeNumber++;
                        $i+=strlen($startCodeBlockInHtmlWithTitle);
                        $titleStartIndex=$i;
                        $lineToFindTitleIn = substr($thisLine,$i,strlen($thisLine));
                        $title = $this->getTitle($lineToFindTitleIn,$i);
                        $i += strlen($title) + strlen($endCharacterForTitle);
                    }
                    elseif  ((substr($thisLine,$i,strlen($startCodeBlockWithNoLineInHtmlWithTitle)))==$startCodeBlockWithNoLineInHtmlWithTitle){
                        $insideCode=true;
                        $codeNumber++;
                        $this->showLineNumber=false;
                        $i+=strlen($startCodeBlockWithNoLineInHtmlWithTitle);
                        $lineToFindTitleIn = substr($thisLine,$i,strlen($thisLine));
                        $title = $this->getTitle($lineToFindTitleIn,$i);
                        $i += strlen($title) + strlen($endCharacterForTitle);
                    }
                    elseif ((substr($thisLine,$i,strlen($startCodeBlockInHtml)))==$startCodeBlockInHtml){
                        $insideCode=true;
                        $codeNumber++;
                        $i+=strlen($startCodeBlockInHtml);
                    }
                    elseif ((substr($thisLine,$i,strlen($startCodeBlockWithNoLineInHtml)))==$startCodeBlockWithNoLineInHtml){
                        $insideCode=true;
                        $codeNumber++;
                        $this->showLineNumber=false;
                        $i+=strlen($startCodeBlockWithNoLineInHtml);
                    }
                    elseif ((substr($thisLine,$i,strlen($endCodeBlockInHtml)))==$endCodeBlockInHtml){
                        $insideCode=false;
                        array_push($codes,$thisCode);
                        $i+=strlen($endCodeBlockInHtml);
                    }
                }

                if ($insideCode){
                    $thisCode .=$thisLine[$i];
                    $thisColorCode='[cpp_code_area_reserved]';
                }
                else{
                    if ($thisCode !=""){
                        $thisCode =$this->changeToCppCode($thisCode);
                        $cppCode=$this->highlightCode($thisCode,$title);
                        $this->showLineNumber=true;
                    }
                    $thisCode="";
                    $thisColorCode="";
                }

            }
        }
        return $cppCode;
    }
    /*
     * this is used when there are multiple [cpp_code] or [cpp_code_no_line] blocks in HTML code.
     * This will keep HTML coding as well as formatted C++ code and return HTML markup for everything
     */
    public function findCppCodeInHtmlBlock($htmlBlock){
        global $startCodeBlockInHtml;
        global $startCodeBlockWithNoLineInHtml;
        global $endCodeBlockInHtml;
        global $startLineHighlighter;
        global $endLineHighlighter;
        global $startGetFormattedCodeFromExistingCode;
        global $endGetFormattedCodeFromExistingCode;
        $title="";
        $lines=explode('\n',$htmlBlock);
        $thisCode="";
        $insideCode=false;
        $codeNumber=0;
        $htmlWithCppCode="";
        $thisColorCode="";
        $cppCode=null;
        $lineHighlighter=false;
        $lineHighlighterCodeIndex="";
        $lineHighlighterLineNumber="";
        $lineHighlighterEndLineNumber="";
        $thisLineHighlighter=null;
        $colonFoundInLineHighlighter=false;
        $commaFoundInLineHighlighter=false;
        $stopBuildingLineHighlighterStartingLine=false;
        $existingCodeBlock=false;
        $existingCodeBlockCodeIndex="";
        $existingCodeBlockStartLineNumber="";
        $existingCodeBlockLineCount="";
        $thisexistingCodeBlock=null;
        $colonFoundInexistingCodeBlock=false;
        $commaFoundInexistingCodeBlock=false;
        $stopBuildingCodeBlockStartingLine=false;

        foreach ($lines as &$thisLine){
            for ($i=0;$i<strlen($thisLine);$i++){

                if ((substr($thisLine,$i,strlen($startCodeBlockInHtml)))==$startCodeBlockInHtml){
                    $insideCode=true;
                }
                elseif ((substr($thisLine,$i,strlen($startCodeBlockWithNoLineInHtml)))==$startCodeBlockWithNoLineInHtml){
                    $insideCode=true;
                }
                elseif ((substr($thisLine,$i,strlen($endCodeBlockInHtml)))==$endCodeBlockInHtml) {
                    $insideCode=false;
                }
                elseif (!$insideCode && ((substr($thisLine,$i,strlen($startLineHighlighter)))==$startLineHighlighter)) {
                    $lineHighlighter=true;
                    $i+=strlen($startLineHighlighter);
                }
                elseif (!$insideCode && $lineHighlighter && ((substr($thisLine,$i,strlen($endLineHighlighter)))==$endLineHighlighter)) {
                    if ($thisLineHighlighter==null){
                        $lineHighlighterCodeIndex = intval($lineHighlighterCodeIndex);
                        $lineHighlighterLineNumber = intval($lineHighlighterLineNumber);
                        $lineHighlighterEndLineNumber  =intval($lineHighlighterEndLineNumber);
                        $thisLineHighlighter = $this->getCppCodesInHtmlBlock($lineHighlighterCodeIndex)->getLineHighlighter($lineHighlighterLineNumber,$lineHighlighterEndLineNumber);
                        $htmlWithCppCode.=$thisLineHighlighter;
                    }
                    $lineHighlighter=false;
                    $lineHighlighterCodeIndex="";
                    $lineHighlighterLineNumber="";
                    $lineHighlighterEndLineNumber="";
                    $thisLineHighlighter=null;
                    $colonFoundInLineHighlighter=false;
                    $commaFoundInLineHighlighter=false;
                    $stopBuildingLineHighlighterStartingLine=false;
                    $i+=strlen($endLineHighlighter);
                }
                elseif (!$insideCode && ((substr($thisLine,$i,strlen($startGetFormattedCodeFromExistingCode)))==$startGetFormattedCodeFromExistingCode)) {
                    $existingCodeBlock=true;
                    $i+=strlen($startGetFormattedCodeFromExistingCode);
                }
                elseif (!$insideCode && $existingCodeBlock && ((substr($thisLine,$i,strlen($endGetFormattedCodeFromExistingCode)))==$endGetFormattedCodeFromExistingCode)) {
                    if ($thisexistingCodeBlock==null){
                        $existingCodeBlockCodeIndex = intval($existingCodeBlockCodeIndex);
                        $existingCodeBlockStartLineNumber = intval($existingCodeBlockStartLineNumber);
                        $existingCodeBlockLineCount = intval($existingCodeBlockLineCount);
                        $thisexistingCodeBlock = $this->getCppCodesInHtmlBlock($existingCodeBlockCodeIndex)->getFormattedLines($existingCodeBlockStartLineNumber,$existingCodeBlockLineCount);
                        $htmlWithCppCode.=$thisexistingCodeBlock;
                    }
                    $existingCodeBlock=false;
                    $existingCodeBlockCodeIndex="";
                    $existingCodeBlockStartLineNumber="";
                    $existingCodeBlockLineCount="";
                    $thisexistingCodeBlock=null;
                    $colonFoundInexistingCodeBlock=false;
                    $commaFoundInexistingCodeBlock=false;
                    $stopBuildingCodeBlockStartingLine=false;
                    $i+=strlen($endGetFormattedCodeFromExistingCode);
                }
                if ($insideCode){
                    $thisCode .= $thisLine[$i];
                }
                else{
                    if ($thisCode !=""){
                        $thisCode.=$endCodeBlockInHtml;
                        $cppCode=$this->findCppCodeInCppBlock($thisCode);
                        $i+=strlen($endCodeBlockInHtml);
                        if (!isset($this->cppCodesInHtmlBlock)){
                            $this->cppCodesInHtmlBlock=array();
                        }
                        array_push($this->cppCodesInHtmlBlock,$cppCode);
                        $htmlWithCppCode.=$cppCode->formattedCode;
                        $this->showLineNumber=true;//reset for next iter
                        $thisCode="";
                        $title="";
                        $cppCode=null;
                    }
                    if ($lineHighlighter){
                        if ($thisLine[$i] == ":"){
                            $colonFoundInLineHighlighter=true;
                            $i++;//add because colon is_numeric() ==false
                        }
                        else{
                            if ($colonFoundInLineHighlighter!= true)
                                $colonFoundInLineHighlighter=false;
                        }
                        if ($thisLine[$i] == ","){
                            $commaFoundInLineHighlighter=true;
                            $i++;//add because comma is_numeric() ==false

                            $colonFoundInLineHighlighter=false;
                        }
                        else{
                            if ($commaFoundInLineHighlighter!= true)
                                $commaFoundInLineHighlighter=false;
                        }

                        if ((!$colonFoundInLineHighlighter)&& (!$commaFoundInLineHighlighter)){
                            $lineHighlighterCodeIndex.= is_numeric($thisLine[$i])?$thisLine[$i]:0;

                        }
                        else if (($colonFoundInLineHighlighter) && (!$commaFoundInLineHighlighter)){
                            $lineHighlighterLineNumber.=is_numeric($thisLine[$i])?$thisLine[$i]:0;
                        }
                        if ($commaFoundInLineHighlighter){
                            $lineHighlighterEndLineNumber.=is_numeric($thisLine[$i])?$thisLine[$i]:0;
                        }
                    }
                    elseif ($existingCodeBlock){
                        if ($thisLine[$i] == ":"){
                            $colonFoundInexistingCodeBlock=true;
                            $i++;//add because colon is_numeric() ==false
                        }
                        else{
                            if ($colonFoundInexistingCodeBlock!= true)
                                $colonFoundInexistingCodeBlock=false;
                        }
                        if ($thisLine[$i] == ","){
                            $commaFoundInexistingCodeBlock=true;
                            $i++;//add because comma is_numeric() ==false
                            $colonFoundInexistingCodeBlock=false;
                        }
                        else{
                            if ($commaFoundInexistingCodeBlock!= true)
                                $commaFoundInexistingCodeBlock=false;
                        }
                        if ((!$colonFoundInexistingCodeBlock) && (!$commaFoundInexistingCodeBlock)){
                            $existingCodeBlockCodeIndex.= is_numeric($thisLine[$i])?$thisLine[$i]:0;
                        }
                        else if (($colonFoundInexistingCodeBlock) && (!$commaFoundInexistingCodeBlock)){

                            $existingCodeBlockStartLineNumber.=is_numeric($thisLine[$i])?$thisLine[$i]:0;
                        }
                        if ($commaFoundInexistingCodeBlock){

                            $existingCodeBlockLineCount.=is_numeric($thisLine[$i])?$thisLine[$i]:0;
                        }
                    }
                    else{

                        $htmlWithCppCode.=$thisLine[$i];
                    }
                }

            }
        }
        return $htmlWithCppCode;
    }
}

?>

