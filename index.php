<?php
include_once "../../format.php";
global $webAddr;
$currentVersion = "v6.03";
?>
<script language='javascript'>
	document.title='EasyLogging++ - C++ Tools';
</script>
<meta name='title' content='EasyLogging++ - C++ Tools' />
<meta name='description' content='Cross platform logging made easy for C/C++ applications.' />
<?php
print '
<link rel="image_src" type="image/jpeg" href="'.$webAddr.'/images/tools.png" />
<table width="100%"><tr><td>
<h1><font color=green>EasyLogging++</font></h1><br/>
<font color=green><b>Cross platform logging made easy for C++ applications.
<br/>Current version '.$currentVersion.'</b></font>
</td><td valign="top" align="right"><a href="https://github.com/mkhan3189/EasyLoggingPP/"> <img style="border: 0;" src="https://s3.amazonaws.com/github/ribbons/forkme_right_green_007200.png" alt="Fork me on GitHub"></a></td></tr>
</table>
<div id="license"  width="50%"><b>License</b><br/><pre>This program is free software: you can redistribute it and/or modify it under terms of the GNU
 General Public License as published by the Free Software Foundation, version 3 of the License.</pre></div><br/>
<img src="'. $webAddr .'/images/github.jpg" />
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="https://github.com/mkhan3189/EasyLoggingPP/">Github</a> 

<br/>
<img src="'. $webAddr .'/images/documentation.jpg" />
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md">Help / Notes</a> 

<br/>
<img src="'. $webAddr .'/images/accordion/download.png" />
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="http://icplusplus.com/tools/easylogging/easyloggingpp.zip">Download Latest Version</a> 

';
include_once "../../foot.php";
?>
