import 'dart:io';

main() async {
  String l = await File('input/in').readAsString();

  int layerLength = 25*6;
  int n0 = 0, n1 = 0, n2 = 0;
  int min0, res;

  for(int i=0; i<l.length-1; i++) {
    if(l[i] == '0')
      n0++;
    else if(l[i] == '1')
      n1++;
    else if(l[i] == '2')
      n2++;


    if( (i+1) % layerLength == 0) {
      if(min0 == null || n0 < min0) {
        min0 = n0;
        res = n1*n2;
      }
      n0 = n1 = n2 = 0;
    }
  }

  print('res --> $res');
}
