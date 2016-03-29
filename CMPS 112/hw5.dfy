//Ryan Coley
//hw5.dfy


// 1
method Min(a: int, b: int) returns (c: int)
   //make sure the return value is one of the values given
   ensures c == a || c == b;
   ensures c <= a && c <= b;
{
   if a > b {
      return b;
   }else {
      return a;
   }

   return c;
}

method TestMin()
{
   var m := Min(12,5);
   assert m == 5;
   var n := Min(23,42);
   assert n == 23;
}

// 2
method Search(arr: array<int>, element: int) returns (idx: int)
   requires arr != null //make sure the array isnt null
   //if the index >= 0 then make sure that the value at the index is the same as the one searched for
   ensures 0 <= idx ==> idx < arr.Length && arr[idx] == element
   //if the index is less than 0 make sure that no values in the array match the element
   ensures 0 > idx ==> (forall i :: 0 <= i < arr.Length ==> arr[i] != element) && idx == -1
{

   var n := 0;
   while (n < arr.Length)
      //bound n
      invariant 0 <= n <= arr.Length
      //make sure that all values up to n don't match the element
      invariant forall i :: 0 <= i < n ==> arr[i] != element
      //define that the loop closes
      decreases arr.Length - n
   {
      if (arr[n] == element) {
         return n;
      }
      n := n + 1;
   }

   return -1;
}

method TestSearch()
{
   var arr := new int[3];
   arr[0] := 23;
   arr[1] := 21;
   arr[2] := 22;
   var s := Search(arr, 21);
   assert s == 1;
   var t := Search(arr, 20);
   assert t == -1;
}

// 3 EXTRA CREDIT
method Search(arr: array<int>, element: int) returns (idx: int)
  //make sure that the array is valid
  requires arr != null && arr.Length >= 0;
  //make sure that the index is within the array and equal to the element
  ensures 0 <= idx ==> idx < arr.Length && arr[idx] == element
  //if the index is less than 0 make sure that no values in the array match the element
  ensures 0 > idx ==> (forall i :: 0 <= i < arr.Length ==> arr[i] != element) && idx == -1
{
  var n := 0;
  while (n < arr.Length)
   //make sure n is between 0 and the array length
   invariant 0 <= n <= arr.Length
   //make sure that all elements upto the current aren't equal to the element
   invariant forall i :: 0 <= i < arr.Length && !(n <= i < arr.Length) ==> arr[i] != element
  {
    if (arr[n] == element) {
      return n;
    }
    n := n + 1;
  }
  return -1;
}

method TestSearch()
{
  var arr := new int[3];
  arr[0] := 23;
  arr[1] := 21;
  arr[2] := 22;
  var s := Search(arr, 21);
  assert s == 1;
  var t := Search(arr, 20);
  assert t == -1;
}
