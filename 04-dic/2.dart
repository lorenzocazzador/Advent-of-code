import 'dart:io';

import 'dart:math';

List<int> convert(String l) {
  List<int> l2 = [];
  for(int i=0; i<l.length; i++) 
    l2.add(int.parse(l[i]));
  return l2;
}

main() {
  List<String> line = stdin.readLineSync().split('-');
  int left = int.parse(line[0]), right = int.parse(line[1]);
  List<int> l = convert(line[0]), r = convert(line[1]);

  var res = 0, pr = 0;
  //print('l --> $l\nr --> $r\n');
  for(int i=l[0]; i<=r[0]; i++)
    for(int j = i; j<=9; j++)
      for(int z = j; z<=9; z++)
        for(int y = z; y<=9; y++)
          for(int x = y; x<=9; x++)
            for(int k = x; k<=9; k++) {
              var num = i*100000 + j*10000 + z*1000 + y*100 + x*10 + k; 
              
              if(num < left || num > right) 
                continue;

              String s = num.toString();
              bool twoAdiacent = false;

              for(int i=0; i<6; i++) {
                if(i>1 && i<5 && s[i-1] == s[i] && s[i-1] != s[i-2] &&  s[i] != s[i+1])
                  twoAdiacent = true;
                else if(i == 5 && s[i] == s[i-1] && s[i-1] != s[i-2])
                  twoAdiacent = true;
                else if(i == 0 && s[i]==s[i+1] && s[i+1] != s[i+2])
                  twoAdiacent = true;
              }

              if(!twoAdiacent) {
                print('$num\n');
                continue;
              }

              res++;
            }

  print('res --> $res');
}