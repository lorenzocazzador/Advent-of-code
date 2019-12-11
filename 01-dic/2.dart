import 'dart:io';

main() {
  int res = 0;
  while(true) {
    String s = stdin.readLineSync();

    if(s == '')
      break;

    int n = int.parse(s);
    while(n > 0) {
      n = n ~/ 3 - 2;
      if(n > 0)
        res += n;  
    }
  }

  print('res --> $res');
}