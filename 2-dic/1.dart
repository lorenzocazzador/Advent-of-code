import 'dart:io';

main() {
  String line = stdin.readLineSync();
  List<String> l = line.split(',');
  List<int> n = l.map(int.parse).toList();

  n[1] = 12;
  n[2] = 2;
  int i=0;
  while(i<n.length) {
    if(n[i] == 1) {
      n[n[i+3]] = n[n[i+1]] + n[n[i+2]];
      i += 4;
    } else if(n[i] == 2) {
      n[n[i+3]] = n[n[i+1]] * n[n[i+2]];
      i += 4;
    } else if(n[i] == 99) {
      break;
    } else {
      print('ERROR');
      break;
    }
  }

  print('${n[0]}');
}