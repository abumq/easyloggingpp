<script language='javascript'>
    buildLineId = function(stringToBuildOff,lineNumber){
    return stringToBuildOff.substring(0,stringToBuildOff.lastIndexOf('line'))+"line"+lineNumber;
    
    }
    highlightLine = function(lineId){
        if (document.getElementById(lineId) != null)
            document.getElementById(lineId).className='HighlightedLine';
        if (document.getElementById(lineId + "-c") != null)
            document.getElementById(lineId+"-c").className='HighlightedLine';
    }
    normalizeLine = function(lineId){
        if (document.getElementById(lineId) != null)
            document.getElementById(lineId).className='';
        if (document.getElementById(lineId + "-c") != null)
            document.getElementById(lineId+"-c").className='';
    }
    highlightMultipleLines = function(startLineId,endLineId){
        var startNumber = parseInt(startLineId.substring(startLineId.lastIndexOf('line')+4));
    var endNumber = parseInt(endLineId.substring(endLineId.lastIndexOf('line')+4));
    
        for (var i=startNumber;i<=endNumber;i++)
    {
        var thisLineId = buildLineId(startLineId,i);
        highlightLine(thisLineId);
    }
    
    }
    normalizeMultipleLines = function(startLineId,endLineId){
        var startNumber = parseInt(startLineId.substring(startLineId.lastIndexOf('line')+4));
    var endNumber = parseInt(endLineId.substring(endLineId.lastIndexOf('line')+4));
    
        for (var i=startNumber;i<=endNumber;i++)
    {
        var thisLineId = buildLineId(startLineId,i);
        normalizeLine(thisLineId);
    }
    }
</script>
