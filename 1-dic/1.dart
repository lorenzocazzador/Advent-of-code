import 'dart:io';

main() {
  int res = 0;
  while(true) {
    String s = stdin.readLineSync();

    if(s == '')
      break;

    res += int.parse(s) ~/ 3 - 2;  
  }

  print('res --> $res');
}