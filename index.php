<?php
include_once "../../format.php";
global $webAddr;
$currentVersion = "v3.06";
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
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md">Quick Help</a> 

<br/>
<img src="'. $webAddr .'/images/read.png" width=25px height=25px/>
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="http://www.icplusplus.com/articles/read.php?uid=9961861bd75a67ed1d152fd83e2962249495dce5">Article on EasyLogging++ Logging</a> 

<br/>
<img src="'. $webAddr .'/images/read.png" width=25px height=25px />
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="http://www.icplusplus.com/articles/read.php?uid=401c16bd01d12e1b18524dd051e2dd07833d3f80">Article on EasyLogging++ Time Tracking</a> 

<br/>
<img src="'. $webAddr .'/images/accordion/download.png" />
<a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="http://icplusplus.com/tools/easylogging/releases/easyloggingpp_' . $currentVersion . '.zip">Download Latest Version</a> 
';
include_once "../../foot.php";
?>
