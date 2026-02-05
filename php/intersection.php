<?php
/*
Write a function that returns the intersection of two lists:
List intersection(List A, List B)

Example: A = [1, 3, 5, 5, 7, 9]   B = [2, 3, 3, 5, 9]
intersection(A,B) -> [3,5,9]

hash tables would improve the below or a built-in PHP function :)
*/

$a = Array(1,3,5,5,7,9);
$b = Array(2,3,3,5,9);

function intersection($a, $b)
{
  $sizeofA = count($a);
  $sizeofB = count($b);
  $c = Array();
  for($i=0;$i<$sizeofA;$i++)
  {
    for($j=0;$j<$sizeofB;$j++)
    {
      if ($a[$i] == $b[$j])
      {
        if (!in_array($b[$j], $c))
        {
          array_push($c, $b[$j]);
          echo "a[${i}] = ".$a[$i]." b[${j}]=".$b[$j]."\n";
        }
      }
    }
  }
}

echo intersection($a,$b);
