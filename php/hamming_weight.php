<?php
  /* Hamming Weight example */
  
  $x = 255; /* binary 11111111 */
  $hamWeight = 0;
  echo decbin($x)."\n";

  while($x > 0)
  {
    if ($x % 2) ++$hamWeight; // look for a remainder with modulus, if 1 we have one (1 literally)! :)
    $x >>= 1;
    echo "x=".decbin($x)."\n";
  }
  echo "weight: {$hamWeight}\n";

?>