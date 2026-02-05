<?php
  /**
   * Paul's fibonacci
   **/
  $a=1;
  $b=0;
  $c=0;
  for($f=1;$f<10;$f++)
  {
     $c = $a + $b;
     $b = $a; // prior
     $a = $c; // current
     echo "fib: ".$c."\n";
  }

  echo "\n";
?>
