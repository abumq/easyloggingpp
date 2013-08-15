<?php
class StringType{
    public static function isdigit($str)
    {
        if (($str=="0") || ($str=="1") || ($str=="2") || ($str=="3") || ($str=="4") || ($str=="5") || ($str=="6") || ($str=="7") || ($str=="8") || ($str=="9"))
            return true;
        else
            return false;
    }
    public static function isalnum($str)
    {
        if (($str=="0") || ($str=="1") || ($str=="2") || ($str=="3") || ($str=="4") || ($str=="5") || ($str=="6") || ($str=="7") || ($str=="8") || ($str=="9") || ($str=="a") || ($str=="b") || ($str=="c") || ($str=="d") || ($str=="e") || ($str=="f") || ($str=="g") || ($str=="h") || ($str=="i") || ($str=="j") || ($str=="k") || ($str=="l") || ($str=="m") || ($str=="n") || ($str=="o") || ($str=="p") || ($str=="q") || ($str=="r") || ($str=="s") || ($str=="t") || ($str=="u") || ($str=="v") || ($str=="w") || ($str=="x") || ($str=="y") || ($str=="z") || ($str=="A") || ($str=="B") || ($str=="C") || ($str=="D") || ($str=="E") || ($str=="F") || ($str=="G") || ($str=="H") || ($str=="I") || ($str=="J") || ($str=="K") || ($str=="L") || ($str=="M") || ($str=="N") || ($str=="O") || ($str=="P") || ($str=="Q") || ($str=="R") || ($str=="S") || ($str=="T") || ($str=="U") || ($str=="V") || ($str=="W") || ($str=="X") || ($str=="Y") || ($str=="Z"))
            return true;
        else
            return false;
    }
    public static function isalpha($str)
    {
        
    if (($str=="a") || ($str=="b") || ($str=="c") || ($str=="d") || ($str=="e") || ($str=="f") || ($str=="g") || ($str=="h") || ($str=="i") || ($str=="j") || ($str=="k") || ($str=="l") || ($str=="m") || ($str=="n") || ($str=="o") || ($str=="p") || ($str=="q") || ($str=="r") || ($str=="s") || ($str=="t") || ($str=="u") || ($str=="v") || ($str=="w") || ($str=="x") || ($str=="y") || ($str=="z") || ($str=="A") || ($str=="B") || ($str=="C") || ($str=="D") || ($str=="E") || ($str=="F") || ($str=="G") || ($str=="H") || ($str=="I") || ($str=="J") || ($str=="K") || ($str=="L") || ($str=="M") || ($str=="N") || ($str=="O") || ($str=="P") || ($str=="Q") || ($str=="R") || ($str=="S") || ($str=="T") || ($str=="U") || ($str=="V") || ($str=="W") || ($str=="X") || ($str=="Y") || ($str=="Z"))
            return true;
        else
            return false;
    }
}
?>
