<?php
    include_once "../../format.php";
    require_once "syntax_highlighter/cppToHtmlSyntaxHighlighter.php";
    global $webAddr;
    $currentVersion = "v 8.91";
    $releaseDate = "12-07-2013 1243hrs";
?>

<script language='javascript'>
	document.title='EasyLogging++ - C++ Tools';
</script>

<meta name='title' content='EasyLogging++ - C++ Tools' />
<meta name='description' content='Cross platform logging made easy for C/C++ applications.' />
<meta name='keywords' content='C++ logging, c++ light fast logging, Thread-safe C++ logger, generic C++ logging, easy to use C++ logger, STL logging, Qt logging, qlog, elpp, easylogging c++, best C++ logger, best c++ logging library' />
<meta charset="UTF-8">

<?php

$highlighter = new Highlighter();

print '
<link rel="image_src" type="image/jpeg" href="'.$webAddr.'/images/tools.png" />

<table width="100%">
    <tr><td>
        <h1><font color=green>EasyLogging++ <sup><font size=3>'. $currentVersion. '</font></sup></font></h1>
<!--
	<div style="
	    float: right;
	    position: absolute;
	    right: 30%;
	">
        <table><tr><td>
	<img src="'.$webAddr.'/images/tick.png">&nbsp;&nbsp;<span style="position: relative; top: -10px; font-size: 1.4em; color: green;">Cross platform</span></td><td>
	<img src="'.$webAddr.'/images/tick.png">&nbsp;&nbsp;<span style="position: relative; top: -10px; font-size: 1.4em; color: green;">Thread-safe</span></td></tr><tr><td>
	<img src="'.$webAddr.'/images/tick.png">&nbsp;&nbsp;<span style="position: relative; top: -10px; font-size: 1.4em; color: green;">Type-safe</span></td><td>
	<img src="'.$webAddr.'/images/tick.png">&nbsp;&nbsp;<span style="position: relative; top: -10px; font-size: 1.4em; color: green;">Highly configurable</span></td></tr><tr><td>
	<img src="'.$webAddr.'/images/tick.png">&nbsp;&nbsp;<span style="position: relative; top: -10px; font-size: 1.4em; color: green;">High performance</span></td><td>
	<img src="'.$webAddr.'/images/tick.png">&nbsp;&nbsp;<span style="position: relative; top: -10px; font-size: 1.4em; color: green;">STL Logging</span></td></tr><tr><td>
	<img src="'.$webAddr.'/images/tick.png">&nbsp;&nbsp;<span style="position: relative; top: -10px; font-size: 1.4em; color: green;">Easy to setup</span></td></tr></table>
</div>
-->

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
</td></tr><tr>
<td width="100%" valign="top">
<br/><br/><p>
Hopefully, by now you have some great reasons to use EasyLogging++, if you are still confused whether or not you should use EasyLogging++, check out read me, and I am sure you will be convinced.<br/>
<br/>
To start using EasyLogging++, <a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="http://icplusplus.com/tools/easylogging/easyloggingpp.zip">download the latest version</a>, configure it directly, initialize it in your application and you are good to go.<br/>
';
$codeBlock="[cpp_code_no_line]#include \"easylogging++.h\"

_INITIALIZE_EASYLOGGINGPP

int main(int argv, const char** argc) {
    LINFO << \"my trivial info log\";
    LOG(INFO) << \"My other (alternate) way of writing trivial log\";
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
<pre style="border: 1px lightgrey solid;width:50">
04/04/2013 20:40:19.671 INFO  my trivial info log
04/04/2013 20:40:19.671 INFO  My other (alternate) way of writing trivial log
04/04/2013 20:40:19.671 INFO  [business] my business info log
04/04/2013 20:40:19.671 INFO  [security] my security info log
04/04/2013 20:40:19.671 INFO  [performance] my performance info log
04/04/2013 20:40:58.671 DEBUG [performance] [mak@high-perf-pc] [int main(int, const char**)] [./homepage.cpp:10] debug performance log
</pre>
This is very basic form of logging using EasyLogging++, there is a lot more to it. Jump to <a style="text-decoration: none; color: green; " onmousemove="this.style.color=\'lightgreen\';" onmouseout="this.style.color=\'green\';" href="https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md"><b>read me</b></a> to check out true potential of EasyLogging++.
</p>
</td></tr><tr>
<td><br/><p>
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
    </pre></p>
</td>
</tr>
<tr><td>
<font color="white">
easylogging, logging c++, logger c++, easy, logger, c++ logging library, fast logging library, thread safe logging, thread-safe logger c++, fastest c++ logging, recommended logging c++, light logging c++, light logger c++, Highly configurable logger c++, STL logging, Qt logging, hierarchical logging c++, c++ performance logger, type safe logger c++, 
</font>
</td></tr></table>

';
include_once "../../foot.php";
?>

