<?php
    include_once "../../format.php";
    global $webAddr;
    $currentVersion = "v 7.41";
    $releaseDate = "25-03-2013 1844hrs";
?>

<script language='javascript'>
	document.title='EasyLogging++ - C++ Tools';
</script>

<meta name='title' content='EasyLogging++ - C++ Tools' />
<meta name='description' content='Cross platform logging made easy for C/C++ applications.' />

<?php

print '
<link rel="image_src" type="image/jpeg" href="'.$webAddr.'/images/tools.png" />

<table width="100%">
    <tr><td>
        <h1><font color=green>EasyLogging++ <sup><font size=3>'. $currentVersion. '</font></sup></font></h1>
        <font color=green>
            <b>Cross platform logging made easy for C++ applications.</b>
            <br/>
            <br/>
            Current version <u>'.$currentVersion.'</u> (' . $releaseDate . ')
        </font>
        </td>
        <td valign="top" align="right">
            <a href="https://github.com/mkhan3189/EasyLoggingPP/"> <img style="border: 0;" src="https://s3.amazonaws.com/github/ribbons/forkme_right_green_007200.png" alt="Fork me on GitHub"></a>
        </td>
    </tr>
</table>


<img src="'. $webAddr .'/images/github.jpg" />
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="https://github.com/mkhan3189/EasyLoggingPP/">Github</a> 

<br/>

<img src="'. $webAddr .'/images/documentation.jpg" />
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md">Help / Notes</a> 

<br/>

<img src="'. $webAddr .'/images/documentation.jpg" />
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="https://github.com/mkhan3189/EasyLoggingPP/blob/master/CHANGE_LOG.md">Change Log / Version History</a>

<br/>

<img src="'. $webAddr .'/images/accordion/download.png" />
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="http://icplusplus.com/tools/easylogging/easyloggingpp.zip">Download Latest Version</a>

<br/>
<br/>
<br/>
<div id="licence"  width="50%">
    <b>Licence</b>
    <br/>
    <pre>
    Copyright (c) 2012-2013 Majid Khan                                       
                                                                         
This software is provided \'as-is\', without any express or implied        
warranty. In no event will the authors be held liable for any damages    
arising from the use of this software.                                   
                                                                         
Permission is granted to anyone to use this software for any purpose,    
including commercial applications, and to alter it and redistribute      
it freely, subject to the following restrictions:                        
                                                                         
1. The origin of this software must not be misrepresented; you must      
   not claim that you wrote the original software. If you use this       
   software in a product, an acknowledgment in the product documentation 
   would be appreciated but is not required.                             
                                                                         
2. Altered source versions must be plainly marked as such, and must      
   not be misrepresented as being the original software.                 
                                                                         
3. This notice may not be removed or altered from any source             
   distribution                                                          
    </pre>
</div><br/>

';
include_once "../../foot.php";
?>
