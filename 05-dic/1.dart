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
      i += 2;
      print('op3, input: ');
      int inp = int.parse(stdin.readLineSync());
      l2[l2[i+1]] = inp;
    } else if(op == 4) {
      print('op4: ${l2[l2[i+1]]}');
      i += 2;
    } else if(op == 99) 
      break;
  }
}