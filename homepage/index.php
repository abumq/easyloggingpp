<?php
    include_once "../../format.php";
    require_once "syntax_highlighter/cppToHtmlSyntaxHighlighter.php";
    global $webAddr;
    $currentVersion = "v 7.62";
    $releaseDate = "04-04-2013 1828hrs";
?>

<script language='javascript'>
	document.title='EasyLogging++ - C++ Tools';
</script>

<meta name='title' content='EasyLogging++ - C++ Tools' />
<meta name='description' content='Cross platform logging made easy for C/C++ applications.' />

<?php

$highlighter = new Highlighter();

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

<table width="100%">
<tr><td width="50%">
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
</div>
</td>
<td width="50%" valign="top">
<div style="overflow: auto; width: 100%; max-height:510px">
<p>
Hopefully, by now you have some great reasons to use EasyLogging++, if you are still confused whether or not you should use EasyLogging++, check out read me, and I am sure you will be convinced.<br/>
<br/>
To start using EasyLogging++, <a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="http://icplusplus.com/tools/easylogging/easyloggingpp.zip">download the latest version</a>, configure it directly, initialize it in your application and you are good to go.<br/>
';
$codeBlock="[cpp_code_no_line]#include \"easylogging++.h\"

_INITIALIZE_EASYLOGGINGPP

int main(int argv, const char** argc) {
    LINFO << \"my trivial info log\";
    BINFO << \"my business info log\";
    SINFO << \"my security info log\";
    PINFO << \"my performance info log\";
    PDEBUG << \"debug performance log\";
    return 0;
}[/cpp_code]";

$basicUsage=$highlighter->findCppCodeInHtmlBlock($codeBlock);
print $basicUsage;

print '
You might be wondering, what is the output we get? Well, it completely depends on your configuration, if you haven&#39;t configured your EasyLogging++, here is what you will get with default configuration for <i>INFO</i> logs;<br/>
<pre style="border: 1px lightgrey solid;">04/04/2013 20:40:19.671 INFO  [log] my trivial info log
04/04/2013 20:40:19.671 INFO  [business] my business info log
04/04/2013 20:40:19.671 INFO  [security] my security info log
04/04/2013 20:40:19.671 INFO  [performance] my performance info log
04/04/2013 21:07:58.763 DEBUG [performance] [mak@high-perf-pc] [int main(int, const char**)] [./homepage.cpp:10] debug performance log
</pre>
<b>This is very basic form of logging using EasyLogging++, there is a lot more to it. Check out <a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md">read me</a> where most of EasyLogging++ potential is covered.</b>
</p>
</div>
</td>
</tr></table>

';
include_once "../../foot.php";
?>

