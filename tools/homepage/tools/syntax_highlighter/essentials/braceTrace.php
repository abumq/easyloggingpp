<?php

class BraceTrace{
    
    protected $braceTraceStack =array();
    function __construct() {
        $this->braceTraceStack=array();
    }
    public function getStartMarkup($title,$lineNumber,$colNumber,$brace){
        if (isset($this->braceTraceStack))
            array_push($this->braceTraceStack,"brace$title-$lineNumber-$colNumber");

        return "<span id='brace$title-$lineNumber-$colNumber' onmouseover='javascript:highlightBrace(\"brace$title-$lineNumber-$colNumber-end\");highlightBrace(\"brace$title-$lineNumber-$colNumber\")' onmouseout='javascript:normalizeBrace(\"brace$title-$lineNumber-$colNumber\");normalizeBrace(\"brace$title-$lineNumber-$colNumber-end\")'>$brace</span>";
    }
    public function getEndMarkup($brace){
        $associatedStartBraceId = "";
        if (isset($this->braceTraceStack))
            $associatedStartBraceId = array_pop($this->braceTraceStack);
        return "<span id='".$associatedStartBraceId."-end' onmouseover='javascript:highlightBrace(\"" . $associatedStartBraceId . "-end\");highlightBrace(\"$associatedStartBraceId\")' onmouseout='javascript:normalizeBrace(\"$associatedStartBraceId\");normalizeBrace(\"".$associatedStartBraceId."-end\")'>$brace</span>";
    }
}
?>
