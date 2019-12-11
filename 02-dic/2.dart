import 'dart:io';

int solve(List<int> n) {
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
  return n[0];
}
main() {
  String line = stdin.readLineSync();
  List<String> l = line.split(',');
  List<int> n = l.map(int.parse).toList();

  int noun, verb, ris;
  for(noun=0; noun<=99; noun++)
    for(verb=0; verb<=99; verb++) {
      List<int> n1 = n.toList();
      n1[1] = noun;
      n1[2] = verb;
      
      if(solve(n1) == 19690720)
        ris = noun * 100 + verb;

    }
  

  print('ris --> $ris');
}