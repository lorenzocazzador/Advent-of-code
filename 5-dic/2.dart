import 'dart:io';

main() {
  List<String> l = stdin.readLineSync().split(',');
  List<int> l2 = l.map(int.parse).toList();

  int i = 0;
  while(i < l2.length) {
    int op = l2[i] % 100, p1 = l2[i] ~/ 100 % 10, p2 = l2[i] ~/ 1000 % 10, p3 = l2[i] ~/ 10000;
    //print('${l2[i]} --> $op -> $p1 $p2 $p3') ;
    
    if(op == 1) {
      int v1 = p1==1 ? l2[i+1] : l2[l2[i+1]],
          v2 = p2==1 ? l2[i+2] : l2[l2[i+2]],
          v3 = l2[i+3];

      l2[v3] = v1 + v2;
      i+=4;
    } else if(op == 2) {
      int v1 = p1==1 ? l2[i+1] : l2[l2[i+1]],
          v2 = p2==1 ? l2[i+2] : l2[l2[i+2]],
          v3 = l2[i+3];

      l2[v3] = v1 * v2;
      i+=4;
    } else if(op == 3) {
      print('op3, input: ');
      int inp = int.parse(stdin.readLineSync());
      print('letto');
      l2[l2[i+1]] = inp;
      i += 2;
    } else if(op == 4) {
      int v1 = p1==1 ? l2[i+1] : l2[l2[i+1]];
      print('op4: i --> $i l2[i] -> ${l2[i]}');
      print('op4: $v1');
      i += 2;
    } else if(op == 5) {
      int v1 = p1==1 ? l2[i+1] : l2[l2[i+1]],
          v2 = p2==1 ? l2[i+2] : l2[l2[i+2]];
      if(v1 != 0)
        i = v2;
      else i += 3;
    } else if(op == 6) {
      int v1 = p1==1 ? l2[i+1] : l2[l2[i+1]],
          v2 = p2==1 ? l2[i+2] : l2[l2[i+2]];
      if(v1 == 0)
        i = v2;
      else i += 3;
    } else if(op == 7) {
      int v1 = p1==1 ? l2[i+1] : l2[l2[i+1]],
          v2 = p2==1 ? l2[i+2] : l2[l2[i+2]],
          v3 = l2[i+3];

      if(v1 < v2)
        l2[v3] = 1;
      else 
        l2[v3] = 0;   

      i += 4;   
    } else if(op == 8) {
      int v1 = p1==1 ? l2[i+1] : l2[l2[i+1]],
          v2 = p2==1 ? l2[i+2] : l2[l2[i+2]],
          v3 = l2[i+3];

      if(v1 == v2)
        l2[v3] = 1;
      else
        l2[v3] = 0;

      i += 4;
    } else if(op == 99) 
      break;
  }
}